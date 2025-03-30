#pragma once
#include <string>

// Constants
const int WINDOW_WIDTH = 650;
const int WINDOW_HEIGHT = 700;
const float GRAVITY = 0.6f;
const float JUMP_VELOCITY = -12.0f;
const float PLAYER_SPEED = 5.0f;
const int PLATFORM_WIDTH = 60;
const int PLATFORM_HEIGHT = 12;
const int NUM_PLATFORMS = 10;
const float MOVING_PLATFORM_SPEED = 2.0f;
const int SLASH_WIDTH = 60;
const int SLASH_HEIGHT = 100;
const int SLASH_UP_WIDTH = 80;
const int SLASH_UP_HEIGHT = 50;
const int SLASH_DURATION = 200;
const int SLASH_DELAY = 500;
const int SLASH_BOOST_DELAY = 250;
const float SLASH_SPEED = 5.0f;
const int SLASH_BOOST_DURATION = 10000;
const size_t MAX_ENEMIES = 8;
const int ENEMY_SIZE = 30;
const float ENEMY_HORIZONTAL_SPEED = 2.0f;
const float ENEMY_FLY_ANIMATION_SPEED = 4.0f;
const float CHASING_ENEMY_SPEED = 3.0f;
const float SHOOTING_MONSTER_SHOOT_DELAY = 2000.0f;
const float MONSTER_BULLET_SPEED = 7.0f;
const int MONSTER_BULLET_SIZE = 5;
const int POWERUP_SIZE = 20;
const float POWERUP_SPAWN_CHANCE = 0.02f;
const int SCORE_PER_SCROLL_UNIT = 2;
const int SCORE_PER_ENEMY = 500;
const std::string BACKGROUND_PATH = "assets/background.png";
const std::string MUSIC_PATH = "assets/background_music.mp3";
const std::string FONT_PATH = "assets/font.ttf";
const std::string ATLAS_PATH = "assets/atlas.png";

// Sprite coordinates
struct SpriteRect {
    int x, y, w, h;
    SDL_Rect toSDLRect() const { return { x, y, w, h }; }
};

const SpriteRect SPRITE_PLAYER_NEUTRAL = { 61, 43, 19, 29 };
const SpriteRect SPRITE_PLAYER_RIGHT = { 118, 13, 20, 27 };
const SpriteRect SPRITE_PLAYER_LEFT = { 63, 16, 20, 27 };
const SpriteRect SPRITE_MONSTER_BULLET = { 17, 47, 5, 5 };
const SpriteRect SPRITE_ENEMY_FLY1 = { 32, 16, 16, 11 };
const SpriteRect SPRITE_ENEMY_FLY2 = { 48, 18, 16, 10 };
const SpriteRect SPRITE_ENEMY_FLY3 = { 32, 33, 16, 11 };
const SpriteRect SPRITE_ENEMY_FLY4 = { 48, 18, 16, 10 };
const SpriteRect SPRITE_SHOOTING_MONSTER1 = { 193, 1, 16, 14 };
const SpriteRect SPRITE_SHOOTING_MONSTER2 = { 209, 1, 16, 14 };
const SpriteRect SPRITE_SHOOTING_MONSTER3 = { 225, 1, 16, 14 };
const SpriteRect SPRITE_SHOOTING_MONSTER4 = { 1, 62, 16, 16 };
const SpriteRect SPRITE_CHASING_ENEMY1 = { 1, 16, 16, 11 };
const SpriteRect SPRITE_CHASING_ENEMY2 = { 18, 16, 14, 10 };
const SpriteRect SPRITE_CHASING_ENEMY3 = { 1, 32, 16, 11 };
const SpriteRect SPRITE_CHASING_ENEMY4 = { 18, 16, 14, 10 };
const SpriteRect SPRITE_SLASH_RIGHT = { 36, 43, 25, 30 };
const SpriteRect SPRITE_SLASH_LEFT = { 271, 1, 25, 30 };
const SpriteRect SPRITE_SLASH_UP = { 242, 1, 28, 24 };
const SpriteRect SPRITE_SHIELD = { 1, 46, 16, 16 };
const SpriteRect SPRITE_SHIELD_EQUIPPED = { 88, 14, 27, 30 };
const SpriteRect SPRITE_SLASH_BOOST = { 2, 81, 15, 14 };
const SpriteRect SPRITE_PLATFORM_NORMAL = { 145, 1, 48, 14 };
const SpriteRect SPRITE_PLATFORM_BREAKING = { 1, 1, 87, 14 };
const SpriteRect SPRITE_PLATFORM_MOVING = { 85, 1, 60, 12 };