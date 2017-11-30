#include <stdio.h>
#include <mlx.h>

void *mlx;
void *window[2];
void *image;
char *data;

int f(void *p)
{
	static int count;

	(void)p;
	// mlx_clear_window(mlx, window);
	// mlx_put_image_to_window(mlx, window, image, count / 100, 0);
	count += 1;
	return (1);
}

struct {
	int x;
	int y;
	int x_origin;
	int y_origin;
}	_drag;

int _loop(struct {
	void *param;
	double time;
	t_window *window;
} *param) {
	#ifdef _GL

		struct { int x; int y; } pos;
		glfwGetWindowPos(param->window->w, &pos.x, &pos.y);
		glfwGetWindowPos(param->window->w, &pos.x, &pos.y);

		mlx_clear_window(mlx, param->window);
		mlx_put_image_to_window(mlx, param->window, image, _drag.x - pos.x, _drag.y - pos.y);

	#else

		mlx_clear_window(mlx, param->window);
		mlx_put_image_to_window(mlx, param->window, image, _drag.x, _drag.y);

	#endif

	return (0);
}

int drag(int x,int y,void *param)
{
	(void)param;
	_drag.x -= _drag.x_origin - x;
	_drag.y -= _drag.y_origin - y;


	_drag.x_origin = x;
	_drag.y_origin = y;
	return (0);
}

int press(int button,int x,int y,void *param)
{
	(void)button;
	(void)param;
	_drag.x_origin = x;
	_drag.y_origin = y;
	mlx_hook(window[0], 6, 0, drag, NULL);
	return (0);
}

int release(int button,int x,int y,void *param)
{
	(void)button;
	(void)x;
	(void)y;
	(void)param;
	mlx_hook(window[0], 6, 0, NULL, NULL);
	return (0);
}

int main()
{
	_drag.x_origin = 0;
	_drag.y_origin = 0;
	mlx = mlx_init();
	window[0] = mlx_new_window(mlx, 800, 600, "1");
	window[1] = mlx_new_window(mlx, 800, 600, "2");
	image = mlx_new_image(mlx, 100, 100);
	struct {
		int bits_per_pixel;
		int size_line;
		int endian;
	} dt ;
	data = mlx_get_data_addr(image, &dt.bits_per_pixel, &dt.size_line, &dt.endian);

	for (int i = 0; i < (100 * 100); i += 1)
	{
		((int*)data)[i] = 0x00FF0000 - (i / (100 * 100) * 0x00FF0000);
	}

	#ifdef _GL
	glfwGetWindowPos(((t_window *)window[0])->w, &_drag.x, &_drag.y);
	#endif
	mlx_put_image_to_window(mlx, window[0], image, _drag.x_origin, _drag.y_origin);

	mlx_loop_hook(mlx, _loop, NULL);
	// mlx_mouse_hook(window[0], g, NULL);
	mlx_hook(window[0], 4, 0, press, NULL);
	mlx_hook(window[0], 5, 0, release, NULL);
	mlx_loop(mlx);
	return 0;
}
