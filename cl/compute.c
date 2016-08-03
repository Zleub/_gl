/*
* @Author: adebray
* @Date:   2016-07-19 13:39:20
* @Last Modified by:   adebray
* @Last Modified time: 2016-08-03 20:32:38
*/

#include <stdio.h>
#include <_gl.h>
#include <_cl.h>

int		connect(cl_device_id *device_id)
{
	// Connect to a compute device
	//
	int err;
	int gpu = 1;
	err = clGetDeviceIDs(NULL, gpu ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU, 1, device_id, NULL);
	if (err != CL_SUCCESS)
	{
		printf("Error: Failed to create a device group!\n");
		exit(EXIT_FAILURE);
	}

	return (err);
}

cl_context		create_context(cl_device_id device_id, cl_context_properties *props)
{
	// Create a compute context
	//
	int err;
	(void)props;
	cl_context context = clCreateContext(props, 1, &device_id, NULL, NULL, &err);
	if (!context)
	{
		printf("Error: Failed to create a compute context!\n");
		exit(EXIT_FAILURE);
	}
	return (context);
}

cl_command_queue	create_command(cl_context context, cl_device_id device_id)
{
	// Create a command commands
	//
	int err;
	cl_command_queue commands = clCreateCommandQueue(context, device_id, 0, &err);
	if (!commands)
	{
		printf("Error: Failed to create a command commands!\n");
		exit(EXIT_FAILURE);
	}
	return (commands);
}

cl_kernel		create_kernel(cl_context context, cl_device_id device_id, char *path, char *name)
{
	// Create the compute program from the source buffer
	//
	int err;
	char *p = load_shader(path);
	cl_program program = clCreateProgramWithSource(context, 1, (const char **) &p, NULL, &err);
	if (!program)
	{
		printf("Error: Failed to create compute program!\n");
		exit(EXIT_FAILURE);
	}

	// Build the program executable
	//
	err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if (err != CL_SUCCESS)
	{
		size_t len;
		char buffer[2048];

		printf("Error: Failed to build program executable!\n");
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		printf("%s\n", buffer);
		exit(1);
	}

	cl_kernel kernel = clCreateKernel(program, name, &err);
	if (!kernel || err != CL_SUCCESS)
	{
		printf("%d\n", err);
		printf("Error: Failed to create compute kernel!\n");
		exit(1);
	}

	clReleaseProgram(program);
	return (kernel);
}

