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

void	init_fps(t_fps *fps)
{
	fps->frames = 0;
	fps->t1 = glfwGetTime();
	fps->t2 = glfwGetTime();
}

void	run_fps(t_window *window, t_fps *fps)
{
	fps->frames += 1;
	fps->t2 = glfwGetTime();
	fps->dt = (fps->t2 - fps->t1) * 1000;
	fps->t += fps->dt;
	if (fps->t2 - fps->t >= 1.0) {
		bzero(fps->str, 12);

		sprintf(fps->str, "%.0f", fps->frames);
		glfwSetWindowTitle(window->w, fps->str);
		fps->t = fps->t2;
		fps->frames = 0;
	}
}
