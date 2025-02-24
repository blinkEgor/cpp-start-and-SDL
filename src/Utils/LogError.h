#pragma once

#include <fstream>  // Для работы с файлами
#include <iostream> // Для вывода в консоль
#include <chrono>   // Для работы со временем
#include <iomanip>  // Для форматирования вывода
#include <ctime>    // Для преобразования времени в строку

void logError( const std::string& message );
std::string getCurrentTime();