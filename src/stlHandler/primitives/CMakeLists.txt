set(SOURCE_LIST
    Channel.hh
    Circle.hh
    Core.hh
    Cuboid.hh
    Pizza.hh
    Rectangle.hh
    Trapezoid.hh
    TrapezoidalChannel.hh
    TrapezoidalPrism.hh
)

set(HEADER_LIST
    Channel.h
    Circle.h
    Core.h
    Cuboid.h
    Pizza.h
    Rectangle.h
    Trapezoid.h
    TrapezoidalChannel.h
    TrapezoidalPrism.h
)

target_sources(${TARGET_NAME} PUBLIC ${SOURCE_LIST} ${HEADER_LIST})
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})