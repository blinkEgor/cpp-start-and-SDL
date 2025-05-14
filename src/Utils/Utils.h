#pragma once

#include <iostream>
#include "LogError.h"

// Перегрузка оператора + для сложения пар значений
inline std::pair< int, int > operator+( const std::pair< int, int >& a, const std::pair< int, int >& b ) {
    return { a.first + b.first, a.second + b.second };
}

// Перегрузка оператора % для проверки остатка от деления для пар
inline std::pair< int, int > operator%( const std::pair< int, int >& a, const std::pair< int, int >& b ) {
    return { a.first % b.first, a.second % b.second };
}

// Функция проверки двух пар значений на противополжные значения
inline bool is_opposite_pair( const std::pair< int, int >& a, const std::pair< int, int >& b ) {
    return a.first == -b.first && a.second == -b.second;
}

// Функция проверки двух пар чисел ровняются ли они друг другу
inline bool is_equal_pair( const std::pair< int, int >& a, const std::pair< int, int >& b ) {
    return a.first == b.first && a.second == b.second;
}

// Функция получения пары рандомных чисел
inline std::pair< int, int > get_rund_pair( const std::pair< int, int >& min, const std::pair< int, int >& max ) {
    // Проверка для первого компонента
    if ( min.first > max.first ) {
        logError( "The minimum for 'first' is higher than the maximum!", LogLevel::WARNING );
        return { 0, 0 };
    }
    
    // Проверка для второго компонента
    if ( min.second > max.second ) {
        logError( "The minimum for 'second' is higher than the maximum!", LogLevel::WARNING );
        return { 0, 0 };
    }

    return { 
        min.first + rand() % ( max.first - min.first + 1 ), 
        min.second + rand() % ( max.second - min.second + 1 ) 
    };
}