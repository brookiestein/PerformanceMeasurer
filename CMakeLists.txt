cmake_minimum_required(VERSION 3.5)

project(PerformanceMeasurer VERSION 1.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(PROGRAM_NAME="PerformanceMeasurer")
add_compile_definitions(VERSION="1.1")
add_compile_definitions(AUTHOR="Brayan MS")
add_compile_definitions(THIS_PROGRAM_URL="https://github.com/brookiestein/PerformanceMeasurer")
add_compile_definitions(OTHER_PROJECTS="https://github.com/brookiestein?tab=repositories")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools Sql Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Sql Charts)

set(TS_FILES translations/PerformanceMeasurer_es_ES.ts
             translations/PerformanceMeasurer_es_DO.ts
             translations/PerformanceMeasurer_es_US.ts)
qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

set(PROJECT_SOURCES
        chart.hpp
        calldetails.hpp
        database.hpp
        mainwindow.hpp
        callsfinder.hpp
        chart.cpp
        calldetails.cpp
        callsfinder.cpp
        database.cpp
        main.cpp
        mainwindow.cpp
        chart.ui
        calldetails.ui
        callsfinder.ui
        mainwindow.ui
        resources.qrc
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PerformanceMeasurer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${QM_FILES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PerformanceMeasurer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(PerformanceMeasurer SHARED
            ${PROJECT_SOURCES}
            ${QM_FILES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PerformanceMeasurer
            ${PROJECT_SOURCES}
            ${QM_FILES}
        )
    endif()
endif()

target_link_libraries(PerformanceMeasurer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                                                  Qt${QT_VERSION_MAJOR}::Sql
                                                  Qt${QT_VERSION_MAJOR}::Charts)

set_target_properties(PerformanceMeasurer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS PerformanceMeasurer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PerformanceMeasurer)
endif()
