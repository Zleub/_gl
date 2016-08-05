#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <math.h>

#include <_gl.h>
#include <_cl.h>

// #include <OpenCL/opencl.h>
#include <OpenCL/cl_gl_ext.h>
#include <OpenGL/CGLDevice.h>
#include <OpenGL/CGLCurrent.h>

#define ANGLE M_PI / 10000000
#define RADIUS 1

float cam_w = 2;

#include <sys/time.h>

#define KERNELS_NUMBER 2
static char *k_names[KERNELS_NUMBER] = {
	"res/x.cl",
	"res/y.cl"
	// "res/z.cl"
} ;

#define FUNCTION_NUMBER 1
static char *f_name[FUNCTION_NUMBER] = {
	"square"
} ;

#define PARAM_NUMBER 6

t_callback g_callback = (t_callback){
	error_callback, // error

	NULL, // windowpos
	resize_callback, // windowsize
	NULL, // windowclose
	NULL, // windowrefresh
	NULL, // windowfocus
	NULL, // windowiconify
	NULL, // framebuffersize

	mouse_button_callback, // mousebutton
	NULL, // cursorpos
	NULL, // cursorenter
	scroll_callback, // scroll
	key_callback, // key
	NULL, // uchar
	NULL, // charmods
	NULL, // drop
	NULL, // joystick

	NULL, // initearlyfun
	NULL // initlatefun
} ;

extern t_vec3 mouse ;

int main()
{
	t_window *window = init(WIDTH, HEIGHT, "Simple Window");
	glfwSwapInterval(1);
	apply_callback(window, &g_callback);

	t_vec4 *v_pos = new_vertices(VNBR);
	circle(v_pos, VNBR, 12);

	t_renderer *r = new_renderer(v_pos, NULL, VNBR);
	assign_shader(r, "res/vertex_shader.glsl", "res/fragment_shader.glsl");

	CGLContextObj kCGLContext = CGLGetCurrentContext();
	CGLShareGroupObj kCGLShareGroup = CGLGetShareGroup(kCGLContext);
	cl_context_properties properties[] = {
		CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
		(cl_context_properties)kCGLShareGroup, 0
	};

	t_context *c = init_context(k_names, f_name, properties);
	t_kernel *k = init_kernel(c, KERNELS_NUMBER, FUNCTION_NUMBER);

	printf("RENDERER\n");
	printf("VAO: %d, VBOP: %d, VBOC: %d\n", r->VAO, r->VBOP, r->VBOC);
	printf("vertices: %d as %lu octets\n", r->vertices_nbr, r->vertices_nbr * sizeof(float) * 4);

	t_param params[PARAM_NUMBER] = {
		{ CREATE_BUFFER, CL_MEM_READ_ONLY, sizeof(unsigned int), NULL},
		{ CREATE_BUFFER, CL_MEM_READ_ONLY, sizeof(float), NULL },
		{ CREATE_BUFFER, CL_MEM_READ_ONLY, sizeof(float) * 3, NULL },
		{ CREATE_BUFFER_FROM_GL, CL_MEM_READ_WRITE, 1, NULL },
		{ CREATE_BUFFER, CL_MEM_READ_ONLY, sizeof(float) * 4 * VNBR, NULL},
		{ CREATE_BUFFER_FROM_GL, CL_MEM_READ_WRITE, 2, NULL }
	} ;

	cl_mem *param_array = init_params(c, k, PARAM_NUMBER, params);

	unsigned int width = PARTICULE_WIDTH ;
	clEnqueueWriteBuffer(c->commands, param_array[0], CL_FALSE, 0, sizeof(unsigned int), &width, 0, NULL, NULL );

	size_t GlobalWorkSize[3] = { PARTICULE_WIDTH, PARTICULE_HEIGHT, 1 };
	k->GlobalWorkSize = GlobalWorkSize ;
	printf("GlobalWorkSize: %zu, %zu, %zu\n", k->GlobalWorkSize[0], k->GlobalWorkSize[1], k->GlobalWorkSize[2]);

	t_fps fps ;
	init_fps(&fps);

	while (!glfwWindowShouldClose(window->w))
	{
		run_fps(window, &fps);

		float dt = 0.0001 ;
		clEnqueueWriteBuffer( c->commands, param_array[2], CL_FALSE, 0, sizeof(float) * 3, &mouse, 0, NULL, NULL );
		clEnqueueWriteBuffer( c->commands, param_array[1], CL_FALSE, 0, sizeof(float), &dt, 0, NULL, NULL );

		clEnqueueAcquireGLObjects( c->commands, 1, &param_array[4], 0, NULL, NULL );
		clEnqueueAcquireGLObjects( c->commands, 1, &param_array[5], 0, NULL, NULL );

		clFinish( c->commands );

		run_kernel(c, k);

		clEnqueueReleaseGLObjects( c->commands, 1, &param_array[4], 0, NULL, NULL );
		clEnqueueReleaseGLObjects( c->commands, 1, &param_array[5], 0, NULL, NULL );
		clFinish( c->commands );

		render(window, r);
		glFinish();

		fps.t1 = glfwGetTime();

	}

	clReleaseMemObject(param_array[0]);
	clReleaseMemObject(param_array[1]);
	clReleaseMemObject(param_array[2]);
	clReleaseMemObject(param_array[3]);
	clReleaseMemObject(param_array[4]);

	clReleaseKernel(k->kernels[0]);
	clReleaseKernel(k->kernels[1]);
	// clReleaseKernel(k->kernels[2]);
	clReleaseCommandQueue(c->commands);
	clReleaseContext(c->context);

	glfwDestroyWindow(window->w);
	glfwTerminate();

	return 0;
}
