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

void lx_new_window(int key)
{
	(void)key;
	new_window(g_mlx_context.vidmode_size.width, g_mlx_context.vidmode_size.height, "test");
}

void debug(int key)
{
	(void)key;
	printf("debug\n");
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

	// [GLFW_KEY_Q] = dummy,
	// [GLFW_KEY_D] = debug,
	[GLFW_KEY_N] = lx_new_window,
	// [GLFW_KEY_M] = switch_mlx_mode
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

void	destroy_callback(GLFWwindow *window)
{
	struct s_window_list *np;

	(void)window;
	printf("GLFW destroy callback\n");
	STAILQ_FOREACH(np, &g_mlx_context.w_head, next) {
		if (np->w.w == window)
			// printf("I got the window\n");
			g_callback.mlxwindowclose(&g_mlx_context, &np->w);
	}
}

void		focus_test(GLFWwindow *w, int action)
{
	(void)w;
	(void)action;
}


void	resize_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	(void)width;
	(void)height;
	printf("size: %d, %d\n", width, height);
	printf("size ratio: %f, %f\n",
		(double)width / (double)g_mlx_context.screen_size.width,
		(double)height / (double)g_mlx_context.screen_size.height
	);

	int x, y;
	glfwGetWindowPos(window, &x, &y);
	printf("pos: %d, %d\n", x, y);
	printf("pos ratio: %f, %f\n",
		(double)x / (double)g_mlx_context.screen_size.width,
		(double)y / (double)g_mlx_context.screen_size.height
	);

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
			(float)moused.x * (float)cam_w,
			(float)moused.y * (float)cam_w,
			0.
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
