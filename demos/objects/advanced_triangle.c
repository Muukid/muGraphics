/*
============================================================
                        DEMO INFO

DEMO NAME:          advanced_triangle.c
DEMO WRITTEN BY:    Muukid
CREATION DATE:      2024-06-15
LAST UPDATED:       2024-06-15

============================================================
                        DEMO PURPOSE

This demo tests if all of the features of a triangle buffer
in mug work.

============================================================
                        DEMO FUNCTION

The demo should render a triangle, which can be toggled into
a triple triangle by pressing the left and right arrow keys.
It should also toggle rendering of triangles in the 4
corners of the screen by pressing space.

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

	// Include math (for sin)
	#include <math.h>

/* Global variables */

	// Global context
	mugContext mug;

	// Graphic to be rendered to
	muGraphic gfx;

	// The API of the graphic
	muGraphicAPI api = MUG_OPENGL;

	// The triangles to be rendered
	muTriangle triangles[] = {
		/* First triangle */
		{
			{ // Point 0
				{ 400, 200 }, // (position)
				{ 1.0, 0.0, 0.0, 1.0 } // (colour)
			},
			{ // Point 1
				{ 200, 400 }, // (position)
				{ 0.0, 1.0, 0.0, 1.0 } // (colour)
			},
			{ // Point 2
				{ 600, 400 }, // (position)
				{ 0.0, 0.0, 1.0, 1.0 } // (colour)
			}
		},

		/* Other three triangles that form a bigger triangle */

		// #1
		{
			{ // Point 0
				{ 400, 200 }, // (position)
				{ 1.0, 0.0, 0.0, 1.0 } // (colour)
			},
			{ // Point 1
				{ 300, 300 }, // (position)
				{ 0.0, 1.0, 0.0, 1.0 } // (colour)
			},
			{ // Point 2
				{ 500, 300 }, // (position)
				{ 0.0, 1.0, 0.0, 1.0 } // (colour)
			}
		},

		// #2
		{
			{ // Point 0
				{ 300, 300 }, // (position)
				{ 0.0, 1.0, 0.0, 1.0 } // (colour)
			},
			{ // Point 1
				{ 200, 400 }, // (position)
				{ 0.0, 0.0, 1.0, 1.0 } // (colour)
			},
			{ // Point 2
				{ 400, 400 }, // (position)
				{ 0.0, 0.0, 1.0, 1.0 } // (colour)
			}
		},

		// #3
		{
			{ // Point 0
				{ 500, 300 }, // (position)
				{ 0.0, 1.0, 0.0, 1.0 } // (colour)
			},
			{ // Point 1
				{ 400, 400 }, // (position)
				{ 0.0, 0.0, 1.0, 1.0 } // (colour)
			},
			{ // Point 2
				{ 600, 400 }, // (position)
				{ 0.0, 0.0, 1.0, 1.0 } // (colour)
			}
		}
	};

	// The corner triangles
	muTriangle corner_triangles[4] = {
		// Top-left
		{
			{ { 0,   0   }, { 1.0, 0.0, 0.0, 1.0 } },
			{ { 100, 0   }, { 1.0, 0.0, 0.0, 1.0 } },
			{ { 0,   100 }, { 1.0, 0.0, 0.0, 1.0 } }
		},
		// Top-right
		{
			{ { 800, 0   }, { 0.0, 1.0, 0.0, 1.0 } },
			{ { 700, 0   }, { 0.0, 1.0, 0.0, 1.0 } },
			{ { 800, 100 }, { 0.0, 1.0, 0.0, 1.0 } }
		},
		// Bottom-left
		{
			{ { 0,   600 }, { 0.0, 0.0, 1.0, 1.0 } },
			{ { 100, 600 }, { 0.0, 0.0, 1.0, 1.0 } },
			{ { 0,   500 }, { 0.0, 0.0, 1.0, 1.0 } }
		},
		// Bottom-right
		{
			{ { 800, 600 }, { 1.0, 1.0, 1.0, 1.0 } },
			{ { 700, 600 }, { 1.0, 1.0, 1.0, 1.0 } },
			{ { 800, 500 }, { 1.0, 1.0, 1.0, 1.0 } }
		},
	};

	// The buffer used for rendering the triangle
	mugObjectBuffer triangle_buffer;

	// The size of the buffer in triangles
	size_m buffer_size = 4;

	// State for which triangles are being rendered
	int state = 0; // 0 = 1 triangle, 1 = 3 triangles

	// Boolean for whether or not to render corner triangles
	muBool corners = MU_FALSE;

/* Outside functions */

	// Keyboard key callback to handle key press logic
	void keyboard_key_callback(muWindow win, muKeyboardKey key, muButtonState keystate) {
		if (keystate != MU_BUTTON_STATE_HELD) {
			return;
		}

		// State changing
		if (key == MU_KEYBOARD_KEY_RIGHT) {
			state += 1;
			if (state > 1) {
				state = 0;
			}
			return;
		}
		if (key == MU_KEYBOARD_KEY_LEFT) {
			state -= 1;
			if (state < 0) {
				state = 1;
			}
			return;
		}

		// Corner changing
		if (key == MU_KEYBOARD_KEY_SPACE) {
			corners = !corners;
			return;
		}

		return; if (win) {} // (to avoid parameter warnings)
	}

/* Main function */

int main(void) {
	/* Initiation */

		// Create global context
		mug_context_create(&mug, MU_WINDOW_SYSTEM_AUTO, MU_TRUE);

		// Use window create info to set keyboard key callback
		muWindowCreateInfo ci = mu_window_default_create_info();
		ci.keyboard_key_callback = keyboard_key_callback;

		// Create graphic
		gfx = mu_graphic_create_via_window(api, "Advanced triangle", 800, 600, ci);

		// Create triangle buffer
		triangle_buffer = mu_gobj_buffer_create(gfx, MUG_OBJECT_TRIANGLE, 
			sizeof(triangles) / sizeof(muTriangle), triangles
		);

	/* Main loop */

		while (mu_graphic_exists(gfx)) {
			// Clear the screen with black
			mu_graphic_clear(gfx, 0.0, 0.0, 0.0, 1.0);

			// Resize buffer and add corners if needed
			if (corners == MU_TRUE && buffer_size == 4) {
				mu_gobj_buffer_resize(gfx, triangle_buffer, 
					(sizeof(triangles) / sizeof(muTriangle)) + (sizeof(corner_triangles) / sizeof(muTriangle)), 0
				);
				buffer_size = 8;
				mu_gobj_buffer_subfill(gfx, triangle_buffer, 4, 4, corner_triangles);
			} else if (corners == MU_FALSE && buffer_size == 8) {
				mu_gobj_buffer_resize(gfx, triangle_buffer, 
					sizeof(triangles) / sizeof(muTriangle), 0
				);
				buffer_size = 4;
			}

			// Sub-fill and sub-render portion of triangles based on state
			if (state == 0) {
				mu_gobj_buffer_subfill(gfx, triangle_buffer, 0, 1, triangles);
				mu_gobj_buffer_subrender(gfx, triangle_buffer, 0, 1);
			} else {
				mu_gobj_buffer_subfill(gfx, triangle_buffer, 1, 3, &triangles[1]);
				mu_gobj_buffer_subrender(gfx, triangle_buffer, 1, 3);
			}

			// Sub-render corners if needed
			if (corners) {
				mu_gobj_buffer_subrender(gfx, triangle_buffer, 4, 4);
			}

			// Swap graphic buffers (to present image)
			mu_graphic_swap_buffers(gfx);

			// Update graphic at ~60 fps
			mu_graphic_update(gfx, 60);
		}

	/* Termination */

		// Destroy triangle buffer
		triangle_buffer = mu_gobj_buffer_destroy(gfx, triangle_buffer);

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

