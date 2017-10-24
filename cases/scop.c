#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include <libft.h>

#include <_gl.h>
#include <colors.h>

typedef struct s_vertices t_vertices;
struct s_vertices {
	/**
	 * List of geometric vertices,
	 * with (x,y,z[,w]) coordinates,
	 * w is optional and defaults to 1.0.
	 */
	t_vec4d *v;
	/**
	 * List of texture coordinates,
	 * in (u, v [,w]) coordinates,
	 * these will vary between 0 and 1,
	 * w is optional and defaults to 0.
	 */
	t_vec4d *vt;
	/**
	 * List of vertex normals in (x,y,z) form;
	 * normals might not be unit vectors.
	 */
	t_vec4d *vn;
	/**
	 * Parameter space vertices in ( u [,v] [,w] ) form;
	 * free form geometry statement ( see below )
	 */
	t_vec4d *vp;
	/**
	 * Polygonal face element (see below)
	 */
	t_vec4d *f;

	unsigned int count;
};

char *keywords[] = {
	"mtllib",
	"o",
	"v",
	"usrmtl",
	"s",
	"f",
	NULL
};

int keywords_len(void)
{
	int i;

	i = 0;
	while (keywords[i])
		i += 1;
	return i;
}

int test(char *s, t_vertices *v)
{
	int i;

	i = 0;
	(void)v;
	while (keywords[i])
	{
		if (!strncmp(s, keywords[i], strlen(keywords[i])))
			break;
		i += 1;
	}
	printf("(%s) -> %s\n", colors[i + 1](s), i == keywords_len() ? "none" : ft_itoa(i));
	return (0);
}

int main(int argc, char const *argv[])
{
	if (argc == 2) {
		int fd = open(argv[1], O_RDONLY);
		if (fd == -1) {
			printf("Usage: ./scop [obj_path]\n");
			exit(EXIT_FAILURE);
		}

		printf("%s: %d\n", maroon(argv[1]), fd);

		char *s;
		t_vertices vertices = { malloc(1024 * sizeof(t_vec4d)), 0 };

		while ( get_next_line(fd, &s) )
		{
			test(s, &vertices);
			free(s);
		}
	}
	else
		printf("Usage: ./scop [obj_path]\n");
	return 0;
}
