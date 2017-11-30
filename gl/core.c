#include <_gl.h>
#include <mlx.h>
#include <sys/time.h>

/**
 * Default #t_context value
 */
t_context g_context = {
	MONO,

	{ 0, 0 },
	{ 0, 0 },

	0,
	STAILQ_HEAD_INITIALIZER(g_context.w_head),
	STAILQ_HEAD_INITIALIZER(g_context.i_head),
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

	/* -- -- */

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
		g_callback.initearly(&g_context);

	STAILQ_INIT(&g_context.w_head);
	STAILQ_INIT(&g_context.i_head);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	if (g_callback.initlate)
		g_callback.initlate(&g_context);

	return (&g_context);
}

/**
 * Global _gl loop. Render each user's window.
 * Calls #t_callback.earlyloop, #t_callback.loop, #t_callback.lateloop
 */
int loop(t_context *mc)
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

			printf("early update 1\n");
			if (!render(&np->w))
				break ;

			printf("early update 2 %p\n", g_callback.loop);
			if (g_callback.loop) {
				g_callback.loop(//(void*)(&time), np
					&((struct {
						void *param;
						double time;
						void *window;
					}){
						.param = NULL,
						.time = time,
						.window = &(np->w)
					})
				);
			}
			printf("early update 3\n");
		}
		printf("early update 4\n");

		glfwPollEvents();

		printf("early update 5\n");
		gettimeofday(&tval_after, NULL);
		timersub(&tval_after, &tval_before, &tval_result);
		dt = tval_result.tv_sec * 1000000 + tval_result.tv_usec;
		time += dt;

		printf("late update\n");
	}

	if (g_callback.lateloop)
		g_callback.lateloop(mc);

	return (1);
}
