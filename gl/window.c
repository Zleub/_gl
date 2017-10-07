#include <_gl.h>
#include <mlx.h>
#include <stdio.h>

struct s_mlx_context g_mlx_context = {
	MULTIPLE, // MONO,

	{ 0, 0 },
	{ 0, 0 },

	0,
	STAILQ_HEAD_INITIALIZER(g_mlx_context.w_head),
	STAILQ_HEAD_INITIALIZER(g_mlx_context.i_head),
	NULL,
	NULL
};

void	*init(void)
{
	if (g_callback.initearly)
		g_callback.initearly(&g_mlx_context);

	STAILQ_INIT(&g_mlx_context.w_head);
	STAILQ_INIT(&g_mlx_context.i_head);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	if (g_callback.initlate)
		g_callback.initlate(&g_mlx_context);

	return (&g_mlx_context);
}

static t_vec3f base_vertices[4] = {
	{ -1., -1., 0. },
	{ -1.,  1., 0. },
	{  1.,  1., 0. },
	{  1., -1., 0. }
};
static t_vec3f base_colors[4] = {
	{ 1., 1., 1. },
	{ 1., 1., 1. },
	{ 1., 1., 1. },
	{ 1., 1., 1. }
};
static t_vec3f base_textures[4] = {
	{ 0., 1., 0 },
	{ 0., 0., 0 },
	{ 1., 0., 0 },
	{ 1., 1., 0 }
};

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
 * Need to be reworked
 */
int		clear_window(t_mlx_context *mlx_context, t_window *window)
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

	for (int i = 0; i < size; ++i)
	{
		img[i] = (t_vec4f){ 0., 0., 0., 0. };
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_FLOAT, img);
	free(img);
	return (1);
}

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
