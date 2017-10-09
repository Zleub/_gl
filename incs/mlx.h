#ifndef MLX_H
# define MLX_H

# include <_gl.h>
# include <sys/queue.h>
# include <stdio.h>

struct s_size {
	int		width;
	int		height;
};

typedef struct s_window_list t_window_list;
struct s_window_list {
	t_window					w;
	STAILQ_ENTRY(s_window_list)	next;
};

typedef struct s_image_list t_image;
struct s_image_list {
	struct s_size				size;
	char						*data;
	STAILQ_ENTRY(s_image_list)	next;
};

/**
 * \todo merge mlx_context with renderer
 */
typedef struct s_mlx_context t_mlx_context;
struct s_mlx_context
{
	unsigned int							mode;

	struct s_size							screen_size;
	struct s_size							vidmode_size;

	unsigned int							window_nbr;
	STAILQ_HEAD(window_head, s_window_list)	w_head;
	STAILQ_HEAD(image_head, s_image_list)	i_head;
	t_window								*active_window;
} ;

# define mlx_init					init
# define mlx_new_window				new_window
# define mlx_clear_window			clear_window
# define mlx_pixel_put				pixel_put
# define mlx_get_data_addr			get_data_addr
# define mlx_put_image_to_window	put_image_to_window

# define mlx_loop			loop
# define mlx_loop_hook		loop_hook
# define mlx_mouse_hook		mouse_hook

# define mlx_new_image new_image

# define X_SIZE r->window_size.x
# define Y_SIZE r->window_size.y

#endif
