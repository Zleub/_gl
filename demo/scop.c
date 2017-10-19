#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include <libft.h>

#ifdef _GL
# include <_gl.h>
# include <colors.h>
#endif

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

int test(char *s)
{
	int i;

	i = 0;
	while (keywords[i])
	{
		if (!strncmp(s, keywords[i], strlen(keywords[i])))
			break;
		i += 1;
	}
	printf("(%s) -> %s\n", s, i == keywords_len() ? "none" : ft_itoa(i));
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

		#ifdef _GL
			printf("%s: %d\n", maroon(argv[1]), fd);
		#else
			printf("%s: %d\n", argv[1], fd);
		#endif

		char *s;
		struct {
			t_vec4d *vertices;
			unsigned int count;
		} vertices = {
			malloc(1024 * sizeof(t_vec4d)), 0
		};

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
