#ifndef DBDG_GL_DBDG_H
#define DBDG_GL_DBDG_H

#ifdef DBDG_MAX_OS
#define GLFW_NO_GLU
#define GLFW_INCLUDE_GL3
#endif

#ifdef DBDG_LINUX_OS
#define GLFW_NO_GLU
#define GL_GLEXT_PROTOTYPES
#endif

#ifdef DBDG_WINDOWS_OS
#define GLFW_NO_GLU
#endif

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GL/freeglut.h"

#include "GLDirector.h"
#include "GLGame.h"
#include "GLScene.h"
#include "GLGraphic.h"
#include "GLInput.h"
#include "GLFont.h"
#include "SpriteBatcher.h"
#include "SpriteBatcher3D.h"
#include "Camera2D.h"
#include "Camera3D.h"
#include "KeyboardHandler.h"
#include "MouseHandler.h"
#include "ScrollHandler.h"

#include "../SpriteAnimation.h"

/*
  GLTexture AssimpModel, XfileModelはManagerクラスからしか呼ばれないようにインクルードしない
 */


#endif
