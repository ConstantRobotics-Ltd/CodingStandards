#include <iostream>
#include "TemplateLibrary.h"



int main(void)
{
	// Create library object.
	cr::templ::TemplateLibrary lib;

	// Set params.
	lib.setParam(cr::templ::TemplateLibraryParam::FIRST_PARAM, 1.0f);
	lib.setParam(cr::templ::TemplateLibraryParam::SECOND_PARAM, 2.0f);
	lib.setParam(cr::templ::TemplateLibraryParam::THIRD_PARAM, 2.0f);

	// Display params.
	std::cout << lib.getParam(cr::templ::TemplateLibraryParam::FIRST_PARAM) << std::endl;
	std::cout << lib.getParam(cr::templ::TemplateLibraryParam::SECOND_PARAM) << std::endl;
	std::cout << lib.getParam(cr::templ::TemplateLibraryParam::THIRD_PARAM) << std::endl;

	// Execute commands.
	lib.executeCommand(cr::templ::TemplateLibraryCommand::FIRST_COMMAND);
	lib.executeCommand(cr::templ::TemplateLibraryCommand::SECOND_COMMAND);
	lib.executeCommand(cr::templ::TemplateLibraryCommand::THIRD_COMMAND);

	// Get params.
	cr::templ::TemplateLibraryParams params;
	lib.getParams(params);

	// Display params.
	std::cout << std::string(params.firstParam ? "true" : "false") << std::endl;
	std::cout << params.secondParam << std::endl;
	std::cout << params.thirdParam << std::endl;

	// Do something.
	std::cout << "Do something:" << std::endl;
	for (int i = 0; i < 10; ++i)
	{
		int value = 0;
		lib.doSomething(value);
		std::cout << "Value: " << value << std::endl;
	}

	return 0;
}