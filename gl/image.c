#include <_gl.h>
#include <mlx.h>

/**
 * Creates a new #t_image based on the MLX image's format.
 */
void		*new_image(t_context *mlx_context, int width, int height)
{
	t_image *ni;

	ni = malloc(sizeof(t_image));
	bzero(ni, sizeof(t_image));
	ni->size.x = width;
	ni->size.y = height;
	ni->data = malloc(width * height * sizeof(int));
	bzero(ni->data, width * height * sizeof(int));
	STAILQ_INSERT_TAIL(&mlx_context->i_head, ni, next);
	return (ni);
}

/**
 * Unwrap the data address from a #t_image.
 */
char	*get_data_addr(t_image *image, int *bits_per_pixel, int *size_line, int *endian)
{
	*bits_per_pixel = sizeof(int) * 8;
	*size_line = image->size.x * sizeof(int);
	*endian = 0;
	return (image->data);
}

/**
 * Put a #t_image to a #t_window.
 */
int		put_image_to_window(t_context *mlx_context, t_window *window, t_image *image, int x, int y)
{
	(void)mlx_context;

	unsigned int tmp_tex;

	glfwMakeContextCurrent(window->w);
	glGenTextures(1, &tmp_tex);
	glBindTexture(GL_TEXTURE_2D, window->r.texture);
	glTexSubImage2D(
		GL_TEXTURE_2D,
		0,
		x,
		y,
		image->size.x,
		image->size.y,
		GL_BGRA,
		GL_UNSIGNED_BYTE,
		image->data
	);
	return (1);
}

/**
 * Batch apply of a #t_callback on a #t_window
 * \todo Find out a better way to achieve that
 */
void	apply_callback(t_window *window, t_callback *callback)
{
	glfwSetErrorCallback(callback->error);

	glfwSetWindowPosCallback(window->w, callback->windowpos);
	glfwSetWindowSizeCallback(window->w, callback->windowsize);
	glfwSetWindowCloseCallback(window->w, callback->windowclose);
	glfwSetWindowRefreshCallback(window->w, callback->windowrefresh);
	glfwSetWindowFocusCallback(window->w, callback->windowfocus);
	glfwSetWindowIconifyCallback(window->w, callback->windowiconify);
	glfwSetFramebufferSizeCallback(window->w, callback->framebuffersize);

	glfwSetKeyCallback(window->w, callback->key);
	glfwSetCharCallback(window->w, callback->uchar);
	glfwSetCharModsCallback(window->w, callback->charmods);
	glfwSetMouseButtonCallback(window->w, callback->mousebutton);
	glfwSetCursorPosCallback(window->w, callback->cursorpos);
	glfwSetCursorEnterCallback(window->w, callback->cursorenter);
	glfwSetScrollCallback(window->w, callback->scroll);
	glfwSetDropCallback(window->w, callback->drop);

	glfwSetJoystickCallback(callback->joystick);
}
