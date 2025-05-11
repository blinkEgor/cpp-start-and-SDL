#include "Text.h"

Text::Text( 
    SDL_Rect text_rect,
    SDL_Color text_color,
    std::string text
) : 
    m_text_rect( text_rect ), 
    m_text_color( text_color ), 
    m_text( text ),

    m_text_texture ( nullptr )
{}

Text::~Text() {
    if ( m_text_texture ) {
        SDL_DestroyTexture( m_text_texture );
        m_text_texture = nullptr;
        logError( "Text texture for Text successfully destroyed", LogLevel::INFO );
    }
}

// Обновляет текст и принимает фактический счёт
void Text::update_text_score( int score ) {
    m_text+= std::to_string( score );
}

// Метод для установки шрифта и генерации текстуры
// - Проверяет есть ли уже текстура и удаляет, если есть 
// - Создаёт поверхность и проверяет ошибки 
// - Создаёт текстуру 
// - Выравнивает текст по центру, относительно заданной позиции при объявлении 
// - Очищает поверхность
void Text::update_text_texture( SDL_Renderer* renderer, TTF_Font* font ) {
    if ( m_text_texture ) SDL_DestroyTexture( m_text_texture );

    SDL_Surface* surface = TTF_RenderText_Solid( font, m_text.c_str(), m_text_color );
    if ( !surface ) {
        logError( "Surface can't create TTF_RenderText_Solid: " + std::string( TTF_GetError() ), LogLevel::ERROR );
        return;
    }

    m_text_texture = SDL_CreateTextureFromSurface( renderer, surface );

    m_text_rect = {
        m_text_rect.x + ( m_text_rect.w - surface->w ) / 2,
        m_text_rect.y + ( m_text_rect.h - surface->h ) / 2,
        surface->w,
        surface->h
    };

    SDL_FreeSurface( surface );
}

// Рисуем текстуру текста если есть текстура
void Text::draw( SDL_Renderer* renderer ) {
    if ( m_text_texture ) {
        SDL_RenderCopy( renderer, m_text_texture, nullptr, &m_text_rect );
    }
}