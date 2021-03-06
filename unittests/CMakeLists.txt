######################
#     Test suite     #
######################

include_directories(../akumulid)
include_directories(../libakumuli)

# Small utils
add_executable(
    test_utils
    test_utils.cpp
    ../akumulid/expected.h
)
target_link_libraries(test_utils
    ${Boost_LIBRARIES}
)
add_test(utils test_utils)

# Streams
add_executable(
    test_streams
    test_stream.cpp
    ../akumulid/stream.cpp 
    ../akumulid/stream.h
)
target_link_libraries(test_streams
    ${Boost_LIBRARIES}
)
add_test(streams test_streams)

# RESP
add_executable(
    test_respstream
    test_respstream.cpp
    ../akumulid/stream.cpp 
    ../akumulid/stream.h
    ../akumulid/resp.cpp 
    ../akumulid/resp.h
)
target_link_libraries(test_respstream
    ${Boost_LIBRARIES}
)
add_test(respstream test_respstream)

# Protocol parser
add_executable(
    test_protocolparser
    test_protocolparser.cpp
    ../akumulid/protocolparser.cpp 
    ../akumulid/protocolparser.h
    ../akumulid/logger.cpp 
    ../akumulid/logger.h
    ../akumulid/stream.cpp 
    ../akumulid/stream.h
    ../akumulid/resp.cpp 
    ../akumulid/resp.h
)
target_link_libraries(
    test_protocolparser
    akumuli
    sqlite3
    ${Boost_LIBRARIES}
    "${LOG4CXX_LIBRARIES}"
    libboost_coroutine.a
    libboost_context.a
)
add_test(protocol-parser test_protocolparser)

# Pipeline test
add_executable(
    test_pipeline
    test_pipeline.cpp
    ../akumulid/ingestion_pipeline.cpp
    ../akumulid/logger.cpp
)
target_link_libraries(
    test_pipeline
    jemalloc
    akumuli
    sqlite3
    "${LOG4CXX_LIBRARIES}"
    "${APR_LIBRARY}"
    "${APRUTIL_LIBRARY}"
    ${Boost_LIBRARIES}
    libboost_coroutine.a
    libboost_context.a
)
add_test(pipeline test_pipeline)

# TCPServer test
add_executable(
    test_tcp_server
    test_tcp_server.cpp
    ../akumulid/ingestion_pipeline.cpp
    ../akumulid/tcp_server.cpp
    ../akumulid/signal_handler.cpp
    ../akumulid/resp.cpp
    ../akumulid/stream.cpp
    ../akumulid/protocolparser.cpp
    ../akumulid/logger.cpp
)
target_link_libraries(test_tcp_server
    jemalloc
    akumuli
    sqlite3
    "${LOG4CXX_LIBRARIES}"
    "${APR_LIBRARY}"
    "${APRUTIL_LIBRARY}"
    ${Boost_LIBRARIES}
    libboost_coroutine.a
    libboost_context.a
)
add_test(tcp-server test_tcp_server)

# QueryCursor

# Pipeline test
add_executable(
    test_querycursor
    test_querycursor.cpp
    ../akumulid/query_results_pooler.cpp
    ../akumulid/ingestion_pipeline.cpp
    ../akumulid/logger.cpp
)
target_link_libraries(
    test_querycursor
    akumuli
    jemalloc
    sqlite3
    "${LOG4CXX_LIBRARIES}"
    "${APR_LIBRARY}"
    "${APRUTIL_LIBRARY}"
    ${Boost_LIBRARIES}
    libboost_coroutine.a
    libboost_context.a
)
add_test(querycursor test_querycursor)


##########################################
#                                        #
#           libakumuli tests             #
#                                        #
##########################################

# Page test
add_executable(
    test_page
    test_page.cpp
    ../libakumuli/page.cpp
    ../libakumuli/buffer_cache.cpp
    ../libakumuli/cursor.cpp
    ../libakumuli/util.cpp
    ../libakumuli/compression.cpp
)

target_link_libraries(
    test_page
    "${SQLITE3_LIBRARY}"
    "${APRUTIL_LIBRARY}"
    "${APR_LIBRARY}"
    ${Boost_LIBRARIES}
    libboost_coroutine.a
    libboost_context.a
    pthread
)

add_test(page test_page)

# Sequencer tests
add_executable(
    test_sequencer
    test_sequencer.cpp
    ../libakumuli/sequencer.cpp
    ../libakumuli/cursor.cpp
    ../libakumuli/page.cpp
    ../libakumuli/buffer_cache.cpp
    ../libakumuli/util.cpp
    ../libakumuli/compression.cpp
)

target_link_libraries(
    test_sequencer
    "${SQLITE3_LIBRARY}"
    "${APRUTIL_LIBRARY}"
    "${APR_LIBRARY}"
    ${Boost_LIBRARIES}
    libboost_coroutine.a
    libboost_context.a
    pthread
)

add_test(sequencer test_sequencer)

# Cursor tests
add_executable(
    test_cursor
    test_cursor.cpp
    ../libakumuli/cursor.cpp
    ../libakumuli/page.cpp
    ../libakumuli/buffer_cache.cpp
    ../libakumuli/util.cpp
    ../libakumuli/compression.cpp
)

target_link_libraries(
    test_cursor
    "${SQLITE3_LIBRARY}"
    "${APRUTIL_LIBRARY}"
    "${APR_LIBRARY}"
    ${Boost_LIBRARIES}
    libboost_coroutine.a
    libboost_context.a
    pthread
)

add_test(cursor test_cursor)

# Mmap test
add_executable(
    test_mmap
    test_mmap.cpp
    ../libakumuli/util.cpp
)

target_link_libraries(
    test_mmap
    "${SQLITE3_LIBRARY}"
    "${APRUTIL_LIBRARY}"
    "${APR_LIBRARY}"
    ${Boost_LIBRARIES}
)

add_test(mmap test_mmap)

# Compression test
add_executable(
    test_compression
    test_compression.cpp
    ../libakumuli/compression.cpp
)

target_link_libraries(
    test_compression
    ${Boost_LIBRARIES}
)

add_test(compression test_compression)

# Storage test
add_executable(
    test_storage
    test_storage.cpp
    ../libakumuli/metadatastorage.cpp
    ../libakumuli/util.cpp
    ../libakumuli/seriesparser.cpp
    ../libakumuli/stringpool.cpp
)

target_link_libraries(
    test_storage
    akumuli
    sqlite3
    "${SQLITE3_LIBRARY}"
    "${APRUTIL_LIBRARY}"
    "${APR_LIBRARY}"
    ${Boost_LIBRARIES}
)

add_test(storage test_storage)

# Series parser tests
add_executable(
    test_seriesparser
    test_parser.cpp
    ../libakumuli/seriesparser.cpp
    ../libakumuli/stringpool.cpp
    ../libakumuli/util.cpp
    ../libakumuli/datetime.cpp
)

target_link_libraries(
    test_seriesparser
    ${Boost_LIBRARIES}
    "${APR_LIBRARY}"
)

add_test(seriesparser test_seriesparser)

# Query processor tests
add_executable(
    test_queryprocessor
    test_queryprocessor.cpp
    ../libakumuli/queryprocessor.cpp
    ../libakumuli/queryprocessor_framework.cpp
    ../libakumuli/saxencoder.cpp
    ../libakumuli/anomalydetector.cpp
    ../libakumuli/hashfnfamily.cpp
    ../libakumuli/seriesparser.cpp
    ../libakumuli/stringpool.cpp
    ../libakumuli/util.cpp
    ../libakumuli/datetime.cpp
    # query_processing folder
    ../libakumuli/query_processing/anomaly.cpp
    ../libakumuli/query_processing/sax.cpp
    ../libakumuli/query_processing/paa.cpp
    ../libakumuli/query_processing/filterbyid.cpp
    ../libakumuli/query_processing/randomsamplingnode.cpp
)

target_link_libraries(
    test_queryprocessor
    ${Boost_LIBRARIES}
    "${APR_LIBRARY}"
)

add_test(queryprocessor test_queryprocessor)

# Datetime test
add_executable(
    test_datetime
    test_datetime.cpp
    ../libakumuli/datetime.cpp
)

target_link_libraries(
    test_datetime
    ${Boost_LIBRARIES}
)

add_test(datetime test_datetime)

# Sax test
add_executable(
    test_sax
    test_sax.cpp
    ../libakumuli/saxencoder.cpp
)

target_link_libraries(
    test_sax
    ${Boost_LIBRARIES}
)

add_test(SAX test_sax)

# Inverted index test
add_executable(
    test_invertedindex
    test_invertedindex.cpp
    ../libakumuli/invertedindex.cpp
)

target_link_libraries(
    test_invertedindex
    ${Boost_LIBRARIES}
)

add_test(invertedindex test_invertedindex)
