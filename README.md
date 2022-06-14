## NoneRender

[![CodeFactor](https://www.codefactor.io/repository/github/hx-w/nonerender/badge)](https://www.codefactor.io/repository/github/hx-w/nonerender)

### Build and run
Move STL file to `./static/STL/`, and rename as `JawScan.stl`

- **Win32**: `.\build.bat && .\main.exe`
- **MacOS**: `sh build.sh && ./main`

### Introduction

- Each nurbs tooth contains 4 nurbs surface (`face1, face2, face3, face4`)
- `face1` with color `white`(DEFAULT), `green`(ON EDGE), `blue`(IN EDGE)
- `face2` with color `yellow`
- `face3` with color `light blue`
- `face4` with color `light green`


### Usage

- `W, A, S, D` for moving camera `front, left, back, right`
- `H` for hiding or showing nurbs face
- `T` for toggle shade mode: `GL_LINE, GL_POINT, GL_FILL`
- `Mouse pressing and moving` for rotating
- `Mouse scrolling` for scaling
- `Ctrl + Left click` for picking point in nurbs face-1
- `Ctrl + R` for clear picked ray/point
- `ESC` for exit

> **Tips**:
> Nurbs face will generate and show gradually,
> You will see those faces below initial camera position.


### Reference

- `src/render/libs`: open source libs for rendering
- `src/infrastructure`: adapted from actual projects
