#include <_gl.h>
#include <stdio.h>

void	version(void)
{
	const unsigned char *renderer;
	const unsigned char *version;

	renderer = glGetString(GL_RENDERER);
	version = glGetString(GL_VERSION);

	printf("Compiled against GLFW %i.%i.%i\n",
		GLFW_VERSION_MAJOR,
		GLFW_VERSION_MINOR,
		GLFW_VERSION_REVISION);
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported: %s\n", version);

}
