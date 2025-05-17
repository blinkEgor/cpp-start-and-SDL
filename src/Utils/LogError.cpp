#include "LogError.h"

// Функция для получения текущего времени в формате "гггг-мм-дд чч:мм:сс"
// Получаем текущее время
// Преобразуем в time_t (время в секундах с эпохи Unix)
// Преобразуем в структуру tm (для форматирования)
// Используем stringstream для форматирования
// Формат: "гггг-мм-дд чч:мм:сс"
std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t( now );
    std::tm now_tm = *std::localtime( &now_time_t );
    std::stringstream ss;
    ss << std::put_time( &now_tm, "%Y-%m-%d %H:%M:%S" );
    return ss.str();
}

// Функция для логирования
// Получаем текущее время
// Определяем префикс в зависимости от уровня логирования
// Открываем файл для записи (добавляем в конец файла)
// Записываем сообщение в файл
// Если файл не удалось открыть, выводим ошибку в консоль
// Выводим сообщение в консоль
void logError( const std::string& message, LogLevel level ) {
    std::string time_str = getCurrentTime();
    std::string level_str;
    switch ( level ) {
        case LogLevel::INFO: level_str = "[INFO] "; break;
        case LogLevel::ERROR: level_str = "[ERROR] "; break;
        case LogLevel::WARNING: level_str = "[WARNING] "; break;
        case LogLevel::DEBUG: level_str = "[DEBUG] "; break;
        default: level_str = "[UNKNOWN] "; break;
    }
    std::ofstream log_file( "error_log.txt", std::ios::app );
    if( log_file.is_open() ) {
        log_file << "[" << time_str << "] " << level_str << message << std::endl;
        log_file.close();
    } else {
        std::cerr << "[" << time_str << "] " << "[ERROR] Failed to open log file!" << std::endl;
    }
    std::cerr << "[" << time_str << "] " << level_str << message << std::endl;
}