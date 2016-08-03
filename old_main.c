/*
* @Author: adebray
* @Date:   2016-07-11 14:52:04
* @Last Modified by:   adebray
* @Last Modified time: 2016-07-18 18:31:25
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <math.h>

#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLEXT
// #define GLFW_INCLUDE_GLU
#include <mlx.h>

#define WIDTH 512
#define HEIGHT 512

unsigned char textureData[WIDTH][HEIGHT][3];

int res = 1;


void draw(int offset_x, int offset_y, int res)
{
	(void)offset_x;
	(void)offset_y;
	(void)res;

	bzero(textureData, WIDTH * HEIGHT * 3);
	for (int i = 0; i < WIDTH; i += 1)
	{
		for (int j = 0; j < HEIGHT; j += 1)
		{
			int x = pow( (i + offset_x - WIDTH / 2) / 10, 2);
			int y = pow( (j + offset_y - HEIGHT / 2) / 10, 2);
			(void)x;
			(void)y;

			textureData[i][j][0] = x * y / 255 < res ? x * y: x + y;
			textureData[i][j][1] = 0 ;
			textureData[i][j][2] = 0 ;

		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
}

GLFWwindow *window;
GLuint textureName;

void gl_texture(void) {

	glGenTextures(1, &textureName);
	glBindTexture(GL_TEXTURE_2D, textureName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

int			clear_window(GLFWwindow *window)
{
	(void)window;
	// glfwMakeContextCurrent(window);
	// glClear(GL_COLOR_BUFFER_BIT);
	// glfwSwapBuffers(window);
	return (0);
}

int			pixel_put(GLFWwindow *window, int x, int y, int color)
{
	(void)window;
	(void)x;
	(void)y;
	(void)color;
	return (0);
}

static const char* vertex_shader_text =

"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"

"varying vec3 color;\n"
"varying vec2 fragTexCoord;\n"

"void main()\n"
"{\n"
"    gl_Position = vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"    fragTexCoord = vPos;\n"
"}\n";

static const char* fragment_shader_text =
"uniform sampler2D tex;\n"

"varying vec3 color;\n"
"varying vec2 fragTexCoord;\n"

"void main()\n"
"{\n"
// "color = texture( myTextureSampler, UV ).rgb;\n"
// "gl_FragColor = texture( myTextureSampler, UV ).rgb;\n"
"    gl_FragColor = texture2D(tex, fragTexCoord);\n"
// "    gl_FragColor = vec4(color, 1.0);\n"
"}\n";

int compile(prog)
{
	glCompileShader(prog);

	GLint success = 0;
	glGetShaderiv(prog, GL_COMPILE_STATUS, &success);
	printf("shader: %s\n", success == GL_FALSE ? "Nop" : "Ok");

	if (success == GL_FALSE) {
		GLint logSize = 0;
		glGetShaderiv(prog, GL_INFO_LOG_LENGTH, &logSize);

		char str[logSize];
		glGetShaderInfoLog(prog, logSize, &logSize, &str[0]);

		printf("-> %s\n", str);
	}

	return success;
}

GLuint gVAO = 0;

struct
{
	float x, y;
	float r, g, b;
} vertices[4] =
{
	{ -1.f, -1.f, 1.f, 1.f, 1.f },
	{  1.f, -1.f, 1.f, 1.f, 1.f },
	{  1.f,  1.f, 1.f, 1.f, 1.f },
	{ -1.f,  1.f, 1.f, 1.f, 1.f }
};

int main()
{
	glfwSetErrorCallback(error_callback);
	window = init(WIDTH, HEIGHT, "Simple Window")->w;

	glfwSetKeyCallback(window, key_callback);

	gl_texture();

	 glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);

	GLuint triangleVBO;
	/* Create a new VBO and use the variable "triangleVBO" to store the VBO id */


	GLuint vertex_shader, fragment_shader, program;
	GLint mvp_location, vpos_location, vcol_location;

	glGenBuffers(1, &triangleVBO);

	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
	compile(vertex_shader);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
	compile(fragment_shader);


	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	mvp_location = glGetUniformLocation(program, "MVP");
	vpos_location = glGetAttribLocation(program, "vPos");
	vcol_location = glGetAttribLocation(program, "vCol");

	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
						  sizeof(float) * 5, (void*) 0);
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
						  sizeof(float) * 5, (void*) (sizeof(float) * 2));

	draw(0, 0, res);
	while (!glfwWindowShouldClose(window))
	{

		// int width, height;
		// glfwGetFramebufferSize(window, &width, &height);
		// glViewport(0, 0, width, height);

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);

		GLint uniform_mytexture = glGetUniformLocation(program, "tex");

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureName);

		glUniform1i(uniform_mytexture, /*GL_TEXTURE*/0);

  		// glBindVertexArray(gVAO);
  		// glEnable(GL_TEXTURE_2D);
		// glEnable(GL_VERTEX_ARRAY);
		// glActiveTexture(GL_TEXTURE0);
		// glBindTexture(GL_TEXTURE_2D, textureName);

		glDrawArrays(GL_QUADS, 0, 4);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return (EXIT_SUCCESS);
}
