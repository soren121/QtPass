cmake_minimum_required(VERSION 3.15)
project(qtpass)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_compile_definitions(VERSION="1.3.2")

include_directories(src)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5GUI REQUIRED)
find_package(Qt5LinguistTools REQUIRED)

file(GLOB TS_FILES "${CMAKE_CURRENT_SOURCE_DIR}/localization/*.ts")
set_source_files_properties(${TS_FILES} PROPERTIES OUTPUT_LOCATION localization)
qt5_add_translation(QM_FILES ${TS_FILES})

add_library(qtpasslib
        src/configdialog.cpp
        src/configdialog.h
        src/debughelper.h
        src/deselectabletreeview.h
        src/enums.h
        src/executor.cpp
        src/executor.h
        src/filecontent.cpp
        src/filecontent.h
        src/imitatepass.cpp
        src/imitatepass.h
        src/keygendialog.cpp
        src/keygendialog.h
        src/mainwindow.cpp
        src/mainwindow.h
        src/pass.cpp
        src/pass.h
        src/passwordconfiguration.h
        src/passworddialog.cpp
        src/passworddialog.h
        src/qprogressindicator.cpp
        src/qprogressindicator.h
        src/qpushbuttonasqrcode.cpp
        src/qpushbuttonasqrcode.h
        src/qpushbuttonwithclipboard.cpp
        src/qpushbuttonwithclipboard.h
        src/qtpass.cpp
        src/qtpass.h
        src/qtpasssettings.cpp
        src/qtpasssettings.h
        src/realpass.cpp
        src/realpass.h
        src/settingsconstants.cpp
        src/settingsconstants.h
        src/simpletransaction.cpp
        src/simpletransaction.h
        src/singleapplication.cpp
        src/singleapplication.h
        src/storemodel.cpp
        src/storemodel.h
        src/trayicon.cpp
        src/trayicon.h
        src/userinfo.h
        src/usersdialog.cpp
        src/usersdialog.h
        src/util.cpp
        src/util.h
        resources.qrc
        ${QM_FILES})

target_link_libraries(qtpasslib Qt5::Core Qt5::Widgets Qt5::Network)

add_executable(qtpass
        main/main.cpp)

target_link_libraries(qtpass qtpasslib)