/*
============================================================
                        DEMO INFO

DEMO NAME:          advanced_rect.c
DEMO WRITTEN BY:    Muukid
CREATION DATE:      2024-06-18
LAST UPDATED:       2024-07-09

============================================================
                        DEMO PURPOSE

This demo tests if all of the features of a rect buffer in
mug work.

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

/* Global variables */
	
	// Global context
	mugContext mug;

	// Graphic to be rendered to
	muGraphic gfx;

	// The API of the graphic
	muGraphicAPI api = MUG_OPENGL;

	// The primary rectangles to be rendered
	muRect rects[] = {
		{ // Rect 1
			{ // Point
				{ 0, 0 }, // (position)
				{ 57.0/255.0, 62.0/255.0, 65.0/255.0, 1 } // (color, "onyx")
			},
			{ // Dimensions
				100, 100
			},
			// Rotation
			0
		},
		{ // Rect 2
			{ // Point
				{ 0, 0 }, // (position)
				{ 88.0/255.0, 123.0/255.0, 127.0/255.0, 1 } // (color, "myrtle green")
			},
			{ // Dimensions
				100, 100
			},
			// Rotation
			0
		}
	};

	#define BORDER_W 20
	#define BORDER_W2 (BORDER_W/2)
	#define BORDER_COL 30.0/255.0, 32.0/255.0, 25.0/255.0 // ("eerie black")
	// Border rectangles
	muRect borders[] = {
		{ // Top
			{ // Point
				{ 400, BORDER_W2 }, // (position)
				{ BORDER_COL, 1 } // (color)
			},
			{ // Dimensions
				800, BORDER_W
			},
			// Rotation
			0
		},
		{ // Bottom
			{ // Point
				{ 400, 600-BORDER_W2 }, // (position)
				{ BORDER_COL, 1 } // (color)
			},
			{ // Dimensions
				800, BORDER_W
			},
			// Rotation
			0
		},
		{ // Left
			{ // Point
				{ BORDER_W2, 300 }, // (position)
				{ BORDER_COL, 1 } // (color)
			},
			{ // Dimensions
				BORDER_W, 600
			},
			// Rotation
			0
		},
		{ // Right
			{ // Point
				{ 800-BORDER_W2, 300 }, // (position)
				{ BORDER_COL, 1 } // (color)
			},
			{ // Dimensions
				BORDER_W, 600
			},
			// Rotation
			0
		},
	};

	// The buffer used for rendering the rectangle
	mugObjectBuffer rect_buffer;
	// The size of the rect buffer in rects
	size_m rect_count = 2;

/* Macros */

	// Pi
	#define PI 3.14159265359

/* Main function */

int main(void) {
	/* Initiation */

		// Create global context
		mug_context_create(&mug, MU_WINDOW_SYSTEM_AUTO, MU_TRUE);

		// Create graphic
		gfx = mu_graphic_create_via_window(api, "Advanced rectangle", 800, 600, mu_window_default_create_info());

		// Create rectangle buffer
		rect_buffer = mu_gobj_buffer_create(gfx, MUG_OBJECT_RECT, 2, rects);

	/* Main loop */

		while (mu_graphic_exists(gfx)) {
			// Clear the graphic with "timberwolf"
			mu_graphic_clear(gfx, 211.0/255.0, 208.0/255.0, 203.0/255.0, 1.0);

			// Add/Remove borders to buffer each 2 seconds
			if (mu_time_get() >= 2.0) {
				mu_time_set(0.0);

				if (rect_count == 2) {
					mu_gobj_buffer_resize(gfx, rect_buffer, 6, 0);
					mu_gobj_buffer_subfill(gfx, rect_buffer, 2, 4, borders);
					rect_count = 6;
				} else {
					mu_gobj_buffer_resize(gfx, rect_buffer, 2, 0);
					rect_count = 2;
				}
			}

			// Render borders if necessary
			if (rect_count == 6) {
				mu_gobj_buffer_subrender(gfx, rect_buffer, 2, 4);
			}

			// Calculate the sin and cos values for each rectangle
			double time = mu_time_get_fixed();
			double r0sin = sin(time),    r0cos = cos(time);
			double r1sin = sin(time+PI), r1cos = cos(time+PI);

			// Rotate rectangles over time
			rects[0].rot = r0sin*0.678;
			rects[1].rot = r1sin*1.345;

			// Move rectangles in a circle over time
			rects[0].center.pos.x = 400.0 + 100.0*r0cos;
			rects[0].center.pos.y = 300.0 + 100.0*r0sin;
			rects[1].center.pos.x = 400.0 + 100.0*r1cos;
			rects[1].center.pos.y = 300.0 + 100.0*r1sin;

			// Update primary rectangle buffer data
			mu_gobj_buffer_subfill(gfx, rect_buffer, 0, 2, rects);

			// Render the rectangle
			mu_gobj_buffer_subrender(gfx, rect_buffer, 0, 2);

			// Swap graphic buffers (to present image)
			mu_graphic_swap_buffers(gfx);

			// Update graphic at ~100 fps
			mu_graphic_update(gfx, 100);
		}

	/* Termination */

		// Destroy rectangle buffer
		rect_buffer = mu_gobj_buffer_destroy(gfx, rect_buffer);

		// Destroy graphic
		gfx = mu_graphic_destroy(gfx);

		// Destroy global context
		mug_context_destroy(&mug);

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

