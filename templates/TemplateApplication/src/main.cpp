#include <iostream>
#include "ConfigReader.h"
#include "TemplateApplicationVersion.h"



/// Custom parameter class.
class CustomParams
{
public:
    /// Parameter 1.
    int param1{1};
    /// Parameter 2.
    int param2{2};

    /// Declare params as readable for JSON.
    JSON_READABLE(CustomParams, param1, param2)
};



int main(void)
{
	std::cout << "TemplateApplication v" << TEMPLATE_APPLICATION_VERSION << std::endl;

	// Read params from file.
	CustomParams params;
    cr::utils::ConfigReader config;
    if(!config.readFromFile("CustomParams.json"))
    {
        // Copy params to config reader.
    	if (!config.set(params, "Params"))
    	{
    	    std::cout << "ERROR: Can't copy params" << std::endl;
    	    return -1;
    	}

    	// Create and write JSON file.
    	if (!config.writeToFile("CustomParams.json"))
    	{
    	    std::cout << "ERROR: Can't write file" << std::endl;
    	    return -1;
    	}
    }
	
	// Read values from "Params" section.
    if(!config.get(params, "Params"))
    {
        std::cout << "ERROR: Can't read params" << std::endl;
        return -1;
    }

	// Show params.
	std::cout << "param1: " << params.param1 << std::endl;
	std::cout << "param2: " << params.param2 << std::endl;

	return 0;
}