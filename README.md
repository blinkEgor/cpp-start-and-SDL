# Snake Game by blinkEgor

## Инструкция для запуска на Linux:

### 1. Установите зависимости (SDL2 + SDL2_ttf):
Debian/Ubuntu:
bash
    sudo apt-get install libsdl2-2.0-0 libsdl2-ttf-2.0-0  

Fedora:
bash
    sudo dnf install SDL2 SDL2_ttf  

Arch/Manjaro:
bash
    sudo pacman -S sdl2 sdl2_ttf  

### 2. Дайте права на запуск исполняемого файла:
bash
    chmod +x snake  

### 3. Запустите игру:
bash
    ./snake  

Важно:
    Убедитесь, что файлы ассетов (шрифты, изображения) находятся в правильных путях (относительно исполняемого файла).
    Если возникают ошибки вида Library not found, переустановите зависимости из п.1.

### Rule for variable naming style

- For object names, use **PascalCase**
- For constant names use **UPPER_SNAKE_CASE**
- For variable names, use **snake_case**
- - Use the **m_** prefix ( member ) for private variables
- For method names, use **snake_case**
- For free function names, use **lowerCamelCase**

### Credits

This game uses:
- SDL2 (https://www.libsdl.org), licensed under the zlib License.
- SDL_image (https://github.com/libsdl-org/SDL_image/blob/main/LICENSE.txt), licensed under the zlib License.
- SDL2_ttf (uses FreeType), licensed under the FreeType License.
- Font "Press Start 2P" by CodeMan38 (https://fonts.google.com/specimen/Press+Start+2P), licensed under SIL Open Font License.