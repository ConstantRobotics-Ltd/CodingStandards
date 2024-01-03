#include <iostream>
#include "TemplateLibrary.h"



int main(void)
{
	// Create library object.
	cr::templ::TemplateLibrary lib;

	// Execute commands.
	lib.executeCommand(cr::templ::TemplateLibraryCommand::FIRST_COMMAND);
	lib.executeCommand(cr::templ::TemplateLibraryCommand::SECOND_COMMAND);
	lib.executeCommand(cr::templ::TemplateLibraryCommand::THIRD_COMMAND);

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