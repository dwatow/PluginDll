 #include "dll_hello_world.h"  

__declspec(dllexport)
const char* HelloWorld()
{
	return "hello world";
}  