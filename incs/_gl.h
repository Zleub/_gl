#ifndef _GL_H
# define _GL_H

#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLEXT
#include <glfw3.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include <limits.h>
#include <math.h>

typedef int		t_vec2i __attribute__((ext_vector_type(2)));
typedef float	t_vec2f __attribute__((ext_vector_type(2)));
typedef double	t_vec2d __attribute__((ext_vector_type(2)));

typedef int		t_vec3i __attribute__((ext_vector_type(3)));
typedef float	t_vec3f __attribute__((ext_vector_type(3)));
typedef double	t_vec3d __attribute__((ext_vector_type(3)));

typedef int		t_vec4i __attribute__((ext_vector_type(4)));
typedef float	t_vec4f __attribute__((ext_vector_type(4)));
typedef double	t_vec4d __attribute__((ext_vector_type(4)));

typedef struct s_mlx_context t_mlx_context ;
typedef struct s_window t_window ;

typedef void (*MLXinitearlyfun)(t_mlx_context *);
typedef void (*MLXinitlatefun)(t_mlx_context *);

typedef void (*MLXwindowclosefun)(t_mlx_context *, t_window *);
typedef void (*MLXwindowresize)(t_mlx_context *, t_window *);

typedef void (*MLXloopearlyfun)(t_mlx_context *);
typedef void (*MLXlooplatefun)(t_mlx_context *);

// -- MLX MANDATORY
typedef int (*MLXloopfun)(void *param) ;

typedef struct s_callback	t_callback;
struct						s_callback {
	GLFWerrorfun			error;

	GLFWwindowposfun		windowpos;
	GLFWwindowsizefun		windowsize;
	GLFWwindowclosefun		windowclose;
	GLFWwindowrefreshfun	windowrefresh;
	GLFWwindowfocusfun		windowfocus;
	GLFWwindowiconifyfun	windowiconify;
	GLFWframebuffersizefun	framebuffersize;

	GLFWmousebuttonfun		mousebutton;
	GLFWcursorposfun		cursorpos;
	GLFWcursorenterfun		cursorenter;
	GLFWscrollfun			scroll;
	GLFWkeyfun				key;
	GLFWcharfun				uchar;
	GLFWcharmodsfun			charmods;
	GLFWdropfun				drop;
	GLFWjoystickfun			joystick;

	MLXinitearlyfun			initearlyfun;
	MLXinitlatefun			initlatefun;

	MLXloopearlyfun			earlyloopfun;
	MLXloopfun				loopfun;
	MLXlooplatefun			lateloopfun;

	MLXwindowclosefun		mlxwindowclose;
	MLXwindowresize			mlxwindowresize;
};

typedef struct s_fps	t_fps;
struct					s_fps {
	char				str[32];
	double				frames;
	double				t;
	double				t1;
	double				t2;
	float				dt;
};

enum window_size {
	SMALLEST,		// 640, 480
	SMALLEST_PLUS,	// 800, 600
	SMALLER,		// 1024, 576
	SMALLER_PLUS,	// 1024, 768
	SMALL,			// 1280, 720
	SMALL_PLUS,		// 1344, 756
	LARGE,			// 1280, 960
	LARGE_PLUS,		// 1344, 1008
	LARGER,			// 1600, 900
	LARGER_PLUS,	// 1600, 1200
	LARGEST,		// 2048, 1152
	FULLSCREEN,		// 2560, 1440
	WSLEN
};

enum e_drawing_mode {
	MLX, // each window its texture
	GL,  // free pleasure
	DMLEN
};

enum e_mlx_mode {
	MONO, // every window draw the first texture
	MULTIPLE, // every window can draw the first texture and its own
	INDEPENDANT, // every window draw its own texture
	RMLEN
};

typedef struct s_renderer	t_renderer;
struct		s_renderer {
	unsigned int	mode;
	unsigned int	VAO;

	struct {
		unsigned int	vertex_shader;
		unsigned int	fragment_shader;
		unsigned int	program;
	};

	struct {
		unsigned int	VBOP;
		unsigned int	VBOC;
		unsigned int	VBOT;
	};

	struct {
		unsigned int	vertices_nbr;
		t_vec3f			*v_pos;
		t_vec3f			*v_col;
	};
	struct {
		int				vpos_location;
		int				vcol_location;
	};

	struct {
		t_vec2i			window_size;
		t_vec3f			*v_tex;
	};
	struct {
		unsigned int	vtex_location;
		unsigned int	texture;
	};
};

typedef struct s_window	t_window;
struct					s_window {
	GLFWwindow			*w;
	struct s_renderer	r;

	t_vec2i				size;
	t_vec2i				position;

	unsigned int		flush;
};

#define PARTICULE_WIDTH 1024 // * 2
#define PARTICULE_HEIGHT 1024 // * 2
#define VNBR (PARTICULE_WIDTH * PARTICULE_HEIGHT)

extern t_callback g_callback ;

// window.c
void			*init(void);
t_window		*new_window(t_mlx_context *mlx_context, int size_x, int size_y, char *title);
int				clear_window(t_mlx_context *mlx_context, t_window *window);
int				pixel_put(t_mlx_context *mlx_context, t_window *window, int x, int y, int color);

// vertices.c
t_vec4f			*new_vertices(unsigned int size);
void			line(t_vec4f *vertices, unsigned int size, unsigned int grain);
void			cube(t_vec4f *vertices, unsigned int size, unsigned int grain);
void			circle(t_vec4f *vertices, unsigned int size, unsigned int grain);
void			inf_cone(t_vec4f *vertices, unsigned int size, unsigned int grain);
void			large_cube(t_vec4f *v_pos, unsigned int size, unsigned int grain);

// shader.c
char			*load_shader(char *filename);
int				compile_shader(int type, unsigned int prog);
unsigned int	make_shader(int type, char *path);

// renderer.c
void			init_renderer(t_renderer *r);
void			assign_shader(t_renderer *r, char *v_path, char *f_path);
int				render(t_window *window);

// callback.c
void			key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void			resize_callback(GLFWwindow *window, int width, int height);
void			error_callback(int error, const char* description);
void			mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void			scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void			apply_callback(t_window *window, t_callback *callback);

// util.c
void			version(void);
void			init_fps(t_fps *fps);
void			run_fps(t_window *window, t_fps *fps);

#endif
