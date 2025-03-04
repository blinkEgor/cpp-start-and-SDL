#pragma once

#include <fstream>  // Для работы с файлами
#include <iostream> // Для вывода в консоль
#include <chrono>   // Для работы со временем
#include <iomanip>  // Для форматирования вывода
#include <ctime>    // Для преобразования времени в строку

// Перечисление для типов сообщений
enum class LogLevel {
    INFO,
    ERROR,
    WARNING,
    DEBUG
};

void logError( const std::string& message, LogLevel level = LogLevel::ERROR );
std::string getCurrentTime();