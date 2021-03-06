#    Copyright (C) 2014 Moonlight Desktop Environment Team
#    Authors:
#       Alexis López Zubieta
#
#    This file is part of the Moonlight Desktop Environment 
#
#    Moonlight Desktop Environment is free software you can redistribute it 
#    and/or modify it under the terms of the GNU General Public License as 
#    published by the Free Software Foundation, either version 3 of the License,
#    or (at your option) any later version.
#
#    Moonlight Desktop Environment is distributed in the hope that it will be
#    useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with Moonlight Desktop Environment.  If not, see 
#    <http://www.gnu.org/licenses/>.
#
## --------------------------------------------------------------
## Sources
## --------------------------------------------------------------
set(${PROJECT_NAME}_PUBLIC_HEADERS
    ../include/core/ICore.h
    ../include/core/IQt5.h

)

set(${PROJECT_NAME}_SOURCES
    Controller.h
    Controller.cpp
    ModuleManager.h
    ModuleManager.cpp
    ModuleModel.h
    ModuleModel.cpp
    CoreConfigurationUI.cpp
    CoreConfigurationUI.h
    main.cpp
)

set ( ${PROJEC_NAME}_UIS
    CoreConfigurationUI.ui
)

set ( ${PROJEC_NAME}_RESOURCES
)

include_directories(../include)
include_directories(${CMAKE_BINARY_DIR})

## --------------------------------------------------------------
## Dependencies
## --------------------------------------------------------------

## QT 5
find_package(Qt5Core    REQUIRED)
find_package(Qt5Gui     REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

QT5_WRAP_UI(${PROJEC_NAME}_UI_HEADERS ${${PROJEC_NAME}_UIS})
QT5_ADD_RESOURCES(${PROJEC_NAME}_QRC_SOURCES ${${PROJEC_NAME}_RESOURCES})

## Core 
find_package(MOONLIGHT_CORE REQUIRED)
include_directories(${MOONLIGHT_CORE_SERIVICES_DIR})

#CppMicroServices
find_package(CppMicroServices NO_MODULE REQUIRED)
include_directories(${CppMicroServices_INCLUDE_DIRS})

## QT5XDG
find_package(QT5XDG REQUIRED)
include(${QTXDG_USE_FILE})  

## LXQT -- depends on QT5XDG
find_package(LXQT-QT5 REQUIRED )
include(${LXQT_USE_FILE})

## --------------------------------------------------------------
## Build Rules
## --------------------------------------------------------------
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${MODULES_INSTALL_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


usFunctionGenerateExecutableInit(${PROJECT_NAME}_SOURCES
                                 IDENTIFIER ${PROJECT_NAME}
                                 )


configure_file( MoonLightDECoreConfig.h.in ${CMAKE_CURRENT_BINARY_DIR}/MoonLightDECoreConfig.h)

add_executable(${PROJECT_NAME} 
    ${${PROJECT_NAME}_PUBLIC_HEADERS}
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJEC_NAME}_UI_HEADERS}
    ${${PROJEC_NAME}_QRC_SOURCES}
)

qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Gui)
qt5_use_modules(${PROJECT_NAME} Widgets)

# Link the CppMicroServices library
target_link_libraries(${PROJECT_NAME} 
    CppMicroServices
    ${LXQT_LIBRARIES}
    ${QTXDG_LIBRARIES}
)

## --------------------------------------------------------------
## Install
## --------------------------------------------------------------

INSTALL(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION ${MODULES_INSTALL_DIR}
    ARCHIVE DESTINATION lib/static)

INSTALL(FILES ${${PROJECT_NAME}_PUBLIC_HEADERS} 
    DESTINATION ${SERVICES_INSTALL_DIR}/core )
