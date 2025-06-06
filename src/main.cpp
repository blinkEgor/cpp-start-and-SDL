#include "Graphics/WindowManager.h"
#include "Utils/LogError.h"
#include "Game/GameManager.h"

int main( int /*argc*/, char** /*args[]*/ ) {
	WindowManager window_manager( "Snake", 800, 544 );
	
	if( !window_manager.init() ) {
		logError( "Failed to initialize WindowManager", LogLevel::ERROR );
		return -1;
	}
	else {
		GameManager game_manager( &window_manager );
		game_manager.game_loop();
	}
	return 0;
}