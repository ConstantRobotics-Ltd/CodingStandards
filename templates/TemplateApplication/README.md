![logo](_static/template_web_logo.png)



# **Template C++ application**

**v1.0.0**



# Table of contents


- [Overview](#Overview)
- [Versions](#versions)
- [Application files](#Application-files)
- [Software Install](#Software-install)
- [Additional section 1](#Additional-section-1)
- [Additional section 2](#Additional-section-2)



## Overview

**TemplateApplication** is an example of application structure. In accordance with our documentation standards, it is mandatory for every application within our project to include a README file like this one. This README should provide comprehensive information about the repository, including its purpose, usage guidelines, and any essential instructions for contributors. Please ensure that the README file follows the format and content similar to the one you are currently reviewing. This practice contributes to consistency, transparency, and ease of use across all our repositories. This application as example depends on open source [**ConfigReader**](https://github.com/ConstantRobotics-Ltd/ConfigReader) library which provides methods to work with JSON files.

Overview section must include explanation of application purpose, C++ standard, important dependencies and main features. This text will be used for publishing on web site. Provide enough information so that the user can immediately understand the purpose of the application and its compatibility with their project.

Generally any application repository should have following structure:

``` xml
3rdparty ------------- Folder with third-party libraries (dependencies)
    Submodule1 ------- Third-party library folder.
    Submodule2 ------- Third-party library folder.
    CMakeLists.txt --- CMake file to include third-party libraries.
src ------------------ Source code folder.
_static -------------- Folder with images for documentation.
.gitignore ----------- File to exclude particular files/folders from repository.
CMakeLists.txt ------- Main CMake file.
README.md ------------ Documentation.
```



# Versions

**Table 1** - Application versions.

| Version | Release date | What's new                                                   |
| ------- | ------------ | ------------------------------------------------------------ |
| 1.0.0   | DD.MM.YYYY   | - Make sure to update application versions table after each release.<br />- Briefly describe every important change or update. <br />- Use bullet list style. |



# Application files

The **TemplateApplication** is a CMake project. Application files chapter should briefly describe what's inside this repository. It is very important so every associate or customer will understand what particular repository includes:

```xml
CMakeLists.txt ---------------------- Main CMake file of the application.
3rdparty ---------------------------- Folder with third-party libraries.
    CMakeLists.txt ------------------ CMake file which includes third-party libraries.
    ConfigReader -------------------- Source code of the ConfigReader library.
src --------------------------------- Folder with source code of the application.
    CMakeLists.txt ------------------ CMake file of the application.
    main.cpp ------------------------ Source code file.
    TemplateApplicationVersion.h ---- Header file which includes version.
    TemplateApplicationVersion.h.in - CMake service file to generate version file.
```



# Software install



In this section explain what user should do to install and run application.



# Additional sections



Any additional information for particular applications. All features should have detailed description.
