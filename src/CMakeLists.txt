#set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_compile_definitions(CORE_LIBRARY)

file(GLOB TS_FILES "../localization/*.ts")
set_source_files_properties(${TS_FILES} PROPERTIES OUTPUT_LOCATION localization)
qt5_add_translation(QM_FILES ${TS_FILES})
add_custom_target(translations DEPENDS ${QM_FILES})

qt5_wrap_ui(ui_configdialog.h configdialog.ui)
qt5_wrap_ui(ui_keygendialog.h keygendialog.ui)
qt5_wrap_ui(ui_mainwindow.h mainwindow.ui)
qt5_wrap_ui(ui_passworddialog.h passworddialog.ui)
qt5_wrap_ui(ui_usersdialog.h usersdialog.ui)

set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${Qt5Svg_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${Qt5Network_EXECUTABLE_COMPILE_FLAGS}")

add_library(qtpasslib #SHARED
        configdialog.cpp
        configdialog.h
        configdialog.ui
        debughelper.h
        deselectabletreeview.h
        enums.h
        executor.cpp
        executor.h
        filecontent.cpp
        filecontent.h
        imitatepass.cpp
        imitatepass.h
        keygendialog.cpp
        keygendialog.h
        keygendialog.ui
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        pass.cpp
        pass.h
        passwordconfiguration.h
        passworddialog.cpp
        passworddialog.h
        passworddialog.ui
        qprogressindicator.cpp
        qprogressindicator.h
        qpushbuttonasqrcode.cpp
        qpushbuttonasqrcode.h
        qpushbuttonwithclipboard.cpp
        qpushbuttonwithclipboard.h
        qtpass.cpp
        qtpass.h
        qtpasssettings.cpp
        qtpasssettings.h
        realpass.cpp
        realpass.h
        settingsconstants.cpp
        settingsconstants.h
        simpletransaction.cpp
        simpletransaction.h
        singleapplication.cpp
        singleapplication.h
        storemodel.cpp
        storemodel.h
        trayicon.cpp
        trayicon.h
        userinfo.h
        usersdialog.cpp
        usersdialog.h
        usersdialog.ui
        util.cpp
        util.h
        ../resources.qrc
        ${QM_FILES})

target_link_libraries(qtpasslib Qt5::Widgets Qt5::Network Qt5::Svg)
add_compile_definitions(QAPPLICATION_CLASS=QApplication)
