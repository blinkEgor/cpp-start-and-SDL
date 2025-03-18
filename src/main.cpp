#include "Graphics/WindowManager.h"
#include "Utils/LogError.h"
#include "Game/GameManager.h"

int main( int /*argc*/, char** /*args[]*/ ) {
	WindowManager WindowManager( "Snake", 32*24+32, 32*16+32 );
	
	if( !WindowManager.init() ) {
		logError( "Failed to initialize WindowManager", LogLevel::ERROR );
		return -1;
	}
	else {
		GameManager GameManager( &WindowManager );
		GameManager.game_loop();
	}
	return 0;
}