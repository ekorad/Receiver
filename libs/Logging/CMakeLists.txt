include_directories(include)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# sources
file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.h)

add_library(Logging ${SOURCES})

target_include_directories(Logging
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(TARGETS Logging DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)