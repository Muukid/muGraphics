/*
============================================================
                        DEMO INFO

DEMO NAME:          lines.c
DEMO WRITTEN BY:    Muukid
CREATION DATE:      2024-08-13
LAST UPDATED:       2024-08-13

============================================================
                        DEMO PURPOSE

This demo tests if line rendering works by rendering a
series of lines moving around in a smooth trail.

If the user presses escape, the window will close.

============================================================
                        LICENSE INFO

This software is licensed under:
(MIT license OR public domain) AND Apache 2.0.
More explicit license information at the end of file.

============================================================
*/

/* Inclusion */
	
	// Include mug
	#define MU_SUPPORT_OPENGL // (For OpenGL support)
	#define MUG_NAMES // (For mug name functions)
	#define MUCOSA_NAMES // (For muCOSA name functions)
	#define MUG_IMPLEMENTATION // (For source code)
	#include "muGraphics.h"

	// Include stdio for printing
	#include <stdio.h>

	// Include math for math functions
	#include <math.h>

	// Include stdlib for random
	#include <stdlib.h>

/* Variables */
	
	// Global context
	mugContext mug;

	// Graphic handle
	muGraphic gfx;

	// Graphic system
	muGraphicSystem gfx_system = MU_GRAPHIC_OPENGL;

	// The window system
	muWindowSystem window_system = MU_WINDOW_NULL; // (Auto)

	// Pixel format
	muPixelFormat format = {
		// RGBA bits
		8, 8, 8, 8,
		// Depth bits
		24,
		// Stencil bits
		0,
		// Samples
		1
	};

	// Window information
	muWindowInfo wininfo = {
		// Title
		(char*)"Window",
		// Resolution (width & height)
		800, 600,
		// Min/Max resolution (none)
		0, 0, 0, 0,
		// Coordinates (x and y)
		50, 50,
		// Pixel format
		&format,
		// Callbacks (default)
		0
	};

	// Window handle
	muWindow win;

	// Window keyboard map
	muBool* keyboard;

	// Lines
	#define LINE_LEN 512
	mugLine lines[LINE_LEN];

	// Line object buffer
	mugObjects linebuf;

/* Macros */

	// Pi multiplied; used as a cycle through the circle
	#define PI (3.14159265359f*8.f)

/* Functions */

	// Initiates all lines' colors (and position to (0,0) to be set later)
	void init_lines(void) {
		// Loop through each line
		for (uint32_m i = 0; i < LINE_LEN; ++i) {
			// Set point positions to (0, 0)
			// Depth will increase as lines progress
			lines[i].points[0].pos[0] = lines[i].points[0].pos[1] = 0.f;
			lines[i].points[0].pos[2] = ((float)i) / ((float)LINE_LEN);
			lines[i].points[1] = lines[i].points[0];
			// Set each color channels of points to 0 or 1 based on random chance
			// (First color is equal to previous line's last point if there is one)
			if (i != 0) {
				lines[i].points[0] = lines[i-1].points[1];
			} else {
				lines[i].points[0].col[0] = rand() & 1;
				lines[i].points[0].col[1] = rand() & 1;
				lines[i].points[0].col[2] = rand() & 1;
			}
			lines[i].points[1].col[0] = rand() & 1;
			lines[i].points[1].col[1] = rand() & 1;
			lines[i].points[1].col[2] = rand() & 1;
			// (Except for alpha, set to 1)
			lines[i].points[0].col[3] = 1.f;
			lines[i].points[1].col[3] = 1.f;
		}
	}

	// Updates all lines to rotate around the center
	void update_lines(uint32_m dim[2]) {
		// Half of dim
		float dim_d2[2] = { ((float)dim[0])/2.f, ((float)dim[1])/2.f };
		// Quarter of dim
		float dim_d4[2] = { ((float)dim[0])/4.f, ((float)dim[1])/4.f };

		// Loop through each line
		for (uint32_m i = 0; i < LINE_LEN; ++i) {
			// Calculate percentage of way through all lines by point
			float point0_per = ((float)i) / ((float)LINE_LEN);
			float point1_per = ((float)(i+1)) / ((float)LINE_LEN);
			// Calculate percentage of way through circle
			// as a percentage of pi
			float p0 = point0_per * PI;
			float p1 = point1_per * PI;
			// Add time to make it rotate over time
			p0 += mu_time_get();
			p1 += mu_time_get();
			// Update position's x and y position, making it swirl around
			lines[i].points[0].pos[0] = (dim_d2[0]+(cosf(p0)*dim_d4[0]))*((cosf(p0*0.83f)/3.f)+1.f);
			lines[i].points[0].pos[1] = (dim_d2[1]+(sinf(p0)*dim_d4[1]))*((sinf(p0*0.64f)/3.f)+1.f);
			lines[i].points[1].pos[0] = (dim_d2[0]+(cosf(p1)*dim_d4[0]))*((cosf(p1*0.83f)/3.f)+1.f);
			lines[i].points[1].pos[1] = (dim_d2[1]+(sinf(p1)*dim_d4[1]))*((sinf(p1*0.64f)/3.f)+1.f);
			// Make points more transparent as we go through line list
			lines[i].points[0].col[3] = point0_per;
			lines[i].points[1].col[3] = point1_per;
		}

		// Re-fill lines
		mu_gobjects_fill(gfx, linebuf, lines);
	}

int main(void)
{

/* Initiation */

	printf("Initiating...\n");

	// Initiate mug
	mug_context_create(&mug, window_system, MU_TRUE);

	// Print currently running window system
	printf("Running window system \"%s\"\n",
		mu_window_system_get_nice_name(muCOSA_context_get_window_system(&mug.cosa))
	);

	// Create graphic via window using OpenGL
	gfx = mu_graphic_create_window(gfx_system, &wininfo);

	// Get window handle
	win = mu_graphic_get_window(gfx);
	// Get window keyboard map
	mu_window_get(win, MU_WINDOW_KEYBOARD_MAP, &keyboard);

	// Initiate line values
	init_lines();

	// Create buffer
	linebuf = mu_gobjects_create(gfx, MUG_OBJECT_LINE, LINE_LEN, lines);

/* Print explanation */

	printf("Window with dark grey background should appear\n");
	printf("Lines should be moving around in a trail\n");
	printf("Press escape to close window\n");

/* Main loop */

	// Run frame-by-frame while graphic exists:
	while (mu_graphic_exists(gfx))
	{
		// Close if escape is pressed
		if (keyboard[MU_KEYBOARD_ESCAPE]) {
			mu_window_close(win);
			continue;
		}

		// Clear the graphic with a slightly green-ish very dark grey
		mu_graphic_clear(gfx, 15.f/255.f, 17.f/255.f, 15.f/255.f);

		// Get window dimensions
		uint32_m dim[2];
		mu_window_get(win, MU_WINDOW_DIMENSIONS, dim);

		// Update line positions
		update_lines(dim);

		// Render lines
		mu_gobjects_render(gfx, linebuf);

		// Swap graphic buffers (to present image)
		mu_graphic_swap_buffers(gfx);
		// Update graphic at ~100 FPS
		mu_graphic_update(gfx, 100.f);
	}

/* Termination */

	// Destroy buffer (required)
	linebuf = mu_gobjects_destroy(gfx, linebuf);

	// Destroy graphic (required)
	gfx = mu_graphic_destroy(gfx);

	// Terminate mug (required)
	mug_context_destroy(&mug);

	// Print possible error
	if (mug.result != MUG_SUCCESS) {
		printf("Something went wrong during the program's life; result: %s\n",
			mug_result_get_name(mug.result)
		);
	} else {
		printf("Successful\n");
	}

	return 0;
}

/*
For all source code:

	------------------------------------------------------------------------------
	This software is available under 2 licenses -- choose whichever you prefer.
	------------------------------------------------------------------------------
	ALTERNATIVE A - MIT License
	Copyright (c) 2024 Hum
	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in
	the Software without restriction, including without limitation the rights to
	use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
	of the Software, and to permit persons to whom the Software is furnished to do
	so, subject to the following conditions:
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
	------------------------------------------------------------------------------
	ALTERNATIVE B - Public Domain (www.unlicense.org)
	This is free and unencumbered software released into the public domain.
	Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
	software, either in source code form or as a compiled binary, for any purpose,
	commercial or non-commercial, and by any means.
	In jurisdictions that recognize copyright laws, the author or authors of this
	software dedicate any and all copyright interest in the software to the public
	domain. We make this dedication for the benefit of the public at large and to
	the detriment of our heirs and successors. We intend this dedication to be an
	overt act of relinquishment in perpetuity of all present and future rights to
	this software under copyright law.
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
	ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
	WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
	------------------------------------------------------------------------------

For Khronos specifications:
	
	Copyright (c) 2013-2020 The Khronos Group Inc.

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.

*/

