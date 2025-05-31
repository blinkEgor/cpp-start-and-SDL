# Snake Game by blinkEgor

## Instructions for running on Linux:
### 1. Install dependencies (SDL2 + SDL2_ttf):
Debian/Ubuntu:
bash
    sudo apt-get install libsdl2-2.0-0 libsdl2-ttf-2.0-0  

Fedora:
bash
    sudo dnf install SDL2 SDL2_ttf  

Arch/Manjaro:
bash
    sudo pacman -S sdl2 sdl2_ttf  

### 2. Grant permissions to run the executable file:
bash
    chmod +x snake  

### 3. Launch the game:
bash
    ./snake  

Important:
    Make sure that asset files (fonts) are in the correct paths (relative to the executable file).
    If errors like Library not found occur, reinstall the dependencies from step 1.

## Licenses
- [EULA](EULA.txt) (terms of use of the game).  
- [Third party licenses](LICENSES.txt).  
- [FreeType License (FTL)](FTL.TXT).  
- [Font "Press Start 2P" (OFL)](OFL.txt).  

## Credits
This game uses:
- SDL2 (https://www.libsdl.org), licensed under the zlib License.
- SDL_image (https://github.com/libsdl-org/SDL_image/blob/main/LICENSE.txt), licensed under the zlib License.
- SDL2_ttf (uses FreeType), licensed under the FreeType License.
- Font "Press Start 2P" by CodeMan38 (https://fonts.google.com/specimen/Press+Start+2P), licensed under SIL Open Font License.