//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  mlx.h
// /ddddy:oddddddddds:sddddd/ By Zleub - Zleub
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2016-08-07 21:35:12
// :ddddddddddhyyddddddddddd: Modified: Zleub
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#ifndef MLX_H
# define MLX_H

#include <sys/queue.h>

#define mlx_init init
#define mlx_new_window new_window

#define WINDOW_MAX 8

struct s_size {
	int		width;
	int		height;
};

typedef struct s_window_list t_window_list;
struct s_window_list {
	t_window					w;
	STAILQ_ENTRY(s_window_list)	next;
};

struct s_mlx_context
{
	unsigned int		mode;

	struct s_size		screen_size;
	struct s_size		vidmode_size;

	unsigned int							window_nbr;
	STAILQ_HEAD(window_head, s_window_list)	w_head;
	struct window_head						*headp;
	t_window								*active_window;
} ;

#endif
