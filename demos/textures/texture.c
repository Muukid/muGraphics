/*
============================================================
                        DEMO INFO

DEMO NAME:          texture.c
DEMO WRITTEN BY:    Muukid
CREATION DATE:      2024-07-30
LAST UPDATED:       2024-07-30

============================================================
                        DEMO PURPOSE

This demo tests basic single-texture rendering.

============================================================
                        DEMO FUNCTION

The demo should display a spinning gradient texture.

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
	
	// Include stdio for printing
	#include <stdio.h>

/* Global variables */

	// Global context
	mugContext mug;

	// Graphic to be rendered to
	muGraphic gfx;

	// The API of the graphic
	muGraphicAPI api = MUG_OPENGL;

	// The texture object to be rendered
	muTextureObject texture_obj = {
		// Rect
		{
			// Center
			{
				// Position
				{ 400.f, 300.f },
				// Color
				{ 1.f, 1.f, 1.f, 1.f }
			},
			// Dimensions
			{ 400.f, 400.f },
			// Rotation
			0.f
		},
		// Texture position
		{ 0.f, 0.f },
		// Texture dimensions
		{ 1.f, 1.f }
	};

	// The buffer used for rendering the texture
	mugObjectBuffer texture_buffer;

	// The texture handle
	mugTexture texture_id;

	// Pixel macros
	#define WIDTH 8
	#define HEIGHT 8
	#define CHANNELS 4

	// Pixel array
	uint8_m pixels[WIDTH*HEIGHT*CHANNELS];

/* Main function */

int main(void) {
	/* Initiation */

		// Create global context
		mug_context_create(&mug, MU_WINDOW_SYSTEM_AUTO, MU_TRUE);

		// Create graphic
		gfx = mu_graphic_create_via_window(api, "Texture", 800, 600, mu_window_default_create_info());

		// Create texture buffer
		texture_buffer = mu_gobj_buffer_create(gfx, MUG_OBJECT_TEXTURE, 1, &texture_obj);

		// Calculate pixels
		for (uint32_m h = 0; h < HEIGHT; h++) {
			uint32_m ph = h*WIDTH;
			for (uint32_m w = 0; w < WIDTH; w++) {
				uint32_m pw = (ph+w)*CHANNELS;
				pixels[pw  ] = ((float)w / (float)WIDTH) * 255.f; // (Gradient on the x; more x, more red)
				pixels[pw+1] = ((float)h / (float)HEIGHT) * 255.f; // (Gradient on the y; more y, more green)
				pixels[pw+2] = 255;
				pixels[pw+3] = 255;
			}
		}

		// Create texture
		texture_id = mu_texture_create(gfx,
			MUG_FORMAT_8UNORM_RGBA, // Format
			MUG_FILTER_NEAREST, // Upscale filter
			MUG_FILTER_NEAREST, // Downscale filter
			MUG_WRAP_CLAMP_TO_EDGE, // X-wrapping filter
			MUG_WRAP_CLAMP_TO_EDGE, // Y-wrapping filter
			WIDTH, HEIGHT, pixels // Pixel data
		);

		// Bind texture
		mu_texture_bind(gfx, texture_id, 0);

	/* Main loop */

		while (mu_graphic_exists(gfx)) {
			// Clear the graphic
			mu_graphic_clear(gfx, 231.0/255.0, 236.0/255.0, 239.0/255.0, 1.0);

			// Rotate texture over time
			texture_obj.rect.rot = mu_time_get();

			// Update texture buffer
			mu_gobj_buffer_fill(gfx, texture_buffer, &texture_obj);

			// Render buffer
			mu_gobj_buffer_render(gfx, texture_buffer);

			// Swap graphic buffers (to present image)
			mu_graphic_swap_buffers(gfx);

			// Update graphic at ~100 fps
			mu_graphic_update(gfx, 100);
		}

	/* Termination */

		// Destroy texture
		texture_id = mu_texture_destroy(gfx, texture_id);

		// Destroy texture buffer
		texture_buffer = mu_gobj_buffer_destroy(gfx, texture_buffer);

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

