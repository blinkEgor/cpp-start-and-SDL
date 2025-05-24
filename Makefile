# -------------------------------
# Linux-сборка 
# -------------------------------

# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++17 -Wall -Wextra -MMD

# Библиотеки
LIBS = -lSDL2 -lSDL2_ttf

# Директории
SRC_DIR = src
OBJ_DIR = obj

# Поиск всех исходников рекурсивно
SRC_FILES := $(shell find $(SRC_DIR) -type f -name "*.cpp")

# Генерация объектных файлов с сохранением структуры папок
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
OBJ_FILES := $(subst $(SRC_DIR)/, $(OBJ_DIR)/, $(OBJ_FILES))

# Имя исполняемого файла
TARGET = snake

# Подключение сгенерированных зависимостей
-include $(OBJ_FILES:.o=.d)

# Правило по умолчанию
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ_FILES) $(LIBS)

# Компиляция .cpp -> .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Запуск
run: $(TARGET)
	./$(TARGET)

# Очистка
clean:
	rm -f $(TARGET)
	rm -rf $(OBJ_DIR)


# -------------------------------
# Windows-сборка !!! НЕ РАБОТАЕТ
# -------------------------------

# Компилятор для Windows
WIN_CXX = x86_64-w64-mingw32-g++

# Папка для объектных файлов
WIN_OBJ_DIR = win-build

# Имя исполняемого файла под Windows
WIN_TARGET = snake.exe

# SDL2 и TTF (в проекте)
WIN_SDL_DIR = win-libs/SDL2
WIN_TTF_DIR = win-libs/SDL2_ttf

# Флаги компиляции (Windows)
WIN_CXXFLAGS = -std=c++17 -Wall -Wextra -I$(WIN_SDL_DIR)/include -I$(WIN_TTF_DIR)/include -Dmain=SDL_main

# Флаги линковки (Windows)
WIN_LIBS = \
	-L$(WIN_SDL_DIR)/lib -lSDL2 \
	-L$(WIN_TTF_DIR)/lib -lSDL2_ttf \
	-mwindows

# Генерация объектников для Windows
WIN_OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(WIN_OBJ_DIR)/%.o, $(SRC_FILES))
WIN_OBJ_FILES := $(subst $(SRC_DIR)/, $(WIN_OBJ_DIR)/, $(WIN_OBJ_FILES))

# Сборка под Windows
# windows: $(WIN_TARGET)

$(WIN_TARGET): $(WIN_OBJ_FILES)
	$(WIN_CXX) $(WIN_CXXFLAGS) -o $(WIN_TARGET) $(WIN_OBJ_FILES) $(WIN_LIBS)

# Компиляция для Windows
$(WIN_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(WIN_CXX) $(WIN_CXXFLAGS) -c $< -o $@

# Очистка Windows-сборки
# clean-windows:
# 	rm -f $(WIN_TARGET)
# 	rm -rf $(WIN_OBJ_DIR)

# -------------------------------
# Архивация
# -------------------------------

# Папка для финальных архивов
DIST_DIR = dist

# Общие файлы в архив
COMMON_FILES = assets docs README.md

# Создание архива для Linux
zip-linux: $(TARGET)
	@mkdir -p $(DIST_DIR)/snake
	cp $(TARGET) $(DIST_DIR)/snake/
	cp -r $(COMMON_FILES) $(DIST_DIR)/snake/
	cd $(DIST_DIR) && zip -r snake_by_blinkegor-linux-v1.0.zip snake
	rm -rf $(DIST_DIR)/snake

# Создание архива для Windows
# zip-windows: $(WIN_TARGET)
# 	@mkdir -p $(DIST_DIR)/snake
# 	cp $(WIN_TARGET) $(DIST_DIR)/snake/
# 	cp -r $(COMMON_FILES) win-libs $(DIST_DIR)/snake/
# 	cd $(DIST_DIR) && zip -r snake_by_blinkegor-windows-v1.0.zip snake
# 	rm -rf $(DIST_DIR)/snake