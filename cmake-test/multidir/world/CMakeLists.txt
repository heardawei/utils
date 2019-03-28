
aux_source_directory(. LOCAL_WORLD_SRCS)

# static/dyncmic library
# add_library(world ${LOCAL_WORLD_SRCS})
add_library(world SHARED ${LOCAL_WORLD_SRCS})