cmake_minimum_required(VERSION 3.13)



################################################################################
## 3RD-PARTY
## dependencies for the project
################################################################################
project(Templates LANGUAGES CXX)



################################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the 3rd-party configuration
################################################################################
add_subdirectory(TemplateApplication)
add_subdirectory(TemplateLibrary)
