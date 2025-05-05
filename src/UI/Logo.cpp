#include "Logo.h"

Logo::Logo( 
    SDL_Rect logo_rect,
    SDL_Color text_color,
    std::string text
) : 
    m_logo_rect( logo_rect ), 
    m_text_color( text_color ), 
    m_text( text ),

    m_text_texture ( nullptr )
{}

Logo::~Logo() {
    if ( m_text_texture ) {
        SDL_DestroyTexture( m_text_texture );
        m_text_texture = nullptr;
        logError( "Text texture for Logo successfully destroyed", LogLevel::INFO );
    }
}

// Метод для установки шрифта и генерации текстуры
// - Проверяет есть ли уже текстура и удаляет, если есть 
// - Создаёт поверхность и проверяет ошибки 
// - Создаёт текстуру 
// - Выравнивает текст по центру, относительно заданной позиции при объявлении 
// - Очищает поверхность
void Logo::update_text_texture( SDL_Renderer* renderer, TTF_Font* font ) {
    if ( m_text_texture ) SDL_DestroyTexture( m_text_texture );

    SDL_Surface* surface = TTF_RenderText_Solid( font, m_text.c_str(), m_text_color );
    if ( !surface ) {
        logError( "Surface can't create TTF_RenderText_Solid: " + std::string( TTF_GetError() ), LogLevel::ERROR );
        return;
    }

    m_text_texture = SDL_CreateTextureFromSurface( renderer, surface );

    m_logo_rect = {
        m_logo_rect.x + ( m_logo_rect.w - surface->w ) / 2,
        m_logo_rect.y + ( m_logo_rect.h - surface->h ) / 2,
        surface->w,
        surface->h
    };

    SDL_FreeSurface( surface );
}

// Рисуем логотип если есть текстура
void Logo::draw( SDL_Renderer* renderer ) {
    if ( m_text_texture ) {
        SDL_RenderCopy( renderer, m_text_texture, nullptr, &m_logo_rect );
    }
}