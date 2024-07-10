

# muGraphics v1.0.0

muGraphics (acrynomized to "mug") is a public domain* single-file C library for high-level cross-graphics-API rendering.

***WARNING!*** This library is still under heavy development, has no official releases, and won't be stable until its first public release v1.0.0.

To use it, download the `muGraphics.h` file, add it to your include path, and include it like so:

```c
#define MUG_IMPLEMENTATION
#include "muGraphics.h"
```

More information about the general structure of a mu library is provided at [the mu library information GitHub repository.](https://github.com/Muukid/mu-library-information)

# System dependencies

The system dependencies for mug are dependent on muCOSA.

## Linker flags

The math library (`-lm`) must be linked.

If the target OS being compiled for is ***Win32***, `user32.dll`, `imm32.dll`, `gdi32.dll`, and `opengl32.dll` must be linked.

If the target OS being compiled for is ***X11*** (Linux), `libX11`, `libpthread`, and `libGL` must be linked.

# Demos

Demos that quickly show the gist of the library and how it works are available in the `demos` folder.

# Licensing

mug is licensed under public domain or MIT, whichever you prefer, as well as [Apache 2.0 due to OpenGL's licensing](https://github.com/KhronosGroup/OpenGL-Registry/issues/376#issuecomment-596187053).


# Other library dependencies

mug has a dependency on the following libraries:

* [muCOSA commit 1bec97f](https://github.com/Muukid/muCOSA/tree/1bec97fc551e44bed87305ae9f6e188e68ddf617).

* [vkbind v1.3.283.0](https://github.com/mackron/vkbind/commit/7c136efb8cd6ce3074770c20f4ee5f240ddc114a).

* [glad 2.0.6 GL v4.0 Core](https://github.com/Dav1dde/glad/releases/tag/v2.0.6).

Note that mu libraries store their dependencies within their files, so you don't need to import these dependencies yourself.

Note that the libraries listed may also have other dependencies that they also include that aren't listed here.

# Result enumerator

The enumerator `mugResult` is used to represent how a function went in mug.

## Values

`MUG_SUCCESS`: the task succeeded.

`MUG_ALLOCATION_FAILED`: memory necessary to allocate to perform the task could not be allocated.

`MUG_UNKNOWN_GRAPHIC_API`: a `muGraphicAPI` value passed was an invalid/unknown enumerator value.

`MUG_UNKNOWN_OBJECT_TYPE`: a `mugObjectType` value passed was an invalid/unknown enumerator value.

`MUG_FAILED_CREATE_GL_BUFFER`: a call to `glGenBuffers` failed.

`MUG_FAILED_CREATE_GL_VERTEX_ARRAY`: a call to `glGenVertexArrays` failed.

`MUG_FAILED_COMPILE_GL_SHADERS`: required OpenGL shaders failed to compile. This would be an issue within mug itself regarding its shader code and would need to be fixed internally.

`MUG_FAILED_INITIATE_VULKAN`: a call to `vkbInit` failed.

`MUG_FAILED_CREATE_VK_INSTANCE`: a call to `vkCreateInstance` failed.

`MUG_FAILED_CREATE_VK_SURFACE`: failed to create a valid `VkSurfaceKHR` object.

`MUG_FAILED_FIND_VALID_PHYSICAL_DEVICE`: no `VkPhysicalDevice`s could not be found.

`MUG_FAILED_FIND_COMPATIBLE_PHYSICAL_DEVICE`: a `VkPhysicalDevice` compatible with mug could not be found.

`MUG_FAILED_GET_QUEUE_FAMILY_PROPERTIES`: information about a `VkQueue` family needed by mug could not be retrieved.

`MUG_FAILED_FIND_NECESSARY_QUEUE_FAMILIES`: a `VkQueue` needed by mug could not be found.

`MUG_FAILED_CREATE_VK_DEVICE`: a call to `vkCreateDevice` failed.

`MUG_FAILED_GET_VK_SURFACE_INFO`: information about the `VkSurfaceKHR` object obtained could not be retrieved.

`MUG_FAILED_GET_GRAPHIC_WINDOW_DIMENSIONS`: information about a graphic's window's dimensions could not be retrieved.

`MUG_FAILED_CREATE_VK_SWAPCHAIN`: a call to `vkCreateSwapchainKHR` failed.

`MUG_FAILED_GET_VK_SWAPCHAIN_INFO`: information about the `VkSwapchainKHR` object obtained could not be retrieved.

`MUG_FAILED_CREATE_VK_SWAPCHAIN_IMAGE_VIEWS`: a `VkSwapchainKHR`'s respective `VkImageView`s could not be created.

`MUG_FAILED_CREATE_VK_COMMAND_POOL`: a call to `vkCreateCommandPool` failed.

`MUG_FAILED_ALLOCATE_VK_COMMAND_BUFFERS`: a call to `vkAllocateCommandBuffers` failed.

`MUG_FAILED_CREATE_VK_SEMAPHORE`: a call to `vkCreateSemaphore` failed.

`MUG_FAILED_CREATE_VK_FENCE`: a call to `vkCreateFence` failed.

`MUG_FAILED_WAIT_FOR_VK_FENCE`: a call to `vkWaitForFences` failed.

`MUG_FAILED_GET_NEXT_VK_SWAPCHAIN_IMAGE`: a call to `vkAcquireNextImageKHR` failed.

`MUG_FAILED_RESET_VK_FENCE`: a call to `vkResetFences` failed.

`MUG_FAILED_RESET_VK_COMMAND_BUFFER`: a call to `vkResetCommandBuffer` failed.

`MUG_FAILED_BEGIN_VK_COMMAND_BUFFER`: a call to `vkBeginCommandBuffer` failed.

`MUG_FAILED_END_VK_COMMAND_BUFFER`: a call to `vkEndCommandBuffer` failed.

`MUG_FAILED_SUBMIT_VK_QUEUE`: a call to `vkQueueSubmit` failed.

`MUG_FAILED_PRESENT_VK_QUEUE`: a call to `vkQueuePresentKHR` failed.

`MUG_FAILED_CREATE_VK_RENDER_PASS`: a call to `vkCreateRenderPass` failed.

`MUG_FAILED_CREATE_VK_FRAMEBUFFERS`: a call to `vkCreateFramebuffer` failed.

`MUG_FAILED_CREATE_VK_BUFFER`: a call to `vkCreateBuffer` failed.

`MUG_FAILED_FIND_COMPATIBLE_VK_MEMORY_TYPE`: the memory type needed to perform the task could not be found or is not available.

`MUG_FAILED_ALLOCATE_VK_MEMORY`: a call to `vkAllocateMemory` failed.

`MUG_FAILED_MAP_VK_MEMORY`: a call to `vkMapMemory` failed.

`MUG_FAILED_CREATE_VK_SHADER_MODULE`: a call to `vkCreateShaderModule` failed. This would be an issue within mug itself regarding its shader code and would need to be fixed internally.

`MUG_FAILED_CREATE_VK_DESCRIPTOR_SET_LAYOUT`: a call to `vkCreateDescriptorSetLayout` failed.

`MUG_FAILED_CREATE_VK_DESCRIPTOR_POOL`: a call to `vkCreateDescriptorPool` failed.

`MUG_FAILED_ALLOCATE_VK_DESCRIPTOR_SETS`: a call to `vkAllocateDescriptorSets` failed.

`MUG_FAILED_CREATE_VK_PIPELINE_LAYOUT`: a call to `vkCreatePipelineLayout` failed.

`MUG_FAILED_CREATE_VK_PIPELINE_GRAPHIC`: a call to `vkCreateGraphicsPipelines` failed.

There are also mug result equivalents for each `muCOSAResult` enumerator value, following the format of `MUG_MUCOSA_...` (ie `MUG_MUCOSA_SUCCESS`).

## Get name

The function `mug_result_get_name` returns a `const char*` representation of a `mugResult` value, defined below: 

```c
MUDEF const char* mug_result_get_name(mugResult result);
```


Note that this function is ***not defined*** unless `MUG_NAMES` is defined before the inclusion of the header file.

# Context

The mug context is the storage container that mug stores its context in.

## Struct

mug stores all of its inner data in a context, using a struct called `mugContext`. It has two important members:

* `result`: the result of the latest non-explicit result-checking function call, defined below: 

```c
mugResult result;
```


* `cosa`: the muCOSA context used by the mug context, defined below: 

```c
muCOSAContext cosa;
```


## Creation and destruction

The function `mug_context_create` creates a mug context, defined below: 

```c
MUDEF void mug_context_create(mugContext* context, muWindowSystem system, muBool set_context);
```


Note that the result of this function is stored within `context->result`.

Note that, upon success, this function automatically calls `mug_context_set` on the created context (as well as `muCOSA_context_set` on `context->cosa`) unless `set_context` is equal to `MU_FALSE`.

The function `mug_context_destroy` destroys a mug context, defined below: 

```c
MUDEF void mug_context_destroy(mugContext* context);
```


## Set context

The function `mug_context_set` sets the global context to the given context, defined below: 

```c
MUDEF void mug_context_set(mugContext* context);
```


Note that this function can be automatically called on a created context with the function `mug_context_create`.

Note that the global context can also be accessed manually via the global variable `mug_global_context`, although this is not recommended.

# Graphic

The "graphic" (respective type `muGraphic`) is a surface being rendered to by some graphics API. Since a graphic is just a reference to a rendering surface, it must be created via some other object that encapsulates a rendering surface. This is why muCOSA is included in mug, as it is able to create objects that have these surfaces, such as a window.

## Graphic API

The enumerator `muGraphicAPI` is used to represent the graphics API associated with a graphic. Its possible values are:

`MUG_OPENGL`: [OpenGL v4.0 Core](https://registry.khronos.org/OpenGL/specs/gl/glspec40.core.pdf).

`MUG_VULKAN`: Vulkan 1.3.283.0.

## Destroy graphic

The function `mug_graphic_destroy` destroys any graphic, defined below: 

```c
MUDEF muGraphic mug_graphic_destroy(mugContext* context, muGraphic graphic);
```


Its non-result-checking equivalent macro is defined below: 

```c
#define mu_graphic_destroy(...) mug_graphic_destroy(mug_global_context, __VA_ARGS__)
```


Note that `mug_graphic_destroy` *must* be called at some point on every successfully-created graphic.

## Window graphic

### Creation

The function `mug_graphic_create_via_window` creates a `muWindow` and creates a `muGraphic` from it, defined below: 

```c
MUDEF muGraphic mug_graphic_create_via_window(mugContext* context, mugResult* result, muGraphicAPI api, const char* name, uint16_m width, uint16_m height, muWindowCreateInfo create_info);
```


Its non-result-checking equivalent macro is defined below: 

```c
#define mu_graphic_create_via_window(...) mug_graphic_create_via_window(mug_global_context, &mug_global_context->result, __VA_ARGS__)
```


Its result-checking equivalent macro is defined below: 

```c
#define mu_graphic_create_via_window_(result, ...) mug_graphic_create_via_window(mug_global_context, result, __VA_ARGS__)
```


### Get window

The function `mug_graphic_get_window` gets the window from a graphic created using a `muWindow`, defined below: 

```c
MUDEF muWindow mug_graphic_get_window(mugContext* context, mugResult* result, muGraphic graphic);
```


Its non-result-checking equivalent macro is defined below: 

```c
#define mu_graphic_get_window(...) mug_graphic_get_window(mug_global_context, &mug_global_context->result, __VA_ARGS__)
```


Its result-checking equivalent macro is defined below: 

```c
#define mu_graphic_get_window_(result, ...) mug_graphic_get_window(mug_global_context, result, __VA_ARGS__)
```


## Main loop graphic functions

There are several graphic functions that are used virtually every frame. This is a list of those functions.

### Get graphic existence status

The function `mug_graphic_exists` returns whether or not a given graphic exists anymore (such as if the graphic is spawned from a window and the window is closed or not), defined below: 

```c
MUDEF muBool mug_graphic_exists(mugContext* context, mugResult* result, muGraphic graphic);
```


Its non-result-checking equivalent macro is defined below: 

```c
#define mu_graphic_exists(...) mug_graphic_exists(mug_global_context, &mug_global_context->result, __VA_ARGS__)
```


Its result-checking equivalent macro is defined below: 

```c
#define mu_graphic_exists_(result, ...) mug_graphic_exists(mug_global_context, result, __VA_ARGS__)
```


Note that a graphic not existing still means that it needs to be destroyed with `mu_graphic_destroy`.

### Clear graphic

The function `mug_graphic_clear` clears the graphical contents of a graphic with a certain color, defined below: 

```c
MUDEF void mug_graphic_clear(mugContext* context, mugResult* result, muGraphic graphic, float r, float g, float b, float a);
```


Its non-result-checking equivalent macro is defined below: 

```c
#define mu_graphic_clear(...) mug_graphic_clear(mug_global_context, &mug_global_context->result, __VA_ARGS__)
```


Its result-checking equivalent macro is defined below: 

```c
#define mu_graphic_clear_(result, ...) mug_graphic_clear(mug_global_context, result, __VA_ARGS__)
```


This function *must* be called before calling any rendering functions.

Note that the `r`, `g`, `b`, and `a` parameters should range between 0.0 and 1.0.

Note that the `a` value has no effect for now, and should be set to 1.0.

### Swap graphic buffers


```c
MUDEF void mug_graphic_swap_buffers(mugContext* context, mugResult* result, muGraphic graphic);
```

Its non-result-checking equivalent macro is defined below: 

```c
#define mu_graphic_swap_buffers(...) mug_graphic_swap_buffers(mug_global_context, &mug_global_context->result, __VA_ARGS__)
```


Its result-checking equivalent macro is defined below: 

```c
#define mu_graphic_swap_buffers_(result, ...) mug_graphic_swap_buffers(mug_global_context, result, __VA_ARGS__)
```


This function should be called near the end of the frame and *before* `mug_graphic_update`.

Before this function is called, `mug_graphic_clear` must have been called at least once.

### Update graphic


```c
MUDEF void mug_graphic_update(mugContext* context, mugResult* result, muGraphic graphic, double target_fps);
```

Its non-result-checking equivalent macro is defined below: 

```c
#define mu_graphic_update(...) mug_graphic_update(mug_global_context, &mug_global_context->result, __VA_ARGS__)
```


Its result-checking equivalent macro is defined below: 

```c
#define mu_graphic_update_(result, ...) mug_graphic_update(mug_global_context, result, __VA_ARGS__)
```


`target_fps` describes the amount of frames per second that mug should attempt to cap at, sleeping for an amount of time to do so. To unlock the FPS, simply set this value to 0.

This function should be called near the end of the frame and *after* `mug_graphic_swap_buffers`, preferably as the last function call of the frame.

# Object buffers

The primary way that mug renders things is with object buffers (respective type `mugObjectBuffer`). There are different object buffer types that are capable of rendering different types of objects.

## Object types

The enum `mugObjectType` is used to represent the object type of a buffer. Its possible values are:

* `MUG_OBJECT_TRIANGLE` - a triangle; respective struct `muTriangle`.

* `MUG_OBJECT_RECT` - a rectangle; respective struct `muRect`.

* `MUG_OBJECT_ROUND_RECT` - a rounded rectangle; respective struct `muRoundRect`.

* `MUG_OBJECT_SQUIRCLE` - a squircle; respective struct `muSquircle`.

* `MUG_OBJECT_CIRCLE` - a circle; respective struct `muCircle`.

## Load object type

The function `mug_gobj_type_load` loads the resources needed for creating object buffers of a given type, defined below: 

```c
MUDEF void mug_gobj_type_load(mugContext* context, mugResult* result, muGraphic graphic, mugObjectType object_type);
```


Its non-result-checking equivalent macro is defined below: 

```c
#define mu_gobj_type_load(...) mug_gobj_type_load(mug_global_context, &mug_global_context->result, __VA_ARGS__)
```


Its result-checking equivalent macro is defined below: 

```c
#define mu_gobj_type_load_(result, ...) mug_gobj_type_load(mug_global_context, result, __VA_ARGS__)
```


This function is automatically called upon creation of an object buffer of type `object_type`, but can also be done manually with this function.

Note that this function will not throw an error if the object type is already loaded.

## Unload object type

The function `mug_gobj_type_unload` unloads the resources needed for creating object buffers of a given type, defined below: 

```c
MUDEF void mug_gobj_type_unload(mugContext* context, muGraphic graphic, mugObjectType object_type);
```


Its non-result-checking equivalent macro is defined below: 

```c
#define mu_gobj_type_unload(...) mug_gobj_type_unload(mug_global_context, __VA_ARGS__)
```


This function should not be called if there are buffers of the given type still in existence.

This function is not required to be called on all loaded object types; it is automatically handled.

## Creation

The function `mug_gobj_buffer_create` creates an object buffer, defined below: 

```c
MUDEF mugObjectBuffer mug_gobj_buffer_create(mugContext* context, mugResult* result, muGraphic graphic, mugObjectType object_type, size_m object_count, void* objects);
```


Its non-result-checking equivalent macro is defined below: 

```c
#define mu_gobj_buffer_create(...) mug_gobj_buffer_create(mug_global_context, &mug_global_context->result, __VA_ARGS__)
```


Its result-checking equivalent macro is defined below: 

```c
#define mu_gobj_buffer_create_(result, ...) mug_gobj_buffer_create(mug_global_context, result, __VA_ARGS__)
```


`objects` is rather a pointer to an `object_count`-length array of objects whose type matches the respective type of the enum value of `object_type` ***or*** 0, which creates the buffer without any data. Calling any function that relies on a buffer's data being filled (such as a render function) when the data isn't initialized will result in undefined behaviour.

`object_count` must be at least 1.

Note that a successfully-created object buffer must be destroyed by the user at some point.

## Destruction

The function `mug_gobj_buffer_destroy` destroys an object buffer, defined below: 

```c
MUDEF mugObjectBuffer mug_gobj_buffer_destroy(mugContext* context, muGraphic graphic, mugObjectBuffer buffer);
```


Its non-result-checking equivalent macro is defined below: 

```c
#define mu_gobj_buffer_destroy(...) mug_gobj_buffer_destroy(mug_global_context, __VA_ARGS__)
```


Note that this function must be called on each successfully-created `mugObjectBuffer` object at some point.

## Render

The function `mug_gobj_buffer_render` renders an object buffer's contents, defined below: 

```c
MUDEF void mug_gobj_buffer_render(mugContext* context, mugResult* result, muGraphic graphic, mugObjectBuffer buffer);
```


Its non-result-checking equivalent macro is defined below: 

```c
#define mu_gobj_buffer_render(...) mug_gobj_buffer_render(mug_global_context, &mug_global_context->result, __VA_ARGS__)
```


Its result-checking equivalent macro is defined below: 

```c
#define mu_gobj_buffer_render_(result, ...) mug_gobj_buffer_render(mug_global_context, result, __VA_ARGS__)
```


Once this function is called, the contents of the buffer should not be modified for the rest of the current frame.

## Sub-render

The function `mug_gobj_buffer_subrender` renders a portion of an object buffer's contents, defined below: 

```c
MUDEF void mug_gobj_buffer_subrender(mugContext* context, mugResult* result, muGraphic graphic, mugObjectBuffer buffer, size_m object_offset, size_m object_count);
```


Its non-result-checking equivalent macro is defined below: 

```c
#define mu_gobj_buffer_subrender(...) mug_gobj_buffer_subrender(mug_global_context, &mug_global_context->result, __VA_ARGS__)
```


Its result-checking equivalent macro is defined below: 

```c
#define mu_gobj_buffer_subrender_(result, ...) mug_gobj_buffer_subrender(mug_global_context, result, __VA_ARGS__)
```


Once this function is called, the buffer should not be destroyed or resized for the rest of the current frame, and the portion of the buffer rendered should not be modified.

## Fill

The function `mug_gobj_buffer_fill` fills an object buffer's contents, defined below: 

```c
MUDEF void mug_gobj_buffer_fill(mugContext* context, mugResult* result, muGraphic graphic, mugObjectBuffer buffer, void* objects);
```


Its non-result-checking equivalent macro is defined below: 

```c
#define mu_gobj_buffer_fill(...) mug_gobj_buffer_fill(mug_global_context, &mug_global_context->result, __VA_ARGS__)
```


Its result-checking equivalent macro is defined below: 

```c
#define mu_gobj_buffer_fill_(result, ...) mug_gobj_buffer_fill(mug_global_context, result, __VA_ARGS__)
```


`objects` is a pointer to an array whose length matches the object length of `buffer` and whose type matches the struct associated with the type of `buffer`.

Note that this function should not be called once the buffer's contents have been rendered for the current frame.

Note that `objects` is not safe to be 0.

## Sub-fill

The function `mug_gobj_buffer_subfill` fills a portion of an object buffer's contents, defined below: 

```c
MUDEF void mug_gobj_buffer_subfill(mugContext* context, mugResult* result, muGraphic graphic, mugObjectBuffer buffer, size_m object_offset, size_m object_count, void* objects);
```


Its non-result-checking equivalent macro is defined below: 

```c
#define mu_gobj_buffer_subfill(...) mug_gobj_buffer_subfill(mug_global_context, &mug_global_context->result, __VA_ARGS__)
```


Its result-checking equivalent macro is defined below: 

```c
#define mu_gobj_buffer_subfill_(result, ...) mug_gobj_buffer_subfill(mug_global_context, result, __VA_ARGS__)
```


`objects` is a pointer to an array of length `object_count` whose type matches the struct associated with the type of `buffer`.

Note that this function should not be called once the buffer's contents being referenced have been rendered for the current frame.

Note that `objects` is not safe to be 0.

## Resize

The function `mug_gobj_buffer_resize` resizes an object buffer and clears its prior contents, defined below: 

```c
MUDEF void mug_gobj_buffer_resize(mugContext* context, mugResult* result, muGraphic graphic, mugObjectBuffer buffer, size_m object_count, void* objects);
```


Its non-result-checking equivalent macro is defined below: 

```c
#define mu_gobj_buffer_resize(...) mug_gobj_buffer_resize(mug_global_context, &mug_global_context->result, __VA_ARGS__)
```


Its result-checking equivalent macro is defined below: 

```c
#define mu_gobj_buffer_resize_(result, ...) mug_gobj_buffer_resize(mug_global_context, result, __VA_ARGS__)
```


Note that this function completely clears whatever contents were in the buffer. This function is primarily used to resize a buffer whilst still maintaining the same handle.

Note that this function should not be called once any portion of the buffer's contents have been rendered for the current frame.

Note that `objects` is safe to be 0.

## Get type

The function `mug_gobj_buffer_get_type` returns the `mugObjectType` the buffer was originally created with, defined below: 

```c
MUDEF mugObjectType mug_gobj_buffer_get_type(mugContext* context, muGraphic graphic, mugObjectBuffer buffer);
```


Its non-result-checking equivalent macro is defined below: 

```c
#define mu_gobj_buffer_get_type(...) mug_gobj_buffer_get_type(mug_global_context, __VA_ARGS__)
```


# Common structs

mug defines several structs used to define shapes. The following is a list of those structs.

## Position

mug uses the struct `muPosition` to represent a 2D position, ranging from (0, 0) being the top-left of the graphic to (width, height) being the bottom-right of the graphic, where width and height are the dimensions of the graphic.

### Members

* `float x` - the x-value of the position.

* `float y` - the y-value of the position.

## Color

mug uses the struct `muColor` to represent a color with its respective red, green, blue, and alpha channels. The channels range from 0.0 to 1.0.

### Members

* `float r` - the red channel of the color.

* `float g` - the green channel of the color.

* `float b` - the blue channel of the color.

* `float a` - the alpha channel of the color.

## Point

mug uses the struct `muPoint` to represent a renderable point, being defined with a position and color.

### Members

* `muPosition pos` - the position of the point.

* `muColor col` - the color of the point.

## Dimensions

mug uses the struct `muDimensions` to represent a width and height.

### Members

* `float width` - the width.

* `float height` - the height.

# Triangle object

The triangle object represents a triangle, AKA three points connected as one shape. Its respective `mugObjectType` enum value is `MUG_OBJECT_TRIANGLE` and its respective struct type is `muTriangle`.

## Struct

The struct `muTriangle` has the following members:

* `muPoint p0` - the first point of the triangle.

* `muPoint p1` - the second point of the triangle.

* `muPoint p2` - the third point of the triangle.

All points are interchangeable and in no particular order; swapping two points with each other will have no visual effect.

# Rect object

The rect object represents a rectangle. Its respective `mugObjectType` enum value is `MUG_OBJECT_RECT` and its respective struct type is `muRect`.

## Struct

The struct `muRect` has the following members:

* `muPoint center` - the center point of the rect.

* `muDimensions dim` - the dimensions of the rect.

* `float rot` - the rotation of the rect in radians.

# Rounded rect object

The rounded rect object represents a rounded rectangle. Its respective `mugObjectType` enum value is `MUG_OBJECT_ROUND_RECT` and its respective struct type is `muRoundRect`.

## Struct

The struct `muRoundRect` has the following members:

* `muPoint center` - the center point of the rect.

* `muDimensions dim` - the dimensions of the rect.

* `float rot` - the rotation of the rect in radians.

* `float round` - the radius of the circles on the rounded edges.

`round` should be at least 0 and less than half of `dim.width` and half of `dim.height`.

# Squircle object

The squircle object represents a [squircle](https://en.wikipedia.org/wiki/Squircle). Its respective `mugObjectType` enum value is `MUG_OBJECT_SQUIRCLE` and its respective struct type is `muSquircle`.

## Struct

The struct `muSquircle` has the following members:

* `muPoint center` - the center of the squircle.

* `muDimensions dim` - the dimensions of the squircle.

* `float rot` - the rotation of the squircle in radians.

* `float exp` - the exponent of the squircle (`(x^exp + y^exp = r^exp)`).

The higher `exp` is, the sharper the edges of the squircle become. `exp` should never be below 0.

# Circle object

The circle object represents a [circle](https://en.wikipedia.org/wiki/Circle). Its respective `mugObjectType` enum value is `MUG_OBJECT_CIRCLE` and its respective struct type is `muCircle`.

## Struct

The struct `muCircle` has the following members:

* `muPoint center` - the center of the circle.

* `float radius` - the radius of the circle. The value of this member should always be greater than or equal to 0.

# Graphics API customization

There are certain things that can be done in mug to customize how a particular graphics API functions. This section covers those.

## Vulkan

### Frame buffering

Vulkan allows frames to be buffered, which means that multiple frames can be used for drawing, which wastes less time waiting for the previous frame to be finished. The amount of these frames is controllable by the macro `MUG_VK_FRAME_BUFFERS`, whose default value is 3.

### Debug messages

Vulkan has a built-in system for printing debug information, but requires the Vulkan SDK to be manually installed on the machine to work. As such, this system is, on default, not used, but can be manually turned on by defining `MUG_VK_DEBUG` before the inclusion of the header file.

Note that defining `MUG_VK_DEBUG` without having the Vulkan SDK is safe, the feature just won't work.

# Version macro

mug defines three macros to define the version of mug: `MUG_VERSION_MAJOR`, `MUG_VERSION_MINOR`, and `MUG_VERSION_PATCH`, following the format of `vMAJOR.MINOR.PATCH`.

# C standard library dependencies

mug has several C standard library dependencies not provided by its other library dependencies, all of which are overridable by defining them before the inclusion of its header. This is a list of all of those dependencies.

## `stdint.h` dependencies

`MU_UINT32_MAX`: equivalent to `UINT32_MAX`

`MU_UINT64_MAX`: equivalent to `UINT64_MAX`

## `stdio.h` dependencies

`mu_printf`: equivalent to `printf`; only defined if `MUG_VK_DEBUG` is defined before the inclusion of the header file.

## `math.h` dependencies

`mu_sin`: equivalent to `sin`

`mu_cos`: equivalent to `cos`
