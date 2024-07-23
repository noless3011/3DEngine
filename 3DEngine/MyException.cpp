#include "stdafx.h"
#include "MyException.h"

DWORD MyException::Win32FromHResult(HRESULT hr)
{
	if ((hr & 0xFFFF0000) == MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, 0))
	{
		return HRESULT_CODE(hr);
	}
	if (hr == S_OK)
	{
		return ERROR_SUCCESS;
	}
	// Not a Win32 HRESULT so return a generic error code
	return ERROR_CAN_NOT_COMPLETE;
}

MyException::MyException(HRESULT Hresult, const char* file, int line)
{
	hr = Hresult;
	MyException::file = std::string(file);
	MyException::line = line;
}

MyException::~MyException()
{
}

void MyException::CheckResult(HRESULT hr)
{
}

std::string MyException::GetMessage() {
	std::string strMessage;

	LPSTR buffer = nullptr;
	DWORD length = FormatMessageA(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		hr,
		0,
		(LPSTR)&buffer,
		0,
		NULL);
	if (length > 0 && buffer != nullptr)
	{
		// Append the formatted message to the string
		strMessage.append(buffer, length);
		// Free the buffer allocated by FormatMessage
		LocalFree(buffer);
	}

	strMessage.append(" [At file: ");
	strMessage.append(file);
	strMessage.append("] [At line: ");
	strMessage.append(std::to_string(line));
	strMessage.append("]");
	return strMessage;
}

HRESULT MyException::GetID()
{
	return hr;
}

EngineException::EngineException()
{
}

EngineException::~EngineException()
{
}