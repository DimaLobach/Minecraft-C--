#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SFML/OpenGL.hpp>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace sf;
using namespace std;

#include <stdlib.h>
#include "init.hpp"
#include "renderHelper.hpp"
#include "block.hpp"
#include "load.hpp"
#include "game.hpp"
#include "render.hpp"
