#include <string>
#include <cstdint>
#include "ConfigReader.h"



namespace cr
{
namespace templ
{



/**
 * @brief Mask for template library params for encoding (serializing).
 */
typedef struct TemplateLibraryParamsMask {
    bool firstParam{ true };
    bool secondParam{ true };
    bool thirdParam{ true };
} TemplateLibraryParamsMask;



/**
 * @brief Class of template library parameters.
 */
class TemplateLibraryParams
{
public:

    /// First param. Here describe what status does this flag define.
    bool firstParam{ false };
    /// Second param. Here describe nuances and param value vaid range.
    int secondParam{ 0 };
    /// Third param. Here describe nuances and param value vaid range.
    float thirdParam{ 0.0f };

    /// Macro from ConfigReader to make params readable/writable from JSON.
    JSON_READABLE(TemplateLibraryParams, firstParam, secondParam, thirdParam)

    /// operator =
    TemplateLibraryParams& operator= (const TemplateLibraryParams& src);

    /**
     * @brief Encode (serialize) params.
     * @param data Pointer to buffer to store serialized params.
     * @param  bufferSize Size of buffer.
     * @param size Size of encoded (serialized) data. Will be <= bufferSize.
     * @param mask Pointer to mask structure. Used to exclude particular
     * params from encoding (from serialization).
     * @return TRUE if params ecnoded (serialized) or FALSE if:
     * 1. bufferSize less tha size of serialized params.
     * 2. Can be other errors depends on implementation.
     */
    bool encode(uint8_t* data, int bufferSize, int& size,
                TemplateLibraryParamsMask* mask = nullptr);

    /**
     * @brief Decode (deserialize) params.
     * @param data Pointer to buffer with encoded (serialized) params.
     * @param dataSize Size of encoded (serialized) params.
     * @return TRUE if params decoded, FALSE otherwise.
     */
    bool decode(uint8_t* data, int dataSize);
};



/**
 * @brief Enum of template library params.
 */
enum class TemplateLibraryParam
{
    /// First param. Here describe nuances and param value vaid range.
    FIRST_PARAM = 1,
    /// Second param. Here describe nuances and param value vaid range.
    SECOND_PARAM,
    /// Third param. Here describe nuances and param value vaid range.
    THIRD_PARAM
};



/**
 * @brief Enum of template library commands.
 */
enum class TemplateLibraryCommand
{
    /// First command.
    FIRST_COMMAND = 1,
    /// Second command.
    SECOND_COMMAND,
    /// Third command.
    THIRD_COMMAND
};



/**
 * @brief Library template class with various methods.
 */
class TemplateLibrary {
public:

    /**
     * @brief Class constructor.
     */
    TemplateLibrary();

    /**
     * @brief Class destructor.
     */
    ~TemplateLibrary();

    /**
     * @brief Get the version of the TemplateLibrary class.
     * @return A string representing the version: "Major.Minor.Patch"
     */
    static std::string getVersion();

    /**
     * @brief Set the value for a specific library parameter.
     * @param id The identifier of the library parameter.
     * @param value The value to set for the parameter.
     * @return TRUE if the parameter was successfully set, FALSE otherwise.
     */
    bool setParam(TemplateLibraryParam id, float value);

    /**
     * @brief Get the value of a specific library parameter.
     * @param id The identifier of the library parameter.
     * @return The value of the specified parameter.
     */
    float getParam(TemplateLibraryParam id);

    /**
     * @brief Get the structure containing all library parameters.
     * @param params Reference to a TemplateParams structure.
     */
    void getParams(TemplateLibraryParams& params);

    /**
     * @brief Execute a template command.
     * @param id The identifier of the library command to be executed.
     * @return TRUE if the command was executed successfully, FALSE otherwise.
     */
    bool executeCommand(TemplateLibraryCommand id);

    /**
     * @brief Any useful method of library.
     * @param value Output value.
     * @return TRUE of success, FALSE otherwise.
     */
    bool doSomething(int& value);

private:

    /// Library parameters structure.
    TemplateLibraryParams m_params;
    /// Any private variable.
    int m_variable{ 0 };
};


}
}