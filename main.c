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

#define VIDMODE SMALLEST_PLUS

void		windows_init_late(struct s_mlx_context *mc)
{
	int count ;
	const GLFWvidmode * vidmodes = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);

	mc->vidmode_size.width = 640;
	mc->vidmode_size.height = 480;
	mc->screen_size.width = 640;
	mc->screen_size.height = 480;
	if (count == WSLEN) {
		mc->vidmode_size.width = vidmodes[VIDMODE].width;
		mc->vidmode_size.height = vidmodes[VIDMODE].height;
		mc->screen_size.width = vidmodes[FULLSCREEN].width;
		mc->screen_size.height = vidmodes[FULLSCREEN].height;
	}

	mlx_new_window(mc->vidmode_size.width, mc->vidmode_size.height, "WindowA");
	mlx_new_window(mc->vidmode_size.width, mc->vidmode_size.height, "WindowB");
	mlx_new_window(mc->vidmode_size.width, mc->vidmode_size.height, "WindowC");

	(void)mc;
}

void		destroy_window(struct s_mlx_context *mc, t_window *w)
{
	(void)mc;
	(void)w;
	printf("MLX destroy callback\n");
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
	/* initlate */			windows_init_late,
	/* mlxwindowclose */	destroy_window,
	/* mlxwindowresize */	NULL
} ;

void debug_window(t_window *w)
{
	printf("[");
	printf("%p", w);
	printf("]\n");
}


int main()
{
	struct s_mlx_context *mc = mlx_init();

	while (mc->window_nbr)
	{
		t_window_list *np;

		STAILQ_FOREACH(np, &mc->w_head, next) {
			if (!render(&np->w))
				break ;
		}
		glfwPollEvents();
	}
	glfwTerminate();
	return (0);
}
