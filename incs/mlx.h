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

#define mlx_init init
#define mlx_new_window new_window

#define WINDOW_MAX 8

struct s_mlx_context
{
	unsigned int		mode;

	unsigned int		window_nbr;
	t_window			*windows[WINDOW_MAX];
	t_window			*active_window;
} ;
