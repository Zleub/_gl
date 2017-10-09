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

/**
 * \todo This ressource should not be required
 */
#define VIDMODE SMALLEST_PLUS

/**
 * \todo This ressource should not be required
 */
const GLFWvidmode * vidmodes ;
/**
 * \todo This ressource should not be required
 */
extern t_mlx_context g_mlx_context;
/**
 * \todo This ressource should not be required
 */
extern t_callback g_callback;

/**
 * Userland #init
 */
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

/**
 * Userland #destroy_callback
 */
void		destroy_window(struct s_mlx_context *mc, t_window *w)
{
	(void)mc;
	(void)w;
	printf("MLX destroy callback\n");
	mc->window_nbr -= 1;
}

/**
 * Userland #loop
 */
int loop_callback(void *param)
{
	static int time;
	double dt = *((double*)param);
	int dti = dt;
	time += dti;

	// printf("%d\n", time);
	mlx_pixel_put(&g_mlx_context, &STAILQ_FIRST(&g_mlx_context.w_head)->w, dti % 10, dti % 10, time * 127);
	// if (dti == 10) {
	// 	mlx_clear_window(&g_mlx_context, &STAILQ_FIRST(&g_mlx_context.w_head)->w);
	// }
	// else if (dti == 11) {
		// void *img = mlx_new_image(&g_mlx_context, 10, 10);
		// struct {
		// 	int bits_per_pixel;
		// 	int size_line;
		// 	int endian;
		// } img_data;
		// char *data = mlx_get_data_addr(img, &img_data.bits_per_pixel, &img_data.size_line, &img_data.endian);
	// }
	return (1);
}

int main()
{
	g_callback.initlate = windows_init_late;
	g_callback.loop = loop_callback;
	g_callback.mlxwindowclose = destroy_window;

	struct s_mlx_context *mc = mlx_init();
	mlx_loop(mc);
	glfwTerminate();
	return (0);
}
