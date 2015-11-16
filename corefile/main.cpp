#include "dll_hello_world.h"
#include <exception>
#include <string>
#include <iostream>
#include <Windows.h>


class DllFile
{
	typedef const char *(*CreateCallBack)();  
	CreateCallBack call_function;
	HINSTANCE dll_core;
public:
	DllFile(const std::string &dll_filename)
	try
	{
		dll_core = LoadLibrary(dll_filename.data());

		if (dll_core == 0)
		{
			throw std::exception("load Dll not success.");
		}
	}
	catch(std::exception &e)
	{
		FreeLibrary(dll_core);
		throw ;
	}
	catch(...)
	{
		FreeLibrary(dll_core);
		throw std::exception("initial DLL false.");
	}

	~DllFile()
	{
		FreeLibrary(dll_core);
	}

	const char* CallFunction(const std::string &symbolname)
	{
		call_function = (CreateCallBack)GetProcAddress(dll_core, symbolname.data());  
		if (call_function == 0)
		{  
			FreeLibrary(dll_core);
			throw std::exception("can not function of DLL.");
		} 
		else
		{
			return call_function();
		}
	}
};

int main()
{  
	try
	{
		DllFile demo_file("dllfile1.dll");
		std::cout << demo_file.CallFunction("HelloWorld") << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
	}
	system("PAUSE");

	return 0;  
}  