#include "TemplateLibrary.h"

int main(void)
{
	cr::templ::TemplateLibrary templateLibrary;
	templateLibrary.setParams(cr::templ::TemplateParam::FIRST_PARAM, true);
	templateLibrary.executeCommand(cr::templ::TemplateCommand::SECOND_COMMAND);
	
	cr::templ::TemplateParams params;
	templateLibrary.getParams(params);

	return 0;
}