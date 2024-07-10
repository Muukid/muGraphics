/*
============================================================
                        DEMO INFO

DEMO NAME:          advanced_round_rect.c
DEMO WRITTEN BY:    Muukid
CREATION DATE:      2024-07-09
LAST UPDATED:       2024-07-10

============================================================
                        DEMO PURPOSE

This demo tests if all of the features of a round rect
buffer in mug work.

============================================================
                        DEMO FUNCTION

The demo should render two spinning rounded rects, with
another set of two blipping in and out of existence in 2-
second intervals. Each rounded rect should be fluctuating in
roundedness at different rates.

============================================================
                        LICENSE INFO

This software is licensed under:
(MIT license OR public domain) AND Apache 2.0.
More explicit license information at the end of file.

============================================================
*/

/* Inclusion */

	// Include mug
	#define MUG_NAMES // For 'mug_result_get_name'
	#define MUG_IMPLEMENTATION
	#include "muGraphics.h"
	
	// Include math for sin/cos
	#include <math.h>

	// Include stdio for printing
	#include <stdio.h>

/* Global variables */

	// Global context
	mugContext mug;

	// Graphic to be rendered to
	muGraphic gfx;

	// The API of the graphic
	muGraphicAPI api = MUG_OPENGL;

	// The rounded rectangles to be rendered
	muRoundRect round_rects[4] = {
		// Round rect #0
		{
			// Center
			{
				{ 400, 300 }, // (position)
				{ 163.0/255.0, 206.0/255.0, 241.0/255.0, 1.0 }, // (color)
			},
			// Dimensions
			{ 100, 100 },
			// Rotation
			0.0,
			// Roundedness
			0
		},
		// Round rect #1
		{
			// Center
			{
				{ 400, 300 }, // (position)
				{ 96.0/255.0, 150.0/255.0, 186.0/255.0, 1.0 }, // (color)
			},
			// Dimensions
			{ 100, 100 },
			// Rotation
			0.0,
			// Roundedness
			0
		},
		// Round rect #2
		{
			// Center
			{
				{ 400, 300 }, // (position)
				{ 39.0/255.0, 76.0/255.0, 119.0/255.0, 1.0 }, // (color)
			},
			// Dimensions
			{ 100, 100 },
			// Rotation
			0.0,
			// Roundedness
			0
		},
		// Round rect #3
		{
			// Center
			{
				{ 400, 300 }, // (position)
				{ 139.0/255.0, 140.0/255.0, 137.0/255.0, 1.0 }, // (color)
			},
			// Dimensions
			{ 100, 100 },
			// Rotation
			0.0,
			// Roundedness
			0
		},
	};

	// State to represent what's rendering;
	// 0 means just the first 2 round rects, 1 means all
	int state = 0;

	// The buffer used for rendering the rounded rectangle
	mugObjectBuffer round_rect_buffer;

/* Macros */

	// Pi
	#define PI 3.14159265359

/* Main function */

int main(void) {
	/* Initiation */

		// Create global context
		mug_context_create(&mug, MU_WINDOW_SYSTEM_AUTO, MU_TRUE);

		// Create graphic
		gfx = mu_graphic_create_via_window(api, "Advanced rounded rectangle", 800, 600, mu_window_default_create_info());

		// Create rectangle buffer
		round_rect_buffer = mu_gobj_buffer_create(gfx, MUG_OBJECT_ROUND_RECT, 2, round_rects);

	/* Main loop */

		while (mu_graphic_exists(gfx)) {
			// Clear the graphic
			mu_graphic_clear(gfx, 231.0/255.0, 236.0/255.0, 239.0/255.0, 1.0);

			// Add/Remove round rects to buffer each 2 seconds
			if (mu_time_get() >= 2.0) {
				mu_time_set(0.0);

				if (state == 0) {
					// Add
					mu_gobj_buffer_resize(gfx, round_rect_buffer, 4, 0);
					state = 1;
				} else {
					// Remove
					mu_gobj_buffer_resize(gfx, round_rect_buffer, 2, 0);
					state = 0;
				}
			}

			// Calculate the sin and cos values for each rounded rectangle
			double time = mu_time_get_fixed();
			double r0sin = sin(time),          r0cos = cos(time);
			double r1sin = sin(time+PI),       r1cos = cos(time+PI);
			double r2sin = sin(time+(PI*0.5)), r2cos = cos(time+(PI*0.5));
			double r3sin = sin(time+(PI*1.5)), r3cos = cos(time+(PI*1.5));

			// Rotate rectangles over time
			round_rects[0].rot = r0sin*0.678;
			round_rects[1].rot = r1sin*1.345;
			round_rects[2].rot = r2cos*1.179;
			round_rects[3].rot = r3cos*0.717;

			// Change roundedness over time
			round_rects[0].round = ((sin(time*1.816))+1.0)*25.0;
			round_rects[1].round = ((sin(time*1.207))+1.0)*25.0;
			round_rects[2].round = ((cos(time*2.305))+1.0)*25.0;
			round_rects[3].round = ((cos(time*1.581))+1.0)*25.0;

			// Move rectangles in a circle over time
			round_rects[0].center.pos.x = 400.0 + 150.0*r0cos;
			round_rects[0].center.pos.y = 300.0 + 150.0*r0sin;
			round_rects[1].center.pos.x = 400.0 + 150.0*r1cos;
			round_rects[1].center.pos.y = 300.0 + 150.0*r1sin;
			round_rects[2].center.pos.x = 400.0 + 150.0*r2cos;
			round_rects[2].center.pos.y = 300.0 + 150.0*r2sin;
			round_rects[3].center.pos.x = 400.0 + 150.0*r3cos;
			round_rects[3].center.pos.y = 300.0 + 150.0*r3sin;

			// Subfill and render two primary round rects
			mu_gobj_buffer_subfill(gfx, round_rect_buffer, 0, 2, round_rects);
			mu_gobj_buffer_subrender(gfx, round_rect_buffer, 0, 2);

			// Subfill and render two alt round rects if we should
			if (state == 1) {
				mu_gobj_buffer_subfill(gfx, round_rect_buffer, 2, 2, &round_rects[2]);
				mu_gobj_buffer_subrender(gfx, round_rect_buffer, 2, 2);
			}

			// Swap graphic buffers (to present image)
			mu_graphic_swap_buffers(gfx);

			// Update graphic at ~100 fps
			mu_graphic_update(gfx, 100);
		}

	/* Termination */

		// Destroy rounded rectangle buffer
		round_rect_buffer = mu_gobj_buffer_destroy(gfx, round_rect_buffer);

		// Destroy graphic
		gfx = mu_graphic_destroy(gfx);

		// Destroy global context
		mug_context_destroy(&mug);

		// Print result
		printf("%s\n", mug_result_get_name(mug.result));

	return 0;
}

/*
For provided source code:
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

	Licensed under the Apache License, Version 2.0 (the "License"); you may not
	use this file except in compliance with the License. You may obtain a copy of
	the License at

	http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software distributed
	under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
	CONDITIONS OF ANY KIND, either express or implied. See the License for the
	specific language governing permissions and limitations under the License.
*/

