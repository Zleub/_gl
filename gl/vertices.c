#include <_gl.h>
#include <stdio.h>


t_vec4	*new_vertices(unsigned int size)
{
	t_vec4		*v;

	v = (t_vec4 *)malloc(sizeof(t_vec4) * size);
	bzero(v, sizeof(t_vec4) * size);

	return (v);
}


#include <time.h>
#include <stdlib.h>

void		line(t_vec4 *v_pos, unsigned int size, unsigned int grain)
{
	srand(time(NULL));
	for (unsigned int i = 0; i < size; ++i)
	{
		v_pos[i].x = 0.;
		v_pos[i].y = ((float)(rand() % (HEIGHT)) / (float)HEIGHT ) ;
		v_pos[i].z = ((float)(rand() % grain) / (float)grain ) + (rand() % 2) - 1;
	}
}

void		cube(t_vec4 *v_pos, unsigned int size, unsigned int grain)
{
	srand(time(NULL));
	for (unsigned int i = 0; i < size; ++i)
	{
		v_pos[i].x = ((float)(rand() % grain) / grain) - 0.5 ;
		v_pos[i].y = ((float)(rand() % grain) / grain) - 0.5 ;
		v_pos[i].z = ((float)(rand() % grain) / grain) - 0.5 ;
	}
}

void		large_cube(t_vec4 *v_pos, unsigned int size, unsigned int grain)
{
	(void)grain;
	srand(time(NULL));
	for (unsigned int i = 0; i < size; ++i)
	{
		v_pos[i].x = ((float)(rand() % 10) / 10) + (rand() % 4) - 2 ;
		v_pos[i].y = ((float)(rand() % 10) / 10) + (rand() % 4) - 2 ;
		v_pos[i].z = ((float)(rand() % 10) / 10) + (rand() % 4) - 2 ;
	}
}

void		circle(t_vec4 *v_pos, unsigned int size, unsigned int grain)
{
	srand(time(NULL));
	for (unsigned int i = 0; i < size; ++i)
	{
		float rad = (rand() % grain + 2.) / grain ;

		v_pos[i].x = rad * sin(2*3.14 * i/VNBR ) ;
		v_pos[i].y = rad * cos(2*3.14 * i/VNBR ) ;
		v_pos[i].z = 0 ;
	}

}

void		inf_cone(t_vec4 *v_pos, unsigned int size, unsigned int grain)
{
	srand(time(NULL));
	for (unsigned int i = 0; i < size; ++i)
	{
		float rad = (rand() % grain + 2.) / grain ;

		v_pos[i].x = rad * sin(2*3.14 * i/VNBR ) ;
		v_pos[i].y = rad * cos(2*3.14 * i/VNBR ) ;
		v_pos[i].z = 1 / rad;
	}

}
