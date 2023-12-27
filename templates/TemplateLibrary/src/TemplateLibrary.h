#include <string>
#include "ConfigReader.h"

namespace cr
{
namespace templ
{

struct TemplateParamsMask
{
    bool firstParam{ true };
    bool secondParam{ true };
    bool thirdParam{ true };
};


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


enum class TemplateParam
{
    /// First template param.
    FIRST_PARAM = 1,
    /// Second template param.
    SECOND_PARAM,
    /// Third template param.
    THIRD_PARAM
};

enum class TemplateCommand
{
    /// First command.
    FIRST_COMMAND = 1,
    /// Second command.
    SECOND_COMMAND,
    /// Third command.
    THIRD_COMMAND
};

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

}
}
