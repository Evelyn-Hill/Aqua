# Aqua
is a cross-platform (Windows, Linux) 2d and (soon to be) 3d game framework. It is *not* explicitly a game engine, but rather a starting point for me to make games.

### Included
- Game and Window Abstractions.
- Event Sytem (soon)
- AssetManager.
- Logging.
- 2d and (soon) 3d renderer.
- Package Format. (soon)

### Not included
- Editor.
- Entity System. 

<hr> 

## Building Aqua

Aqua relies **heavily** on git submodules and I reccomend you use it as a submodule in your own project.
to clone aqua with submodules included use -
<br>
`git clone --recurse-submodules https://github.com/Evelyn-Hill/Aqua.git`
<br> 
then run
<br>
`cmake --preset ninja-debug`
<br>
`cmake --build build/`

## Contributions

Aqua is open for external contributions on an extremely limited basis. If you'd like to contribute please first open a discussion
here on github with your suggestion. Most suggestions will be denied because we have a very specific internal roadmap that we are
shooting for. Any PR or Issue opened without first opening a discussion will be deleted/ignored.
