/*
============================================================
                        DEMO INFO

DEMO NAME:          triangle.c
DEMO WRITTEN BY:    Muukid
CREATION DATE:      2024-08-13
LAST UPDATED:       2024-08-13

============================================================
                        DEMO PURPOSE

This demo tests if triangle rendering works by drawing a
multi-color triangle onto the screen.

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

/* Variables */
	
	// Global context
	mugContext mug;

	// Graphic handle
	muGraphic gfx;

	// Graphic system
	muGraphicSystem gfx_system = MU_GRAPHIC_OPENGL;

	// The window system
	muWindowSystem window_system = MU_WINDOW_NULL; // (Auto)

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
		0,
		// Callbacks (default)
		0
	};

	// Window handle
	muWindow win;

	// Window keyboard map
	muBool* keyboard;

	// Triangle
	mugTriangle triangle = {
		// Points
		{
			// Position                Color
			{ { 400.f, 150.f, 0.f }, { 1.f, 0.f, 0.f, 1.f } },
			// Position                Color
			{ { 200.f, 450.f, 0.f }, { 0.f, 1.f, 0.f, 1.f } },
			// Position                Color
			{ { 600.f, 450.f, 0.f }, { 0.f, 0.f, 1.f, 1.f } }
		}
	};

	// Triangle buffer
	mugObjects tribuf;

/* Functions */

	// Sinf but between 0 and 1
	float fixed_sinf(float n) {
		return (sinf(n) + 1.f) / 2.f;
	}

	// Scaler for all random sin(time*random) calculations
	// (All random values lie between 0 and 10)
	#define scaler 0.2f

	// Updates triangle colors
	void update_triangle_colors(void) {
		// Get time
		float time = mu_time_get();

		// Fluctuate each triangle's alpha by a random amount
		// - Point 0
		triangle.points[0].col[0] = fixed_sinf(time*1.59634f*scaler);
		triangle.points[0].col[1] = fixed_sinf(time*4.03644f*scaler);
		triangle.points[0].col[2] = fixed_sinf(time*4.86660f*scaler);
		triangle.points[0].col[3] = fixed_sinf(time*2.73407f*scaler);
		// - Point 1
		triangle.points[1].col[0] = fixed_sinf(time*6.12220f*scaler);
		triangle.points[1].col[1] = fixed_sinf(time*3.70472f*scaler);
		triangle.points[1].col[2] = fixed_sinf(time*8.57223f*scaler);
		triangle.points[1].col[3] = fixed_sinf(time*8.84136f*scaler);
		// - Point 2
		triangle.points[2].col[0] = fixed_sinf(time*8.90930f*scaler);
		triangle.points[2].col[1] = fixed_sinf(time*9.22284f*scaler);
		triangle.points[2].col[2] = fixed_sinf(time*7.03314f*scaler);
		triangle.points[2].col[3] = fixed_sinf(time*3.18437f*scaler);
	}

	// Updates triangle positions
	void update_triangle_positions(uint32_m dim[2]) {
		// Convert dimensions to float
		float fdim[2] = { (float)dim[0], (float)dim[1] };

		// Scale positions based on dimensions
		// - Point 0
		triangle.points[0].pos[0] = .5f  * fdim[0];
		triangle.points[0].pos[1] = .25f * fdim[1];
		// - Point 1
		triangle.points[1].pos[0] = .25f * fdim[0];
		triangle.points[1].pos[1] = .75f * fdim[1];
		// - Point 2
		triangle.points[2].pos[0] = .75f * fdim[0];
		triangle.points[2].pos[1] = .75f * fdim[1];
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

	// Create buffer
	tribuf = mu_gobjects_create(gfx, MUG_OBJECT_TRIANGLE, 1, &triangle);

/* Print explanation */

	printf("Window with dark grey background should appear\n");
	printf("Multi-colored triangle should be visible on screen\n");
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

		// Update triangle colors
		update_triangle_colors();

		// Get window dimensions
		uint32_m dim[2];
		mu_window_get(win, MU_WINDOW_DIMENSIONS, dim);

		// Update triangle positions
		update_triangle_positions(dim);

		// Re-fill buffer
		mu_gobjects_fill(gfx, tribuf, &triangle);

		// Render triangle
		mu_gobjects_render(gfx, tribuf);

		// Swap graphic buffers (to present image)
		mu_graphic_swap_buffers(gfx);
		// Update graphic at ~100 FPS
		mu_graphic_update(gfx, 100.f);
	}

/* Termination */

	// Destroy buffer (required)
	tribuf = mu_gobjects_destroy(gfx, tribuf);

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

