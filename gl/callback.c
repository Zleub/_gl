#include <_gl.h>
#include <stdio.h>

void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)window;
	(void)key;
	(void)scancode;
	(void)action;
	(void)mods;
}

void	resize_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	(void)width;
	(void)height;
	// printf("%d, %d\n", width, height);
}

void	error_callback(int error, const char* description)
{
	(void)error;
	puts(description);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	(void)window;
	(void)button;
	(void)action;
	(void)mods;
}

extern float cam_w;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	(void)window;
	(void)xoffset;
	cam_w += yoffset / 10;
}
