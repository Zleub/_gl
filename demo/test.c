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

int g(int button,int x,int y,void *param)
{
	(void)param;
	printf("[%d] %d %d\n", button, x, y);
	return (0);
}

int main()
{
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

	mlx_put_image_to_window(mlx, window[0], image, 0, 0);

	mlx_loop_hook(mlx, f, NULL);
	mlx_mouse_hook(window[0], g, NULL);
	mlx_loop(mlx);
	return 0;
}
