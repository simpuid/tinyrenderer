project('tinyrenderer','cpp',version : '0.1',default_options : ['warning_level=3','cpp_std=c++17'])
#include directory
incdir = include_directories('include')

#main file
main = 'source/main.cpp'

#source files
sources = [
	'source/image.cpp',
	'source/shapes.cpp',
	'source/model.cpp',
	'source/color.cpp',
	'source/zbuffer.cpp',
	'source/camera.cpp'
]

#main executable
executable('main','source/main.cpp',include_directories:incdir,sources : [sources,main])