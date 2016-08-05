#include <_gl.h>
#include <stdio.h>

t_window	*init(int size_x, int size_y, char *title)
{
	t_window	*w;

	if (g_callback.initearlyfun)
		g_callback.initearlyfun();
	if (!glfwInit())
		exit(EXIT_FAILURE);
	if (g_callback.initlatefun)
	{
		if (!(g_callback.initlatefun()))
			return (NULL);
	}
	w = new_window(size_x, size_y, title);
	glfwMakeContextCurrent(w->w);
	return (w);
}

t_window	*new_window(int size_x, int size_y, char *title)
{
	t_window	*nw;

	nw = malloc(sizeof(t_window));
	bzero(nw, sizeof(t_window));

	nw->w = glfwCreateWindow(size_x, size_y, title, NULL, NULL);
	nw->size.x = size_x;
	nw->size.y = size_y;
	return (nw);
}
