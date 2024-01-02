#include "TemplateLibrary.h"

int main(void)
{
	cr::templ::TemplateLibrary templateLibrary;
	templateLibrary.executeCommand(cr::templ::TemplateCommand::FIRST_COMMAND);
	return 0;
}