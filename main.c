#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <math.h>

#include <_gl.h>
#include <_cl.h>

// #include <OpenCL/opencl.h>
#include <OpenCL/cl_gl_ext.h>
#include <OpenGL/CGLDevice.h>
#include <OpenGL/CGLCurrent.h>

#include <mlx.h>
#include <signal.h>

#define ANGLE M_PI / 10000000
#define RADIUS 1

void		windows_init(struct s_mlx_context *mc)
{
	mc->windows[0] = mlx_new_window(480, 640, "WindowA");
	mc->windows[1] = mlx_new_window(640, 480, "WindowB");
	mc->windows[2] = mlx_new_window(640, 640, "WindowC");

	for (unsigned int i = 0; i < mc->window_nbr; ++i)
	{
		apply_callback(mc->windows[i], &g_callback);
	}
}

void		destroy_window(struct s_mlx_context *mc, t_window **w)
{
	(void)mc;
	(void)w;
	printf("mlx_destroy_window\n");
	mc->window_nbr -= 1;
}

void focus_test(GLFWwindow *w, int i);
void destroy_callback(GLFWwindow *window);

t_callback g_callback = (t_callback){
	/* error */				error_callback,

	/* windowpos */			NULL,
	/* windowsize */		resize_callback,
	/* windowclose */		destroy_callback,
	/* windowrefresh */		NULL,
	/* windowfocus */		focus_test,
	/* windowiconify */		NULL,
	/* framebuffersize */	NULL,

	/* mousebutton */		mouse_button_callback,
	/* cursorpos */			NULL,
	/* cursorenter */		NULL,
	/* scroll */			scroll_callback,
	/* key */				key_callback,
	/* uchar */				NULL,
	/* charmods */			NULL,
	/* drop */				NULL,
	/* joystick */			NULL,

	/* initearly */			NULL,
	/* initlate */			windows_init,
	/* mlxwindowclose */	destroy_window,
	/* mlxwindowresize */	NULL
} ;

int main()
{
	struct s_mlx_context *mc = mlx_init();

	while (mc->window_nbr)
	{
		for (unsigned int i = 0; i < WINDOW_MAX; ++i)
		{
			if (mc->windows[i])
				render(mc->windows[i]);
		}

		glfwPollEvents();
	}

	return (0);
}
