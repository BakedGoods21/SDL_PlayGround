// GL Libraries
#include <GL/glew.h>
#include <cmath>

// BakedEngine Libraries
#include "BakedEngine/BakedEngine.h"
#include "BakedEngine/FastTrig.h"

namespace BakedEngine
{

bool init(uint32_t subSystemFlags/* = SDL_INIT_EVERYTHING*/)
{
	// Initialize SDL Every subsystem
	//  -  SDL_INIT_TIMER          0x00000001u
	//  -  SDL_INIT_AUDIO          0x00000010u
	//  -  SDL_INIT_VIDEO          0x00000020u  /**< SDL_INIT_VIDEO implies SDL_INIT_EVENTS */
	//  -  SDL_INIT_JOYSTICK       0x00000200u  /**< SDL_INIT_JOYSTICK implies SDL_INIT_EVENTS */
	//  -  SDL_INIT_HAPTIC         0x00001000u
	//  -  SDL_INIT_GAMECONTROLLER 0x00002000u  /**< SDL_INIT_GAMECONTROLLER implies SDL_INIT_JOYSTICK */
	//  -  SDL_INIT_EVENTS         0x00004000u
	//  -  SDL_INIT_SENSOR         0x00008000u
	//  -  SDL_INIT_NOPARACHUTE    0x00100000u  /**< compatibility; this flag is ignored. */
	if ( SDL_InitSubSystem(subSystemFlags) < 0 )
	{
		return false;
	}

	// OpenGL Attributes
	const int _glMajorVersion = 3;
	int _glMinorVersion = 1;
	SDL_GLprofile _contextProfile = SDL_GL_CONTEXT_PROFILE_CORE;
	bool _isDoubleBufferEnabled = true;

	// Use OpenGL 3.1 core
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, _glMajorVersion );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, _glMinorVersion );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, _contextProfile );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, _isDoubleBufferEnabled );

	initializeBakedTrig();

	return true;
}

} // End of namespace BakedEngine
