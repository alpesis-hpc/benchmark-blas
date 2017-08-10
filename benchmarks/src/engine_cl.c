#include <benchmarks/engine_cl.h>


/* --------------------------------------------------------------------------------------------- */

void engine_cl_init (engine_cl * t, devices_cl * d)
{
  t->device_id = get_device_cl_id (d, 0);

  // creates the OpenCL context, queue, and an event
  t->context = clCreateContext (NULL, 1, &t->device_id, NULL, NULL, NULL);
  t->queue = clCreateCommandQueue (t->context, t->device_id, 0, NULL);
  t->event = NULL;
}


void engine_cl_del (engine_cl * t)
{
  clReleaseCommandQueue (t->queue);
  clReleaseContext (t->context);

  free (t);
}

/* --------------------------------------------------------------------------------------------- */

void devices_cl_init (devices_cl * d)
{
  // OpenCL platform settings
  const size_t platform_id = 0;
 
  // initialize the OpenCL platform
  cl_uint num_platforms;
  clGetPlatformIDs(0, NULL, &num_platforms);
  d->platforms = (cl_platform_id*)malloc(num_platforms*sizeof(cl_platform_id));
  clGetPlatformIDs(num_platforms, d->platforms, NULL);
  cl_platform_id platform = d->platforms[platform_id];

  // initialize the OpenCL device
  cl_uint num_devices;
  clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
  d->devices = (cl_device_id*)malloc(num_devices*sizeof(cl_device_id));
  clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, num_devices, d->devices, NULL);
}


void devices_cl_del (devices_cl * d)
{
  free (d->platforms);
  free (d->devices);
}

 
cl_device_id get_device_cl_id (devices_cl * d, const size_t device_index)
{
  return d->devices[device_index]; 
}
