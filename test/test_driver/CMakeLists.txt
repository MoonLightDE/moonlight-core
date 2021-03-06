#    Copyright (C) 2014 Moonlight Desktop Environment Team
#    Authors:
#       Alexis López Zubieta
#    This file is part of the Moonlight Desktop Environment
#
#    Moonlight Desktop Environment is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    Moonlight Desktop Environment is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with Moonlight Desktop Environment.  If not, see <http://www.gnu.org/licenses/>.
#
set(MODULE_NAME test_driver)
project(moonlightDE-${MODULE_NAME})

## --------------------------------------------------------------
## Sources
## --------------------------------------------------------------
set(${PROJECT_NAME}_PUBLIC_HEADERS
)

set(${PROJECT_NAME}_SOURCES 
    Activator.cpp
    TestICore.h    
    TestICore.cpp
)

set (${PROJECT_NAME}_UIS
)

set (${PROJECT_NAME}_RESOURCES
)

set( ${PROJECT_NAME}_DESCRIPTOR 
    moonlightDE-test_driver.desktop
)

## --------------------------------------------------------------
## Dependencies - Qt
## -------------------------------- ------------------------------
find_package(Qt5Core    REQUIRED)
find_package(Qt5Test REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

QT5_WRAP_UI(${PROJECT_NAME}_UI_HEADERS ${${PROJECT_NAME}_UIS})
QT5_ADD_RESOURCES(${PROJECT_NAME}_QRC_SOURCES ${${PROJECT_NAME}_RESOURCES})

## --------------------------------------------------------------
## Dependencies - internal
## --------------------------------------------------------------

## MoonLight Core
find_package(MOONLIGHT_CORE REQUIRED)
include_directories(${MOONLIGHT_CORE_SERIVICES_DIR})

#CppMicroServices
find_package(CppMicroServices NO_MODULE REQUIRED)
include_directories(${CppMicroServices_INCLUDE_DIRS})


include_directories(${CMAKE_BINARY_DIR})

## --------------------------------------------------------------
## Build Rules
## --------------------------------------------------------------
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${MODULES_INSTALL_DIR})

usFunctionGenerateModuleInit( ${PROJECT_NAME}_SOURCES
    NAME ${PROJECT_NAME}
    LIBRARY_NAME ${MODULE_NAME}
)

add_library(${PROJECT_NAME} SHARED 
    ${${PROJECT_NAME}_HEADERS}
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_UI_HEADERS}
    ${${PROJECT_NAME}_QRC_SOURCES}
)


qt5_use_modules(${PROJECT_NAME} 
    Core
    Test
)

# Link the CppMicroServices library
target_link_libraries(${PROJECT_NAME} ${CppMicroServices_LIBRARIES} )

## --------------------------------------------------------------
## Install
## --------------------------------------------------------------
INSTALL(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION ${MOONLIGHT_CORE_MODULES_DIR}
    ARCHIVE DESTINATION lib/static)

INSTALL(FILES ${${PROJECT_NAME}_DESCRIPTOR} 
    DESTINATION ${MOONLIGHT_CORE_DESCRIPTORS_DIR})