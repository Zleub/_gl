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
	printf("%d, %d\n", width, height);
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
	printf("%d\n", button);
}

extern float cam_w;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	(void)window;
	(void)xoffset;
	cam_w += yoffset / 10;
}

void apply_callback(t_window *window, t_callback *callback)
{
	glfwSetErrorCallback(callback->error);

	glfwSetWindowPosCallback(window->w, callback->windowpos);
	glfwSetWindowSizeCallback(window->w, callback->windowsize);
	glfwSetWindowCloseCallback(window->w, callback->windowclose);
	glfwSetWindowRefreshCallback(window->w, callback->windowrefresh);
	glfwSetWindowFocusCallback(window->w, callback->windowfocus);
	glfwSetWindowIconifyCallback(window->w, callback->windowiconify);
	glfwSetFramebufferSizeCallback(window->w, callback->framebuffersize);

	glfwSetKeyCallback(window->w, callback->key);
	glfwSetCharCallback(window->w, callback->uchar);
	glfwSetCharModsCallback(window->w, callback->charmods);
	glfwSetMouseButtonCallback(window->w, callback->mousebutton);
	glfwSetCursorPosCallback(window->w, callback->cursorpos);
	glfwSetCursorEnterCallback(window->w, callback->cursorenter);
	glfwSetScrollCallback(window->w, callback->scroll);
	glfwSetDropCallback(window->w, callback->drop);

	glfwSetJoystickCallback(callback->joystick);
}

t_callback g_callback = (t_callback){
	error_callback, // error

	NULL, // windowpos
	resize_callback, // windowsize
	NULL, // windowclose
	NULL, // windowrefresh
	NULL, // windowfocus
	NULL, // windowiconify
	NULL, // framebuffersize

	mouse_button_callback, // mousebutton
	NULL, // cursorpos
	NULL, // cursorenter
	scroll_callback, // scroll
	key_callback, // key
	NULL, // uchar
	NULL, // charmods
	NULL, // drop
	NULL // joystick
} ;
