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
    /// First template param. Here describe what status does this flag define.
    bool firstParam{ false };
    /// Second template param. Here describe what number does it store and what is the range.
    int secondParam{ 0 };
    /// Third template param. Here describe what number does it store and what is the range and why float.
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

/**
 * @brief The TemplateLibrary class provides a template library with various functionalities.
 */
class TemplateLibrary {
public:
    /**
     * @brief Constructor for the TemplateLibrary class.
     */
    TemplateLibrary();

    /**
     * @brief Destructor for the TemplateLibrary class.
     */
    ~TemplateLibrary();

    /**
     * @brief Get the version of the TemplateLibrary class.
     * @return A string representing the version.
     */
    static std::string getVersion();

    /**
     * @brief Set the value for a specific template parameter.
     * @param id The identifier of the template parameter.
     * @param value The value to set for the parameter.
     * @return True if the parameter was successfully set, false otherwise.
     */
    bool setParam(TemplateParam id, float value);

    /**
     * @brief Get the value of a specific template parameter.
     * @param id The identifier of the template parameter.
     * @return The value of the specified parameter.
     */
    float getParam(TemplateParam id);

    /**
     * @brief Get the structure containing all template parameters.
     * @param params Reference to a TemplateParams structure to store the parameters.
     */
    void getParams(TemplateParams& params);

    /**
     * @brief Execute a template command.
     * @param id The identifier of the template command to be executed.
     * @return True if the command was executed successfully, false otherwise.
     */
    bool executeCommand(TemplateCommand id);
};
}
}
