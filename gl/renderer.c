#include <_gl.h>
#include <stdio.h>

t_renderer		*new_renderer(t_vec4 *v_pos, t_vec4 *v_col, unsigned int size)
{
	t_renderer	*r;

	r = malloc(sizeof(t_renderer));
	bzero(r, sizeof(t_renderer));
	r->v_pos = v_pos;
	r->v_col = v_col;
	r->vertices_nbr = size;

	glGenVertexArrays(1, &r->VAO);
	glBindVertexArray(r->VAO);

	return r;
}

void			assign_shader(t_renderer *r, char *v_path, char *f_path)
{
	r->vertex_shader = make_shader(GL_VERTEX_SHADER, v_path);
	r->fragment_shader = make_shader(GL_FRAGMENT_SHADER, f_path);

	r->program = glCreateProgram();
	glAttachShader(r->program, r->vertex_shader);
	glAttachShader(r->program, r->fragment_shader);
	glLinkProgram(r->program);

	r->vpos_location = glGetAttribLocation(r->program, "vPos");
	r->vcol_location = glGetAttribLocation(r->program, "vCol");

	glGenBuffers(1, &r->VBOP);
	glBindBuffer(GL_ARRAY_BUFFER, r->VBOP);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * r->vertices_nbr, r->v_pos, GL_STATIC_DRAW);
	glEnableVertexAttribArray(r->vpos_location);
	glVertexAttribPointer(r->vpos_location, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glGenBuffers(1, &r->VBOC);
	glBindBuffer(GL_ARRAY_BUFFER, r->VBOC);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * r->vertices_nbr, r->v_col, GL_STATIC_DRAW);
	glEnableVertexAttribArray(r->vcol_location);
	glVertexAttribPointer(r->vcol_location, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);
}

extern float cam_w;

int				render(t_window *window, t_renderer *r)
{
	if (glfwWindowShouldClose(window->w))
		return (-1);

	// glfwMakeContextCurrent(window->w);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// glClear(GL_COLOR_BUFFER_BIT);

	GLint __w = glGetUniformLocation(r->program, "w");
	glUniform1f(__w, cam_w);

	glUseProgram(r->program);

	glDrawArrays(GL_POINTS, 0, VNBR);

	glfwSwapBuffers(window->w);
	glfwPollEvents();

	return (1);
}
