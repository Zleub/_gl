#include <_gl.h>
#include <mlx.h>
#include <stdio.h>

/** The default vertices definition */
static t_vec3f base_vertices[4] = {
	{ -1., -1., 0. },
	{ -1.,  1., 0. },
	{  1.,  1., 0. },
	{  1., -1., 0. }
};
/** The default colors definition */
static t_vec3f base_colors[4] = {
	{ 1., 1., 1. },
	{ 1., 1., 1. },
	{ 1., 1., 1. },
	{ 1., 1., 1. }
};
/** The default textures definition */
static t_vec3f base_textures[4] = {
	{ 0., 1., 0 },
	{ 0., 0., 0 },
	{ 1., 0., 0 },
	{ 1., 1., 0 }
};

/**
 * Create a new window in respect of MLX's windows
 */
t_window	*new_window(t_mlx_context *mlx_context, int size_x, int size_y, char *title)
{
	t_window_list	*nw;

	nw = malloc(sizeof(t_window_list));
	bzero(nw, sizeof(t_window_list));

	if (STAILQ_EMPTY(&mlx_context->w_head))
		nw->w.w = glfwCreateWindow(size_x, size_y, title, NULL, NULL);
	else
		nw->w.w = glfwCreateWindow(size_x, size_y, title, NULL, STAILQ_FIRST(&mlx_context->w_head)->w.w);
	STAILQ_INSERT_TAIL(&mlx_context->w_head, nw, next);

	int a[2];
	glfwGetWindowSize(nw->w.w, &a[0], &a[1]);
	nw->w.size.x = a[0];
	nw->w.size.y = a[1];
	glfwGetWindowPos(nw->w.w, &a[0], &a[1]);
	nw->w.position.x = a[0];
	nw->w.position.y = a[1];

	apply_callback(&nw->w, &g_callback);
	g_callback.windowfocus(nw->w.w, 1);

	mlx_context->window_nbr += 1;
	glfwMakeContextCurrent(nw->w.w);

	bzero(&(nw->w.r), sizeof(t_renderer));
	nw->w.r.v_pos = base_vertices;
	nw->w.r.v_col = base_colors;
	nw->w.r.v_tex = base_textures;
	nw->w.r.vertices_nbr = 4;
	nw->w.r.window_size = (t_vec2i){ size_x, size_y };

	init_renderer(&(nw->w.r));
	nw->w.r.mode = mlx_context->mode;
	glfwMakeContextCurrent(0);

	// printf("%p\n", nw);
	// printf("%p vs %p\n", &nw, &nw->w);
	return (&nw->w);
}

/**
 * \todo Need to be reworked
 * Clears a #t_window
 */
int		clear_window(t_mlx_context *mlx_context, t_window *window)
{
	(void)mlx_context;

	glfwMakeContextCurrent(window->w);
	glBindTexture(GL_TEXTURE_2D, window->r.texture);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	t_renderer *r = &window->r;
	t_vec4f emptyData[X_SIZE * Y_SIZE];
	bzero(emptyData, sizeof(t_vec4f) * X_SIZE * Y_SIZE);
	glTexSubImage2D(
		GL_TEXTURE_2D,
		0,
		0,
		0,
		X_SIZE,
		Y_SIZE,
		GL_BGRA,
		GL_UNSIGNED_BYTE,
		&emptyData[0]
	);

	return (1);
}

/**
 * \todo Need to be reworked
 * Put a pixel into a #t_window in respect to MLX's
 */
int		pixel_put(t_mlx_context *mlx_context, t_window *window, int x, int y, int color)
{
	(void)mlx_context;

	glfwMakeContextCurrent(window->w);
	// glBindTexture(GL_TEXTURE_2D, window->r.texture);

	t_renderer *r = &window->r;
	(void)r;
	int w = X_SIZE;
	int h = Y_SIZE;
	int size = w * h ;

	t_vec4f *img = malloc(sizeof(t_vec4f) * size);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, img);

	unsigned int c = color;
	img[x + y * w] = (t_vec4f){
		((0xff000000 & c) >> 24) / 255. ,
		((0xff0000 & c) >> 16) / 255. ,
		((0xff00 & c) >> 8) / 255. ,
		((0xff & c)) / 255.
	};
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_FLOAT, img);
	free(img);
	return (1);

}
