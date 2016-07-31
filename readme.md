# Galaxy

A simple OpenGL 2D star/galaxy N-body gravity simulator.

* Author: [Mikko Ronkainen](http://mikkoronkainen.com)
* Website: [github.com/mikoro/cellvision](https://github.com/mikoro/galaxy)

[Youtube video](https://youtu.be/vU7oqISAM1k)

![Screenshot](http://mikoro.github.io/images/galaxy/readme-screenshot.jpg "Screenshot")

## Download

| Windows 64-bit                                                                                                     | Mac OS X (10.9+)                                                                                                   | Linux 64-bit                                                                                                     |
|--------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------|
| [galaxy-win-0.1.0.zip](https://github.com/mikoro/galaxy/releases/download/v0.1.0/galaxy-win-0.1.0.zip)             | N/A | N/A |

**Note:** You'll need graphics drivers that have support for at least OpenGL 4.3.

## Features

- 32768 differently sized and colored stars, all affecting each other.
- All data stored in a single vertex buffer.
- Compute shaders are used in two passes. First pass calculates the forces for each star and the second pass does the velocity/position integration.
- Geometry shader is used for generating quads from the star positions.
- Fragment shader is used for modeling the star shape.

## Instructions

Settings can be changed prior to launching by editing the *galaxy.ini* file.

### Controls

| Key                      | Action                                                                                |
|--------------------------|---------------------------------------------------------------------------------------|
| **Space**                | Reset stars                                                                           |
| **Mouse left**           | Attract stars to mouse cursor                                                         |

## License

    Galaxy
    Copyright © 2016 Mikko Ronkainen
    
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    
    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
