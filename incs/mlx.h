#ifndef MLX_H
# define MLX_H

#include <sys/queue.h>

struct s_size {
	int		width;
	int		height;
};

typedef struct s_window_list t_window_list;
struct s_window_list {
	t_window					w;
	STAILQ_ENTRY(s_window_list)	next;
};

typedef struct s_mlx_context t_mlx_context;
struct s_mlx_context
{
	unsigned int							mode;

	struct s_size							screen_size;
	struct s_size							vidmode_size;

	unsigned int							window_nbr;
	STAILQ_HEAD(window_head, s_window_list)	w_head;
	struct window_head						*headp;
	t_window								*active_window;
} ;

#define mlx_init init
#define mlx_new_window new_window
#define mlx_clear_window clear_window
#define mlx_pixel_put pixel_put

#define mlx_loop loop

#define mlx_new_image new_image

#define X_SIZE 16 // r->window_size.x
#define Y_SIZE 16 // r->window_size.y

#endif
