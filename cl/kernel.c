/*
* @Author: adebray
* @Date:   2016-08-03 20:31:54
* @Last Modified by:   adebray
* @Last Modified time: 2016-08-04 00:43:33
*/

#include <stdio.h>
#include <_cl.h>

t_context	*init_context(char **kernel_names, char **function_names, cl_context_properties *properties)
{
	t_context	*nc;

	nc = (t_context *)malloc(sizeof(t_context));
	connect(&nc->device_id);
	nc->context = create_context(nc->device_id, properties);
	nc->commands = create_command(nc->context, nc->device_id);

	nc->kernel_names = kernel_names;
	nc->function_names = function_names;

	return (nc);
}

t_kernel	*init_kernel(t_context *context, unsigned int k_nbr, unsigned int f_nbr)
{
	t_kernel	*nk;

	nk = (t_kernel *)malloc(sizeof(t_kernel));
	nk->k_size = k_nbr;
	nk->kernels = (cl_kernel *)malloc(sizeof(cl_kernel) * k_nbr);

	while (k_nbr && f_nbr == 1)
	{
		printf("linear %s with %s\n", context->kernel_names[k_nbr - 1], context->function_names[0]);
		nk->kernels[k_nbr - 1] = create_kernel(context->context, context->device_id, context->kernel_names[k_nbr - 1], context->function_names[0]);
		k_nbr -= 1;
	}

	while (k_nbr && k_nbr == f_nbr)
	{
		printf("associated %s with %s\n", context->kernel_names[k_nbr - 1], context->function_names[f_nbr - 1]);
		nk->kernels[k_nbr - 1] = create_kernel(context->context, context->device_id, context->kernel_names[k_nbr - 1], context->function_names[f_nbr - 1]);
		k_nbr -= 1;
		f_nbr -= 1;
	}

	if (k_nbr)
		printf("Warning, no kernel initiated\n");

	return (nk);
}

static char		*buffer_function_to_string(int e)
{
	if (e == CREATE_BUFFER)
		return ("create_buffer");
	else if (e == CREATE_BUFFER_FROM_GL)
		return ("create_buffer_from_gl");
	else
		return (NULL);
}

cl_mem			*init_params(t_context *context, t_kernel *k, unsigned int p_nbr, t_param *params)
{
	int err;
	int kernel_nbr;
	int param_nbr;

	k->p_size = p_nbr;
	k->params = (cl_mem *)malloc(sizeof(cl_mem) * p_nbr);

	param_nbr = p_nbr;
	while (param_nbr)
	{
		printf("\tparam[%d].create_function %s\n", param_nbr - 1, buffer_function_to_string(params[param_nbr - 1].create_function));
		if (params[param_nbr - 1].create_function == CREATE_BUFFER)
			k->params[param_nbr - 1] = clCreateBuffer(context->context, params[param_nbr - 1].cl_mem_mask, params[param_nbr - 1].size, params[param_nbr - 1].whatever, &err);
		else if (params[param_nbr - 1].create_function == CREATE_BUFFER_FROM_GL)
			k->params[param_nbr - 1] = clCreateFromGLBuffer(context->context, params[param_nbr - 1].cl_mem_mask, params[param_nbr - 1].size, &err);

		// printf("err: %d\n", err);
		kernel_nbr = k->k_size;
		while (kernel_nbr)
		{
			printf("kernel[%d]: %s. Set arg n%d, size: %zu\n", kernel_nbr - 1, context->kernel_names[kernel_nbr - 1], param_nbr - 1, params[param_nbr - 1].size);
			clSetKernelArg(k->kernels[kernel_nbr - 1], param_nbr - 1, sizeof(cl_mem), &k->params[param_nbr - 1]);
			kernel_nbr -= 1;
		}
		param_nbr -= 1;
	}


	return (k->params);
}

void			run_kernel(t_context *context, t_kernel *kernel)
{
	int kernel_nbr;

	kernel_nbr = kernel->k_size;
	while (kernel_nbr)
	{
		clEnqueueNDRangeKernel(context->commands, kernel->kernels[kernel_nbr - 1], 2, NULL, kernel->GlobalWorkSize, NULL, 0, NULL, NULL );
		kernel_nbr -= 1;
	}
}
