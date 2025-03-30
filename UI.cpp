#include "UI.h"
#include "Constants.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>

SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(path);
    if (!surface) { SDL_Log("Failed to load: %s, %s", path, IMG_GetError()); return nullptr; }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

SDL_Texture* createTextTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, const SDL_Color& color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) return nullptr;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void updateUITextures(SDL_Renderer* renderer, UI& ui, Player& player) {
    static const SDL_Color white = { 255, 255, 255, 255 };
    static const SDL_Color yellow = { 255, 255, 0, 255 };

    if (ui.scoreTexture) SDL_DestroyTexture(ui.scoreTexture);
    std::string scoreText = "Score: " + std::to_string(ui.currentScore) + "  Kills: " + std::to_string(ui.totalEnemiesKilled);
    ui.scoreTexture = createTextTexture(renderer, ui.font, scoreText, white);
    SDL_QueryTexture(ui.scoreTexture, nullptr, nullptr, &ui.scoreRect.w, &ui.scoreRect.h);
    ui.scoreRect.x = 10; ui.scoreRect.y = 10;

    if (ui.highScoreTexture) SDL_DestroyTexture(ui.highScoreTexture);
    std::string highScoreText = "High Score: " + std::to_string(ui.highScore);
    ui.highScoreTexture = createTextTexture(renderer, ui.font, highScoreText, white);
    SDL_QueryTexture(ui.highScoreTexture, nullptr, nullptr, &ui.highScoreRect.w, &ui.highScoreRect.h);
    ui.highScoreRect.x = 10; ui.highScoreRect.y = 40;

    if (ui.titleTexture) SDL_DestroyTexture(ui.titleTexture);
    ui.titleTexture = createTextTexture(renderer, ui.titleFont, "Slash Hopper", yellow);
    SDL_QueryTexture(ui.titleTexture, nullptr, nullptr, &ui.titleRect.w, &ui.titleRect.h);
    ui.titleRect.x = (WINDOW_WIDTH - ui.titleRect.w) / 2;
    ui.titleRect.y = WINDOW_HEIGHT / 4;

    if (ui.playTexture) SDL_DestroyTexture(ui.playTexture);
    ui.playTexture = createTextTexture(renderer, ui.font, "Press SPACE to Play", white);
    SDL_QueryTexture(ui.playTexture, nullptr, nullptr, &ui.playRect.w, &ui.playRect.h);
    ui.playRect.x = (WINDOW_WIDTH - ui.playRect.w) / 2;
    ui.playRect.y = WINDOW_HEIGHT / 2;

    if (ui.exitTexture) SDL_DestroyTexture(ui.exitTexture);
    ui.exitTexture = createTextTexture(renderer, ui.font, "Press ESC to Exit", white);
    SDL_QueryTexture(ui.exitTexture, nullptr, nullptr, &ui.exitRect.w, &ui.exitRect.h);
    ui.exitRect.x = (WINDOW_WIDTH - ui.exitRect.w) / 2;
    ui.exitRect.y = WINDOW_HEIGHT / 2 + 40;

    if (ui.instructionsTexture) SDL_DestroyTexture(ui.instructionsTexture);
    ui.instructionsTexture = createTextTexture(renderer, ui.font, "Arrows:Move  Space:Jump  Q/E/W:Slash", white);
    SDL_QueryTexture(ui.instructionsTexture, nullptr, nullptr, &ui.instructionsRect.w, &ui.instructionsRect.h);
    ui.instructionsRect.x = (WINDOW_WIDTH - ui.instructionsRect.w) / 2;
    ui.instructionsRect.y = WINDOW_HEIGHT - 100;

    if (ui.gameOverTexture) SDL_DestroyTexture(ui.gameOverTexture);
    ui.gameOverTexture = createTextTexture(renderer, ui.titleFont, "You Died!", yellow);
    SDL_QueryTexture(ui.gameOverTexture, nullptr, nullptr, &ui.gameOverRect.w, &ui.gameOverRect.h);
    ui.gameOverRect.x = (WINDOW_WIDTH - ui.gameOverRect.w) / 2;
    ui.gameOverRect.y = WINDOW_HEIGHT / 4;

    if (ui.playAgainTexture) SDL_DestroyTexture(ui.playAgainTexture);
    ui.playAgainTexture = createTextTexture(renderer, ui.font, "R to Replay || ESC to Exit", white);
    SDL_QueryTexture(ui.playAgainTexture, nullptr, nullptr, &ui.playAgainRect.w, &ui.playAgainRect.h);
    ui.playAgainRect.x = (WINDOW_WIDTH - ui.playAgainRect.w) / 2;
    ui.playAgainRect.y = WINDOW_HEIGHT / 2;

    if (player.slashBoostTimerTexture) SDL_DestroyTexture(player.slashBoostTimerTexture);
    if (player.slashBoostActive) {
        Uint32 remainingTime = static_cast<Uint32>((SLASH_BOOST_DURATION - (SDL_GetTicks() - player.slashBoostStartTime)) / 1000);
        std::string timerText = "Slash Boost: " + std::to_string(remainingTime + 1) + "s";
        player.slashBoostTimerTexture = createTextTexture(renderer, ui.font, timerText, yellow);
        SDL_QueryTexture(player.slashBoostTimerTexture, nullptr, nullptr, &player.slashBoostTimerRect.w, &player.slashBoostTimerRect.h);
        player.slashBoostTimerRect.x = 10;
        player.slashBoostTimerRect.y = 70;
    }
    else {
        player.slashBoostTimerTexture = nullptr;
    }
}

// Hàm khởi tạo SDL
bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer) {
    // Khởi tạo video và audio
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ||
        IMG_Init(IMG_INIT_PNG) == 0 ||                        // Khởi tạo tải ảnh PNG
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0 || // Khởi tạo âm thanh
        TTF_Init() == -1) return false;                       // Khởi tạo font

    // Tạo cửa sổ game
    window = SDL_CreateWindow("Slash Hopper", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (!window) return false;

    // Tạo renderer với tăng tốc phần cứng
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    return renderer != nullptr; // Trả về true nếu thành công
}