#pragma once

class EngineException {
	EngineException();
	~EngineException();
};

class MyException : public std::exception {
public:
	MyException(HRESULT Hresult, const char* file, int line);
	~MyException();
	static void CheckResult(HRESULT hr);
	std::string GetMessage();
	HRESULT GetID();
private:
	HRESULT hr;
	int line;
	std::string file;
private:
	DWORD Win32FromHResult(HRESULT hr);
};

#define CHECK_HRESULT(hr) if (FAILED(hr)) {throw MyException(hr, __FILE__, __LINE__);}
