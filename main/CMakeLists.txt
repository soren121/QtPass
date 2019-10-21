include_directories(../src)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB TS_FILES "../localization/*.ts")
set_source_files_properties(${TS_FILES} PROPERTIES OUTPUT_LOCATION localization)
qt5_add_translation(QM_FILES ${TS_FILES})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(qtpass
        main.cpp)

target_link_libraries(qtpass qtpasslib Qt5::Widgets Qt5::Network Qt5::Svg)
add_compile_definitions(QAPPLICATION_CLASS=QApplication)
