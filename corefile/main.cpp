#include "coreapi.h"
#include <string>
#include <iostream>
#include <Windows.h>


typedef IRenderer *(*CreateRendererFunc)();
typedef const char *(*RendererNameStr)() ;
//typedef void (*DestroyRendererFunc)(IRenderer *r);
//typedef FARPROC PluginFunc;

std::string LoadPlugIn(const std::string& dll_name)
{
	HINSTANCE handle = LoadLibrary(dll_name.data());
	if (handle == 0)
	{
		std::cout << "LoadLibrary is false." << std::endl;
		return "";
	}
	else
	{
		std::cout << "LoadLibrary is success." << std::endl;
	}

	CreateRendererFunc create_renderer = (CreateRendererFunc)GetProcAddress(handle, "CreateRenderer");
	RendererNameStr name_string = (RendererNameStr)GetProcAddress(handle, "DisplayName");
	std::string display_name(name_string());
	if (create_renderer == 0 || name_string == 0)
	{
		std::cout << "GetProcAddress is false." << std::endl;
		return "";
	}
	else
	{
		std::cout << "GetProcAddress is success." << std::endl;
		RendererFactory::RegisterRenderer(display_name, create_renderer);
	}
	return display_name;
}


void CallRanderer(const std::string& str)
{
	IRenderer* r = RendererFactory::CreateRenderer(str);
	r->Render();
	delete r;
}

int main()
{
	std::string dll_name1;
	std::string dll_name2;

	dll_name1 = LoadPlugIn("my_dll_code.dll");
	dll_name2 = LoadPlugIn("my_dll2.dll");

	CallRanderer(dll_name1);
	CallRanderer(dll_name2);

	system("pause");
	return 0;
}