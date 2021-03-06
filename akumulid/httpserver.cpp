#include "httpserver.h"
#include "utility.h"
#include <cstring>

#include <boost/bind.hpp>

namespace Akumuli {
namespace Http {

//! Microhttpd callback functions
namespace MHD {
static ssize_t read_callback(void *data, uint64_t pos, char *buf, size_t max) {
    AKU_UNUSED(pos);
    QueryResultsPooler* cur = (QueryResultsPooler*)data;
    auto status = cur->get_error();
    if (status) {
        return MHD_CONTENT_READER_END_OF_STREAM;
    }
    size_t sz;
    bool is_done;
    std::tie(sz, is_done) = cur->read_some(buf, max);
    if (is_done) {
        return MHD_CONTENT_READER_END_OF_STREAM;
    }
    return sz;
}

static void free_callback(void *data) {
    QueryResultsPooler* cur = (QueryResultsPooler*)data;
    cur->close();
    delete cur;
}

static int accept_connection(void           *cls,
                             MHD_Connection *connection,
                             const char     *url,
                             const char     *method,
                             const char     *version,
                             const char     *upload_data,
                             size_t         *upload_data_size,
                             void          **con_cls)
{
    if (strcmp(method, "POST") == 0) {
        QueryProcessor *queryproc = static_cast<QueryProcessor*>(cls);
        QueryResultsPooler* cursor = static_cast<QueryResultsPooler*>(*con_cls);

        if (cursor == nullptr) {
            cursor = queryproc->create();
            *con_cls = cursor;
            return MHD_YES;
        }
        if (*upload_data_size) {
            cursor->append(upload_data, *upload_data_size);
            *upload_data_size = 0;
            return MHD_YES;
        }

        auto error_response = [&](const char* msg) {
            char buffer[0x200];
            int len = snprintf(buffer, 0x200, "-%s\r\n", msg);
            auto response = MHD_create_response_from_buffer(len, buffer, MHD_RESPMEM_MUST_COPY);
            int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
            MHD_destroy_response(response);
            return ret;
        };

        // Should be called once
        try {
            cursor->start();
        } catch (const std::exception& err) {
            return error_response(err.what());
        }

        // Check for error
        auto err = cursor->get_error();
        if (err != AKU_SUCCESS) {
            const char* error_msg = aku_error_message(err);
            return error_response(error_msg);
        }

        auto response = MHD_create_response_from_callback(MHD_SIZE_UNKNOWN, 64*1024, &read_callback, cursor, &free_callback);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    } else {
        // Unsupported method
        // TODO: implement GET handler for simple queries (self diagnostics)
        return MHD_NO;
    }
}
}

HttpServer::HttpServer(unsigned short port, std::shared_ptr<QueryProcessor> qproc, AccessControlList const& acl)
    : acl_(acl)
    , proc_(qproc)
    , port_(port)
{
}

HttpServer::HttpServer(unsigned short port, std::shared_ptr<QueryProcessor> qproc)
    : HttpServer(port, qproc, AccessControlList())
{
}

void HttpServer::start(SignalHandler* sig, int id) {
    daemon_ = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION,
                               port_,
                               NULL,
                               NULL,
                               &MHD::accept_connection,
                               proc_.get(),
                               MHD_OPTION_END);
    if (daemon_ == nullptr) {
        BOOST_THROW_EXCEPTION(std::runtime_error("can't start daemon"));
    }

    auto self = shared_from_this();
    sig->add_handler(boost::bind(&HttpServer::stop, std::move(self)), id);
}

void HttpServer::stop() {
    MHD_stop_daemon(daemon_);
}

}  // namespace Http
}  // namespace Akumuli

