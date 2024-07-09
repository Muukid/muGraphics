/*
============================================================
                        DEMO INFO

DEMO NAME:          rect.c
DEMO WRITTEN BY:    Muukid
CREATION DATE:      2024-06-15
LAST UPDATED:       2024-07-09

============================================================
                        DEMO PURPOSE

This demo shows how rectangle rendering works in mug.

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

	// The rectangle to be rendered
	muRect rect = {
		{ // Point
			{ 400, 300 }, // (position)
			{ 1, 0, 0, 1 } // (color)
		},
		{ // Dimensions
			200, 200
		},
		// Rotation
		0
	};

	// The buffer used for rendering the rectangle
	mugObjectBuffer rect_buffer;

/* Main function */

int main(void) {
	/* Initiation */

		// Create global context
		mug_context_create(&mug, MU_WINDOW_SYSTEM_AUTO, MU_TRUE);

		// Create graphic
		gfx = mu_graphic_create_via_window(api, "Rectangle", 800, 600, mu_window_default_create_info());

		// Create rectangle buffer
		rect_buffer = mu_gobj_buffer_create(gfx, MUG_OBJECT_RECT, 1, &rect);

	/* Main loop */

		while (mu_graphic_exists(gfx)) {
			// Clear the graphic with black
			mu_graphic_clear(gfx, 0.0, 0.0, 0.0, 1.0);

			// Change the rectangle's rotation over time
			rect.rot = mu_time_get();

			// Change the rectangle's color over time
			rect.center.col.r = 0.5*sin((2.29622*mu_time_get())/2.0) + 0.5;
			rect.center.col.g = 0.5*sin((4.12983*mu_time_get())/2.1) + 0.5;
			rect.center.col.b = 0.5*sin((3.51460*mu_time_get())/2.2) + 0.5;

			// Update rectangle buffer data
			mu_gobj_buffer_fill(gfx, rect_buffer, &rect);

			// Render the rectangle
			mu_gobj_buffer_render(gfx, rect_buffer);

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

