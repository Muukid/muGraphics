/*
============================================================
                        DEMO INFO

DEMO NAME:          round_rects.c
DEMO WRITTEN BY:    Muukid
CREATION DATE:      2024-08-16
LAST UPDATED:       2024-08-16

============================================================
                        DEMO PURPOSE

This demo tests if round rect rendering works by rendering 4
round rects rotating around the center, with two disappear-
ing/reappearing every two seconds. Each rect should be fluc-
tuating in roundness smoothly, and should be rotating at a
unique rate back and forth.

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

	// The round rects to be rendered (only initially defining color and radius)
	mugRoundRect roundrects[4] = {
		{ { { 0.f }, { 163.f/255.f, 206.f/255.f, 241.f/255.f, 1.f } }, { 100.f, 100.f }, 0.f, 10.f },
		{ { { 0.f }, { 96.f /255.f, 150.f/255.f, 186.f/255.f, 1.f } }, { 100.f, 100.f }, 0.f, 10.f },
		{ { { 0.f }, { 39.f /255.f, 76.f /255.f, 119.f/255.f, 1.f } }, { 100.f, 100.f }, 0.f, 10.f },
		{ { { 0.f }, { 139.f/255.f, 140.f/255.f, 137.f/255.f, 1.f } }, { 100.f, 100.f }, 0.f, 10.f }
	};

	// Boolean deeming whether or not to render roundrects[2] and roundrects[3]
	// Changes every 2 seconds
	muBool render_alt = MU_TRUE;

	// Round rect object buffer
	mugObjects roundrectbuf;

/* Macros */

	// Pi
	#define PI 3.14159265359

/* Functions */

	// Flips the state of render_alt every 2 seconds
	void handle_render_alt(void) {
		// Every two seconds:
		if (mu_time_get() >= 2.0) {
			// Reset timer
			mu_time_set(0.0);
			// Flip render_alt
			render_alt = !render_alt;
		}
	}

	// Calculates the position/exponent of each round rect for a frame
	void update_roundrects(void) {
		// Calculate the sin and cos values for each round rect
		double time = mu_fixed_time_get();
		double r0sin = sin(time),          r0cos = cos(time);
		double r1sin = sin(time+PI),       r1cos = cos(time+PI);
		double r2sin = sin(time+(PI*0.5)), r2cos = cos(time+(PI*0.5));
		double r3sin = sin(time+(PI*1.5)), r3cos = cos(time+(PI*1.5));

		// Change radius over time
		roundrects[0].radius = 25.0*(sin(time*1.816)+1.0);
		roundrects[1].radius = 25.0*(sin(time*1.207)+1.0);
		roundrects[2].radius = 25.0*(sin(time*2.305)+1.0);
		roundrects[3].radius = 25.0*(sin(time*1.581)+1.0);

		// Move round rects around the center over time
		// - Round rect 0
		roundrects[0].center.pos[0] = 400.0 + (150.0*r0cos);
		roundrects[0].center.pos[1] = 300.0 + (150.0*r0sin);
		// - Round rect 1
		roundrects[1].center.pos[0] = 400.0 + (150.0*r1cos);
		roundrects[1].center.pos[1] = 300.0 + (150.0*r1sin);
		// - Round rect 2
		roundrects[2].center.pos[0] = 400.0 + (150.0*r2cos);
		roundrects[2].center.pos[1] = 300.0 + (150.0*r2sin);
		// - Round rect 3
		roundrects[3].center.pos[0] = 400.0 + (150.0*r3cos);
		roundrects[3].center.pos[1] = 300.0 + (150.0*r3sin);

		// Rotate round rects over time
		roundrects[0].rot = r0sin*1.8364;
		roundrects[1].rot = r1sin*1.4018;
		roundrects[2].rot = r2sin*0.9584;
		roundrects[3].rot = r3sin*2.1239;

		// Subfill two primary round rects
		mu_gobjects_subfill(gfx, roundrectbuf, 0, 2, roundrects);
		// Subfill two alt round rects if we should
		if (render_alt) {
			mu_gobjects_subfill(gfx, roundrectbuf, 2, 2, &roundrects[2]);
		}
	}

	// Renders round rects
	void render_roundrects(void) {
		// Render two primary round rects
		mu_gobjects_subrender(gfx, roundrectbuf, 0, 2);
		// Render two alt round rects if we should
		if (render_alt) {
			mu_gobjects_subrender(gfx, roundrectbuf, 2, 2);
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
	roundrectbuf = mu_gobjects_create(gfx, MUG_OBJECT_ROUND_RECT, 4, roundrects);

/* Print explanation */

	printf("Window with dark grey background should appear\n");
	printf("Four round rects should be spinning around the center, rotating back and forth at differing rates\n");
	printf("The round rects should be smoothly fluctuating in the roundedness of their edges\n");
	printf("The same two round rects should be appearing/disappearing every two seconds\n");
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

		// Update state of render_alt
		handle_render_alt();

		// Update round rect data
		update_roundrects();

		// Render round rect data
		render_roundrects();

		// Swap graphic buffers (to present image)
		mu_graphic_swap_buffers(gfx);
		// Update graphic at ~100 FPS
		mu_graphic_update(gfx, 100.f);
	}

/* Termination */

	// Destroy buffer (required)
	roundrectbuf = mu_gobjects_destroy(gfx, roundrectbuf);

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

