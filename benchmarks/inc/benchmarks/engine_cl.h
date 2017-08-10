#ifndef ENGINE_CL_H
#define ENGINE_CL_H

#ifdef __APPLE__
  #include <OpenCL/cl.h>
#else
  #include <CL/cl.h>
#endif


/* --------------------------------------------------------------------------------------------- */

typedef struct
{
  cl_device_id device_id;

  cl_context context;
  cl_command_queue queue;
  cl_event event;  
} engine_cl;


typedef struct
{
  cl_platform_id * platforms;
  cl_device_id * devices;
} devices_cl;

/* --------------------------------------------------------------------------------------------- */

void engine_cl_init (engine_cl * t, devices_cl * d);
void engine_cl_del (engine_cl * t);


/* --------------------------------------------------------------------------------------------- */

void devices_cl_init (devices_cl * d);
void devices_cl_del (devices_cl * d);

cl_device_id get_device_cl_id (devices_cl * d, const size_t device_index);

#endif
