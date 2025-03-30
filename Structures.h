#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Constants.h"

// Game States and Structures
enum GameState { START_MENU, PLAYING, GAME_OVER_MENU };

struct Player {
    float x, y, vy;
    int w, h;
    Uint32 lastSlashTime;
    SpriteRect sprite;
    int slashDirection;
    Uint32 slashStartTime;
    bool shieldActive;
    bool slashBoostActive;
    Uint32 slashBoostStartTime;
    int jumpCount;
    int movementState;
    SDL_Texture* slashBoostTimerTexture;
    SDL_Rect slashBoostTimerRect;
};

struct Slash { float x, y; int w, h; bool active; int direction; Uint32 startTime; float vx, vy; SpriteRect sprite; float alpha; };
struct MonsterBullet { float x, y, vx, vy; bool active; bool deflected; SpriteRect sprite; };
struct Enemy {
    float x, y; int w, h; bool active; float centerX, centerY; float speed; float horizontalVelocity;
    SpriteRect spriteFly[4]; SpriteRect spriteShooting[4]; SpriteRect spriteChasing[4];
    bool isShootingMonster; bool isChasingEnemy; Uint32 lastShotTime;
};
enum PowerUpType { SHIELD, SLASH_BOOST, NONE };
struct PowerUp { float x, y; int w, h; bool active; PowerUpType type; SpriteRect sprite; };
enum PlatformType { NORMAL, BREAKING, MOVING };
struct Platform { float x, y; int w, h; PlatformType type; bool active; float direction; SpriteRect sprite; PowerUp powerUp; };
struct Background { SDL_Texture* texture; int width, height; float y; };
struct UI {
    TTF_Font* font;
    TTF_Font* titleFont; 
    SDL_Texture* scoreTexture; SDL_Rect scoreRect;
    SDL_Texture* highScoreTexture; SDL_Rect highScoreRect;
    SDL_Texture* titleTexture; SDL_Rect titleRect;
    SDL_Texture* playTexture; SDL_Rect playRect;
    SDL_Texture* exitTexture; SDL_Rect exitRect;
    SDL_Texture* gameOverTexture; SDL_Rect gameOverRect;
    SDL_Texture* playAgainTexture; SDL_Rect playAgainRect;
    SDL_Texture* instructionsTexture; SDL_Rect instructionsRect;
    int currentScore;
    int highScore;
    int totalEnemiesKilled;
    float totalScrollDistance;
    Uint32 startTime;
    float enemySpawnChance;
};