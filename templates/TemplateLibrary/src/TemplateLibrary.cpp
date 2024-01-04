#include "TemplateLibrary.h"
#include "TemplateLibraryVersion.h"



cr::templ::TemplateLibraryParams &cr::templ::TemplateLibraryParams::operator= (const cr::templ::TemplateLibraryParams &src)
{
	// Check yourself.
    if (this == &src)
	{
		return *this;
	}

	// Copy params.
	firstParam = src.firstParam;
	secondParam = src.secondParam;
	thirdParam = src.thirdParam;

	return *this;
}



bool cr::templ::TemplateLibraryParams::encode(uint8_t* data, int bufferSize, int& size,
                cr::templ::TemplateLibraryParamsMask* mask)
{
	// Check buffer size.
	if (bufferSize < 13)
	{
		return false;
	}

	// Prepare params mask.
	TemplateLibraryParamsMask paramsMask;
	if (mask != nullptr)
	{
		paramsMask = *mask;
	}

	// Copy atributes.
	data[0] = 0x02;
    data[1] = TEMPLATE_LIBRARY_MAJOR_VERSION;
    data[2] = TEMPLATE_LIBRARY_MINOR_VERSION;

	// Fill bit mask for params.
	int pos = 3;
	data[pos] = 0x00;
    data[pos] = data[pos] | (paramsMask.firstParam ? (uint8_t)128 : (uint8_t)0);
    data[pos] = data[pos] | (paramsMask.secondParam ? (uint8_t)64 : (uint8_t)0);
    data[pos] = data[pos] | (paramsMask.thirdParam ? (uint8_t)32 : (uint8_t)0);
    pos += 1;

	// Copy params to buffer.
	if (paramsMask.firstParam)
	{
		data[pos] = firstParam ? 0x01 : 0x00;
		pos += 1;
	}

	if (paramsMask.secondParam)
	{
		memcpy(&data[pos], &secondParam, 4); pos += 4;
	}

	if (paramsMask.thirdParam)
	{
		memcpy(&data[pos], &thirdParam, 4); pos += 4;
	}

	size = pos;

	return true;
}



bool cr::templ::TemplateLibraryParams::decode(uint8_t* data, int dataSize)
{
	// Check data size.
	if (dataSize < 4)
	{
		return false;
	}

	// Check atributes.
	if (data[0] != 0x02 ||
		data[1] != TEMPLATE_LIBRARY_MAJOR_VERSION ||
		data[2] != TEMPLATE_LIBRARY_MINOR_VERSION)
	{
		return false;
	}

	// Decode params.
	int pos = 4;
    if ((data[3] & (uint8_t)128) == (uint8_t)128)
    {
		if (dataSize < pos + 1)
        {
            return false;
		}
        firstParam = data[pos] == 0x00 ? false : true;
		pos += 1;
    }
    else
    {
        firstParam = false;
    }
    if ((data[3] & (uint8_t)64) == (uint8_t)64)
    {
        if (dataSize < pos + 4)
        {
            return false;
		}
        memcpy(&secondParam, &data[pos], 4);
		pos += 4;
    }
    else
    {
        secondParam = 0;
    }
    if ((data[3] & (uint8_t)32) == (uint8_t)32)
    {
        if (dataSize < pos + 4)
        {
            return false;
		}
        memcpy(&thirdParam, &data[pos], 4);
		pos += 4;
    }
    else
    {
        thirdParam = 0.0f;
    }

	return true;
}



cr::templ::TemplateLibrary::TemplateLibrary()
{

}



cr::templ::TemplateLibrary::~TemplateLibrary()
{

}



std::string cr::templ::TemplateLibrary::getVersion()
{
	return TEMPLATE_LIBRARY_VERSION;
}



bool cr::templ::TemplateLibrary::setParam(cr::templ::TemplateLibraryParam id, float value)
{
	switch (id)
	{
	case TemplateLibraryParam::FIRST_PARAM:
	{
		if (value != 0.0f && value != 1.0f)
		{
			return false;
		}

		m_params.firstParam = value == 0.0f ? false : true;
		return true;
	}

	case TemplateLibraryParam::SECOND_PARAM:
	{
		if (value < 100.0f || value > 100.0f)
		{
			return false;
		}

		m_params.secondParam = static_cast<int>(value);
		return true;
	}

	case TemplateLibraryParam::THIRD_PARAM:
	{
		if (value < 100.0f || value > 100.0f)
		{
			return false;
		}

		m_params.thirdParam = value;
		return true;
	}

	default:
		return false;
	}

	return false;
}



float cr::templ::TemplateLibrary::getParam(cr::templ::TemplateLibraryParam id) const
{
	switch (id)
	{
	case TemplateLibraryParam::FIRST_PARAM:
	{
		return m_params.firstParam ? 1.0f : 0.0f;
	}
	case TemplateLibraryParam::SECOND_PARAM:
	{
		return static_cast<float>(m_params.secondParam);
	}
	case TemplateLibraryParam::THIRD_PARAM:
	{
		return m_params.thirdParam;
	}
	}

	return -1.0f;
}



void cr::templ::TemplateLibrary::getParams(cr::templ::TemplateLibraryParams& params) const
{
	params = m_params;
}



bool cr::templ::TemplateLibrary::executeCommand(cr::templ::TemplateLibraryCommand id)
{
	switch (id)
	{
	case TemplateLibraryCommand::FIRST_COMMAND:
	{
		m_variable = 1;
		return true;
	}

	case TemplateLibraryCommand::SECOND_COMMAND:
	{
		m_variable = 2;
		return true;
	}

	case TemplateLibraryCommand::THIRD_COMMAND:
	{
		m_variable = 3;
		return true;
	}
	
	default:
	{
		return false;
	}
	}

	return false;
}



bool cr::templ::TemplateLibrary::doSomething(int& value)
{
	value = m_variable++;
	return true;
}