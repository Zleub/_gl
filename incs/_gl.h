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

typedef struct vec2 {
	float		x;
	float		y;
}				t_vec2;

typedef struct rgb {
	float		r;
	float		g;
	float		b;
}				t_rgb;

typedef struct vec3 {
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct vec4 {
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec4;

typedef struct	s_vertices
{
	float x, y, z;
	float r, g, b;
}				t_vertices;

typedef struct				s_window {
	GLFWwindow				*w;
	struct vec2				size;
	struct vec2				position;

	GLFWwindowposfun		poscb;
	GLFWwindowsizefun		sizecb;
	GLFWwindowclosefun		closefun;
	GLFWwindowrefreshfun	refreshfun;
	GLFWwindowfocusfun		focuscb;
	GLFWwindowiconifyfun	iconfun;
	GLFWframebuffersizefun	fbfun;
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

#define PARTICULE_WIDTH 1536
#define PARTICULE_HEIGHT 1536
#define VNBR (PARTICULE_WIDTH * PARTICULE_HEIGHT)

// window.c
t_window		*init(int size_x, int size_y, char *title);
t_window		*new_window(int size_x, int size_y, char *title);

// vertices.c
t_vec4			*new_vertices(unsigned int size);
void			line(t_vec4 *vertices, unsigned int size);
void			cube(t_vec4 *vertices, unsigned int size, unsigned int grain);
void			circle(t_vec4 *vertices, unsigned int size, unsigned int grain);
void			sphere(t_vec4 *vertices, unsigned int size);
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
void			run_system(t_window *w, t_system *s);

// callback.c
void			key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void			resize_callback(GLFWwindow *window, int width, int height);
void			error_callback(int error, const char* description);
void			scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// util.c
void			version(void);

#endif
