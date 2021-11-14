include_directories(include)

# sources
file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.h)

add_library(Logging ${SOURCES})

target_include_directories(Logging
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(TARGETS Logging DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)