/*
* @Author: adebray
* @Date:   2016-09-02 23:36:06
* @Last Modified by:   Zleub
* @Last Modified time: 2016-09-04 05:19:38
*/

#include <stdio.h>
#include <mlx.h>

void *mlx;
void *window[2];
void *image[3];
char *data[3];

int f(void *p)
{
	static int count;

	(void)p;
	mlx_clear_window(mlx, window[0]);
	mlx_put_image_to_window(mlx, window[0], image[0], count / 100, 0);
	count += 1;

	return (1);
}

int main()
{
	mlx = mlx_init();
	window[0] = mlx_new_window(mlx, 800, 600, "Hello1");
	// window[1] = mlx_new_window(mlx, 800, 600, "Hello2");
	image[0] = mlx_new_image(mlx, 100, 100);
	image[1] = mlx_new_image(mlx, 100, 100);
	image[2] = mlx_new_image(mlx, 100, 100);
	struct {
		int bits_per_pixel;
		int size_line;
		int endian;
	} dt ;
	data[0] = mlx_get_data_addr(image[0], &dt.bits_per_pixel, &dt.size_line, &dt.endian);
	printf("%d, %d, %d\n", dt.bits_per_pixel, dt.size_line, dt.endian);
	data[1] = mlx_get_data_addr(image[1], &dt.bits_per_pixel, &dt.size_line, &dt.endian);
	printf("%d, %d, %d\n", dt.bits_per_pixel, dt.size_line, dt.endian);
	data[2] = mlx_get_data_addr(image[2], &dt.bits_per_pixel, &dt.size_line, &dt.endian);
	printf("%d, %d, %d\n", dt.bits_per_pixel, dt.size_line, dt.endian);

	for (int i = 0; i < (100 * 100); i += 1)
	{
		((int*)data[0])[i] = 0x00FF0000;
		((int*)data[1])[i] = 0x0000FF00;
		((int*)data[2])[i] = 0x000000FF;
	}
	((int*)data[0])[0] = 0x00FF00FF;

	mlx_put_image_to_window(mlx, window[0], image[0], 0, 0);
	mlx_put_image_to_window(mlx, window[0], image[1], 100, 0);
	mlx_put_image_to_window(mlx, window[0], image[2], 0, 100);
	// mlx_put_image_to_window(mlx, window[1], image[2], 0, 100);


	// mlx_loop_hook(mlx, f, NULL);
	mlx_loop(mlx);
	return 0;
}
