#include <_gl.h>
#include <mlx.h>
#include <sys/time.h>

/**
 * Default #t_mlx_context value
 */
t_mlx_context g_mlx_context = {
	MULTIPLE,

	{ 0, 0 },
	{ 0, 0 },

	0,
	STAILQ_HEAD_INITIALIZER(g_mlx_context.w_head),
	STAILQ_HEAD_INITIALIZER(g_mlx_context.i_head),
	NULL
};

/**
 * Default #t_callback value
 */
t_callback g_callback = (t_callback){
	.error = error_callback,
	.windowpos = pos_callback,
	.windowsize = resize_callback,
	.windowclose = destroy_callback,
	.windowrefresh = NULL,
	.windowfocus = focus_test,
	.windowiconify = NULL,
	.framebuffersize = NULL,
	.mousebutton = mouse_button_callback,
	.cursorpos = cursor_pos,
	.cursorenter = NULL,
	.scroll = scroll_callback,
	.key = key_callback,
	.uchar = NULL,
	.charmods = NULL,
	.drop = NULL,
	.joystick = NULL,
	.initearly = NULL,
	.initlate = NULL,
	.earlyloop = NULL,
	.loop = NULL,
	.lateloop = NULL,
	.mlxwindowclose = NULL,
	.mlxwindowresize = NULL,
	.mlxmousebutton = NULL
} ;

struct {
	int n;
	int(*f)();
	void *p;
}	event_table[] = {
	/* 0 */ { 2, NULL, NULL },
	/* 1 */ { 3, NULL, NULL },
	/* 2 */ { 4, NULL, NULL },
	/* 3 */ { 5, NULL, NULL },
	/* 4 */ { 6, NULL, NULL },
	/* 5 */ { 12, NULL, NULL },
	/* 6 */ { 17, NULL, NULL },
	/* 7 */ { -1, NULL, NULL }
};

/**
 * Global _gl init. Calls #t_callback.initearly, #t_callback.initlate
 */
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

/**
 * Global _gl loop. Render each user's window.
 * Calls #t_callback.earlyloop, #t_callback.loop, #t_callback.lateloop
 */
int loop(t_mlx_context *mc)
{
	static double dt;
	static double time;
	struct timeval tval_before, tval_after, tval_result;

	if (g_callback.earlyloop)
		g_callback.earlyloop(mc);

	while (mc->window_nbr)
	{
		t_window_list *np;

		gettimeofday(&tval_before, NULL);
		STAILQ_FOREACH(np, &mc->w_head, next) {

			if (!render(&np->w))
				break ;

			if (g_callback.loop) {
				g_callback.loop((void*)(&time));
			}
		}

		glfwPollEvents();

		gettimeofday(&tval_after, NULL);
		timersub(&tval_after, &tval_before, &tval_result);
		dt = tval_result.tv_sec * 1000000 + tval_result.tv_usec;
		time += dt;
	}

	if (g_callback.lateloop)
		g_callback.lateloop(mc);

	return (1);
}
