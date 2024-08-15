/*
============================================================
                        DEMO INFO

DEMO NAME:          rects.c
DEMO WRITTEN BY:    Muukid
CREATION DATE:      2024-08-15
LAST UPDATED:       2024-08-15

============================================================
                        DEMO PURPOSE

This demo tests if rect rendering works by rendering two
rects around the center of the screen, with corner borders
appearing/disappearing every two seconds.

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

	// Border macros
	// - Width
	#define BORDER_W 16.f
	// - Width / 2
	#define BORDER_W2 (BORDER_W/2.f)
	// - Border color
	#define BORDER_COL 49.f/255.f, 51.f/255.f, 53.f/255.f

	// Rects
	mugRect rects[] = {
		// Rect 0 (rotating around circle)
		{
			// Center point (position and color)
			{ { 0.f, 0.f, 0.f }, { 158.f/255.f, 181.f/255.f, 43.f/255.f, 1.f } },
			// Dimensions
			{ 100.f, 100.f },
			// Rotation
			0
		},
		// Rect 1 (rotating around circle)
		{
			// Center point (position and color)
			{ { 0.f, 0.f, 0.f }, { BORDER_COL, 1.f } },
			// Dimensions
			{ 100.f, 100.f },
			// Rotation
			0
		},
		// Rect 2 (top corner)
		{
			// Center point (position and color)
			{ { 400.f, BORDER_W2, 0.f }, { BORDER_COL, 1.f } },
			// Dimensions
			{ 800.f, BORDER_W },
			// Rotation
			0
		},
		// Rect 3 (bottom corner)
		{
			// Center point (position and color)
			{ { 400.f, 600.f-BORDER_W2, 0.f }, { BORDER_COL, 1.f } },
			// Dimensions
			{ 800.f, BORDER_W },
			// Rotation
			0
		},
		// Rect 4 (left corner)
		{
			// Center point (position and color)
			{ { BORDER_W2, 300.f, 0.f }, { BORDER_COL, 1.f } },
			// Dimensions
			{ BORDER_W, 600.f },
			// Rotation
			0
		},
		// Rect 5 (right corner)
		{
			// Center point (position and color)
			{ { 800.f-BORDER_W2, 300.f, 0.f }, { BORDER_COL, 1.f } },
			// Dimensions
			{ BORDER_W, 600.f },
			// Rotation
			0
		}
	};

	// Rect object buffer
	mugObjects rectbuf;

	// Boolean for if we're rendering corners currently
	muBool corners = MU_TRUE;

/* Macros */

	// Pi
	#define PI 3.14159265359f

/* Functions */

	// Renders the primary rects
	void render_rects(void) {
		// Calculate the sin and cos values for each rectangle
		double time = mu_fixed_time_get();
		double r0sin = sin(time),    r0cos = cos(time);
		double r1sin = sin(time+PI), r1cos = cos(time+PI);

		// Rotate rectangles over time
		rects[0].rot = r0sin*0.678f;
		rects[1].rot = r1sin*1.345f;

		// Move rectangles in a circle over time
		rects[0].center.pos[0] = 400.f + 100.f*r0cos;
		rects[0].center.pos[1] = 300.f + 100.f*r0sin;
		rects[1].center.pos[0] = 400.f + 100.f*r1cos;
		rects[1].center.pos[1] = 300.f + 100.f*r1sin;

		// Update and render the primary rects
		mu_gobjects_subfill(gfx, rectbuf, 0, 2, rects);
		mu_gobjects_subrender(gfx, rectbuf, 0, 2);
	}

	// Renders the corner rects
	void render_corners(void) {
		// Flip if we're rendering corners every 2 seconds
		if (mu_time_get() > 2.f) {
			mu_time_set(0.f);
			corners = !corners;
		}

		// Render corners if necessary
		if (corners) {
			mu_gobjects_subrender(gfx, rectbuf, 2, 4);
		}
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
	rectbuf = mu_gobjects_create(gfx, MUG_OBJECT_RECT, 6, rects);

/* Print explanation */

	printf("Window with dark grey background should appear\n");
	printf("Two rectangles should be rotating at different rates around the center\n");
	printf("Corner borders should be appearing/disappearing every two seconds\n");
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

		// Render primary rects
		render_rects();

		// Render corner rects
		render_corners();

		// Swap graphic buffers (to present image)
		mu_graphic_swap_buffers(gfx);
		// Update graphic at ~100 FPS
		mu_graphic_update(gfx, 100.f);
	}

/* Termination */

	// Destroy buffer (required)
	rectbuf = mu_gobjects_destroy(gfx, rectbuf);

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

