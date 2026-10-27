*This project has been created as part of the 42 curriculum by amugisha*

# Description

The project is to build a small program that displays a 3D object created with a modeling tool such as Blender.

This 3D object will be stored in a .obj file. I will be responsible for parsing it
and rendering it correctly.

Inside a window, the 3D object must be displayed in perspective, and i must be able to rotate and translate it around its three main axes of symmetry, using any user input
method of my choice (keyboard, mouse, etc.).

Using various colors, i must make the different faces of the object visually distin-
guishable.

Finally, pressing a dedicated key should apply a texture to the object. Pressing that same key again should toggle it back to the colored view. A smooth transition between the two is expected, with no abrupt cuts.

### Requierment

Language accepted: C, C++ or Rust.
No leack accepted !
Graphic librairy accepted: OpenGL, Vulkan, or Metal.

# Instructions

Install GLAD and GLFW. Take the good version for your device.
I all ready compile libs for x86_64_linux-gnu, if you don't have the same, complie the libs.

move "local" folder at ~/ and execute this command
```
export LD_LIBRARY_PATH="$HOME/local/lib:$LD_LIBRARY_PATH"
```

if you whant percice this command, add this command in your ~/.zshrc ou ~/.bashrc

For build default model

- make : compile with default model
- make all : same than make alone 
- make re : same than fclean then

```
make
```
or

```
make all
```

For build model

- 42
- 42N : model with normal and UV
- teapot
- teapot2 : model with normal and UV
- dragon
- luffy

```
make model
```

For clean

- clean : remove object file (.o)
- fclean : remove object file and executable

```
make command
```

# Resources

https://learnopengl.com/

https://www.brainvoyager.com/bv/doc/UsersGuide/CoordsAndTransforms/SpatialTransformationMatrices.html

https://www.glfw.org/docs/latest/