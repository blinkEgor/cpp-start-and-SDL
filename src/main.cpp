#include "Graphics/WindowManager.h"
#include "Utils/LogError.h"
#include "Game/GameManager.h"

int main( int /*argc*/, char** /*args[]*/ ) {
	WindowManager windowManager( "Snake", 32*24+32, 32*16+32 );
	
	if( !windowManager.init() ) {
		logError( "Failed to initialize WindowManager", LogLevel::ERROR );
		return -1;
	}
	else {
		GameManager gameManager( &windowManager );
		gameManager.gameLoop();
	}
	return 0;
}