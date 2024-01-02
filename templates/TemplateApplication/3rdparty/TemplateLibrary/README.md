![logo](_static/template_web_logo.png)



# **Template  C++ library**

**v1.0.0**



# Table of contents

- [Overview](#Overview)
- [Versions](#Versions)
- [Library files](#Library-files)
- [TemplateLibrary interface class description](#TemplateLibrary-interface-class-description)
  - [Class declaration](#Class-declaration)
  - [getVersion method](#getVersion-method)
  - [setParam method](#setParam-method)
  - [getParam method](#getParam-method)
  - [getParams method](#getParams-method)
  - [executeCommand method](#executeCommand-method)
- [Data structures](#Data-structures)
  - [TemplateCommand enum](#TemplateCommand-enum)
  - [TemplateParam enum](#TemplateParam-enum)
- [TemplateParams class description](#TemplateParams-class-description)
  - [Class declaration](#Class-declaration)
  - [Serialize template params](#Serialize-template-params)
  - [Deserialize template params](#Deserialize-template-params)
  - [Read params from JSON file and write to JSON file](#Read-params-from-JSON-file-and-write-to-JSON-file)
- [Build and connect to your project](#Build-and-connect-to-your-project)



# Overview

**TemplateLibrary** C++ library provides standard interface as well defines data structures and rules to stand as an example for other repositories in ConstantRobotics's RapidPixel SDK. In accordance with our documentation standards, it is mandatory for every repository within our project to include a README file like this one. This README should provide comprehensive information about the repository, including its purpose, usage guidelines, and any essential instructions for contributors. Please ensure that the README file follows the format and content similar to the one you are currently reviewing. This practice contributes to consistency, transparency, and ease of use across all our repositories.

# Versions

**Table 1** - Library versions.

| Version | Release date | What's new                                                   |
| ------- | ------------ | ------------------------------------------------------------ |
| 1.0.0   | DD.MM.YYYY   | - Make sure to update library versions table after each release.<br />- Briefly describe every important change or update. <br />- Use bullet list style. |



# Library files

The **TemplateLibrary** is a CMake project. Library files chapter should briefly describe what's inside this library. It is very important so every associate or customer will understand what particular repository includes:

```xml
CMakeLists.txt ------------------- Main CMake file of the library.
3rdparty ------------------------- Folder with third-party libraries.
    CMakeLists.txt --------------- CMake file which includes third-party libraries.
    ConfigReader ----------------- Source code of the ConfigReader library.
example -------------------------- Folder with the simplest example of TemplateLibrary usage.
    CMakeLists.txt --------------- CMake file for simple example.
    main.cpp --------------------- Source code file of simple example application.
test ----------------------------- Folder for internal tests of TemplateLibrary.
    CMakeLists.txt --------------- CMake file for codec test application.
    main.cpp --------------------- Source code file of TemplateLibrary class test application.
src ------------------------------ Folder with source code of the library.
    CMakeLists.txt --------------- CMake file of the library.
    TemplateLibrary.cpp ------------------- Source code file of the library.
    TemplateLibrary.h --------------------- Header file which includes TemplateLibrary class declaration.
    TemplateLibraryVersion.h -------------- Header file which includes version of the library.
    TemplateLibraryVersion.h.in ----------- CMake service file to generate version file.
```



# TemplateLibrary interface class description



## Class declaration

**TemplateLibrary** interface class declared in **TemplateLibrary.h** file. Class declaration:

```cpp
class TemplateLibrary
{
public:
    /// Class destructor.
    TemplateLibrary();
    
    /// Class destructor.
    ~TemplateLibrary();

    /// Get TemplateLibrary class version.
    static std::string getVersion();
    
    /// Set the template param.
    bool setParam(TemplateParam id, float value);
    
    /// Get the template param.
    float getParam(TemplateParam id);
    
    /// Get the template params structure.
    void getParams(TemplateParams& params);
    
    /// Execute template command.
    bool executeCommand(TemplateCommand id);
};
```



## getVersion method

**getVersion()** method returns string of current class version. Method declaration:

```cpp
static std::string getVersion();
```

Method can be used without **TemplateLibrary** class instance:

```cpp
std::cout << "TemplateLibrary version: " << cr::templ::TemplateLibrary::getVersion() << std::endl;
```

Console output:

```bash
TemplateLibrary class version: 1.0.0
```



## setParam method

**setParam(...)** method sets new template parameters value. Every implementation of library with parameters have to provide thread-safe **setParam(...)** method call. This means that the **setParam(...)** method can be safely called from any thread. Method declaration:

```cpp
bool setParam(TemplateParam id, float value);
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| id        | Template parameter ID according to TemplateParam enum (see description of **TemplateParam** enum). |
| value     | Template parameter value. Value depends on parameter ID (see description of **TemplateParam** enum). |

**Returns:** TRUE if the parameter was set or FALSE if not.



## getParam method

**getParam(...)** method returns template parameter value. Every implementation of library with parameters have to provide thread-safe getParam(...)** method call. This means that the **getParam(...)** method can be safely called from any thread. Method declaration:

```cpp
float getParam(TemplateParam id);
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| id        | Template parameter ID according to TemplateParam enum (see description of [**TemplateParam enum**](#TemplateParam-enum)). |

**Returns:** parameter value or **-1** if the parameters doesn't exist.



## getParams method

**getParams(...)** method is designed to obtain template parameters. Every implementation of library with parameters have to provide thread-safe **getParams(...)** method call. This means that the **getParams(...)** method can be safely called from any thread. Method declaration:

```cpp
void getParams(TemplateParams& params);
```

| Parameter | Description                                         |
| --------- | --------------------------------------------------- |
| params    | Reference to TemplateParams object to store params. |



# Data structures



## TemplateCommand enum

Enum declaration:

```cpp
enum class TemplateCommand
{
    /// First command.
    FIRST_COMMAND = 1,
    /// Second command.
    SECOND_COMMAND,
    /// Third command.
    THIRD_COMMAND
};
```

**Table 2** - Template commands description.

| Command        | Description                   |
| -------------- | ----------------------------- |
| FIRST_COMMAND  | First command.                |
| SECOND_COMMAND | Second command.               |
| THIRD_COMMAND  | Third command.                |



## TemplateParam enum

Enum declaration:

```cpp
enum class TemplateParam
{
    /// First template param.
    FIRST_PARAM = 1,
    /// Second template param.
    SECOND_PARAM,
    /// Third template param.
    THIRD_PARAM
};
```

**Table 3** - Template params description.

| Parameter    | Access       | Description            |
| ------------ | ------------ | ---------------------- |
| FIRST_PARAM  | read / write | First template param.  |
| SECOND_PARAM | read / write | Second template param. |
| THIRD_PARAM  | read / write | Third template param.  |

# TemplateParams class description

**TemplateParams** class is used  to provide example params structure. Also **TemplateParams** provide possibility to write/read params from JSON files (**JSON_READABLE** macro) and provide methods to encode and decode params.



## Class declaration

**TemplateParams** interface class declared in **TemplateLibrary.h** file. Class declaration:

```cpp
class TemplateParams
{
public:
    /// First template param.
    bool firstParam{ false };
    /// Second template param.
    int secondParam{ 0 };
    /// Third template param.
    float thirdParam{ 0.0f };

    JSON_READABLE(TemplateParams, firstParam, secondParam, thirdParam)

    /// operator =
    TemplateParams& operator= (const TemplateParams& src);

    /// Encode params.
    bool encode(uint8_t* data, int bufferSize, int& size,
                TemplateParamsMask* mask = nullptr);

    /// Decode params.
    bool decode(uint8_t* data, int dataSize);
};
```

**Table 4** - TemplateParams class fields description is related to [**TemplateParam enum**](#TemplateParam -enum) description.

| Field       | type  | Description            |
| ----------- | ----- | ---------------------- |
| firstParam  | bool  | First template param.  |
| secondParam | int   | Second template param. |
| thirdParam  | float | Third template param.  |

**None:** *TemplateParams class fields listed in Table 4 **must** reflect params set/get by methods setParam(...) and getParam(...).* 



## Serialize template params

[**TemplateParams class**](#TemplateParams -class-description) provides method **encode(...)** to serialize template params (fields of [**TemplateParams class**](#TemplateParams -class-description), see Table 4). Serialization of template params necessary in case when you have to send template params via communication channels. Method provides options to exclude particular parameters from serialization. To do this method inserts binary mask (8 bytes) where each bit represents particular parameter and **decode(...)** method recognizes it. Method declaration:

```cpp
bool encode(uint8_t* data, int bufferSize, int& size, TemplateParamsMask* mask = nullptr);
```

| Parameter  | Value                                                        |
| ---------- | ------------------------------------------------------------ |
| data       | Pointer to data buffer. Buffer size must be >= 237 bytes.    |
| bufferSize | Data buffer size. Buffer size must be >= 237 bytes.          |
| size       | Size of encoded data.                                        |
| mask       | Parameters mask - pointer to **TemplateParamsMask** structure. **TemplateParamsMask** (declared in TemplateLibrary.h file) determines flags for each field (parameter) declared in [**TemplateParams class**](#TemplateParams-class-description). If the user wants to exclude any parameters from serialization, he can put a pointer to the mask. If the user wants to exclude a particular parameter from serialization, he should set the corresponding flag in the **TemplateParamsMask** structure. |

**Returns:** TRUE if params encoded (serialized) or FALSE if not.

**TemplateParamsMask** structure declaration:

```cpp
struct TemplateParamsMask
{
    bool firstParam{ true };
    bool secondParam{ true };
    bool thirdParam{ true };
};
```

Example without parameters mask:

```cpp
// Encode data.
TemplateParams in;
in.profile = 10;
uint8_t data[1024];
int size = 0;
in.encode(data, 1024, size);
std::cout << "Encoded data size: " << size << " bytes" << std::endl;
```

Example with parameters mask:

```cpp
// Prepare params.
TemplateParams in;
in.profile = 3;

// Prepare mask.
TemplateParamsMask mask;
mask.profile = false; // Exclude profile. Others by default.

// Encode.
uint8_t data[1024];
int size = 0;
in.encode(data, 1024, size, &mask);
cout << "Encoded data size: " << size << " bytes" << endl;
```



## Deserialize template params

[**TemplateParams class**](#TemplateParams-class-description) provides method **decode(...)** to deserialize template params (fields of TemplateParams class, see Table 4). Deserialization of template params necessary in case when you need to receive params via communication channels. Method automatically recognizes which parameters were serialized by **encode(...)** method. Method declaration:

```cpp
bool decode(uint8_t* data, int dataSize);
```

| Parameter | Value                                                   |
| --------- | ------------------------------------------------------- |
| data      | Pointer to data buffer with serialized template params. |
| dataSize  | Size of command data.                                   |

**Returns:** TRUE if params decoded (deserialized) or FALSE if not.

Example:

```cpp
// Encode data.
TemplateParams in;
uint8_t data[1024];
int size = 0;
in.encode(data, 1024, size);
cout << "Encoded data size: " << size << " bytes" << endl;

// Decode data.
TemplateParams out;
if (!out.decode(data, size))
    cout << "Can't decode data" << endl;
```



## Read params from JSON file and write to JSON file

**TemplateLibrary** depends on [**ConfigReader**](https://github.com/ConstantRobotics-Ltd/ConfigReader) library which provides method to read params from JSON file and to write params to JSON file. Example of writing and reading params to JSON file:

```cpp
// Write params to file.
cr::utils::ConfigReader inConfig;
inConfig.set(in, "templateParams");
inConfig.writeToFile("TestTemplateParams.json");

// Read params from file.
cr::utils::ConfigReader outConfig;
if(!outConfig.readFromFile("TestTemplateParams.json"))
{
    cout << "Can't open config file" << endl;
    return false;
}
```

**TestTemplateParams.json** will look like:

```json
{
    "templateParams": 
    {
        "firstParam": true,
        "secondParam": 1
        "thirdParam": 0.5f
    }
}
```



# Build and connect to your project

Typical commands to build **TemplateLibrary**:

```bash
git clone https://github.com/ConstantRobotics-Ltd/TemplateLibrary.git
cd TemplateLibrary
git submodule update --init --recursive
mkdir build
cd build
cmake ..
make
```

If you want connect **TemplateLibrary** to your CMake project as source code you can make follow. For example, if your repository has structure:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
```

You can add repository **TemplateLibrary** as submodule by commands:

```bash
cd <your respository folder>
git submodule add https://github.com/ConstantRobotics-Ltd/TemplateLibrary.git 3rdparty/TemplateLibrary
git submodule update --init --recursive
```

In you repository folder will be created folder **3rdparty/TemplateLibrary** which contains files of **TemplateLibrary** repository with subrepository **ConfigReader** and **ConfigReader**. New structure of your repository:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
3rdparty
    TemplateLibrary
```

Create CMakeLists.txt file in **3rdparty** folder. CMakeLists.txt should contain:

```cmake
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
endif()

################################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the 3rd-party configuration
################################################################################
if (${PARENT}_SUBMODULE_TEMPLATE_LIBRARY)
    add_subdirectory(TemplateLibrary)
endif()
```

File **3rdparty/CMakeLists.txt** adds folder **TemplateLibrary** to your project and excludes test application and example (TemplateLibrary class test applications and example of custom TemplateLibrary class implementation) from compiling. Your repository new structure will be:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
3rdparty
    CMakeLists.txt
    TemplateLibrary
```

Next you need include folder 3rdparty in main **CMakeLists.txt** file of your repository. Add string at the end of your main **CMakeLists.txt**:

```cmake
add_subdirectory(3rdparty)
```

Next you have to include **TemplateLibrary** library in your **src/CMakeLists.txt** file:

```cmake
target_link_libraries(${PROJECT_NAME} TemplateLibrary)
```

Done!
