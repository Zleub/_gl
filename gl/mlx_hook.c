#include <_gl.h>
#include <mlx.h>
#include <stdio.h>

/**
 * The loop_callback setter
 * \todo Handle param
 */
int		mouse_hook(t_window *window, int (*f)(), void *param )
{
	(void)window;
	(void)param;
	g_callback.mlxmousebutton = f;
	return (0);
}

/**
 * The loop_callback setter
 * \todo Handle param
 */
void	loop_hook(t_mlx_context *mlx_context, int (*f)(), void *param )
{
	(void)mlx_context;
	(void)param;
	g_callback.loop = f;
}

enum events {
	flagsChanged = 2 | 3,
	keyDown = 2,
	keyUp = 3,
	mouseDown = 4,
	rightMouseDown = 4,
	otherMouseDown = 4,
	mouseUp = 5,
	rightMouseUp = 5,
	otherMouseUp = 5,
	mouseMoved = 6,
	mouseDragged = 6,
	rightMouseDragged = 6,
	otherMouseDragged = 6,
	scrollWheel = 4,
	exposeNotification = 12,
	closeNotification = 17,
};

extern struct {
	int n;
	int(*f)();
	void *p;
}	event_table[];

/**
 * Generic event setter.
 */
void hook(t_window *window, int x_event, int x_mask, int (*f)(), void * param )
{
	(void)window;
	(void)x_event;
	(void)x_mask;
	(void)f;
	(void)param;
	printf("%s\n", __func__);
	int i = 0;
	while (event_table[i].n != -1)
	{
		if (event_table[i].n == x_event)
		{
			printf("setting up %d\n", i);
			event_table[i].f = f;
			event_table[i].p = param;
		}
		i += 1;
	}
}
