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
	bzero(g_mlx_context.windows, sizeof(t_window *) * WINDOW_MAX);

	if (g_callback.initlatefun)
		g_callback.initlatefun(&g_mlx_context);

	return (&g_mlx_context);
}

static t_vec3f base_vertices[4] = {
	{ .x = -1., .y = -1., .z = 0. },
	{ .x = -1., .y =  1., .z = 0. },
	{ .x =  1., .y =  1., .z = 0. },
	{ .x =  1., .y = -1., .z = 0. }
};
static t_vec3f base_colors[4] = {
	{ .x = 1., .y = 1., .z = 1. },
	{ .x = 1., .y = 1., .z = 1. },
	{ .x = 1., .y = 1., .z = 1. },
	{ .x = 1., .y = 1., .z = 1. }
};
static t_vec3f base_textures[4] = {
	{ .x = 0., .y = 1., .z = 0 },
	{ .x = 0., .y = 0., .z = 0 },
	{ .x = 1., .y = 0., .z = 0 },
	{ .x = 1., .y = 1., .z = 0 }
};

static t_window *first_window;

t_window	*new_window(int size_x, int size_y, char *title)
{
	static int count = 0;
	t_window	*nw;

	nw = malloc(sizeof(t_window));
	bzero(nw, sizeof(t_window));

	if (count == 0) {
		nw->w = glfwCreateWindow(size_x, size_y, title, NULL, NULL);
		first_window = nw;
	}
	else {
		nw->w = glfwCreateWindow(size_x, size_y, title, NULL, first_window->w);
	}
	glfwGetWindowSize(nw->w, &nw->size.x, &nw->size.y);
	glfwGetWindowPos(nw->w, &nw->position.x, &nw->position.y);

	g_mlx_context.window_nbr += 1;
	glfwMakeContextCurrent(nw->w);

	bzero(&(nw->r), sizeof(t_renderer));
	nw->r.v_pos = base_vertices;
	nw->r.v_col = base_colors;
	nw->r.v_tex = base_textures;
	nw->r.vertices_nbr = 4;
	nw->r.window_size = (t_vec2i){ size_x, size_y };

	init_renderer(&(nw->r));
	glfwMakeContextCurrent(0);

	count += 1;
	return (nw);
}
