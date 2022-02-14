##***************************************************************************
##    Original code written in: May 2006    
##    copyright: (C) Carlucio Santos Cordeiro
##***************************************************************************
lib_sources = [
    'src/Engine/Core/Application.cpp',
    'src/Engine/Core/Clock.cpp',
    'src/Engine/Core/TimeSourceSDL.cpp',
    'src/Engine/Core/TimeSourceHRLinux.cpp',
    'src/Engine/Core/Timer.cpp',

    'src/Engine/Gfx/Camera.cpp',
    'src/Engine/Gfx/FogState.cpp',
    'src/Engine/Gfx/LightState.cpp',
    'src/Engine/Gfx/Md2.cpp',
    'src/Engine/Gfx/RenderableObject.cpp',
    'src/Engine/Gfx/Scene.cpp',
    'src/Engine/Gfx/SceneObject.cpp',
    'src/Engine/Gfx/Screen.cpp',
    'src/Engine/Gfx/ShaderState.cpp',
    'src/Engine/Gfx/SimulationObject.cpp',
    'src/Engine/Gfx/Sphere.cpp',
    'src/Engine/Gfx/Terrain.cpp',
    'src/Engine/Gfx/TextBox.cpp',
    'src/Engine/Gfx/Texture.cpp',
    'src/Engine/Gfx/Trimesh.cpp',
    'src/Engine/Gfx/Viewport.cpp',
    'src/Engine/Gfx/WireframeState.cpp',

    'src/Engine/Math/Matrix3.cpp',
    'src/Engine/Math/Matrix4.cpp',
    'src/Engine/Math/Vector2.cpp',
    'src/Engine/Math/Vector3.cpp',
    'src/Engine/Math/Vector4.cpp',
    'src/Engine/Math/multifractal.cpp',
    'src/Engine/Math/noise.cpp',
    'src/Engine/Math/transform.cpp']


prog_sources = [
    'src/FlockingDemo/Atmosphere.cpp',
    'src/FlockingDemo/Sky.cpp',
    'src/FlockingDemo/Sun.cpp',
    'src/FlockingDemo/Boid.cpp',
    'src/FlockingDemo/FlockingDemo.cpp',
    'src/FlockingDemo/LeaderBoid.cpp',
    'src/FlockingDemo/main.cpp' ]

scatter_sources = [
    'src/ScatteringDemo/Atmosphere.cpp',
    'src/ScatteringDemo/Sky.cpp',
    'src/ScatteringDemo/Sun.cpp',
    'src/ScatteringDemo/ScatteringDemo.cpp',
    'src/ScatteringDemo/Bird.cpp',
    'src/ScatteringDemo/main.cpp' ]


libs = ['engine', 'GL', 'GLU', 'GLEW', 'SDL', 'SDL_image']
libpath = ['.', '/usr/lib', '/usr/local/lib']


opt_flags = '-Wall -O3 -pipe -funroll-loops -fomit-frame-pointer `sdl-config --cflags`'
dbg_flags = '-Wall -g `sdl-config --cflags`'


opt_env = Environment(LIBS = libs, LIBPATH = libpath, CCFLAGS = opt_flags)
dbg_env = Environment(LIBS = libs, LIBPATH = libpath, CCFLAGS = dbg_flags)


lib = opt_env.Library('engine', lib_sources)
prg = opt_env.Program('flocking', prog_sources)
scatter = opt_env.Program('scatter', scatter_sources)

Depends(prg, lib)
