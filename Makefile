# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++17 -Wall -Wextra

# Библиотеки
LIBS = -lSDL2

# Директории
SRC_DIR = src
OBJ_DIR = obj

# Исходные файлы
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/Graphics/*.cpp $(SRC_DIR)/Game/*.cpp $(SRC_DIR)/Utils/*.cpp $(SRC_DIR)/Entities/*.cpp)

# Объектные файлы
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Имя исполняемого файла
TARGET = main

# Правило по умолчанию
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ_FILES) $(LIBS)

# Правило для компиляции .cpp файлов в .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Запуск программы
run: $(TARGET)
	./$(TARGET)

# Очистка
clean:
	rm -f $(TARGET)
	rm -rf $(OBJ_DIR)