![img](_static/rapid_pixel_logo.png)

# Rapid Pixel SDK Coding Standards

# Table of contents

- [Intro](#Intro)
- [SDK Structure](#SDK Structure)
- [Repository Structure](#Repository Structure)
	- [demo](#demo)
	- [example](#example)
	- [src](#src)
	- [test](#test)
- [Coding Guide](#Coding Guide)
  - [Style](##Style)
    - [Naming](###Naming)
    - [Composition](#Composition)
    - [Good practices](###Good practices)
  - [Recommended tools and libraries](#Recommended tools and libraries)
  - [Recommended tools and libraries](#Recommended tools and libraries)
  - [Recommended tools and libraries](#Recommended tools and libraries)
  
- [SDK Structure](#SDK Structure)
- 

# Intro

Welcome to our Way of Work document for RapidPixel SDK. This guide outlines essential principles for efficient collaboration, project management, code maintenance, library usage, and readability. By following these guidelines, we aim to boost efficiency, organization, and code quality. Let's work together to create high-quality software while minimizing unnecessary challenges. Thank you for contributing to our cohesive and productive development environment!

# SDK Structure

SDK(Software Development Toolkit) is distributed across multiple repositories, each serving a specific purpose. Structure leverages a predominantly private repository setup, securing proprietary code and sensitive information. However, for shared practices and streamlined development, we maintain selected public template repositories. These templates offer standardized configurations and guidelines.

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

# Coding Guide

The main point of coding guide is to provide a set of rules that will be fundamental in Rapid Pixel SDK structure. Our code should be optimized for the reader, not the writer. The most important is efficiency, but to build up expandable and easy to maintain coding projects we have to follow basic standards.

## Style

Consistency is the most important aspect of style. The second most important aspect is following a style that the average C++ programmer is used to reading. C++ allows for arbitrary-length identifier names, so there's no reason to be terse when naming things. Use descriptive names, and be consistent in the style.

### Naming

1. Use **PascalCase** for naming: a class, an enum class or a function, e.g. - *'TemplateLibrary'*.

2. Use **camelCase** for naming: a local variable or a method, e.g. - *'setParam()'*.

3. Use **upper case with underscores** for naming: a constant, e.g. - *'MAX_CONSTANT_VALUE'*.

4. Distinguish private class field with a *'m_'* prefix, e.g. - *'m_frameWidth'*(*'m_'* stands for "member").

5. Don't name anything starting with underscore *'_'*.

### Composition

1. Comment blocks should use `//`, not `/* */`. `/* */` is reserved for documentation in header file only.

2. Strive to strike a balance in commenting your code - while it is crucial to provide sufficient comments for clarity and understanding, aim to keep them concise and focused, avoiding unnecessary verbosity to maintain code readability and promote efficient collaboration, e.g. - 
  ```c++
  // Good comment:
  // This equation comes from mass–energy equivalence E=mc^2.
  auto energy = mass * speedOfLight * speedOfLight;
  
  // Bad comment(code explains itself, comment is redundant):
  // Check if energy was calculated.
  if (energy.isCalculated()) {}
  ```
3. Curly brackets *'{}'* are **required** for blocks. It costs you nothing, but can cost a lot of time for someone changing code after you, e.g. 


   ```c++
   // Bad Idea
   // This compiles and does what you want, but can lead to confusing
   // errors if modification are made in the future and close attention is not paid.
   for (int i = 0; i < 15; ++i)
     std::cout << i << std::endl;
   
   // Good Idea
   // It's clear which statements are part of the loop (or if block, or whatever).
   for (int i = 0; i < 15; ++i) 
   {
     std::cout << i << std::endl;
   }
   ```
4. Take whole line for a single curly bracket (just to keep the same visual style everywhere).
   ```c++
   // Like this:
   if (i == 0) 
   {
     std::cout << i << std::endl;
   }
   // Not like this:
   if (i == 0) {
     std::cout << i << std::endl;
   }
   ```

5. Keep lines a reasonable length. In header files do not cross length of **80** characters.

6. ssa 

7. ada 

### Good practices

1. Use *'nullptr'* to indicate a null pointer. Not NULL nor 0.

2. **Never** use *'using namespace'* in a header file. Try to avoid also in source C++ files.

3. Apply *'include'* guards to avoid including the same file multiple times. Use *'#pragma once'*.

4. Always use namespaces while creating new class.
   ```c++
   #pragma once
   
   namespace temp
   {
   class TempClass
   {
       
   };
   }
   ```

   

   

   

   

## Recommended tools and libraries



