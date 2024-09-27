/*
============================================================
                        DEMO INFO

DEMO NAME:          texture_array.c
DEMO WRITTEN BY:    Muukid
CREATION DATE:      2024-09-27
LAST UPDATED:       2024-09-27

============================================================
                        DEMO PURPOSE

This demo tests if texture array rendering works by
rendering a spinning textured rect with a pixelated
gradient. The gradient should switch to a different gradient
every second.

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

/* Texture logic */

	// The texture array rect to be renderd
	mug2DTextureArrayRect texrect = {
		// Center point
		{
			// Position (xyz)
			{ 400.f, 300.f, 0.f },
			// Color (rgba)
			{ 1.f, 1.f, 1.f, 1.f }
		},
		// Dimensions
		{ 300.f, 300.f },
		// Rotation
		0.f,
		// Texture position
		{ 0.f, 0.f, 0.f },
		// Texture dimensions
		{ 1.f, 1.f }
	};

	// Texture rect object buffer
	mugObjects texbuf;

	// Texture info
	mugTextureInfo texinfo = {
		// Type (2D array)
		MUG_TEXTURE_2D_ARRAY,
		// Format (uint8_m RGBA)
		MUG_TEXTURE_U8_RGBA,
		// Wrapping x and y (clamp)
		{ MUG_TEXTURE_CLAMP, MUG_TEXTURE_CLAMP },
		// Filtering up-/downscale (nearest)
		{ MUG_TEXTURE_NEAREST, MUG_TEXTURE_NEAREST }
	};

	// Texture handle
	mugTexture tex;

/* Pixel logic */

	// Pixel dimensions
	#define WIDTH 8
	#define HEIGHT 8
	#define DEPTH 8
	uint32_m dim[3] = { WIDTH, HEIGHT, DEPTH };

	// Pixel array
	uint8_m pixels[WIDTH*HEIGHT*DEPTH*4];

	// Fills pixels with data
	void calc_pixel(void) {
		// Loop through each layer
		size_m lb = 0;
		for (uint32_m l = 0; l < DEPTH; ++l) {
			// Loop through each horizontal strip
			for (uint32_m h = 0; h < HEIGHT; ++h) {
				// Calculate offset based on horizontal strip
				uint32_m ph = h*WIDTH;
				// Loop through each vertical strip in this horizontal strip
				for (uint32_m w = 0; w < WIDTH; ++w) {
					// Calculate offset based on pixel
					uint32_m pw = (ph+w)*4;
					// Set RGBA values
					// - Gradient on the x; more x, more red
					pixels[lb+pw  ] = ((float)w / (float)WIDTH) * 255.f * (((float)l)/((float)DEPTH));
					// - Gradient on the y; more y, more green
					pixels[lb+pw+1] = ((float)h / (float)HEIGHT) * 255.f * (1.f - (((float)l)/((float)DEPTH)));
					// - Blue and alpha stay constant
					pixels[lb+pw+2] = pixels[lb+pw+3] = 255;

					// Because we start off with a lot of blue, (0,0) of the texture
					// will be blue, and (1,1) will be white.
				}
			}
			// Increment to next depth
			lb += WIDTH*HEIGHT*4;
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

	// Calculate pixel data
	calc_pixel();
	// Create texture
	tex = mu_gtexture_create(gfx, &texinfo, dim, (muByte*)pixels);

	// Create buffer
	texbuf = mu_gobjects_create(gfx, MUG_OBJECT_TEXTURE_2D_ARRAY, 1, &texrect);
	// Set texture for buffer
	mu_gobjects_texture(gfx, texbuf, tex);

/* Print explanation */

	printf("Window with dark grey background should appear\n");
	printf("A rect with a gradient texture should be spinning\n");
	printf("Gradient should be changing every second\n");
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

		// If it has been a second:
		if (mu_time_get() >= 1.0) {
			// Reset time to 0
			mu_time_set(0.0);
			// Increment layer
			texrect.tex_pos[2] += 1.f;
			// (+ wrap around value if necessary)
			if (texrect.tex_pos[2] >= DEPTH) {
				texrect.tex_pos[2] = 0.f;
			}
		}

		// Rotate texture over time
		texrect.rot = mu_fixed_time_get();
		// Update buffer
		mu_gobjects_fill(gfx, texbuf, &texrect);
		// Render buffer
		mu_gobjects_render(gfx, texbuf);

		// Swap graphic buffers (to present image)
		mu_graphic_swap_buffers(gfx);
		// Update graphic at ~100 FPS
		mu_graphic_update(gfx, 100.f);
	}

/* Termination */

	// Destroy buffer (required)
	texbuf = mu_gobjects_destroy(gfx, texbuf);

	// Destroy texture (required)
	mu_gtexture_destroy(gfx, tex);

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

