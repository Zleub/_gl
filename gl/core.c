#include <_gl.h>
#include <mlx.h>

extern t_mlx_context g_mlx_context;

void focus_test(GLFWwindow *w, int i);
void destroy_callback(GLFWwindow *window);
int loop_callback(void *param);

#include <sys/time.h>

t_callback g_callback = (t_callback){
	/* error */				error_callback,

	/* windowpos */			NULL,
	/* windowsize */		resize_callback,
	/* windowclose */		destroy_callback,
	/* windowrefresh */		NULL,
	/* windowfocus */		focus_test,
	/* windowiconify */		NULL,
	/* framebuffersize */	NULL,

	/* mousebutton */		mouse_button_callback,
	/* cursorpos */			NULL,
	/* cursorenter */		NULL,
	/* scroll */			scroll_callback,
	/* key */				key_callback,
	/* uchar */				NULL,
	/* charmods */			NULL,
	/* drop */				NULL,
	/* joystick */			NULL,

	/* -------------------*/

	/* initearly */			NULL,
	/* initlate */			NULL,

	/* earlyloop */			NULL,
	/* loop */				NULL,
	/* lateloop */			NULL,

	/* windowclose */		NULL,
	/* windowresize */		NULL
} ;

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
