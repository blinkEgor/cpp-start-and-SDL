#pragma once

#include <iostream>

// Перегрузка оператора + для сложения пар значений
inline std::pair< int, int > operator+( const std::pair< int, int >& a, const std::pair< int, int >& b ) {
    return { a.first + b.first, a.second + b.second };
}

// Перегрузка оператора % для проверки остатка от деления для пар
inline std::pair< int, int > operator%( const std::pair< int, int >& a, const std::pair< int, int >& b ) {
    return { a.first % b.first, a.second % b.second };
}

// Функция проверки двух пар значений на противополжные значения
inline bool is_opposite_pair( const std::pair<int, int>& a, const std::pair<int, int>& b ) {
    return a.first == -b.first && a.second == -b.second;
}

// Функция получения пары рандомных чисел
inline std::pair< int, int > get_rund_pair( const std::pair<int, int>& min, const std::pair<int, int>& max ) {
    return { 
        min.first + rand() % ( max.first - min.first + 1 ), 
        min.second + rand() % ( max.second - min.second + 1 ) 
    };
}