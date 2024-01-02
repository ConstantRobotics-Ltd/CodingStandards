#include "TemplateLibrary.h"
#include "TemplateLibraryVersion.h"

cr::templ::TemplateLibrary::TemplateLibrary()
{
}

cr::templ::TemplateLibrary::~TemplateLibrary()
{
}

std::string cr::templ::TemplateLibrary::getVersion()
{
	return std::string();
}

bool cr::templ::TemplateLibrary::setParam(TemplateParam id, float value)
{
	return false;
}

float cr::templ::TemplateLibrary::getParam(TemplateParam id)
{
	return 0.0f;
}

void cr::templ::TemplateLibrary::getParams(TemplateParams& params)
{
}

bool cr::templ::TemplateLibrary::executeCommand(TemplateCommand id)
{
	return false;
}
