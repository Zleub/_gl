#include <_gl.h>
#include <mlx.h>
#include <stdio.h>

/**
 * \deprecated Useless/Forgiven Usage
 */
float cam_w;
/**
 * \deprecated Useless/Forgiven Usage
 */
t_vec3f mouse ;

typedef void(*t_key_function)(int key) ;

/**
 * A dummy functions for keys events
 */
void	dummy(int key)
{
	printf("dummy %d\n", key);
}

/**
 * \deprecated Useless/Forgiven Usage
 */
void	switch_mlx_mode(int key)
{
	(void)key;

	if (g_mlx_context.active_window->r.mode == MONO)
		g_mlx_context.active_window->r.mode = MULTIPLE;
	else
		g_mlx_context.active_window->r.mode = MONO;

}

/**
 * \deprecated Useless/Forgiven Usage
 */
void	create_window(int key)
{
	(void)key;
	new_window(&g_mlx_context, g_mlx_context.vidmode_size.width, g_mlx_context.vidmode_size.height, "test");
}

/**
 * \deprecated Useless/Forgiven Usage
 */
void	debug(int key)
{
	(void)key;
	printf("debug\n");
}

/**
 * A static array for easy keys events bindings.
 *
 * \todo A duplicate should be handled by window,
 * minimized on key/value access.
 */
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
	[GLFW_KEY_N] = create_window,
	[GLFW_KEY_M] = switch_mlx_mode
} ;

/**
 * The default key callback #g_callback
 */
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

/**
 * \deprecated Useless/Forgiven Usage
 */
void	destroy_callback(GLFWwindow *window)
{
	struct s_window_list *np;

	(void)window;
	printf("GLFW destroy callback\n");
	STAILQ_FOREACH(np, &g_mlx_context.w_head, next) {
		if (np->w.w == window && g_callback.mlxwindowclose)
			g_callback.mlxwindowclose(&g_mlx_context, &np->w);
	}
}

/**
 * The handler for the GLFW focus callback
 * \todo Should trigger a userland MLX focus callback
 */
void	focus_test(GLFWwindow *window, int action)
{
	(void)window;
	(void)action;
	struct s_window_list *np;

	(void)window;
	printf("GLFW focus callback\n");
	STAILQ_FOREACH(np, &g_mlx_context.w_head, next) {
		if (np->w.w == window)
			g_mlx_context.active_window = &np->w;
	}

}

/**
 * The handler for the GLFW resize callback
 * \todo Should trigger a userland MLX resize callback
 */
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

/**
 * \deprecated Useless/Forgiven Usage
 */
void	error_callback(int error, const char* description)
{
	(void)error;
	puts(description);
}

#define PRESS 1
#define RELEASE 0

// event[2] -> flagsChanged
// event[3] -> flagsChanged
// event[2] -> keyDown
// event[3] -> keyUp
// event[4] -> mouseDown
// event[4] -> rightMouseDown
// event[4] -> otherMouseDown
// event[5] -> mouseUp
// event[5] -> rightMouseUp
// event[5] -> otherMouseUp
// event[6] -> mouseMoved
// event[6] -> mouseDragged
// event[6] -> rightMouseDragged
// event[6] -> otherMouseDragged
// event[4] -> scrollWheel
// event[12] -> exposeNotification
// event[17] -> closeNotification

extern struct {
	int n;
	int(*f)();
	void *p;
}	event_table[];

/**
 * The handler for the GLFW mouse button callback
 * \todo Should trigger a userland MLX mouse button callback
 */
void	mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	(void)window;
	(void)button;
	(void)action;
	(void)mods;
	// printf("%s: %d\n", __func__, button);
	int width ;
	int height ;

	glfwGetWindowSize(window, &width, &height);

	struct { double x ; double y ; } moused;
	glfwGetCursorPos(window, &moused.x, &moused.y);

	// printf("%d\n", action);

	if (action == 1) {
		if (g_callback.mlxmousebutton)
			g_callback.mlxmousebutton(button, moused.x, moused.y, NULL);
		if (event_table[2].f)
			event_table[2].f(button, (int)moused.x, (int)moused.y, event_table[2].p);
	}
	else if (action == 0) {
		if (event_table[3].f)
			event_table[3].f(button, (int)moused.x, (int)moused.y, event_table[3].p);
	}
}

void	cursor_pos(GLFWwindow *window, double x, double y)
{
	(void)window;
	if (event_table[4].f) {
		event_table[4].f((int)x, (int)y, event_table[4].p);
	}
}

/**
 * The handler for the GLFW scroll callback
 * \todo Should trigger a userland MLX scroll callback
 */
void	scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	(void)window;
	(void)xoffset;
	cam_w += yoffset / 10;
}

void	pos_callback(GLFWwindow*window, int x, int y)
{
	(void)x;
	(void)y;
	if (g_callback.loop)
		g_callback.loop(window);
}
