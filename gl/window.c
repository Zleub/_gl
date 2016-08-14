#include <_gl.h>
#include <mlx.h>
#include <stdio.h>

struct s_mlx_context g_mlx_context ;

void	*init(void)
{
	if (g_callback.initearlyfun)
		g_callback.initearlyfun(&g_mlx_context);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	bzero(&g_mlx_context, sizeof(struct s_mlx_context));
	STAILQ_INIT(&g_mlx_context.w_head);

	if (g_callback.initlatefun)
		g_callback.initlatefun(&g_mlx_context);

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

t_window	*new_window(int size_x, int size_y, char *title)
{
	t_window_list	*nw;

	if (g_mlx_context.window_nbr == WINDOW_MAX)
	{
		printf("max window reached\n");
		return (0);
	}

	nw = malloc(sizeof(t_window_list));
	bzero(nw, sizeof(t_window_list));

	nw->w.w = glfwCreateWindow(size_x, size_y, title, NULL, NULL);
	STAILQ_INSERT_TAIL(&g_mlx_context.w_head, nw, next);


	int a[2];
	glfwGetWindowSize(nw->w.w, &a[0], &a[1]);
	nw->w.size.x = a[0];
	nw->w.size.y = a[1];
	glfwGetWindowPos(nw->w.w, &a[0], &a[1]);
	nw->w.position.x = a[0];
	nw->w.position.y = a[1];

	apply_callback(&nw->w, &g_callback);
	g_callback.windowfocus(nw->w.w, 1);

	g_mlx_context.window_nbr += 1;
	glfwMakeContextCurrent(nw->w.w);

	bzero(&(nw->w.r), sizeof(t_renderer));
	nw->w.r.v_pos = base_vertices;
	nw->w.r.v_col = base_colors;
	nw->w.r.v_tex = base_textures;
	nw->w.r.vertices_nbr = 4;
	nw->w.r.window_size = (t_vec2i){ size_x, size_y };

	init_renderer(&(nw->w.r));
	glfwMakeContextCurrent(0);

	return (&nw->w);
}
