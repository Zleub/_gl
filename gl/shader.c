#include <_gl.h>
#include <stdio.h>

char		*load_shader(char *filename)
{
	int		fd;
	char	*str;
	char	*tmp;
	char	buf[1024];

	if ((fd = open(filename, O_RDONLY)) < 2)
	{
		printf("open error\n");
		exit(-1);
	}
	str = malloc(1);
	*str = 0;
	bzero(buf, 1024);
	while (read(fd, buf, 1023) > 0)
	{
		tmp = (char *)malloc(strlen(str) + strlen(buf) + 1);
		bzero(tmp, strlen(str) + strlen(buf) + 1);
		strncpy(tmp, str, strlen(str));
		strncpy(tmp + strlen(str), buf, strlen(buf));
		free(str);
		str = tmp;
		bzero(buf, 1024);
	}

	close(fd);
	return (str);
}

int			compile_shader(int type, unsigned int prog)
{
	glCompileShader(prog);

	GLint success = 0;
	glGetShaderiv(prog, GL_COMPILE_STATUS, &success);

	char *strtype;

	if (type == GL_VERTEX_SHADER)
		strtype = "Vertex";
	if (type == GL_FRAGMENT_SHADER)
		strtype = "Fragment";

	printf("%s shader: %s\n", strtype, success == GL_FALSE ? "Nop" : "Ok");
	if (success == GL_FALSE) {
		GLint logSize = 0;
		glGetShaderiv(prog, GL_INFO_LOG_LENGTH, &logSize);

		char str[logSize + 1];
		bzero(str, logSize + 1);
		glGetShaderInfoLog(prog, logSize, &logSize, &str[0]);

		printf("-> %s\n", str);
	}

	return (success);
}

unsigned int	make_shader(int type, char *path)
{
	char *shader_text;
	unsigned int shader;

	shader = glCreateShader(type);
	shader_text = load_shader(path);
	glShaderSource(shader, 1, (const char *const *)&shader_text, NULL);
	compile_shader(type, shader);

	// free(shader_text);
	printf("%s done\n", path);
	return (shader);
}
