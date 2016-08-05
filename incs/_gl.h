#ifndef MLX_H
# define MLX_H

#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLEXT
#include <glfw3.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include <limits.h>
#include <math.h>

typedef struct	vec2 {
	float		x;
	float		y;
}				t_vec2;

typedef struct	rgb {
	float		r;
	float		g;
	float		b;
}				t_rgb;

typedef struct	vec3 {
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct	vec4 {
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec4;

typedef struct	s_vertices
{
	float		x;
	float		y;
	float		z;
	float		r;
	float		g;
	float		b;
}				t_vertices;

typedef void (*MLXinitearlyfun)() ;
typedef int (*MLXinitlatefun)() ;

typedef struct				s_callback {
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
}							t_callback ;

typedef struct				s_fps {
	char					str[32];
	double					frames;
	double					t;
	double					t1;
	double					t2;
	float					dt;
}							t_fps ;

typedef struct				s_window {
	GLFWwindow				*w;
	struct vec2				size;
	struct vec2				position;
}							t_window;

typedef struct				s_renderer {
	unsigned int			VAO;
	unsigned int			VBOP;
	unsigned int			VBOC;

	t_vec4					*v_pos;
	t_vec4					*v_col;
	unsigned int			vertices_nbr;

	t_vec3					camera;

	unsigned int			vertex_shader;
	unsigned int			fragment_shader;
	unsigned int			program;

	int						vpos_location;
	int						vcol_location;

}							t_renderer;

enum {
	POSITION,
	FORMULA,
	PLENGTH
};

enum {
	ATTRACTOR,
	REPULSOR,
	EMITTER,
	RECEPTER,
	TLEN
};

typedef struct				s_system {
	t_renderer				*renderer;
	unsigned int			system_number;
	t_vec3					*velocity;
	t_vec3					**array[PLENGTH];

}							t_system;

typedef t_vec3 (*t_position_ft)(int nbr);

#define WIDTH 1024
#define HEIGHT 1024

#define PARTICULE_WIDTH 16 // * 2
#define PARTICULE_HEIGHT 16 // * 2
#define VNBR (PARTICULE_WIDTH * PARTICULE_HEIGHT)

extern t_callback g_callback ;

// window.c
t_window		*init(int size_x, int size_y, char *title);
t_window		*new_window(int size_x, int size_y, char *title);

// vertices.c
t_vec4			*new_vertices(unsigned int size);
void			line(t_vec4 *vertices, unsigned int size, unsigned int grain);
void			cube(t_vec4 *vertices, unsigned int size, unsigned int grain);
void			circle(t_vec4 *vertices, unsigned int size, unsigned int grain);
void			inf_cone(t_vec4 *vertices, unsigned int size, unsigned int grain);
void			large_cube(t_vec4 *v_pos, unsigned int size, unsigned int grain);

// shader.c
char			*load_shader(char *filename);
int				compile_shader(int type, unsigned int prog);
unsigned int	make_shader(int type, char *path);

// renderer.c
t_renderer		*new_renderer(t_vec4 *v_pos, t_vec4 *v_col, unsigned int size);
void			assign_shader(t_renderer *r, char *v_path, char *f_path);
int				render(t_window *w, t_renderer *r);

// _ps.c
t_system		*new_system(t_renderer *r, unsigned int size, t_position_ft f);

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
