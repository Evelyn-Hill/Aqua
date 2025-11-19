# Aqua
is a cross-platform (Windows, Linux) 2d and (soon to be) 3d game framework. It is *not* explicitly a game engine, but rather a starting point for me to make games.

### Included
- Game and Window Abstractions.
- AssetManager.
- Logging.
- 2d and (soon) 3d renderer.

### Not included
- Editor.
- Entity System.
- Package Format.

<hr> 

## Building Aqua

Aqua relies heavily on git submodules and I reccomend you use it as a submodule in your own project.
to clone aqua with submodules included use
<br>
`git clone --recurse-submodules https://github.com/Evelyn-Hill/Aqua.git`
<br> 
then run
<br>
`cmake -B build`
`cmake --build build`
