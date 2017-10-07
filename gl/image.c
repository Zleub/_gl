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
	size_t pixel_nb = width*height;
	while (pixel_nb--) ((int*)ni->data)[pixel_nb] = 0xFF000000;
	// glGenTextures(1, &ni->ref);
	// printf("%s: glGenTextures %d\n", __func__, ni->ref);
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
	(void)x;
	(void)y;
	(void)image;
	(void)mlx_context;

	unsigned int tmp_tex;

	// t_renderer *r = &window->r;
	glfwMakeContextCurrent(window->w);

	glGenTextures(1, &tmp_tex);
	glBindTexture(GL_TEXTURE_2D, window->r.texture);
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, image->size.width, image->size.height, GL_BGRA, GL_UNSIGNED_BYTE, image->data);
	// glTexImage2D(
	// 	/* target */ GL_TEXTURE_2D,
	// 	/* level */ 0,
	// 	/* internalFormat */ GL_RGBA,
	// 	/* width */ image->size.width,
	// 	/* height */ image->size.height,
	// 	/* border */ 0,
	// 	/* format */ GL_BGRA,
	// 	/* type */ GL_UNSIGNED_BYTE,
	// 	/* data */ image->data
	// );
	return (1);
}
