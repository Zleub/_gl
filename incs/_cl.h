#ifndef FT_CL_H
# define FT_CL_H

#include <OpenCL/opencl.h>

typedef struct			s_context
{
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	commands;

	char				**kernel_names;
	char				**function_names;
}						t_context;

typedef struct			s_kernel
{
	size_t				*GlobalWorkSize;

	unsigned int		k_size;
	cl_kernel			*kernels;

	unsigned int		p_size;
	cl_mem				*params;

}						t_kernel;

enum {
	CREATE_BUFFER,
	CREATE_BUFFER_FROM_GL
} ;

typedef struct				s_param
{
	unsigned int			create_function;
	unsigned int			cl_mem_mask;
	size_t					size;
	void					*whatever;
}							t_param;

// compute.c
int					connect(cl_device_id *device_id);

cl_context			create_context(cl_device_id device_id, cl_context_properties *props);
cl_command_queue	create_command(cl_context context, cl_device_id device_id);
cl_kernel			create_kernel(cl_context context, cl_device_id device_id, char *source, char *name);

// kernel.c

t_context			*init_context(char **kernel_names, char **function_names, cl_context_properties *properties);
t_kernel			*init_kernel(t_context *context, unsigned int k_nbr, unsigned int p_nbr);
cl_mem				*init_params(t_context *context, t_kernel *k, unsigned int p_nbr, t_param *params);

void				run_kernel(t_context *context, t_kernel *kernel);


#endif
