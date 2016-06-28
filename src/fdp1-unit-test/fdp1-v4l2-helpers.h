/*
 * FDP1 Unit Test Utility
 *      Author: Kieran Bingham
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version
 */


#include <linux/videodev2.h>

#ifndef _FDP1_V4L2_HELPERS_H_
#define _FDP1_V4L2_HELPERS_H_

struct fdp1_v4l2_dev {
	int fd;

	struct v4l2_capability cap;
	struct v4l2_format fmt;
	struct v4l2_control ctrl;
};

struct fdp1_v4l2_buffer {
	uint32_t n_planes;
	struct v4l2_plane planes[3];
	uint32_t sizes[3]; // plane sizes
	char * mem[3];
};

#define MAX_BUFFER_POOL_SIZE 4
struct fdp1_v4l2_buffer_pool {
	unsigned int qty;
	struct fdp1_v4l2_buffer buffer[MAX_BUFFER_POOL_SIZE];
};

void start_test(struct fdp1_context * fdp1, char * test);
struct fdp1_v4l2_dev * fdp1_v4l2_open(struct fdp1_context * fdp1);
int fdp1_v4l2_close(struct fdp1_v4l2_dev * dev);

int fdp1_v4l2_set_fmt(struct fdp1_context * fdp1,
		      struct fdp1_v4l2_dev * v4l2_dev,
		      uint32_t type,
		      uint32_t width,
		      uint32_t height,
		      uint32_t fourcc,
		      uint32_t field);

struct fdp1_v4l2_buffer_pool *
fdp1_v4l2_allocate_buffers(struct fdp1_context * fdp1,
			   struct fdp1_v4l2_dev * v4l2_dev,
			   uint32_t type,
			   uint32_t buffers_requested);

void fdp1_v4l2_free_buffers(struct fdp1_v4l2_buffer_pool * pool);

#endif /* _FDP1_V4L2_HELPERS_H_ */
