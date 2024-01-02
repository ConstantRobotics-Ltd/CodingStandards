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
    - [Documentation](#Documentation)
    - [Good practices](###Good practices)
  - [Memory Managment](##Memory Managment)
  - [Code Managment](##Code Managment)
  	- [Commits](###Commits)
  	- [Branches](###Branches)
  	- [Pull-requests](###Pull-requests)
- [Resources](#Resources)

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
    // errors if modification are made in the future and close attention  is not paid.
    for (int i = 0; i < 15; ++i)
      std::cout << i << std::endl;
    
    // Good Idea
    // It's clear which statements are part of the loop (or if block, or  whatever).
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
6. Namespace name should be descriptive and short. Before adding a new namespace check if it doesn't exist in different form. For example do not add *'cr::image'* if there is already *'cr::frame'*.
7. 3 lines empty spaces between methods bodies?

### Documentation

1. Each class, method, field, function has to have descriptive documentation written as a comment in header file.

2. Use `/* */` only for documentation, e.g. -
   ```c++
    /**
     * @brief Set the value for a specific template parameter.
     * @param id The identifier of the template parameter.
     * @param value The value to set for the parameter.
     * @return True if the parameter was successfully set, false otherwise.
     */
   bool setParam(TemplateParam id, float value);
   ```
3. Keep the documentation up-to-date when making changes to the code.

### Good practices

1. Use *'nullptr'* to indicate a null pointer. Not NULL nor 0.

2. **Never** use *'using namespace'* in a header file. Try to avoid also in source C++ files, since it can create name conflicts and ambiguities. [Why is "using namespace" considered a bad practice](https://stackoverflow.com/questions/1452721/why-is-using-namespace-std-considered-bad-practice)

3. Apply *'include'* guards to avoid including the same file multiple times. Use *'#pragma once'*.

4. Always use namespaces while creating new class. All namespaces should be placed in one general namespace *'cr'*.
```c++
   #pragma once
   
   namespace cr
   {
   namespace temp
   {
   class TempClass
   {
       TempClass();
   };
   }
   }
```
5. Always initialize variables. Initialize variables with curly brackets to avoid narrowing chosen value:
   ```c++
   unsigned value = -1; // Narrowing from signed to unsigned.
   unsigned valueB{ -1 }; // Narrowing from signed to unsigned not alllowed, compile time error.
   ```
   
6. Use C++-style cast instead of C-style cast. Use the C++-style cast (static\_cast<>, dynamic\_cast<> ...) instead of the C-style cast. The C++-style cast allows more compiler checks and is considerably safer. Additionally the C++ cast style is more visible and has the possibility to search for. [Further reading](https://anteru.net/blog/2007/c-background-static-reinterpret-and-c-style-casts/).

7. Avoid using macros for constant values. Use constexpr, not `#define PI 3.14159;`,
   but `constexpr double PI = 3.14159;`.

## Memory Management

1. Using smart pointers such as `std::unique_ptr` and `std::shared_ptr` in C++11 and later versions is recommended over raw memory access, allocation, and deallocation to mitigate the risks of memory errors and leaks.

2. Always use `const` if possible, this helps the compiler optimize the code and is more unequivocal for developer.

3. Returning by `&` or `const &` can have significant performance savings when the normal use of the returned value is for observation. Returning by value is better for thread safety and if the normal use of the returned value is to make a copy anyhow, there's no performance lost.

4. Never return `nullptr` from a function. When a function returns pointer and some condition is not satisfied, just return pointer to the empty value.

5. Shared variables. Use `std::atomic` for basic types. Use `std::mutex` library for operating with shared variables, in cases like parameters class:
   ```c++
   std::atomic<bool> templateVariable{ false };
   templateVariable.store(true);
   
   TemplateParams templateParams;
   std::mutex templateParamsMutex;
   
   templateParamsMutex.lock();
   templateParams.firstParam = true;
   templateParamsMutex.unlock();
   ```

6. If semantically correcy prefer `++i` to `i++`. Pre-increment is faster than post-increment (it doesn't require copy of the object being made).



## Code Management

### Commits 

1. Commit as often as possible. Don't wait until you finish the task with commiting. Wrong combination of `Ctrl+Z` and `Ctrl+Y` may cost you losing a lot of code while prototyping. Frequent commits allow you to make smaller, focused changes to your codebase. Each commit represents a single logical unit of work or a specific feature/fix. This granularity makes it easier to understand the history of changes, identify the cause of issues, and review or revert changes if needed.

2. Write your commit messages in the imperative mood, as it follows same style as commits generated by git commands. 
   ```bash
   # Bad practice. Using dots at the end also bad idea.
   git commit -m "Version number in documentation updated."
   # Good practice.
   git commit -m "Update version number in documentation"
   ```
3. Make your commit message descriptive, but not longer than 80 chars.
   ```bash
   # Bad practice.
   git commit -m "Fix bug"
   # Good practice.
   git commit -m "Fix memory leak after copying frame bug"
   ```

   

### Branches

1. When to create a branch?
2. Branch names.
3. When to close?

### Pull-requests

1. PR title.
2. PR description.
3. PR rules, reviewers, who close, who opens, etc.








## Recommended tools and libraries



IDEs?

# Resources

C++ best practices -
1. https://github.com/cpp-best-practices/cppbestpractices
2. https://google.github.io/styleguide/cppguide.html
3. https://isocpp.org/wiki/faq/coding-standards
4. Clean C++ - Stephan Roth, 2017


Clean Code tips - 

1. https://gist.github.com/wojteklu/73c6914cc446146b8b533c0988cf8d29

General standards -

1. https://www.devbridge.com/articles/coding-best-practices/
2. https://medium.com/agile-adapt/composing-meaningful-tasks-c1ca51064c1a
