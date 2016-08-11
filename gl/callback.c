#include <_gl.h>
#include <mlx.h>
#include <stdio.h>

extern struct s_mlx_context g_mlx_context;
extern float cam_w;
t_vec3f mouse ;

typedef void(*t_key_function)(int key) ;

void dummy(int key)
{
	printf("dummy %d\n", key);
}

void switch_mlx_mode(int key)
{
	(void)key;

	if (g_mlx_context.active_window->r.mode == MONO)
		g_mlx_context.active_window->r.mode = MULTIPLE;
	else
		g_mlx_context.active_window->r.mode = MONO;

}

static t_key_function key_array[350] = {
	[GLFW_KEY_1] = dummy,
	[GLFW_KEY_2] = dummy,
	[GLFW_KEY_3] = dummy,
	[GLFW_KEY_4] = dummy,
	[GLFW_KEY_5] = dummy,
	[GLFW_KEY_6] = dummy,
	[GLFW_KEY_7] = dummy,
	[GLFW_KEY_8] = dummy,

	[GLFW_KEY_KP_1] = dummy,
	[GLFW_KEY_KP_2] = dummy,
	[GLFW_KEY_KP_3] = dummy,
	[GLFW_KEY_KP_4] = dummy,
	[GLFW_KEY_KP_5] = dummy,
	[GLFW_KEY_KP_6] = dummy,
	[GLFW_KEY_KP_7] = dummy,
	[GLFW_KEY_KP_8] = dummy,

	[GLFW_KEY_M] = switch_mlx_mode
} ;

void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)window;
	(void)key;
	(void)scancode;
	(void)action;
	(void)mods;
	if (action != 0) return ;

	if (key_array[key]) {
		return key_array[key](key);
	}
}

void destroy_callback(GLFWwindow *window)
{
	unsigned int i;

	i = 0;
	while (i < WINDOW_MAX)
	{
		if (g_mlx_context.windows[i]
			&& g_mlx_context.windows[i]->w == window
			&& g_callback.mlxwindowclose) {
				glfwMakeContextCurrent(0);
				glfwDestroyWindow(g_mlx_context.windows[i]->w);
				free(g_mlx_context.windows[i]);
				g_mlx_context.windows[i] = 0;
			return g_callback.mlxwindowclose(&g_mlx_context, &g_mlx_context.windows[i]);
		}
		i += 1;
	}
}

void		focus_test(GLFWwindow *w, int action)
{
	unsigned int i;

	i = 0;
	(void)action;
	while (i < WINDOW_MAX)
	{
		if (g_mlx_context.windows[i]
			&& g_mlx_context.windows[i]->w == w
			&& g_callback.mlxwindowclose) {
			g_mlx_context.active_window = g_mlx_context.windows[i];
			return ;
		}
		i += 1;
	}
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

void	mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	(void)window;
	(void)button;
	(void)action;
	(void)mods;
	printf("%d\n", button);
	int width ;
	int height ;

	glfwGetWindowSize(window, &width, &height);

	if (button == 0)
	{
		struct { double x ; double y ; } moused;

		glfwGetCursorPos(window, &moused.x, &moused.y);

		moused.x = (moused.x - width / 2) / width;
		moused.y = (height / 2 - moused.y) / height;

		mouse = (t_vec3f){
			.x = (float)moused.x * (float)cam_w,
			.y = (float)moused.y * (float)cam_w,
			.z = 0.
		};
	}
}

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
