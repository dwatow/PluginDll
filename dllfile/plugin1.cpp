#include "plugin1.h"

IRenderer * CreateRenderer()
{
	return new OpenGLRenderer;
}

void DestroyRenderer( IRenderer *r )
{
	delete r;
}

const char* DisplayName()
{
	return "OpenGL Renderer";
}
