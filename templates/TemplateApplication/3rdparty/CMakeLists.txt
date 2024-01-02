cmake_minimum_required(VERSION 3.13)

################################################################################
## 3RD-PARTY
## dependencies for the project
################################################################################
project(3rdparty LANGUAGES CXX)

################################################################################
## SETTINGS
## basic 3rd-party settings before use
################################################################################
# To inherit the top-level architecture when the project is used as a submodule.
SET(PARENT ${PARENT}_YOUR_PROJECT_3RDPARTY)
# Disable self-overwriting of parameters inside included subdirectories.
SET(${PARENT}_SUBMODULE_CACHE_OVERWRITE OFF CACHE BOOL "" FORCE)

################################################################################
## CONFIGURATION
## 3rd-party submodules configuration
################################################################################
SET(${PARENT}_SUBMODULE_TEMPLATE_LIBRARY                ON  CACHE BOOL "" FORCE)
if (${PARENT}_SUBMODULE_TEMPLATE_LIBRARY)
    SET(${PARENT}_TEMPLATE_LIBRARY                      ON  CACHE BOOL "" FORCE)
    SET(${PARENT}_TEMPLATE_LIBRARY_TEST                 OFF CACHE BOOL "" FORCE)
    SET(${PARENT}_TEMPLATE_LIBRARY_EXAMPLE              OFF CACHE BOOL "" FORCE)
    SET(${PARENT}_TEMPLATE_LIBRARY_DEMO                 OFF CACHE BOOL "" FORCE)
endif()

################################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the 3rd-party configuration
################################################################################
if (${PARENT}_SUBMODULE_TEMPLATE_LIBRARY)
    add_subdirectory(TemplateLibrary)
endif()