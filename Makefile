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