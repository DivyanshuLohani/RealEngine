# RealEngine

A cross-platform (Windows / Linux) C++20 game engine built on **OpenGL**, with a
renderer-agnostic architecture so the graphics backend can be replaced later
without touching engine or game code.

Target rendering fidelity: **pre-2007 era titles** (early programmable pipeline —
dynamic lighting, shadow mapping, post-processing, particles). Scope is intended
to grow over time.

## Architecture at a glance

```
 Sandbox (game / demo)
        │  uses only public engine headers
        ▼
 RealEngine  ── Core (Application, Log, Events, Window abstraction)
        │    ── Render (backend-agnostic interfaces: RendererAPI, Shader,
        │              Texture, Buffer, VertexArray, Framebuffer, ...)
        ▼
 Platform/OpenGL  ── the only code that includes <glad/gl.h> and <GLFW/glfw3.h>
```

* **Nothing above `Engine/src/Engine/Platform/OpenGL/` includes OpenGL or GLFW
  headers.** A second backend (Vulkan/D3D11) only has to implement the interfaces
  in `Engine/include/Engine/Render/`.
* The backend is selected at configure time via `-DRE_RENDERER_BACKEND=OpenGL`.

## Dependencies

Resolved automatically by CMake (`cmake/Dependencies.cmake`). System packages are
preferred when present, otherwise pinned releases are fetched with `FetchContent`:

| Library | Role |
|---------|------|
| GLFW    | Window, input, GL context creation |
| glad2   | OpenGL 4.6 core function loader |
| GLM     | Math |
| spdlog  | Logging |
| stb     | Image loading (stb_image) |

## Building

### Linux
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
./build/bin/Sandbox
```

### Windows (Visual Studio / Ninja)
```bat
cmake -S . -B build -G "Visual Studio 17 2022"
cmake --build build --config Debug
build\bin\Debug\Sandbox.exe
```

## Project layout

```
RealEngine/
├── CMakeLists.txt          Root build script (options, deps, targets)
├── cmake/                  Dependencies.cmake, CompilerWarnings.cmake
├── Engine/                 The engine static library ("RealEngine")
│   ├── include/Engine/     Public API headers
│   └── src/Engine/         Implementation + OpenGL backend
├── Sandbox/                Runnable demo application
└── Assets/                 Runtime assets (shaders, textures, models)
```

## Roadmap

- [x] **Phase 0** — Project skeleton, build system, GLFW window, logging, events, clear-color loop
- [X] **Phase 1** — Delta time, input abstraction, resize handling
- [ ] **Phase 2** — RHI + OpenGL backend: buffers, shaders, vertex arrays, first triangle
- [ ] **Phase 3** — Cameras (orthographic + perspective) and math integration
- [ ] **Phase 4** — Textures, alpha blending
- [ ] **Phase 5** — Batched 2D sprite renderer
- [ ] **Phase 6** — 3D meshes, Blinn-Phong forward lighting, materials
- [ ] **Phase 7** — Shadow mapping, SSAO, bloom + tonemapping, skybox, particles
- [ ] **Phase 8** — ECS, scene serialization, asset manager, audio
- [ ] **Phase 9** — Additional renderer backend, editor tooling, scripting
