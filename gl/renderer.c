#include <_gl.h>
// #include <mlx.h>
#include <stdio.h>

void			init_renderer(t_renderer *r)
{
	glGenVertexArrays(1, &r->VAO);
	glBindVertexArray(r->VAO);


	assign_shader(r, "res/std_vertex.glsl", "res/std_fragment.glsl");
}

#define COLOR_LEN 16
static t_vec3f color_table[COLOR_LEN] = {
	{ 0.,   0.,   0. },
	{ 1.,   1.,   1. },
	{ 1.,   0.,   0. },
	{ 0.,   1.,   0. },
	{ 0.,   0.,   1. },
	{ 1.,   1.,   0. },
	{ 0.,   1.,   1. },
	{ 1.,   0.,   1. },
	{ 0.75, 0.75, 0.75 },
	{ 0.5,  0.5,  0.5 },
	{ 0.5,  0.,   0. },
	{ 0.5,  0.5,  0. },
	{ 0.,   0.5,  0. },
	{ 0.5,  0.,   0.5 },
	{ 0.,   0.5,  0.5 },
	{ 0.,   0.,   0.5 }
};

void			assign_shader(t_renderer *r, char *v_path, char *f_path)
{
	static int j = 0;

	printf("-NEW WINDOW-------------------------------\n");

	r->vertex_shader = make_shader(GL_VERTEX_SHADER, v_path);
	r->fragment_shader = make_shader(GL_FRAGMENT_SHADER, f_path);

	r->program = glCreateProgram();
	glAttachShader(r->program, r->vertex_shader);
	glAttachShader(r->program, r->fragment_shader);
	glLinkProgram(r->program);

	r->vpos_location = glGetAttribLocation(r->program, "vPos");
	r->vcol_location = glGetAttribLocation(r->program, "vCol");
	r->vtex_location = glGetAttribLocation(r->program, "tPos");
	unsigned int t = glGetUniformLocation(r->program, "tex");

	glGenBuffers(1, &r->VBOP);
	glBindBuffer(GL_ARRAY_BUFFER, r->VBOP);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec3f) * r->vertices_nbr, r->v_pos, GL_STATIC_DRAW);
	glEnableVertexAttribArray(r->vpos_location);
	glVertexAttribPointer(r->vpos_location, sizeof(t_vec3f) / sizeof(float), GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glGenBuffers(1, &r->VBOC);
	glBindBuffer(GL_ARRAY_BUFFER, r->VBOC);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec3f) * r->vertices_nbr, r->v_col, GL_STATIC_DRAW);
	glEnableVertexAttribArray(r->vcol_location);
	glVertexAttribPointer(r->vcol_location, sizeof(t_vec3f) / sizeof(float), GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glGenBuffers(1, &r->VBOT);
	glBindBuffer(GL_ARRAY_BUFFER, r->VBOT);
	glEnableVertexAttribArray(r->vtex_location);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec3f) * r->vertices_nbr, r->v_tex, GL_STATIC_DRAW);
	glVertexAttribPointer(r->vtex_location, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glGenTextures(1, &r->texture);
	glBindTexture(GL_TEXTURE_2D, r->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unsigned int size = r->window_size.x * r->window_size.y ;

	t_vec3f *img = malloc(sizeof(t_vec3f) * size);
	for (unsigned int i = 0; i < size; ++i)
	{
		img[i] = color_table[j % COLOR_LEN];
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, r->window_size.x, r->window_size.y, 0, GL_RGB, GL_FLOAT, img);
	free(img);

	glUniform1i(t, 0);

	printf("r->vertex_shader: %d\n", r->vertex_shader);
	printf("r->fragment_shader: %d\n", r->fragment_shader);
	printf("r->program: %d\n", r->program);
	printf("r->texture: %d\n", r->texture);
	printf("------------------------------------------\n");
	printf(" \n");

	j += 1;
}

extern float cam_w;
// extern struct s_mlx_context g_mlx_context;

int				render(t_window *window)
{
	if (glfwWindowShouldClose(window->w))
	{
		glfwMakeContextCurrent(0);
		glfwDestroyWindow(window->w);
		// STAILQ_REMOVE(&g_mlx_context.w_head, np, entry, entries);
		// free(window);
		// window = 0;
		return (0);
	}
	else
	{
		glfwMakeContextCurrent(window->w);
		if (window->flush > 0) {
			glClear(GL_COLOR_BUFFER_BIT);
			window->flush -= 1;
		}

		glActiveTexture(0);
		if (window->r.mode == MONO)
			glBindTexture(GL_TEXTURE_2D, 1);
		else
			glBindTexture(GL_TEXTURE_2D, window->r.texture);

		// printf("%d\n", window->r.program);
		glUseProgram(window->r.program);
		glDrawArrays(GL_TRIANGLE_FAN, 0, window->r.vertices_nbr);
		glfwSwapBuffers(window->w);
		glfwMakeContextCurrent(0);
	}

	return (1);
}
