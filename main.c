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

const GLFWvidmode * vidmodes ;

void		windows_init_late(struct s_mlx_context *mc)
{
	int count = 0;
	vidmodes = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);

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

	mlx_new_window(mc, mc->vidmode_size.width, mc->vidmode_size.height, "WindowA");
	mlx_new_window(mc, mc->vidmode_size.width, mc->vidmode_size.height, "WindowB");
	mlx_new_window(mc, mc->vidmode_size.width, mc->vidmode_size.height, "WindowC");

	(void)mc;
	// printf("%p\n", mc);
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
int loop_callback(void *param);

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

	/* -------------------*/

	/* initearly */			NULL,
	/* initlate */			windows_init_late,

	/* earlyloop */			NULL,
	/* loop */				loop_callback,
	/* lateloop */			NULL,

	/* windowclose */		destroy_window,
	/* windowresize */		NULL
} ;

extern t_mlx_context g_mlx_context;

#include <sys/time.h>
int loop_callback(void *param)
{
	double dt = *((double*)param);
	int dti = dt / (1000000 / 4);

	mlx_pixel_put(&g_mlx_context, &STAILQ_FIRST(&g_mlx_context.w_head)->w, dti, 10, 0xfa000000);
	if (dti == 10) {
		mlx_clear_window(&g_mlx_context, &STAILQ_FIRST(&g_mlx_context.w_head)->w);
	}
	else if (dti == 11) {
		void *img = mlx_new_image(&g_mlx_context, 10, 10);
	}
	return (1);
}

// int mlxSetLoopCallback(t_mlx_context *mlx_context, MLXloopfun loopfun, void *param)
// {

// }

int loop(t_mlx_context *mc)
{
	static double dt;
	static double time;
	struct timeval tval_before, tval_after, tval_result;

	if (g_callback.earlyloopfun)
		g_callback.earlyloopfun(mc);

	while (mc->window_nbr)
	{
		t_window_list *np;

		gettimeofday(&tval_before, NULL);
		STAILQ_FOREACH(np, &mc->w_head, next) {

			if (!render(&np->w))
				break ;

			if (g_callback.loopfun) {
				g_callback.loopfun((void*)(&time));
			}

		}

		glfwPollEvents();

		gettimeofday(&tval_after, NULL);
		timersub(&tval_after, &tval_before, &tval_result);
		dt = tval_result.tv_sec * 1000000 + tval_result.tv_usec;
		time += dt;
	}

	if (g_callback.lateloopfun)
		g_callback.lateloopfun(mc);

	return (1);
}

int main()
{
	struct s_mlx_context *mc = mlx_init();

	mlx_loop(mc);
	glfwTerminate();
	return (0);
}
