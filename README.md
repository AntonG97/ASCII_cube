# ASCII Cube

A terminal-based 3D ASCII renderer written in C++. It rotates and renders
triangle-mesh shapes using perspective projection, face-visibility checks,
scanline rasterization, and a depth buffer.

The repository also contains `ascii_cube.c`, the original C cube renderer.
The CMake project builds the C++ application, `Rotating_Ascii`.

## Shapes

The C++ renderer supports:

- `cube`
- `octahedron`
- `tetrahedron`
- `random` — selects one of the supported shapes

## Build

Requirements: CMake 3.15 or newer, a C++17 compiler, and Make.

From the repository root:

```bash
cmake -S . -B build
cmake --build build
```

The build creates `./Rotating_Ascii` in the repository root.

## Run

```bash
./Rotating_Ascii <shape> [scale] [-color]
```

The shape is required. `scale` is an optional positive integer that controls
the shape's size (default: `20`). Color is optional; use `-color`, `-Color`,
`-c`, or `-C`. These optional arguments can be supplied in either order.

Examples:

```bash
./Rotating_Ascii cube
./Rotating_Ascii tetrahedron 12 -color
./Rotating_Ascii random -c
```

The terminal output is fixed at 40 columns by 20 rows.

## Controls

Type `q` or `clear` followed by Enter to exit. Press `Ctrl+C` to exit as well.
The program restores the terminal colors and cursor when it shuts down.

## Architecture

- **CLI_Parser** validates command-line arguments and creates shapes.
- **Transformation** rotates shape vertices and applies perspective projection.
- **Renderer** coordinates transformation and rasterization for each frame.
- **Rasterizer** culls invisible faces, fills triangles, and depth-tests pixels.
- **FrameBuffer** stores character pixels; **CLIpc** displays them in the terminal.

See [doc/Architecture.drawio](doc/Architecture.drawio) for the architecture
diagram.
