cmake_minimum_required(VERSION 3.19)
project(veil LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(LayerShellQt REQUIRED)


qt_standard_project_setup()

qt_add_executable(veil
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    controlpanel.h controlpanel.cpp
)

target_link_libraries(veil
    PRIVATE
        Qt::Core
        Qt::Widgets
        LayerShellQt::Interface
)

install(TARGETS veil
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET veil
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
