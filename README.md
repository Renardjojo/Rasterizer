# Rasterizer
> Mencias Anaelle & Six Jonathan.
> December 2019

## Summary
- [Description](##Description "Goto description part")
- [Command](##Command "Goto command part")
- [How to compil](##How-to-compil "Goto compil part")
- [How to launch](##How-to-launch "Goto launch part")
- [Bug](##Bug "Goto bug part")
- [Technical aspect](##Technical-aspect "Goto yechnical part")

## Description

Rasterizer is a project inspired of OpenGl. It consist to draw 3D shape with different projection. Different demonstration is proposed to show with different setting the capacity of this rasterizer project. 

Rasterizer is a process of renderisation consisting to draw pixel on screen in good emplacement.

## Command

### Keyboard :
Command | Action
------------- | -------------
F1          | Switch demo (7 demos)
F2          | Show edge (on/off)
F3          | Display in tripolar color (on/off)
F4          | Display depth buffer (on/off)
F5          | Show normal vector (on/off)
F6          | Display entities fills (on/off)
F7          | Show referntial (on/off)
F8          | Enable back face culling (on/off)
F9          | Enable anti aliazing (on/off)
F10         | Use Phong light algorythm (on/off)
F11         | Use Blinn-Phong light algorythm  (on/off)
F12         | Switch Ortho/Perspective  (on/off)
P           | Pause (on/off)
BackSpace   | go back in time
W           | Move foward
A           | Move left
S           | Move backward
D           | move rigth
Esc         | Exit


### Mouse :
Command | Action
------------- | -------------
Wheel forward/Rearward     | Scale entites


## How to compil
Open terminal in source of project and execut this command

```
make
```

## How to launch

```
make run
or
./bin/exe
```

## Bug

SDL dosn't use the same format to load png or jpg. (RGB or RGBA). It can cause texture bug color. 

## Technical aspect

This project can load .obj (mesh of 3d object) and .mtl (material setting) files.

Ligth run with Phong or Blinn-Phong algorythm.

Clipping is apply in Rasterizer pipelline.

This project is depending to :
- SDL 2.0
- tinyObj

