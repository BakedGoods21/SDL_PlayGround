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

	initializeBakedTrig();

	return true;
}

} // End of namespace BakedEngine
