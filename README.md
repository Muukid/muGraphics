

# muGraphics v1.0.0

muGraphics (acrynomized to "mug") is a public domain* single-file C library for high-level 2D cross-graphics-API rendering. Its header is automatically defined upon inclusion if not already included (`MUG_H`), and the source code is defined if `MUG_IMPLEMENTATION` is defined, following the internal structure of:

```c
#ifndef MUG_H
#define MUG_H
// (Header code)
#endif

#ifdef MUG_IMPLEMENTATION
// (Source code)
#endif
```

Therefore, a standard inclusion of the file to get all automatic functionality looks like:

```c
#define MUG_IMPLEMENTATION
#include "muGraphics.h"
```

More information about the general structure of a mu library is provided at [the mu library information GitHub repository](https://github.com/Muukid/mu-library-information).

> Note that the example inclusion here won't automatically have compatibility with any graphics APIs, as which graphics APIs mug uses needs to be manually defined via macros; see the (graphics API support macros section)[#graphics-API-support-macros] for more details.

# Demos

Demos are designed for mug to both test its functionality and to allow users to get the basic idea of the structure of the library quickly without having to read the documentation in full. These demos are available in the `demos` folder.

# System dependencies

mug uses muCOSA, which, for the version it uses, has various system dependencies, which are listed below.

## Win32 dependencies

To compile with Windows, you need to link the following files under the given circumstances:

`user32.dll` and `imm32.dll` in any given circumstance.

`gdi32.dll` and `opengl32.dll` if `MU_SUPPORT_OPENGL` is defined by the user.

# Licensing

mug is licensed under public domain or MIT, whichever you prefer, as well as (technically) [Apache 2.0 due to OpenGL's licensing](https://github.com/KhronosGroup/OpenGL-Registry/issues/376#issuecomment-596187053).

# Multi-threading

mug does not directly support thread safety, and must be implemented by the user themselves. Thread safety in mug can be generally achieved by locking each object within a mug context (ie `muGraphic` for example), making sure that only one thread ever interacts with the given object at once. This includes render calls, buffer creation, etc. There are a few known exceptions to this to achieve total thread safety, which are detailed below, but multi-threading with mug is not thoroughly tested.

## Context creation

If `MU_SUPPORT_OPENGL` is defined, two contexts cannot be created at the same time.

## Graphic updating

Due to limitations with the handling of messages on Win32, no more than one graphic can be updated safely at any given time across threads.

## Window resizing/moving

Due to the way that Win32 handles messages when the window is being resized or moved, a call to `mug_graphic_update` on a graphic created via a muCOSA window will hang for the entire duration of the window being dragged/moved. Handling implemented by users of mug should expect this, and handle vital functionality that needs to be executed over this time on a separate thread.

# Known issues and limitations

This section covers the known issues and limitations of the libraries.

## Limited support

This version of mug is meant to be very basic and minimal, and thus, it only supports Win32 (via muCOSA) and OpenGL. More support for various other systems (such as other window systems like X11/Wayland, or other graphics APIs such as Vulkan) is planned in the future, but for now, mug's reach in this regard is very limited.

## 2D rendering

mug is built around a 2D-rendering context, meaning that there's no practical way to get efficient 3D graphics rendering. This is for several reasons, primarily the fact that a full 3D environment would then likely need more advanced rendering methods, such as lighting, which would rather be implemented internally, which wouldn't fully make sense since mug is primarily made for utility applications, or need to be implemented by the user themselves, which would imply shader customization, which brings many complications in terms of just the concept of cross-graphics-API shader code, but also handling compilation on graphics APIs such as Vulkan, which don't have built-in runtime shader compilers.

This all means that mug is set up to create and render exclusively 2D objects. This doesn't mean that it's impossible to render in 3D, as mug does have depth buffers to make rendering order easier to structure for the user when building GUIs, but it does mean that 3D matrix calculations would need to be handled on the CPU. Additionally, advanced shader effects such as realtime 3D lighting would be practically impossible (unless you wanted to build your own raytracing/CPU-side renderer by creating a pixel grid and setting the values of each pixel manually, knock yourself out!).

## Multi-texture rendering

Modern graphics APIs are designed to make rendering multiple textures in one shader very difficult and generally discouraged as an option. For example, OpenGL 3.3 doesn't support choosing a sampler based on given vertex data, meaning that you would need to make the jump to OpenGL 4.0+ to get that feature. And, even then, the limits on how many samplers can be stored in a shader (especially in regards to whether or not you're storing them as an array or as separate variables, which, yes, does affect the amount the shader can hold) are not queryable as values (at least as far as I'm aware), making "the amount of sampler2Ds you can hold in a shader" a very hard-to-figure-out amount that needs to be handled at runtime, and can be very small on certain devices, making the handling of texture buffers device-dependent, which makes coding them on the user-side hell, and makes the act of going through the effort very questionable, especially on those lower-end devices; all of this, and you're now having to use a later version of OpenGL, which can harm compatibility.

For all these complications, mug only allows one texture to be used per texture buffer, which forces the user to get creative with how they handle the rendering of multiple textures. It's an unfortunate conundrum, but manufacturers are gonna do what they're gonna do.

## Create graphic with pre-existing window

To keep mug code simplistic for now, it is impossible to create a graphic generated from a window that already was created; the window-graphic-creation process must create the window internally. This doesn't realistically limit the user's ability to customize their window, as they still have access to fully customize the window via the `muWindowInfo` parameter, but nevertheless, it would be more flexible to provide support for creating graphics with a muCOSA window that already existed beforehand.

## Vertex data up front

When vertex data (as well as index data) needs to be generated and a buffer needs to be filled with it, it is first allocated in its entirety on the CPU side. This may be too much for the CPU to allocate at the moment, at which case it would be more appropriate to cut it up into smaller pieces and subfill the data, but this system has yet to be implemented. This means that if the vertex/index data needed to create a given object buffer cannot be allocated up front on the CPU's side, the buffer will fail to create despite there being a way to still accomplish the task with less memory needed.

## Stability with large object counts

There are no checks performed on buffers so large that they cause integer overflow, meaning that the usage of too many objects will likely just result in a crash. There is no way to check for buffer size limits with mug's provided API; a buffer will simply fail to create if too large and give a non-successful result value.

## Colors of each rect corner

Every aspect about a rect is customizable besides the individual color of each corner of the rect; every rect is defined by one color and one color only, making rect gradient effects only possible by rendering triangles that form rects, which is slightly less optimal and slightly more annoying.


# Other library dependencies

mug has a dependency on:

* [muCOSA v2.0.0](https://github.com/Muukid/muCOSA/releases/tag/v2.0.0).

* [glad 2.0.6 GL v3.3 Core](https://github.com/Dav1dde/glad/releases/tag/v2.0.6). glad is only included in the implementation of mug, meaning that only defining the header of mug won't give the user access to OpenGL.

> Note that mu libraries store their dependencies within their files, so you don't need to import these dependencies yourself; this section is purely to give more information about the contents that this file defines. The libraries listed may also have other dependencies that they also include that aren't explicitly listed here.

# Graphics API support macros

Each graphics API needs to have a macro defined to enable support for it. The following macros are defined for the given graphics APIs to be supported:

* OpenGL 3.3 Core - `MU_SUPPORT_OPENGL`.

So, for example, an inclusion of mug with OpenGL 3.3 Core would look like:

```c
#define MU_SUPPORT_OPENGL
#define MUG_IMPLEMENTATION
#include "muGraphics.h"
```

# Version

The macros `MUG_VERSION_MAJOR`, `MUG_VERSION_MINOR`, and `MUG_VERSION_PATCH` are defined to match its respective release version, following the formatting of `MAJOR.MINOR.PATCH`.

# mug context

mug operates in a context, encapsulated by the type `mugContext`, which has the following members:

* `mugResult result` - the result of the latest non-successful non-result-checking function call regarding the context; starting value upon context creation is `MUG_SUCCESS`, and is set to another value if a function whose result is not set manually by the user doesn't return a success result value.

* `muCOSAContext cosa` - the muCOSA context used by the mug context.

## Creation and destruction

The function `mug_context_create` creates a mug context, defined below: 

```c
MUDEF void mug_context_create(mugContext* context, muWindowSystem system, muBool set_context);
```


The result of this function is stored within `context->result`. Upon success, this function automatically calls `mug_context_set` on the created context, as well as `muCOSA_context_set` on the created muCOSA context, unless `set_context` is equal to `MU_FALSE`.

> It is valid for `system` to be `MU_WINDOW_NULL` for this function, in which case, the best currently available window system will be automatically chosen by muCOSA. More information about the window system is available via muCOSA's documentation.

For every successfully created context, it must be destroyed, which is done with the function `mug_context_destroy`, defined below: 

```c
MUDEF void mug_context_destroy(mugContext* context);
```


This function cannot fail if given a valid pointer to an active context (otherwise, a crash is likely), so no result value is ever indicated by this function via any means.

## Global context

mug uses a global variable to reference the currently "set" context whenever a function is called that assumes a context (ie it doesn't take a parameter for context). This global variable can be changed to reference a certain context via the function `mug_context_set`, defined below: 

```c
MUDEF void mug_context_set(mugContext* context);
```


## Non-result/context-checking functions

If a function takes a `mugContext` and `mugResult` parameter, there will likely be two defined macros for calling the function without explicitly passing those parameters, with the current global context being assumed for both parameters.

Non-result-checking functions are functions that assume the `mugContext` parameter to be the current global context, and assume the `mugResult` parameter to be the current global context's result member. These functions' parameters are simply the normal function's parameters, but without the context or result parameter, instead being routed to the current global context. The name of these functions are simply the normal name, but `mug_...` is replaced with just `mu_...`.

Result-checking functions are functions that also assume (and thus don't make you specify) the `mugContext` parameter to be the current global context, but they still make you specify the `mugResult` parameter, and the global context's result member goes unreferenced. The name of these functions is the same as the non-result-checking functions, but with an underscore appended at the end.

For example, if you the function `mug_graphic_do_something` existed with these parameters:
```c
MUDEF void mug_graphic_do_something(mugContext* context, mugResult* result, int a, int b);
```

then the function `mu_graphic_do_something`, the "non-result-checking function", exists with these parameters:
```c
MUDEF void mu_graphic_do_something(int a, int b);
// Calls mug_graphic_do_something with the global context
// and its respective result member.
```

and the function `mu_graphic_do_something_`, the "result-checking function", exists with these parameters:
```c
MUDEF void mu_graphic_do_something_(mugResult* result, int a, int b);
// Calls mug_graphic_do_something with the global context
// and the given result pointer.
```

> Note that, in reality, the non-result and result-checking functions aren't defined as actual independent functions, but instead, as macros to the original function. More information about the type `mugResult` can be found in the [result section](#result).

# Graphic

The "graphic" (respective type `muGraphic`; typedef for `void*`) is a surface being rendered to by some graphics API. Since a graphic is just a reference to a rendering surface, it must be created via some other object that encapsulates a rendering surface. This is why muCOSA is included in mug, as it is able to create objects that have these surfaces, such as a window.

## Graphic system

The "graphic system" (respective type `muGraphicSystem`; typedef for `uint8_m`) is a value representing which supported system is being used to render to a given graphic. It has the following supported values:

* `MU_GRAPHIC_OPENGL` - OpenGL 3.3 Core.

## Destroy graphic

The function `mug_graphic_destroy` destroys a given graphic, defined below: 

```c
MUDEF muGraphic mug_graphic_destroy(mugContext* context, muGraphic gfx);
```


This function must be called on every successfully-created graphic before the destruction of the context used to create it. This function returns 0.

> The macro `mu_graphic_destroy` is the non-result-checking equivalent.

## Window graphic

A "window graphic" is a graphic created via a muCOSA window.

### Creation

The function `mug_graphic_create_window` creates a `muGraphic` by creating a `muWindow` object, defined below: 

```c
MUDEF muGraphic mug_graphic_create_window(mugContext* context, mugResult* result, muGraphicSystem system, muWindowInfo* info);
```


This function allows the user to set their desired pixel format. This means that the user can disable depth testing by not including any depth bits (assuming that their pixel format is chosen as desired).

> The macro `mu_graphic_create_window` is the non-result-checking equivalent, and the macro `mu_graphic_create_window_` is the result-checking equivalent.

### Get window

The function `mug_graphic_get_window` retrieves the window handle generated from a successfully-created graphic that was created using a muCOSA window, defined below: 

```c
MUDEF muWindow mug_graphic_get_window(mugContext* context, muGraphic gfx);
```


> The macro `mu_graphic_get_window` is the non-result-checking equivalent.

## Main loop graphic functions

There are four primary functions that must be called every single frame in a particular manner; these functions are `mug_graphic_exists`, `mug_graphic_clear`, `mug_graphic_swap_buffers`, and `mug_graphic_update`. A valid mug frame loop is formatted like so:

```c
// Loop frame-by-frame while the graphic exists:
while (mu_graphic_exists(gfx))
{
// Clear the graphic with black
mu_graphic_clear(gfx, 0.f, 0.f, 0.f);

// ...Frame-by-frame logic and rendering should occur here...

// Swap graphic buffers (to present image)
mu_graphic_swap_buffers(gfx);

// Update graphic at ~100 FPS
mu_graphic_update(gfx, 100.f);
}
```

All of the functions demonstrated in this section should only be called once each frame, and in the order given. Explicit documentation on these functions and what they do is provided below.

### Get graphic existence status

The graphic can stop existing for several reasons, such as in the case of it coming from a window and the user closing the window. For this, the function `mug_graphic_exists` exists, which returns whether or not the graphic exists at any given, and is used to establish a loop for as long as the graphic is alive, defined below: 

```c
MUDEF muBool mug_graphic_exists(mugContext* context, muGraphic gfx);
```


The status of this function is updated every time `mug_graphic_update` is called, meaning that the two should always be called consecutively. For this reason, `mug_graphic_update` should be called at the end of the `mug_graphic_exists` loop, so that upon the existence check being called, the graphic's state for this has been updated directly beforehand.

> The macro `mu_graphic_exists` is the non-result-checking equivalent.

### Clear graphic

Once the current frame has started, the contents of the graphic are undefined (both in the case of the current frame being the first frame or it not being the first frame). To resolve this, the graphic must be cleared with the function `mug_graphic_clear`, defined below: 

```c
MUDEF void mug_graphic_clear(mugContext* context, mugResult* result, muGraphic gfx, float r, float g, float b);
```


This function clears the color of each pixel in the graphic with the given RGB values (each value must range between `0.f` and `1.f`). It also clears the depth-buffer of the graphic. Not calling this function before calling any rendering function, `mug_graphic_swap_buffers`, or `mug_graphic_update`, will result in undefined behavior, as the contents of the graphic are unknown in the state between the beginning of the frame and the execution of the function `mug_graphic_clear`.

> The macro `mu_graphic_clear` is the non-result-checking equivalent, and the macro `mu_graphic_clear_` is the result-checking equivalent.

### Swap graphic buffers

One all rendering calls for a given frame have been executed, it must be presented to the screen, which is what `mug_graphic_swap_buffers` does, defined below: 

```c
MUDEF void mug_graphic_swap_buffers(mugContext* context, mugResult* result, muGraphic gfx);
```


This function should be called after all rendering functions have been called for a given frame, and no rendering functions should be called after this function for the given frame.

> The macro `mu_graphic_swap_buffers` is the non-result-checking equivalent, and the macro `mu_graphic_swap_buffers_` is the result-checking equivalent.

### Update graphic

Once the graphic has been presented, before the next frame potentially starts, the graphic's state needs to be internally updated; this is performed with the function `mug_graphic_update`, defined below: 

```c
MUDEF void mug_graphic_update(mugContext* context, mugResult* result, muGraphic gfx, float target_fps);
```


The parameter `target_fps` specifies the desired amount of frames that the user wants to be processed each second, given as a rate of frames per second. `mug_graphic_update` accomplishes this by sleeping for the time required to reach this desired FPS, keeping track internally of the approximate time it has taken for each frame to be processed. This does mean that no compensation is performed if the approximate time is at or above the time needed to reach the desired FPS rate. This functionality is not performed if `target_fps` is less than or equal to `0.f`.

> The macro `mu_graphic_update` is the non-result-checking equivalent, and the macro `mu_graphic_update_` is the result-checking equivalent.

# Objects

An ***object*** in mug (commonly called a "gobject" in the API) is something that is rendered to the screen. Its ***type*** defines what type of object it is, such as a triangle object.

## Object types

All object types defined by mug are represented by the type `mugObjectType` (typedef for `uint16_m`). It has the following defined values:

* `MUG_OBJECT_POINT` - a [point](#point).

* `MUG_OBJECT_LINE` - a [line](#line).

* `MUG_OBJECT_TRIANGLE` - a [triangle](#triangle).

* `MUG_OBJECT_RECT` - a [rect](#rect).

* `MUG_OBJECT_CIRCLE` - a [circle](#circle).

## Load object type

The ability to render a certain object type can be pre-loaded via the function `mug_gobject_load`, defined below: 

```c
MUDEF void mug_gobject_load(mugContext* context, mugResult* result, muGraphic gfx, mugObjectType obj_type);
```


> The macro `mu_gobject_load` is the non-result-checking equivalent, and the macro `mu_gobject_load_` is the result-checking equivalent.

Object types are also loaded automatically when an object buffer is created with the type, so this function doesn't need to be called. This function just gives a successful result if the object type was already loaded.

## Deload object type

No object types are automatically loaded upon context creation. However, once an object type is loaded in mug, rather via an explicit call to `mug_gobject_load` or automatically loaded via the creation of an object buffer of the given type, it is never automatically deloaded until the graphic is destroyed. An object type can be manually deloaded via the function `mug_gobject_deload`, defined below: 

```c
MUDEF void mug_gobject_deload(mugContext* context, muGraphic gfx, mugObjectType obj_type);
```


Calling this function with an object type who has currently active buffers will result in undefined behavior.

> The macro `mu_gobject_deload` is the non-result-checking equivalent.

## Object type modifiers

There are certain attributes about each object type can be universally (per mug context) changed for each object of that given type. These attributes are represented by the type `mugObjectMod` (typedef for `uint8_m`), and has the following defined values:

* `MUG_OBJECT_ADD_POS` - an array of three floats representing an x-, y-, and z-offset (respectively) added to the position of every object of a given type. The default values of all three offsets are 0.

* `MUG_OBJECT_MUL_POS` - an array of three floats representing an x-, y-, and z-scale (respectively) multiplied to the position of every object of a given type. The default values of all three scales are 1.

* `MUG_OBJECT_ADD_COL` - an array of four floats representing an r-, g-, b-, and a-offset (respectively) added to the color channels of every object of a given type. The default values of all four offsets are 0.

* `MUG_OBJECT_MUL_COL` - an array of four floats representing an r-, g-, b-, and a-scale (respectively) multiplied to the color channels of every object of a given type. The default values of all four scales are 1.

Multiplication is performed first, followed by addition. For objects that use non-polygonal borders (those being circles), the math for the color of each pixel is performed first, setting the alpha to 0 (or some intermediary between that and the given alpha value) if the pixel is not within the object, followed by the modification. This could be used to flip the alpha result (via setting the multipler to -1 and the adder to 1, thus inversing the alpha value), inverting the object's borders.

### Set object type modifier

The values of an object type modifier can be modified using the function `mug_gobject_mod`, defined below: 

```c
MUDEF void mug_gobject_mod(mugContext* context, muGraphic gfx, mugObjectType type, mugObjectMod mod, float* data);
```


This function must only be called on an object type that is currently loaded. Once an object type is deloaded and loaded again, the values of an attribute go back to their defaults.

> The macro `mu_gobject_mod` is the non-result-checking equivalent.

## Point

A "point" in mug is a single-pixel point. Its respective struct is `mugPoint`, and has the following members:

* `float pos[3]` - the position of the point, with indexes 0, 1, and 2 being the x-, y-, and z-coordinates respectively. All x- and y-coordiantes of a point visible on the graphic range between (0) and (the width of the graphic minus 1). All z-coordinates of a point should range between 0 and 1; any other value is not guaranteed to render properly. A pixel with a z-coordinate greater than or equal to the pixel rendered beforehand will draw over it.

* `float col[4]` - the colors of the point, with indexes 0, 1, 2, and 3 being the red, green, blue, and alpha channels respectively. All channels' values should range between 0 and 1; any other value is not guaranteed to render properly. A value of 0 means none of the channel, and a value of 1 means the maximum intensity of the channel.

## Line

A "line" in mug is a single-pixel line. Its respective struct is `mugLine`, and has the following members:

* `mugPoint points[2]` - the two points defining the line.

## Triangle

A "triangle" in mug is a filled-in triangle defined by three points connected to each other. Its respective struct is `mugTriangle`, and has the following members:

* `mugPoint points[3]` - the three points defining the triangle.

## Rect

A "rect" in mug is a filled-in rectangle defined by a center point, width/height, and rotation around the center point. Its respective struct is `mugRect`, and has the following members:

* `mugPoint center` - the center point of the rect. The point's color determines the color of the rect.

* `float dim[2]` - the dimensions of the rect, in width (`dim[0]`) and height (`dim[1]`).

* `float rot` - the rotation of the rect around the center point, in radians.

## Circle

A "circle" in mug is a filled-in circle defined by a center point and radius. Its respective struct is `mugCircle`, and has the following members:

* `mugPoint center` - the center point of the circle. The point's color determines the color of the circle.

* `float radius` - the radius of the circle.

# Object buffers

Objects are collectively stored, updated, and rendered in buffers (referred to as "gobjects" in the API), which are stored GPU-side. The type for an object buffer is `mugObjects` (typedef for `void*`).

## Create object buffer

An object buffer can be created via the function `mug_gobjects_create`, defined below: 

```c
MUDEF mugObjects mug_gobjects_create(mugContext* context, mugResult* result, muGraphic gfx, mugObjectType type, uint32_m obj_count, void* objs);
```


If `objs` is 0, the buffer is simply allocated, but filled with undefined data. If `objs` is not 0, it should be a pointer to an array of objects whose type matches the object type indicated by `type`, and whose length (in objects) should match `obj_count`.

Every object buffer that is created must be destroyed before the graphic that was used to create it is destroyed.

> The macro `mu_gobjects_create` is the non-result-checking equivalent, and the macro `mu_gobjects_create_` is the result-checking equivalent.

## Destroy object buffer

Every successfully created object buffer must be destroyed at some point with the function `mug_gobjects_destroy`, defined below: 

```c
MUDEF mugObjects mug_gobjects_destroy(mugContext* context, muGraphic gfx, mugObjects objs);
```


If any portion of the object buffer has been rendered during the current frame, it should not be destroyed until the entire frame has passed (AKA after `mug_graphic_update` has been called). This function returns 0.

> The macro `mu_gobjects_destroy` is the non-result-checking equivalent.

## Render object buffer

An object buffer can be rendered to a graphic using the function `mug_gobjects_render`, defined below: 

```c
MUDEF void mug_gobjects_render(mugContext* context, mugResult* result, muGraphic gfx, mugObjects objs);
```


Once an object buffer has been rendered, no fill/subfill/destroy actions should be performed on the object buffer.

> The macro `mu_gobjects_render` is the non-result-checking equivalent, and the macro `mu_gobjects_render_` is the result-checking equivalent.

## Subrender object buffer

An object buffer can be rendered like normal, except for with a specified offset (by an amount of objects) into the buffer and a specified length (also in amount of objects) using the function `mug_gobjects_subrender`, defined below: 

```c
MUDEF void mug_gobjects_subrender(mugContext* context, mugResult* result, muGraphic gfx, mugObjects objs, uint32_m offset, uint32_m count);
```


Rules about buffer rendering from `mug_gobjects_render` apply here as well.

> The macro `mu_gobjects_subrender` is the non-result-checking equivalent, and the macro `mu_gobjects_subrender_` is the result-checking equivalent.

## Fill

An object buffer's contents can be replaced using the function `mug_gobjects_fill`, defined below: 

```c
MUDEF void mug_gobjects_fill(mugContext* context, mugResult* result, muGraphic gfx, mugObjects objs, void* data);
```


`data` must be a valid pointer to an array of objects whose type matches the object type of the object buffer, and whose length matches the object count of the buffer.

> The macro `mu_gobjects_fill` is the non-result-checking equivalent, and the macro `mu_gobjects_fill_` is the result-checking equivalent.

## Subfill

An object buffer's contents can be partially filled via specifying an offset and length (both in units of objects) into the buffer using the function `mug_gobjects_subfill`, defined below: 

```c
MUDEF void mug_gobjects_subfill(mugContext* context, mugResult* result, muGraphic gfx, mugObjects objs, uint32_m offset, uint32_m count, void* data);
```


`data` must be a valid pointer to an array of objects whose type matches the object type of the object buffer, and whose length matches the length specified by `count`.

> The macro `mu_gobjects_subfill` is the non-result-checking equivalent, and the macro `mu_gobjects_subfill_` is the result-checking equivalent.

# Result

The type `mugResult` (typedef for `uint16_m`) is used to represent how a task in mug went. It has the following defined values:

* `MUG_SUCCESS` - the task succeeded; real value 0.

* `MUG_FAILED_MALLOC` - `mu_malloc` returned a failure value, and the task was unable to be completed.

* `MUG_FAILED_REALLOC` - `mu_realloc` returned a failure value, and the task was unable to be completed.

* `MUG_UNKNOWN_GRAPHIC_SYSTEM` - a `muGraphicSystem` value given by the user was unrecognized. This could happen because support for the requested graphics API was not defined by the user, such as passing `MU_GRAPHIC_OPENGL` without defining `MU_SUPPORT_OPENGL`.

* `MUG_UNKNOWN_OBJECT_TYPE` - a `mugObjectType` value given by the user was unrecognized.

* `MUG_UNKNOWN_OBJECT_MOD` - a `mugObjectMod` value given by the user was unrecognized.

* `MUG_MUCOSA_...` - a muCOSA function was called, which gave a non-success result value, which has been converted to a `mugResult` equivalent. There is a `mugResult` equivalent for any `muCOSAResult` value (besides `MUCOSA_SUCCESS`), and the conditions of the given `muCOSAResult` value apply based on the muCOSA documentation. Note that the value of the muCOSA-equivalent does not necessarily match the value of the mug version.

* `MUG_GL_FAILED_LOAD` - the required OpenGL functionality failed to load from the function call to `gladLoadGL`.

* `MUG_GL_FAILED_COMPILE_VERTEX_SHADER` - a vertex shader in OpenGL necessary to perform the task failed to compile.

* `MUG_GL_FAILED_COMPILE_FRAGMENT_SHADER` - a fragment shader in OpenGL necessary to perform the task failed to compile.

* `MUG_GL_FAILED_LINK_SHADERS` - shaders necessary to be linked to a shader program in OpenGL to perform the task failed to link.

* `MUG_GL_FAILED_ALLOCATE_BUFFER` - an internal OpenGL buffer needed to perform the task was unable to be allocated to the correct size.

* `MUG_GL_FAILED_CREATE_BUFFER` - a necessary call to create an OpenGL buffer failed.

* `MUG_GL_FAILED_CREATE_VERTEX_ARRAY` - a necessary call to create an OpenGL vertex array failed.

All non-success values (unless explicitly stated otherwise) mean that the function fully failed; AKA, it was "fatal", and the library continues as if the function had never been called. So, for example, if something was supposed to be allocated, but the function fatally failed, nothing was allocated.

There are non-fatal failure values, which mean that the function still executed, but not fully to the extent that the user would expect from the function. The function `mug_result_is_fatal` returns whether or not a given result function value is fatal, defined below: 

```c
MUDEF muBool mug_result_is_fatal(mugResult result);
```


This function also considers the fatal status of `mugResult` values representing `muCOSAResult` values.

> This function returns `MU_TRUE` if the value of `result` is invalid. It returns `MU_FALSE` if `result` is equal to `MUG_SUCCESS`.

## Result names

The name function `mug_result_get_name` returns a `const char*` representation of the given result value (for example, `MUG_SUCCESS` returns "MUG_SUCCESS"), defined below: 

```c
MUDEF const char* mug_result_get_name(mugResult result);
```


It will return "MU_UNKNOWN" in the case that `result` is an invalid result value.

> This function is a "name" function, and therefore is only defined if `MUG_NAMES` is also defined by the user.

## muCOSA-mug result to muCOSA result

The function `mug_to_muCOSA_result` returns the muCOSA-equivalent of a mug result that represents a `muCOSAResult` value (for example, `MUG_MUCOSA_FAILED_MALLOC` returns `MUCOSA_FAILED_MALLOC`), defined below: 

```c
MUDEF muCOSAResult mug_to_muCOSA_result(mugResult result);
```


This function returns `MUG_SUCCESS`/`MUCOSA_SUCCESS` (same value) if no muCOSA equivalent exists for the given `mugResult` value.

## muCOSA result to mug result

The function `muCOSA_to_mug_result` returns the mug-equivalent of a muCOSA result value (for example, `MUCOSA_FAILED_MALLOC` returns `MUG_MUCOSA_FAILED_MALLOC`), defined below: 

```c
MUDEF mugResult muCOSA_to_mug_result(muCOSAResult result);
```


This function returns `MUG_SUCCESS`/`MUCOSA_SUCCESS` (same value) if no mug equivalent exists for the given `muCOSAResult` value, rather because the given `muCOSAResult` value is invalid or is equal to `MUCOSA_SUCCESS`.

# C standard library dependencies

mug has several C standard library dependencies, all of which are overridable by defining them before the inclusion of its header. The following is a list of those dependencies.

## `math.h` dependencies

* `mu_sinf` - equivalent to `sinf`.

* `mu_cosf` - equivalent to `cosf`.
