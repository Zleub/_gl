#include <_gl.h>
#include <stdio.h>

t_system		*new_system(t_renderer *r, unsigned int size, t_position_ft f)
{
	unsigned int	i;
	t_system		*ps;

	(void)f;
	ps = (t_system *)malloc(sizeof(t_system));
	bzero(ps, sizeof(t_system));

	ps->renderer = r;
	// ps->velocity = (t_vec3 *)malloc(sizeof(t_vec3) * r->vertices_nbr);
	// bzero(ps->velocity, sizeof(t_vec3) * r->vertices_nbr);

	if (size > 0)
	{
		ps->system_number = size;
		ps->array[POSITION] = (t_vec3 **)malloc(sizeof(t_vec3*) * size);
	}

	i = 0;
	while (i < size)
	{
		ps->array[POSITION][i] = (t_vec3 *)(r->v_pos + i);
		i += 1;
	}

	return (ps);
}


void		run_system(t_window *w, t_system *s)
{
	unsigned int i;

	i = s->system_number;
	while (i < s->renderer->vertices_nbr)
	{
		(void)w;
		// translate(w, s, i);
		i += 1;
	}
	glBindBuffer(GL_ARRAY_BUFFER, s->renderer->VBOP);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec3) * s->renderer->vertices_nbr, s->renderer->v_pos, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, s->renderer->VBOC);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec3) * s->renderer->vertices_nbr, s->renderer->v_col, GL_STATIC_DRAW);

	// glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec3) * s->renderer->vertices_nbr, s->renderer->v_pos, GL_STATIC_DRAW);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec3) * s->renderer->vertices_nbr, s->renderer->v_col, GL_STATIC_DRAW);
}
