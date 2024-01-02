# Repository structure

The SDK repositories follow structure designed to enhance clarity and facilitate efficient development. Template library that stands as an example of perfect folder and files layout can be found here - [TemplateLibrary](https://github.com/ConstantRobotics-Ltd/CodingStandards/tree/master/templates/TemplateLibrary).

``` markdown
  --- 3rdparty
  --- demo
  --- example
  --- src
  --- test
  --- .gitignore
  --- .gitmodules
  --- CMakeLists.txt
  --- README.md
```

## 3rdparty
**3rdparty** folder should contain all necessary dependencies to the main project. Make sure it does not include any redundant libraries. Additional CMakeLists.txt file inside is obligatory.

## demo

**demo** folder should contain *main.cpp* file with related *CMakLists.txt* file. Also additional *3rdparty* folder with dependencies if needed. Demo application have to allow user testing all main functionalities of the library. It should enclose ability to test different parameters and record a video (for video processing libraries), but also be as simple as possible. Include manual in .md and .pdf formats.

## example

**example** folder should contain *main.cpp* file with related *CMakLists.txt* file. The simplest application possible with the shortest code.

## src

**src** folder should contain all *Lib.cpp* and *Lib.h* files as well as version files and related *CMakLists.txt* file. 

## test

**test** folder should contain *main.cpp* file with related *CMakLists.txt* file. Folder designed for all testing related stuff that is necessary during creation of library. Can be used for internal tests of feature, but it does not mean it can be dirty.