# Имя игры
GAME_NAME = snake
# Версия
VERSION = v1.0
# Стадия
STAGE.1 = proto
STAGE.2 = alpha
STAGE.3 = beta
STAGE.4 = release
STAGE = $(STAGE.1)

# Операционная система
IOS.1 = linux
ISO.2 = win

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
TARGET = $(GAME_NAME)

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

# -------------------------------
# Windows-сборка
# -------------------------------

# Компилятор для Windows
WIN_CXX = x86_64-w64-mingw32-g++

# Папка для объектных файлов
WIN_OBJ_DIR = win-obj

# Имя исполняемого файла под Windows
WIN_TARGET = $(GAME_NAME).exe

# Библиотеки
WIN_LIBS := $(shell x86_64-w64-mingw32-pkg-config sdl2 SDL2_ttf --cflags --libs)

# Флаги компиляции (Windows)
WIN_CXXFLAGS = -std=c++17 -Wall -Wextra -MMD

# Генерация объектников для Windows
WIN_OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(WIN_OBJ_DIR)/%.o, $(SRC_FILES))
WIN_OBJ_FILES := $(subst $(SRC_DIR)/, $(WIN_OBJ_DIR)/, $(WIN_OBJ_FILES))

# Подключение сгенерированных зависимостей
-include $(WIN_OBJ_FILES:.o=.d)

# Сборка под Windows
windows: $(WIN_TARGET) 

$(WIN_TARGET): $(WIN_OBJ_FILES)
	$(WIN_CXX) $(WIN_CXXFLAGS) -o $@ $^ $(WIN_LIBS)

# Компиляция для Windows
$(WIN_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(WIN_CXX) $(WIN_CXXFLAGS) -c $< -o $@

# -------------------------------
# Архивация
# -------------------------------

# Папка для финальных архивов
DIST_DIR = dist

# Общие файлы
DLL = libgcc_s_seh-1.dll libstdc++-6.dll SDL2.dll SDL2_ttf.dll
COMMON_FILES = assets docs README.md

# Имена главной папки и архива
ZIP_NAME_LIN = $(GAME_NAME)_$(STAGE)_$(VERSION)_$(IOS.1).zip
ZIP_NAME_WIN = $(GAME_NAME)_$(STAGE)_$(VERSION)_$(ISO.2).zip

# Создание архива для Linux
zip-lin: $(TARGET)
	@mkdir -p $(DIST_DIR)/$(GAME_NAME)_$(VERSION)_$(IOS.1)
	cp $(TARGET) $(DIST_DIR)/$(GAME_NAME)_$(VERSION)_$(IOS.1)/
	cp -r $(COMMON_FILES) $(DIST_DIR)/$(GAME_NAME)_$(VERSION)_$(IOS.1)/
	cd $(DIST_DIR) && zip -r $(ZIP_NAME_LIN) $(GAME_NAME)_$(VERSION)_$(IOS.1)
	rm -rf $(DIST_DIR)/$(GAME_NAME)_$(VERSION)_$(IOS.1)

# Создание архива для Windows
zip-win: $(WIN_TARGET)
	@mkdir -p $(DIST_DIR)/$(GAME_NAME)_$(VERSION)_$(IOS.2)
	cp $(WIN_TARGET) $(DIST_DIR)/$(GAME_NAME)_$(VERSION)_$(IOS.2)/
	cp -r $(COMMON_FILES) $(DLL) $(DIST_DIR)/$(GAME_NAME)_$(VERSION)_$(IOS.2)/
	cd $(DIST_DIR) && zip -r $(ZIP_NAME_WIN) $(GAME_NAME)_$(VERSION)_$(IOS.2)
	rm -rf $(DIST_DIR)/$(GAME_NAME)_$(VERSION)_$(IOS.2)

# Очистка
clean:
	rm -f $(TARGET)
	rm -rf $(OBJ_DIR)
	rm -f $(WIN_TARGET)
	rm -rf $(WIN_OBJ_DIR)

clean-linux:
	rm -f $(TARGET)
	rm -rf $(OBJ_DIR)

clean-windows:
	rm -f $(WIN_TARGET)
	rm -rf $(WIN_OBJ_DIR)

clean-dist:
	rm -rf $(DIST_DIR)