#include <_gl.h>
#include <mlx.h>

void		*new_image(t_mlx_context *mlx_context, int width, int height)
{
	t_image *ni;

	ni = malloc(sizeof(t_image));
	bzero(ni, sizeof(t_image));

	ni->size.width = width;
	ni->size.height = height;
	ni->data = malloc(width * height * sizeof(int));
	bzero(ni->data, width * height * sizeof(int));
	glGenTextures(1, &ni->ref);

	STAILQ_INSERT_TAIL(&mlx_context->i_head, ni, next);
	return (ni);
}

char	*get_data_addr(t_image *image, int *bits_per_pixel, int *size_line, int *endian)
{
	*bits_per_pixel = sizeof(int) * 8;
	*size_line = image->size.width * sizeof(int);
	*endian = 0;

	return (image->data);
}

int		put_image_to_window(t_mlx_context *mlx_context, t_window *window, t_image *image, int x, int y)
{
	(void)mlx_context;
	// t_renderer *r = &window->r;
	glfwMakeContextCurrent(window->w);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->size.width, image->size.height, 0, GL_RGBA, GL_FLOAT, image->data + (x + y * image->size.width) * sizeof(int));
	return (1);
}
