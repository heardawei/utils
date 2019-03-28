aux_source_directory(. LOCAL_HELLO_SRCS)

# static/dyncmic library
# add_library(hello ${LOCAL_HELLO_SRCS})
add_library(hello SHARED ${LOCAL_HELLO_SRCS})
