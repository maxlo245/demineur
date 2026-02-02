// demineur.cpp : Jeu de démineur avancé

#include "framework.h"
#include "demineur.h"
#include <vector>
#include <random>
#include <chrono>
#include <cmath>

#define MAX_LOADSTRING 100

// Constantes du jeu
const int BASE_CELL_SIZE = 40;  // Taille par défaut
const int HEADER_HEIGHT = 100;
const int MARGIN = 15;
const int FOOTER_HEIGHT = 100; // Zone pour le HUD en bas
const int MAX_PARTICLES = 100;
const int MAX_HINTS = 3;

// Résolution fixe 1920x1080
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

// Variable dynamique pour la taille des cellules
int CELL_SIZE = BASE_CELL_SIZE;

// Fonction pour calculer la taille optimale des cellules
int CalculateOptimalCellSize(int rows, int cols) {
    int availableWidth = WINDOW_WIDTH - 2 * MARGIN - 50;  // Marges + espace
    int availableHeight = WINDOW_HEIGHT - HEADER_HEIGHT - FOOTER_HEIGHT - 4 * MARGIN - 50;
    
    int maxCellSizeByWidth = availableWidth / cols;
    int maxCellSizeByHeight = availableHeight / rows;
    
    int optimalSize = min(maxCellSizeByWidth, maxCellSizeByHeight);
    optimalSize = min(optimalSize, BASE_CELL_SIZE); // Ne jamais dépasser 40px
    optimalSize = max(optimalSize, 20); // Minimum 20px pour rester lisible
    
    return optimalSize;
}

// Niveaux de difficulté
enum Difficulty {
    FACILE = 0,
    MOYEN = 1,
    DIFFICILE = 2,
    EXPERT = 3,
    PERSONNALISE = 4
};

struct DifficultySettings {
    int rows;
    int cols;
    int mines;
};

const DifficultySettings DIFFICULTIES[] = {
    {9, 9, 10},      // Facile
    {16, 16, 40},    // Moyen
    {16, 30, 99},    // Difficile
    {24, 30, 180},   // Expert
    {0, 0, 0}        // Personnalisé
};

// Modes de jeu
enum GameMode {
    CLASSIC = 0,
    NO_FLAGS = 1,
    SPEED_RUN = 2,
    ZEN_MODE = 3
};

// Thèmes visuels
enum Theme {
    THEME_DARK = 0,
    THEME_LIGHT = 1,
    THEME_OCEAN = 2,
    THEME_FOREST = 3,
    THEME_SUNSET = 4
};

// État d'une cellule
enum CellState {
    HIDDEN,
    REVEALED,
    FLAGGED,
    QUESTION
};

struct Cell {
    bool hasMine;
    int adjacentMines;
    CellState state;
    bool isHinted;
    float revealAnimation;
    float shakeAnimation;
};

// Particule pour effets visuels
struct Particle {
    float x, y;
    float vx, vy;
    COLORREF color;
    int life;
    int maxLife;
    bool active;
};

// Statistiques du joueur
struct GameStats {
    int gamesPlayed;
    int gamesWon;
    int gamesLost;
    int totalTime;
    int bestTime[5];  // Par difficulté
    int currentStreak;
    int longestStreak;
    int flagsUsed;
    int cellsRevealed;
};

// Configuration du jeu
struct GameConfig {
    bool soundEnabled;
    bool animationsEnabled;
    bool particlesEnabled;
    bool autoFlag;
    bool questionMarks;
    Theme currentTheme;
    GameMode gameMode;
    float zoomLevel;
};

// Variables globales
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

// Cache d'objets GDI pour la performance (évite de créer/détruire en boucle)
static HBRUSH g_brushGray = NULL;
static HBRUSH g_brushLightGray = NULL;
static HBRUSH g_brushDarkGray = NULL;
static HBRUSH g_brushBlack = NULL;
static HBRUSH g_brushRed = NULL;
static HPEN g_penWhite = NULL;
static HPEN g_penDarkGray = NULL;
static HPEN g_penBlack = NULL;
static HFONT g_fontDigital = NULL;
static HFONT g_fontCell = NULL;

// État du jeu
enum GameState {
    STATE_MENU,
    STATE_PLAYING,
    STATE_PAUSED
};

// Variables du jeu
std::vector<std::vector<Cell>> grid;
int currentDifficulty = FACILE;
int rows, cols, totalMines;
int flagsPlaced = 0;
bool gameStarted = false;
bool gameOver = false;
bool gameWon = false;
bool firstClick = true;
int revealedCells = 0;
std::chrono::steady_clock::time_point startTime;
int elapsedSeconds = 0;
GameState gameState = STATE_MENU;

// Variables avancées
std::vector<Particle> particles;
GameStats playerStats = {0};
GameConfig gameConfig = {true, true, true, false, true, THEME_DARK, CLASSIC, 1.0f};
int hintsRemaining = MAX_HINTS;
std::vector<std::pair<int, int>> moveHistory;
bool showingHint = false;
int hintRow = -1, hintCol = -1;
int comboMultiplier = 1;
int score = 0;
bool isPaused = false;
float cellHoverX = -1, cellHoverY = -1;
int lastRevealedCount = 0;

// Variables pour le menu animé
float menuAnimationTime = 0.0f;
std::vector<Particle> menuParticles;
const int MAX_MENU_PARTICLES = 50;

// ??? Variables pour le fond de jeu animé ???
float gameBackgroundTime = 0.0f;
std::vector<Particle> gameBackgroundParticles;
const int MAX_BACKGROUND_PARTICLES = 30;

// Déclarations de fonctions
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void InitializeGame(int difficulty);
void PlaceMines(int excludeRow, int excludeCol);
void CalculateAdjacentMines();
void RevealCell(int row, int col);
void ToggleFlag(int row, int col);
void CheckWinCondition();
void RevealAllMines();
void DrawGame(HDC hdc, HWND hWnd);
void DrawCell(HDC hdc, int row, int col, int x, int y);
void DrawHeader(HDC hdc, int width);
COLORREF GetNumberColor(int num);
void DrawMine(HDC hdc, int x, int y, int size);
void DrawFlag(HDC hdc, int x, int y, int size);
void DrawQuestion(HDC hdc, int x, int y, int size);
void DrawGradientRect(HDC hdc, RECT rect, COLORREF color1, COLORREF color2, bool vertical);
void InitGDICache();
void CleanupGDICache();

// Stubs pour fonctions avancées - IMPLÉMENTATIONS RÉELLES
void InitParticles() { 
    particles.clear(); 
    particles.resize(MAX_PARTICLES); 
    for (auto& p : particles) p.active = false;
    
    // Initialiser les particules du menu
    menuParticles.clear();
    menuParticles.resize(MAX_MENU_PARTICLES);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distX(0.0, (double)WINDOW_WIDTH);
    std::uniform_real_distribution<> distY(0.0, (double)WINDOW_HEIGHT);
    std::uniform_real_distribution<> distSpeed(-0.5, 0.5);
    
    COLORREF menuColors[] = {
        RGB(255, 255, 255), RGB(200, 220, 255), RGB(255, 220, 200),
        RGB(220, 255, 220), RGB(255, 240, 200)
    };
    
    for (auto& p : menuParticles) {
        p.x = (float)distX(gen);
        p.y = (float)distY(gen);
        p.vx = (float)distSpeed(gen);
        p.vy = (float)distSpeed(gen);
        p.color = menuColors[rand() % 5];
        p.life = 255;
        p.maxLife = 255;
        p.active = true;
    }
    
    // ??? Initialiser les particules du fond de jeu ???
    gameBackgroundParticles.clear();
    gameBackgroundParticles.resize(MAX_BACKGROUND_PARTICLES);
    
    COLORREF bgColors[] = {
        RGB(100, 150, 255), RGB(150, 100, 255), RGB(255, 150, 200),
        RGB(150, 255, 200), RGB(255, 200, 100)
    };
    
    for (auto& p : gameBackgroundParticles) {
        p.x = (float)distX(gen);
        p.y = (float)distY(gen);
        p.vx = (float)distSpeed(gen) * 0.5f;
        p.vy = (float)distSpeed(gen) * 0.5f;
        p.color = bgColors[rand() % 5];
        p.life = 255;
        p.maxLife = 255;
        p.active = true;
    }
}

void UpdateParticles() {
    if (!gameConfig.particlesEnabled) return;
    
    for (auto& p : particles) {
        if (p.active) {
            p.x += p.vx;
            p.y += p.vy;
            p.vy += 0.5f; // Gravité
            p.life--;
            
            if (p.life <= 0) {
                p.active = false;
            }
        }
    }
}

void UpdateMenuParticles() {
    menuAnimationTime += 0.016f; // ~60 FPS
    
    for (auto& p : menuParticles) {
        if (p.active) {
            // Mouvement sinusoïdal pour effet de flottement
            p.x += p.vx + sin(menuAnimationTime * 2.0f + p.y * 0.01f) * 0.2f;
            p.y += p.vy + cos(menuAnimationTime * 1.5f + p.x * 0.01f) * 0.2f;
            
            // Rebondir sur les bords
            if (p.x < 0 || p.x > WINDOW_WIDTH) p.vx *= -1;
            if (p.y < 0 || p.y > WINDOW_HEIGHT) p.vy *= -1;
            
            // Garder dans les limites
            if (p.x < 0) p.x = 0;
            if (p.x > WINDOW_WIDTH) p.x = (float)WINDOW_WIDTH;
            if (p.y < 0) p.y = 0;
            if (p.y > WINDOW_HEIGHT) p.y = (float)WINDOW_HEIGHT;
        }
    }
}

// ??? Fonction pour mettre à jour les particules du fond de jeu ???
void UpdateGameBackgroundParticles() {
    gameBackgroundTime += 0.016f; // ~60 FPS
    
    for (auto& p : gameBackgroundParticles) {
        if (p.active) {
            // Mouvement lent et fluide
            p.x += p.vx + sin(gameBackgroundTime * 1.0f + p.y * 0.005f) * 0.3f;
            p.y += p.vy + cos(gameBackgroundTime * 0.8f + p.x * 0.005f) * 0.3f;
            
            // Rebondir sur les bords
            if (p.x < 0 || p.x > WINDOW_WIDTH) p.vx *= -1;
            if (p.y < 0 || p.y > WINDOW_HEIGHT) p.vy *= -1;
            
            // Garder dans les limites
            if (p.x < 0) p.x = 0;
            if (p.x > WINDOW_WIDTH) p.x = (float)WINDOW_WIDTH;
            if (p.y < 0) p.y = 0;
            if (p.y > WINDOW_HEIGHT) p.y = (float)WINDOW_HEIGHT;
        }
    }
}

void CreateExplosion(int x, int y, COLORREF color) {
    if (!gameConfig.particlesEnabled) return;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-5.0, 5.0);
    
    for (int i = 0; i < 20; i++) {
        for (auto& p : particles) {
            if (!p.active) {
                p.x = (float)x;
                p.y = (float)y;
                p.vx = (float)dist(gen);
                p.vy = (float)dist(gen) - 3.0f;
                p.color = color;
                p.life = 30 + rand() % 20;
                p.maxLife = p.life;
                p.active = true;
                break;
            }
        }
    }
}

void CreateConfetti(int x, int y) {
    if (!gameConfig.particlesEnabled) return;
    
    COLORREF colors[] = {
        RGB(255, 107, 107), RGB(78, 205, 196), 
        RGB(255, 195, 113), RGB(199, 125, 255),
        RGB(255, 218, 121)
    };
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-8.0, 8.0);
    
    for (int i = 0; i < 15; i++) {
        for (auto& p : particles) {
            if (!p.active) {
                p.x = (float)x;
                p.y = (float)y;
                p.vx = (float)dist(gen);
                p.vy = (float)dist(gen) - 10.0f;
                p.color = colors[rand() % 5];
                p.life = 60 + rand() % 40;
                p.maxLife = p.life;
                p.active = true;
                break;
            }
        }
    }
}

void DrawParticles(HDC hdc) {
    if (!gameConfig.particlesEnabled) return;
    
    for (const auto& p : particles) {
        if (p.active) {
            int size = 4;
            
            HBRUSH brush = CreateSolidBrush(p.color);
            SelectObject(hdc, brush);
            SelectObject(hdc, GetStockObject(NULL_PEN));
            
            Ellipse(hdc, (int)p.x - size/2, (int)p.y - size/2, 
                    (int)p.x + size/2, (int)p.y + size/2);
            
            DeleteObject(brush);
        }
    }
}

void DrawScorePanel(HDC hdc, int x, int y) {
    RECT panel = {x, y, x + 200, y + 70};
    
    // Fond du panneau avec dégradé
    DrawGradientRect(hdc, panel, RGB(40, 40, 40), RGB(60, 60, 60), true);
    
    // Bordure dorée épaisse
    HPEN pen = CreatePen(PS_SOLID, 3, RGB(255, 215, 0));
    SelectObject(hdc, pen);
    SelectObject(hdc, GetStockObject(NULL_BRUSH));
    RoundRect(hdc, panel.left, panel.top, panel.right, panel.bottom, 12, 12);
    DeleteObject(pen);
    
    // Libellé "SCORE"
    SetBkMode(hdc, TRANSPARENT);
    HFONT labelFont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
    SelectObject(hdc, labelFont);
    
    RECT labelRect = {panel.left, panel.top + 5, panel.right, panel.top + 25};
    SetTextColor(hdc, RGB(200, 200, 200));
    DrawText(hdc, L"SCORE", -1, &labelRect, DT_CENTER | DT_SINGLELINE);
    DeleteObject(labelFont);
    
    // Valeur du score
    HFONT scoreFont = CreateFont(32, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
    SelectObject(hdc, scoreFont);
    
    WCHAR scoreText[50];
    swprintf_s(scoreText, L"%d", score);
    RECT scoreRect = {panel.left, panel.top + 25, panel.right, panel.bottom - 5};
    SetTextColor(hdc, RGB(255, 215, 0));
    DrawText(hdc, scoreText, -1, &scoreRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    
    DeleteObject(scoreFont);
}

void DrawComboIndicator(HDC hdc, int x, int y) {
    if (comboMultiplier <= 1) return;
    
    RECT rect = {x, y, x + 180, y + 60};
    
    // Effet de lueur animé avec plusieurs couches
    for (int i = 0; i < 5; i++) {
        HBRUSH brush = CreateSolidBrush(RGB(255 - i*30, 140 - i*20, 0));
        RECT expandRect = {rect.left - i*3, rect.top - i*3, 
                          rect.right + i*3, rect.bottom + i*3};
        FrameRect(hdc, &expandRect, brush);
        DeleteObject(brush);
    }
    
    // Fond avec dégradé orange
    DrawGradientRect(hdc, rect, RGB(255, 165, 0), RGB(255, 140, 0), true);
    
    SetBkMode(hdc, TRANSPARENT);
    HFONT font = CreateFont(36, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
    SelectObject(hdc, font);
    
    WCHAR comboText[50];
    swprintf_s(comboText, L"×%d COMBO!", comboMultiplier);
    
    // Ombre noire
    RECT shadowRect = {rect.left + 2, rect.top + 2, rect.right + 2, rect.bottom + 2};
    SetTextColor(hdc, RGB(0, 0, 0));
    DrawText(hdc, comboText, -1, &shadowRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    
    // Texte principal
    SetTextColor(hdc, RGB(255, 255, 255));
    DrawText(hdc, comboText, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    
    DeleteObject(font);
}

void DrawHintButton(HDC hdc, int x, int y) {
    RECT button = {x, y, x + 120, y + 60};
    
    // Couleur selon disponibilité avec dégradé
    COLORREF color1 = hintsRemaining > 0 ? RGB(76, 175, 80) : RGB(80, 80, 80);
    COLORREF color2 = hintsRemaining > 0 ? RGB(56, 142, 60) : RGB(60, 60, 60);
    
    DrawGradientRect(hdc, button, color1, color2, true);
    
    // Bordure blanche épaisse
    HPEN pen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
    SelectObject(hdc, pen);
    SelectObject(hdc, GetStockObject(NULL_BRUSH));
    RoundRect(hdc, button.left, button.top, button.right, button.bottom, 12, 12);
    DeleteObject(pen);
    
    // Icône et texte
    SetBkMode(hdc, TRANSPARENT);
    HFONT iconFont = CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
    SelectObject(hdc, iconFont);
    
    RECT iconRect = {button.left, button.top + 5, button.right, button.top + 30};
    SetTextColor(hdc, RGB(255, 255, 255));
    DrawText(hdc, L"?? AIDE", -1, &iconRect, DT_CENTER | DT_SINGLELINE);
    DeleteObject(iconFont);
    
    // Compteur
    HFONT countFont = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
    SelectObject(hdc, countFont);
    
    WCHAR hintText[20];
    swprintf_s(hintText, L"Reste: %d", hintsRemaining);
    RECT countRect = {button.left, button.top + 32, button.right, button.bottom - 5};
    DrawText(hdc, hintText, -1, &countRect, DT_CENTER | DT_SINGLELINE);
    
    DeleteObject(countFont);
}

void DrawProgressBar(HDC hdc, int x, int y, int width, float progress) {
    RECT bg = {x, y, x + width, y + 30};
    RECT fill = {x + 3, y + 3, x + (int)((width - 6) * progress), y + 27};
    
    // Fond noir
    HBRUSH bgBrush = CreateSolidBrush(RGB(30, 30, 30));
    FillRect(hdc, &bg, bgBrush);
    DeleteObject(bgBrush);
    
    // Remplissage avec dégradé vert brillant
    if (progress > 0) {
        DrawGradientRect(hdc, fill, RGB(76, 175, 80), RGB(139, 195, 74), false);
    }
    
    // Bordure blanche épaisse
    HPEN pen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
    SelectObject(hdc, pen);
    SelectObject(hdc, GetStockObject(NULL_BRUSH));
    RoundRect(hdc, bg.left, bg.top, bg.right, bg.bottom, 8, 8);
    DeleteObject(pen);
    
    // Pourcentage
    SetBkMode(hdc, TRANSPARENT);
    HFONT font = CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
    SelectObject(hdc, font);
    
    WCHAR progressText[20];
    swprintf_s(progressText, L"%d%%", (int)(progress * 100));
    SetTextColor(hdc, RGB(255, 255, 255));
    DrawText(hdc, progressText, -1, &bg, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    
    DeleteObject(font);
}

void ShowHint() {
    if (hintsRemaining <= 0 || gameOver) return;
    
    // Trouver une cellule sûre
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j].state == HIDDEN && !grid[i][j].hasMine) {
                grid[i][j].isHinted = true;
                hintsRemaining--;
                showingHint = true;
                hintRow = i;
                hintCol = j;
                return;
            }
        }
    }
}

void CalculateScore() { 
    if (!gameStarted) return;
    
    score = revealedCells * 10;
    
    // Bonus de temps (plus rapide = plus de points)
    if (elapsedSeconds > 0) {
        int timeBonus = max(0, 1000 - elapsedSeconds * 10);
        score += timeBonus;
    }
    
    // Multiplicateur de combo
    score *= comboMultiplier;
    
    // Bonus pour hints non utilisés
    score += hintsRemaining * 50;
}

void UpdateComboMultiplier() { 
    int revealed = revealedCells - lastRevealedCount;
    if (revealed > 5) {
        comboMultiplier = min(5, comboMultiplier + 1);
    } else if (revealed <= 1) {
        comboMultiplier = 1;
    }
    lastRevealedCount = revealedCells;
}

void UpdateStats(bool won) {
    playerStats.gamesPlayed++;
    
    if (won) {
        playerStats.gamesWon++;
        playerStats.currentStreak++;
        if (playerStats.currentStreak > playerStats.longestStreak) {
            playerStats.longestStreak = playerStats.currentStreak;
        }
    } else {
        playerStats.gamesLost++;
        playerStats.currentStreak = 0;
    }
    
    playerStats.totalTime += elapsedSeconds;
    playerStats.flagsUsed += flagsPlaced;
    playerStats.cellsRevealed += revealedCells;
}

void AnimateCellReveal(int row, int col) {}
void UpdateAnimations() {}
void ShakeCell(int row, int col) {}
void ApplyTheme(Theme theme) { gameConfig.currentTheme = theme; }
COLORREF GetThemeBackgroundColor() { return RGB(238, 238, 238); }
COLORREF GetThemeHeaderColor1() { return RGB(66, 66, 66); }
COLORREF GetThemeHeaderColor2() { return RGB(97, 97, 97); }
COLORREF GetThemeCellColor() { return RGB(220, 220, 220); }
COLORREF GetThemeAccentColor() { return RGB(255, 69, 58); }
void SaveStats() {}
void LoadStats() {}
void ResetStats() { playerStats = {0}; }
int GetCurrentScore() { return score; }
void AddBonusPoints(int points) { score += points; }
void RevealSafeCell() {}
void HighlightSafeCells() {}
void ClearHint() { 
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j].isHinted = false;
        }
    }
    showingHint = false; 
    hintRow = -1; 
    hintCol = -1; 
}
bool IsCellSafe(int row, int col) { return true; }
int CountAdjacentFlags(int row, int col) { return 0; }
void AutoRevealAdjacentCells(int row, int col) {}
void SetGameMode(GameMode mode) { gameConfig.gameMode = mode; }
void ApplyModeRules() {}
bool CanUseFlagsInMode() { return true; }
void CheckSpeedRunTime() {}
void ActivateZenMode() {}
void ChordClick(int row, int col) {}
void QuickRevealArea(int row, int col) {}
void SmartFlag(int row, int col) {}
void DrawPauseButton(HDC hdc, int x, int y) {}
void DrawTooltip(HDC hdc, int x, int y, const WCHAR* text) {}
void DrawGlowEffect(HDC hdc, int x, int y, int size, COLORREF color) {}
void DrawPulseEffect(HDC hdc, RECT rect) {}
void DrawRippleEffect(HDC hdc, int x, int y, int radius) {}
void DrawSparkle(HDC hdc, int x, int y) {}
void DrawShadow(HDC hdc, RECT rect, int depth) {}
void ToggleAnimation() { gameConfig.animationsEnabled = !gameConfig.animationsEnabled; }
void ToggleParticles() { gameConfig.particlesEnabled = !gameConfig.particlesEnabled; }
void ToggleSound() { gameConfig.soundEnabled = !gameConfig.soundEnabled; }
void SetZoomLevel(float zoom) { gameConfig.zoomLevel = zoom; }
void ToggleAutoFlag() { gameConfig.autoFlag = !gameConfig.autoFlag; }

// Initialisation du cache GDI (améliore considérablement les performances)
void InitGDICache() {
    if (!g_brushGray) {
        g_brushGray = CreateSolidBrush(RGB(192, 192, 192));
        g_brushLightGray = CreateSolidBrush(RGB(189, 189, 189));
        g_brushDarkGray = CreateSolidBrush(RGB(128, 128, 128));
        g_brushBlack = CreateSolidBrush(RGB(0, 0, 0));
        g_brushRed = CreateSolidBrush(RGB(255, 0, 0));
        
        g_penWhite = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
        g_penDarkGray = CreatePen(PS_SOLID, 2, RGB(128, 128, 128));
        g_penBlack = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
        
        g_fontDigital = CreateFont(32, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Consolas");
            
        g_fontCell = CreateFont(CELL_SIZE - 8, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
    }
}

void CleanupGDICache() {
    if (g_brushGray) DeleteObject(g_brushGray);
    if (g_brushLightGray) DeleteObject(g_brushLightGray);
    if (g_brushDarkGray) DeleteObject(g_brushDarkGray);
    if (g_brushBlack) DeleteObject(g_brushBlack);
    if (g_brushRed) DeleteObject(g_brushRed);
    if (g_penWhite) DeleteObject(g_penWhite);
    if (g_penDarkGray) DeleteObject(g_penDarkGray);
    if (g_penBlack) DeleteObject(g_penBlack);
    if (g_fontDigital) DeleteObject(g_fontDigital);
    if (g_fontCell) DeleteObject(g_fontCell);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEMINEUR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEMINEUR));
    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

void InitializeGame(int difficulty)
{
    currentDifficulty = difficulty;
    const DifficultySettings& settings = DIFFICULTIES[difficulty];
    
    rows = settings.rows;
    cols = settings.cols;
    totalMines = settings.mines;
    
    // ??? CALCULER LA TAILLE OPTIMALE DES CELLULES ???
    CELL_SIZE = CalculateOptimalCellSize(rows, cols);
    
    // Recréer la police pour les cellules avec la nouvelle taille
    if (g_fontCell) {
        DeleteObject(g_fontCell);
        g_fontCell = CreateFont(CELL_SIZE - 8, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
    }
    
    grid.clear();
    grid.resize(rows, std::vector<Cell>(cols));
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = {false, 0, HIDDEN, false, 1.0f, 0.0f};
        }
    }
    
    flagsPlaced = 0;
    gameStarted = false;
    gameOver = false;
    gameWon = false;
    firstClick = true;
    revealedCells = 0;
    elapsedSeconds = 0;
    hintsRemaining = MAX_HINTS;
    comboMultiplier = 1;
    score = 0;
    lastRevealedCount = 0;
    isPaused = false;
    
    InitParticles();
    ClearHint();
}

void PlaceMines(int excludeRow, int excludeCol)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distRow(0, rows - 1);
    std::uniform_int_distribution<> distCol(0, cols - 1);
    
    int minesPlaced = 0;
    while (minesPlaced < totalMines) {
        int r = distRow(gen);
        int c = distCol(gen);
        
        if (!grid[r][c].hasMine && 
            !(abs(r - excludeRow) <= 1 && abs(c - excludeCol) <= 1)) {
            grid[r][c].hasMine = true;
            minesPlaced++;
        }
    }
    
    CalculateAdjacentMines();
}

void CalculateAdjacentMines()
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!grid[i][j].hasMine) {
                int count = 0;
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        if (di == 0 && dj == 0) continue;
                        int ni = i + di;
                        int nj = j + dj;
                        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && grid[ni][nj].hasMine) {
                            count++;
                        }
                    }
                }
                grid[i][j].adjacentMines = count;
            }
        }
    }
}

void RevealCell(int row, int col)
{
    if (row < 0 || row >= rows || col < 0 || col >= cols) return;
    if (grid[row][col].state != HIDDEN) return;
    
    grid[row][col].state = REVEALED;
    revealedCells++;
    
    if (grid[row][col].hasMine) {
        gameOver = true;
        gameWon = false;
        RevealAllMines();
        return;
    }
    
    if (grid[row][col].adjacentMines == 0) {
        for (int di = -1; di <= 1; di++) {
            for (int dj = -1; dj <= 1; dj++) {
                if (di != 0 || dj != 0) {
                    RevealCell(row + di, col + dj);
                }
            }
        }
    }
}

void ToggleFlag(int row, int col)
{
    if (row < 0 || row >= rows || col < 0 || col >= cols) return;
    if (grid[row][col].state == REVEALED) return;
    
    if (grid[row][col].state == HIDDEN) {
        grid[row][col].state = FLAGGED;
        flagsPlaced++;
    }
    else if (grid[row][col].state == FLAGGED) {
        grid[row][col].state = QUESTION;
        flagsPlaced--;
    }
    else if (grid[row][col].state == QUESTION) {
        grid[row][col].state = HIDDEN;
    }
}

void CheckWinCondition()
{
    int totalRevealed = 0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j].state == REVEALED && !grid[i][j].hasMine) {
                totalRevealed++;
            }
        }
    }
    
    if (totalRevealed == rows * cols - totalMines) {
        gameWon = true;
        gameOver = true;
        UpdateStats(true);
        CalculateScore();
        
        // Célébration avec confettis!
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (rand() % 3 == 0) { // 1 confetti sur 3 pour ne pas surcharger
                    CreateConfetti(MARGIN + j * CELL_SIZE + CELL_SIZE/2,
                                 HEADER_HEIGHT + MARGIN + i * CELL_SIZE + CELL_SIZE/2);
                }
            }
        }
    }
}

void RevealAllMines()
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j].hasMine) {
                grid[i][j].state = REVEALED;
                
                // Explosion de particules
                CreateExplosion(MARGIN + j * CELL_SIZE + CELL_SIZE/2,
                              HEADER_HEIGHT + MARGIN + i * CELL_SIZE + CELL_SIZE/2,
                              RGB(255, 100, 100));
            }
        }
    }
    UpdateStats(false);
}

COLORREF GetNumberColor(int num)
{
    switch (num) {
        case 1: return RGB(25, 118, 210);    // Bleu moderne
        case 2: return RGB(56, 142, 60);     // Vert
        case 3: return RGB(211, 47, 47);     // Rouge
        case 4: return RGB(123, 31, 162);    // Violet
        case 5: return RGB(255, 111, 0);     // Orange
        case 6: return RGB(0, 172, 193);     // Cyan
        case 7: return RGB(66, 66, 66);      // Gris foncé
        case 8: return RGB(158, 158, 158);   // Gris
        default: return RGB(0, 0, 0);
    }
}

void DrawGradientRect(HDC hdc, RECT rect, COLORREF color1, COLORREF color2, bool vertical)
{
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    
    int steps = vertical ? height : width;
    if (steps <= 0) return;
    
    for (int i = 0; i < steps; i++) {
        int r = GetRValue(color1) + (GetRValue(color2) - GetRValue(color1)) * i / steps;
        int g = GetGValue(color1) + (GetGValue(color2) - GetGValue(color1)) * i / steps;
        int b = GetBValue(color1) + (GetBValue(color2) - GetBValue(color1)) * i / steps;
        
        HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
        RECT lineRect;
        if (vertical) {
            lineRect = {rect.left, rect.top + i, rect.right, rect.top + i + 1};
        } else {
            lineRect = {rect.left + i, rect.top, rect.left + i + 1, rect.bottom};
        }
        FillRect(hdc, &lineRect, brush);
        DeleteObject(brush);
    }
}

void DrawMine(HDC hdc, int x, int y, int size)
{
    int centerX = x + size / 2;
    int centerY = y + size / 2;
    int radius = size / 3;
    
    // Ombre de la mine
    HBRUSH shadowBrush = CreateSolidBrush(RGB(100, 0, 0));
    SelectObject(hdc, shadowBrush);
    SelectObject(hdc, GetStockObject(NULL_PEN));
    Ellipse(hdc, centerX - radius + 2, centerY - radius + 2, 
            centerX + radius + 2, centerY + radius + 2);
    DeleteObject(shadowBrush);
    
    // Corps de la mine
    HBRUSH mineBrush = CreateSolidBrush(RGB(40, 40, 40));
    SelectObject(hdc, mineBrush);
    Ellipse(hdc, centerX - radius, centerY - radius, 
            centerX + radius, centerY + radius);
    DeleteObject(mineBrush);
    
    // Piques de la mine
    HPEN minePen = CreatePen(PS_SOLID, 3, RGB(40, 40, 40));
    HPEN oldPen = (HPEN)SelectObject(hdc, minePen);
    
    // 8 piques
    for (int i = 0; i < 8; i++) {
        double angle = i * 3.14159 / 4;
        int x1 = centerX + (int)(radius * 0.7 * cos(angle));
        int y1 = centerY + (int)(radius * 0.7 * sin(angle));
        int x2 = centerX + (int)(radius * 1.5 * cos(angle));
        int y2 = centerY + (int)(radius * 1.5 * sin(angle));
        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2, y2);
    }
    
    // Point brillant
    HBRUSH highlightBrush = CreateSolidBrush(RGB(150, 150, 150));
    SelectObject(hdc, highlightBrush);
    SelectObject(hdc, GetStockObject(NULL_PEN));
    Ellipse(hdc, centerX - radius / 3, centerY - radius / 3,
            centerX, centerY);
    
    SelectObject(hdc, oldPen);
    DeleteObject(minePen);
    DeleteObject(highlightBrush);
}

void DrawFlag(HDC hdc, int x, int y, int size)
{
    int centerX = x + size / 2;
    int bottomY = y + size - 8;
    int topY = y + 8;
    int flagWidth = size / 2;
    
    // Mât du drapeau
    HPEN polePen = CreatePen(PS_SOLID, 3, RGB(101, 67, 33));
    HPEN oldPen = (HPEN)SelectObject(hdc, polePen);
    MoveToEx(hdc, centerX, topY, NULL);
    LineTo(hdc, centerX, bottomY);
    
    // Base du mât
    HBRUSH baseBrush = CreateSolidBrush(RGB(101, 67, 33));
    SelectObject(hdc, baseBrush);
    SelectObject(hdc, GetStockObject(NULL_PEN));
    Rectangle(hdc, centerX - 4, bottomY - 3, centerX + 4, bottomY);
    DeleteObject(baseBrush);
    
    // Drapeau
    POINT flagPoints[3] = {
        {centerX, topY},
        {centerX + flagWidth, topY + size / 4},
        {centerX, topY + size / 2}
    };
    
    HBRUSH flagBrush = CreateSolidBrush(RGB(244, 67, 54));
    SelectObject(hdc, flagBrush);
    Polygon(hdc, flagPoints, 3);
    
    // Ombre du drapeau
    HBRUSH shadowBrush = CreateSolidBrush(RGB(198, 40, 40));
    SelectObject(hdc, shadowBrush);
    POINT shadowPoints[3] = {
        {centerX, topY + size / 4},
        {centerX + flagWidth, topY + size / 4},
        {centerX, topY + size / 2}
    };
    Polygon(hdc, shadowPoints, 3);
    
    SelectObject(hdc, oldPen);
    DeleteObject(polePen);
    DeleteObject(flagBrush);
    DeleteObject(shadowBrush);
}

void DrawQuestion(HDC hdc, int x, int y, int size)
{
    RECT rect = {x, y, x + size, y + size};
    
    SetBkMode(hdc, TRANSPARENT);
    HFONT hFont = CreateFont(size * 3 / 4, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
    HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
    
    // Ombre du texte
    SetTextColor(hdc, RGB(100, 100, 100));
    RECT shadowRect = {x + 2, y + 2, x + size + 2, y + size + 2};
    DrawText(hdc, L"?", -1, &shadowRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    
    // Texte principal
    SetTextColor(hdc, RGB(33, 150, 243));
    DrawText(hdc, L"?", -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    
    SelectObject(hdc, oldFont);
    DeleteObject(hFont);
}

void DrawCell(HDC hdc, int row, int col, int x, int y)
{
    Cell& cell = grid[row][col];
    RECT rect = {x + 1, y + 1, x + CELL_SIZE - 1, y + CELL_SIZE - 1};
    
    // Effet de hint (lueur verte)
    if (cell.isHinted && cell.state == HIDDEN) {
        for (int i = 0; i < 3; i++) {
            HPEN glowPen = CreatePen(PS_SOLID, 3 - i, RGB(0, 255 - i*50, 0));
            SelectObject(hdc, glowPen);
            SelectObject(hdc, GetStockObject(NULL_BRUSH));
            Rectangle(hdc, x - i, y - i, x + CELL_SIZE + i, y + CELL_SIZE + i);
            DeleteObject(glowPen);
        }
    }
    
    if (cell.state == REVEALED) {
        if (cell.hasMine) {
            // Dégradé rouge pour les mines
            DrawGradientRect(hdc, rect, RGB(255, 235, 238), RGB(255, 205, 210), true);
            DrawMine(hdc, x, y, CELL_SIZE);
        } else {
            // Dégradé subtil pour les cases révélées
            COLORREF color1 = RGB(245, 245, 245);
            COLORREF color2 = RGB(250, 250, 250);
            DrawGradientRect(hdc, rect, color1, color2, true);
            
            if (cell.adjacentMines > 0) {
                SetBkMode(hdc, TRANSPARENT);
                HFONT hFont = CreateFont(CELL_SIZE * 3 / 5, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                    ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
                HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
                
                // Ombre du chiffre
                WCHAR text[10];
                swprintf_s(text, L"%d", cell.adjacentMines);
                RECT shadowRect = {rect.left + 2, rect.top + 2, rect.right + 2, rect.bottom + 2};
                SetTextColor(hdc, RGB(200, 200, 200));
                DrawText(hdc, text, -1, &shadowRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                
                // Chiffre principal
                SetTextColor(hdc, GetNumberColor(cell.adjacentMines));
                DrawText(hdc, text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                
                SelectObject(hdc, oldFont);
                DeleteObject(hFont);
            }
        }
        
        // Bordure fine pour les cases révélées
        HPEN penBorder = CreatePen(PS_SOLID, 1, RGB(189, 189, 189));
        HPEN oldPen = (HPEN)SelectObject(hdc, penBorder);
        SelectObject(hdc, GetStockObject(NULL_BRUSH));
        Rectangle(hdc, x, y, x + CELL_SIZE, y + CELL_SIZE);
        SelectObject(hdc, oldPen);
        DeleteObject(penBorder);
    } else {
        // Effet 3D amélioré pour les cases non révélées
        DrawGradientRect(hdc, rect, RGB(220, 220, 220), RGB(189, 189, 189), true);
        
        // Bordures 3D plus prononcées
        HPEN penLight = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
        HPEN penMedium = CreatePen(PS_SOLID, 2, RGB(230, 230, 230));
        HPEN penDark = CreatePen(PS_SOLID, 2, RGB(130, 130, 130));
        HPEN penDarker = CreatePen(PS_SOLID, 3, RGB(100, 100, 100));
        
        // Coin supérieur gauche (clair)
        SelectObject(hdc, penLight);
        MoveToEx(hdc, x, y + CELL_SIZE - 3, NULL);
        LineTo(hdc, x, y);
        LineTo(hdc, x + CELL_SIZE - 3, y);
        
        SelectObject(hdc, penMedium);
        MoveToEx(hdc, x + 3, y + CELL_SIZE - 6, NULL);
        LineTo(hdc, x + 3, y + 3);
        LineTo(hdc, x + CELL_SIZE - 6, y + 3);
        
        // Coin inférieur droit (sombre)
        SelectObject(hdc, penDarker);
        MoveToEx(hdc, x + CELL_SIZE, y + 3, NULL);
        LineTo(hdc, x + CELL_SIZE, y + CELL_SIZE);
        LineTo(hdc, x + 3, y + CELL_SIZE);
        
        SelectObject(hdc, penDark);
        MoveToEx(hdc, x + CELL_SIZE - 3, y + 6, NULL);
        LineTo(hdc, x + CELL_SIZE - 3, y + CELL_SIZE - 3);
        LineTo(hdc, x + 6, y + CELL_SIZE - 3);
        
        DeleteObject(penLight);
        DeleteObject(penMedium);
        DeleteObject(penDark);
        DeleteObject(penDarker);
        
        // Contenu de la case
        if (cell.state == FLAGGED) {
            DrawFlag(hdc, x, y, CELL_SIZE);
        } else if (cell.state == QUESTION) {
            DrawQuestion(hdc, x, y, CELL_SIZE);
        }
    }
}

void DrawHeader(HDC hdc, int width)
{
    RECT headerRect = {MARGIN, MARGIN, width - MARGIN, HEADER_HEIGHT};
    
    // Dégradé élégant pour l'en-tête
    DrawGradientRect(hdc, headerRect, RGB(66, 66, 66), RGB(97, 97, 97), true);
    
    // Bordure de l'en-tête
    HPEN borderPen = CreatePen(PS_SOLID, 2, RGB(33, 33, 33));
    HPEN oldPen = (HPEN)SelectObject(hdc, borderPen);
    SelectObject(hdc, GetStockObject(NULL_BRUSH));
    RoundRect(hdc, headerRect.left, headerRect.top, headerRect.right, headerRect.bottom, 10, 10);
    SelectObject(hdc, oldPen);
    DeleteObject(borderPen);
    
    SetBkMode(hdc, TRANSPARENT);
    
    // Panneau gauche - Compteur de mines
    RECT minesPanel = {MARGIN + 15, MARGIN + 15, MARGIN + 160, HEADER_HEIGHT - 15};
    HBRUSH panelBrush = CreateSolidBrush(RGB(33, 33, 33));
    HPEN panelPen = CreatePen(PS_SOLID, 1, RGB(150, 150, 150));
    SelectObject(hdc, panelBrush);
    SelectObject(hdc, panelPen);
    RoundRect(hdc, minesPanel.left, minesPanel.top, minesPanel.right, minesPanel.bottom, 8, 8);
    DeleteObject(panelBrush);
    DeleteObject(panelPen);
    
    HFONT digitalFont = CreateFont(32, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Consolas");
    HFONT oldFont = (HFONT)SelectObject(hdc, digitalFont);
    
    WCHAR minesText[50];
    int remainingMines = totalMines - flagsPlaced;
    swprintf_s(minesText, L"%03d", remainingMines < 0 ? 0 : remainingMines);
    SetTextColor(hdc, RGB(255, 69, 58));
    DrawText(hdc, minesText, -1, &minesPanel, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    
    // Panneau droit - Chronomètre
    RECT timePanel = {width - MARGIN - 160, MARGIN + 15, width - MARGIN - 15, HEADER_HEIGHT - 15};
    panelBrush = CreateSolidBrush(RGB(33, 33, 33));
    panelPen = CreatePen(PS_SOLID, 1, RGB(150, 150, 150));
    SelectObject(hdc, panelBrush);
    SelectObject(hdc, panelPen);
    RoundRect(hdc, timePanel.left, timePanel.top, timePanel.right, timePanel.bottom, 8, 8);
    DeleteObject(panelBrush);
    DeleteObject(panelPen);
    
    if (gameStarted && !gameOver) {
        auto now = std::chrono::steady_clock::now();
        elapsedSeconds = (int)std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
    }
    
    WCHAR timeText[50];
    swprintf_s(timeText, L"%03d", elapsedSeconds > 999 ? 999 : elapsedSeconds);
    SetTextColor(hdc, RGB(48, 209, 88));
    DrawText(hdc, timeText, -1, &timePanel, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    
    // Panneau central - Statut
    if (gameOver) {
        RECT statusPanel = {MARGIN + 180, MARGIN + 10, width - MARGIN - 180, HEADER_HEIGHT - 10};
        
        HFONT statusFont = CreateFont(36, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
        SelectObject(hdc, statusFont);
        
        if (gameWon) {
            // Ombre du texte
            SetTextColor(hdc, RGB(0, 80, 0));
            RECT shadowRect = {statusPanel.left + 2, statusPanel.top + 2, 
                             statusPanel.right + 2, statusPanel.bottom + 2};
            DrawText(hdc, L"VICTOIRE!", -1, &shadowRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            
            SetTextColor(hdc, RGB(76, 175, 80));
            DrawText(hdc, L"VICTOIRE!", -1, &statusPanel, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        } else {
            // Ombre du texte
            SetTextColor(hdc, RGB(100, 0, 0));
            RECT shadowRect = {statusPanel.left + 2, statusPanel.top + 2, 
                             statusPanel.right + 2, statusPanel.bottom + 2};
            DrawText(hdc, L"GAME OVER", -1, &shadowRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            
            SetTextColor(hdc, RGB(244, 67, 54));
            DrawText(hdc, L"GAME OVER", -1, &statusPanel, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }
        DeleteObject(statusFont);
    } else {
        // Bouton central (emoji de smiley)
        RECT smileyRect = {width / 2 - 25, MARGIN + 20, width / 2 + 25, HEADER_HEIGHT - 20};
        HBRUSH smileyBrush = CreateSolidBrush(RGB(255, 193, 7));
        HPEN smileyPen = CreatePen(PS_SOLID, 2, RGB(255, 152, 0));
        SelectObject(hdc, smileyBrush);
        SelectObject(hdc, smileyPen);
        Ellipse(hdc, smileyRect.left, smileyRect.top, smileyRect.right, smileyRect.bottom);
        DeleteObject(smileyBrush);
        DeleteObject(smileyPen);
        
        // Dessiner le visage souriant
        HPEN facePen = CreatePen(PS_SOLID, 2, RGB(66, 66, 66));
        SelectObject(hdc, facePen);
        
        // Yeux
        int eyeY = MARGIN + 30;
        Ellipse(hdc, width / 2 - 12, eyeY, width / 2 - 8, eyeY + 4);
        Ellipse(hdc, width / 2 + 8, eyeY, width / 2 + 12, eyeY + 4);
        
        // Bouche souriante
        Arc(hdc, width / 2 - 10, MARGIN + 25, width / 2 + 10, MARGIN + 45, 
            width / 2 + 8, MARGIN + 35, width / 2 - 8, MARGIN + 35);
        
        DeleteObject(facePen);
    }
    
    SelectObject(hdc, oldFont);
    DeleteObject(digitalFont);
}

void DrawMenuButton(HDC hdc, RECT button, const WCHAR* text, bool hovered) {
    // Couleur selon hover
    COLORREF color1 = hovered ? RGB(76, 175, 80) : RGB(52, 73, 94);
    COLORREF color2 = hovered ? RGB(56, 142, 60) : RGB(44, 62, 80);
    
    DrawGradientRect(hdc, button, color1, color2, true);
    
    // Bordure blanche
    HPEN pen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
    SelectObject(hdc, pen);
    SelectObject(hdc, GetStockObject(NULL_BRUSH));
    RoundRect(hdc, button.left, button.top, button.right, button.bottom, 15, 15);
    DeleteObject(pen);
    
    // Texte
    SetBkMode(hdc, TRANSPARENT);
    HFONT font = CreateFont(48, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
    SelectObject(hdc, font);
    
    // Ombre
    RECT shadowRect = {button.left + 3, button.top + 3, button.right + 3, button.bottom + 3};
    SetTextColor(hdc, RGB(0, 0, 0));
    DrawText(hdc, text, -1, &shadowRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    
    // Texte principal
    SetTextColor(hdc, RGB(255, 255, 255));
    DrawText(hdc, text, -1, &button, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    
    DeleteObject(font);
}

void DrawMenu(HDC hdc, HWND hWnd) {
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);
    int width = clientRect.right;
    int height = clientRect.bottom;
    
    // ????? Fond avec dégradé bleu foncé ANIMÉ ?????
    COLORREF color1 = RGB(41 + (int)(sin(menuAnimationTime) * 10), 128, 185);
    COLORREF color2 = RGB(109, 213 + (int)(cos(menuAnimationTime * 0.7f) * 10), 250);
    DrawGradientRect(hdc, clientRect, color1, color2, true);
    
    // ????? Effet de flou avec couches semi-transparentes ANIMÉES ?????
    for (int layer = 0; layer < 3; layer++) {
        for (int i = 0; i < 10; i++) {
            int x = (width / 10) * i + (int)(sin(menuAnimationTime + i) * 30);
            int y = (height / 10) * ((layer * 3 + i) % 10) + (int)(cos(menuAnimationTime * 0.8f + i) * 20);
            int size = 80 + (int)(sin(menuAnimationTime + i * 0.5f) * 20);
            
            // Couleur semi-transparente
            int alpha = 220 - layer * 20;
            HBRUSH blurBrush = CreateSolidBrush(RGB(alpha, alpha, 255));
            SelectObject(hdc, blurBrush);
            SelectObject(hdc, GetStockObject(NULL_PEN));
            
            // Dessiner plusieurs fois pour effet de flou
            for (int j = 0; j < 3; j++) {
                int offset = j * 2;
                Ellipse(hdc, x - size/2 + offset, y - size/2 + offset, 
                       x + size/2 + offset, y + size/2 + offset);
            }
            
            DeleteObject(blurBrush);
        }
    }
    
    // ????? Particules flottantes ANIMÉES avec trainée ?????
    for (const auto& p : menuParticles) {
        if (p.active) {
            int size = 6 + (int)(sin(menuAnimationTime * 3.0f + p.x * 0.1f) * 3);
            
            // Trainée de la particule (3 niveaux)
            for (int trail = 0; trail < 3; trail++) {
                int trailX = (int)p.x - trail * (int)p.vx * 5;
                int trailY = (int)p.y - trail * (int)p.vy * 5;
                int trailSize = size - trail;
                int trailAlpha = 255 - trail * 60;
                
                HBRUSH trailBrush = CreateSolidBrush(RGB(trailAlpha, trailAlpha, 255));
                SelectObject(hdc, trailBrush);
                SelectObject(hdc, GetStockObject(NULL_PEN));
                
                Ellipse(hdc, trailX - trailSize/2, trailY - trailSize/2, 
                       trailX + trailSize/2, trailY + trailSize/2);
                
                DeleteObject(trailBrush);
            }
        }
    }
    
    // ????? Vignette pour effet de profondeur ?????
    for (int i = 0; i < 100; i += 10) {
        int alpha = 10 + i / 10;
        HPEN vignettePen = CreatePen(PS_SOLID, 20, RGB(0, 0, alpha));
        SelectObject(hdc, vignettePen);
        SelectObject(hdc, GetStockObject(NULL_BRUSH));
        Rectangle(hdc, i, i, width - i, height - i);
        DeleteObject(vignettePen);
    }
    
    // ????? Titre avec effet de lueur multiple ANIMÉ ?????
    HFONT titleFont = CreateFont(120, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
    SelectObject(hdc, titleFont);
    
    SetBkMode(hdc, TRANSPARENT);
    RECT titleRect = {0, 100, width, 250};
    
    // Effet de lueur (glow) animé - 10 couches
    for (int glow = 10; glow > 0; glow -= 2) {
        int glowIntensity = 100 + glow * 10 + (int)(sin(menuAnimationTime * 2.0f) * 20);
        RECT glowRect = {titleRect.left - glow, titleRect.top - glow, 
                        titleRect.right + glow, titleRect.bottom + glow};
        SetTextColor(hdc, RGB(glowIntensity, 150 + glow * 5, 255));
        DrawText(hdc, L"?? DÉMINEUR", -1, &glowRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
    
    // Ombre portée noire
    SetTextColor(hdc, RGB(0, 0, 0));
    RECT titleShadow = {titleRect.left + 5, titleRect.top + 5, titleRect.right + 5, titleRect.bottom + 5};
    DrawText(hdc, L"?? DÉMINEUR", -1, &titleShadow, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    
    // Titre principal blanc éclatant
    SetTextColor(hdc, RGB(255, 255, 255));
    DrawText(hdc, L"?? DÉMINEUR", -1, &titleRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    
    DeleteObject(titleFont);
    
    // ????? Sous-titre ANIMÉ avec pulsation ?????
    HFONT subtitleFont = CreateFont(32, 0, 0, 0, FW_NORMAL, TRUE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
    SelectObject(hdc, subtitleFont);
    
    RECT subtitleRect = {0, 250, width, 300};
    int subtitleAlpha = 200 + (int)(sin(menuAnimationTime * 2.0f) * 55);
    SetTextColor(hdc, RGB(subtitleAlpha, subtitleAlpha, subtitleAlpha + 20));
    DrawText(hdc, L"Version Ultra HD 1920×1080 • Flou Dynamique Activé ?", -1, &subtitleRect, DT_CENTER | DT_SINGLELINE);
    
    DeleteObject(subtitleFont);
    
    // ????? Boutons avec animation de pulsation ?????
    int buttonWidth = 400;
    int buttonHeight = 80;
    int buttonSpacing = 30;
    int startY = 400;
    int centerX = width / 2;
    
    // Animation de pulsation pour le bouton JOUER
    float pulse = sin(menuAnimationTime * 2.0f) * 5;
    
    RECT playButton = {centerX - buttonWidth/2 - (int)pulse, startY - (int)pulse, 
                      centerX + buttonWidth/2 + (int)pulse, startY + buttonHeight + (int)pulse};
    RECT optionsButton = {centerX - buttonWidth/2, startY + buttonHeight + buttonSpacing, 
                          centerX + buttonWidth/2, startY + 2*buttonHeight + buttonSpacing};
    RECT quitButton = {centerX - buttonWidth/2, startY + 2*(buttonHeight + buttonSpacing), 
                       centerX + buttonWidth/2, startY + 3*buttonHeight + 2*buttonSpacing};
    
    // ????? Aura lumineuse verte autour du bouton JOUER ?????
    for (int aura = 5; aura > 0; aura--) {
        HPEN auraPen = CreatePen(PS_SOLID, 2, RGB(100 + aura * 20, 255 - aura * 20, 100));
        SelectObject(hdc, auraPen);
        SelectObject(hdc, GetStockObject(NULL_BRUSH));
        RoundRect(hdc, playButton.left - aura*2, playButton.top - aura*2, 
                 playButton.right + aura*2, playButton.bottom + aura*2, 15, 15);
        DeleteObject(auraPen);
    }
    
    DrawMenuButton(hdc, playButton, L"? JOUER", false);
    DrawMenuButton(hdc, optionsButton, L"? OPTIONS", false);
    DrawMenuButton(hdc, quitButton, L"? QUITTER", false);
    
    // ????? Footer ANIMÉ avec pulsation ?????
    HFONT footerFont = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
    SelectObject(hdc, footerFont);
    
    RECT footerRect = {0, height - 60, width, height - 20};
    int footerAlpha = 150 + (int)(cos(menuAnimationTime * 1.5f) * 50);
    SetTextColor(hdc, RGB(footerAlpha, footerAlpha + 10, footerAlpha + 20));
    DrawText(hdc, L"Cliquez sur JOUER pour commencer • Utilisez le menu Difficulté pour choisir votre niveau ??", 
             -1, &footerRect, DT_CENTER | DT_SINGLELINE);
    
    DeleteObject(footerFont);
}

void DrawGame(HDC hdc, HWND hWnd)
{
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);
    int width = clientRect.right - clientRect.left;
    int height = clientRect.bottom - clientRect.top;
    
    // ????????? FOND ANIMÉ AUTOUR DE LA ZONE DE JEU ?????????
    // Dégradé de fond animé
    COLORREF bgColor1 = RGB(30 + (int)(sin(gameBackgroundTime * 0.5f) * 15), 
                           35 + (int)(cos(gameBackgroundTime * 0.3f) * 15), 
                           50 + (int)(sin(gameBackgroundTime * 0.4f) * 20));
    COLORREF bgColor2 = RGB(50 + (int)(cos(gameBackgroundTime * 0.4f) * 15), 
                           60 + (int)(sin(gameBackgroundTime * 0.6f) * 15), 
                           80 + (int)(cos(gameBackgroundTime * 0.5f) * 20));
    DrawGradientRect(hdc, clientRect, bgColor1, bgColor2, true);
    
    // Vagues lumineuses animées (effet aurora)
    for (int wave = 0; wave < 5; wave++) {
        float waveOffset = gameBackgroundTime + wave * 1.5f;
        int numPoints = 100;
        
        for (int i = 0; i < numPoints - 1; i++) {
            float x1 = (float)width * i / numPoints;
            float x2 = (float)width * (i + 1) / numPoints;
            
            float y1 = height * 0.3f + sin(waveOffset + x1 * 0.01f) * 80 + wave * 60;
            float y2 = height * 0.3f + sin(waveOffset + x2 * 0.01f) * 80 + wave * 60;
            
            int alpha = 30 - wave * 5;
            HPEN wavePen = CreatePen(PS_SOLID, 3, RGB(100 + wave * 20, 150 + wave * 10, 255 - wave * 20));
            SelectObject(hdc, wavePen);
            
            MoveToEx(hdc, (int)x1, (int)y1, NULL);
            LineTo(hdc, (int)x2, (int)y2);
            
            DeleteObject(wavePen);
        }
    }
    
    // Particules de fond flottantes
    for (const auto& p : gameBackgroundParticles) {
        if (p.active) {
            int size = 8 + (int)(sin(gameBackgroundTime * 2.0f + p.x * 0.05f) * 4);
            
            // Effet de lueur autour de la particule
            for (int glow = 3; glow > 0; glow--) {
                int glowSize = size + glow * 3;
                int glowAlpha = 100 - glow * 30;
                
                HBRUSH glowBrush = CreateSolidBrush(p.color);
                SelectObject(hdc, glowBrush);
                SelectObject(hdc, GetStockObject(NULL_PEN));
                
                Ellipse(hdc, (int)p.x - glowSize/2, (int)p.y - glowSize/2, 
                       (int)p.x + glowSize/2, (int)p.y + glowSize/2);
                
                DeleteObject(glowBrush);
            }
            
            // Particule principale
            HBRUSH brush = CreateSolidBrush(p.color);
            SelectObject(hdc, brush);
            SelectObject(hdc, GetStockObject(NULL_PEN));
            
            Ellipse(hdc, (int)p.x - size/2, (int)p.y - size/2, 
                   (int)p.x + size/2, (int)p.y + size/2);
            
            DeleteObject(brush);
        }
    }
    
    // Étoiles scintillantes
    for (int star = 0; star < 30; star++) {
        int starX = (star * 137) % width;
        int starY = (star * 219) % height;
        float brightness = sin(gameBackgroundTime * 3.0f + star * 0.5f) * 0.5f + 0.5f;
        int alpha = (int)(brightness * 255);
        
        HBRUSH starBrush = CreateSolidBrush(RGB(alpha, alpha, 255));
        SelectObject(hdc, starBrush);
        SelectObject(hdc, GetStockObject(NULL_PEN));
        
        int starSize = 3 + (int)(brightness * 2);
        Ellipse(hdc, starX - starSize/2, starY - starSize/2, 
               starX + starSize/2, starY + starSize/2);
        
        DeleteObject(starBrush);
    }
    // ????????? FIN DU FOND ANIMÉ ?????????
    
    DrawHeader(hdc, width);
    
    // Centrer la grille dans l'espace disponible
    int gridWidth = cols * CELL_SIZE;
    int gridHeight = rows * CELL_SIZE;
    int availableHeight = height - HEADER_HEIGHT - FOOTER_HEIGHT - 4 * MARGIN;
    
    int startX = (width - gridWidth) / 2;
    int startY = HEADER_HEIGHT + MARGIN + (availableHeight - gridHeight) / 2;
    
    // Panneau de fond pour la grille (effet Windows 7)
    RECT gridPanel = {startX - 10, startY - 10, 
                      startX + gridWidth + 10, 
                      startY + gridHeight + 10};
    
    // Fond gris Windows 7
    FillRect(hdc, &gridPanel, g_brushGray);
    
    // Bordure enfoncée 3D
    SelectObject(hdc, g_penBlack);
    MoveToEx(hdc, gridPanel.left, gridPanel.bottom - 1, NULL);
    LineTo(hdc, gridPanel.left, gridPanel.top);
    LineTo(hdc, gridPanel.right - 1, gridPanel.top);
    
    SelectObject(hdc, g_penWhite);
    MoveToEx(hdc, gridPanel.left + 1, gridPanel.bottom - 1, NULL);
    LineTo(hdc, gridPanel.right - 1, gridPanel.bottom - 1);
    LineTo(hdc, gridPanel.right - 1, gridPanel.top + 1);
    
    // Dessiner toutes les cellules
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            DrawCell(hdc, i, j, startX + j * CELL_SIZE, startY + i * CELL_SIZE);
        }
    }
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEMINEUR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = NULL;  // Pas de fond automatique pour éviter les flashs
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DEMINEUR);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   InitializeGame(currentDifficulty);
   LoadStats();
   
   // Initialiser le cache GDI
   InitGDICache();

   // Résolution fixe 1920x1080 - Calculer la taille de fenêtre avec bordures
   RECT windowRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
   AdjustWindowRect(&windowRect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, TRUE);
   
   int windowWidth = windowRect.right - windowRect.left;
   int windowHeight = windowRect.bottom - windowRect.top;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, 
      WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
      CW_USEDEFAULT, 0, windowWidth, windowHeight, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   SetTimer(hWnd, 1, 1000, NULL);  // Timer principal (1 seconde)
   SetTimer(hWnd, 2, 16, NULL);    // Timer d'animation (60 FPS)

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case IDM_DIFFICULTY_FACILE:
                currentDifficulty = FACILE;
                InitializeGame(currentDifficulty);
                gameState = STATE_PLAYING;
                InvalidateRect(hWnd, NULL, FALSE);
                break;
            case IDM_DIFFICULTY_MOYEN:
                currentDifficulty = MOYEN;
                InitializeGame(currentDifficulty);
                gameState = STATE_PLAYING;
                InvalidateRect(hWnd, NULL, FALSE);
                break;
            case IDM_DIFFICULTY_DIFFICILE:
                currentDifficulty = DIFFICILE;
                InitializeGame(currentDifficulty);
                gameState = STATE_PLAYING;
                InvalidateRect(hWnd, NULL, FALSE);
                break;
            case IDM_DIFFICULTY_EXPERT:
                currentDifficulty = EXPERT;
                InitializeGame(currentDifficulty);
                gameState = STATE_PLAYING;
                InvalidateRect(hWnd, NULL, FALSE);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    
    case WM_ERASEBKGND:
        return 1;
    
    case WM_KEYDOWN:
        {
            switch (wParam) {
                case 'H': // Hint
                    if (gameState == STATE_PLAYING && !gameOver && hintsRemaining > 0) {
                        ShowHint();
                        InvalidateRect(hWnd, NULL, FALSE);
                    }
                    break;
                case 'P': // Pause
                    if (gameState == STATE_PLAYING) {
                        isPaused = !isPaused;
                        InvalidateRect(hWnd, NULL, FALSE);
                    }
                    break;
                case 'R': // Restart
                    if (gameState == STATE_PLAYING) {
                        InitializeGame(currentDifficulty);
                        InvalidateRect(hWnd, NULL, FALSE);
                    }
                    break;
                case 'C': // Clear hint
                    if (gameState == STATE_PLAYING) {
                        ClearHint();
                        InvalidateRect(hWnd, NULL, FALSE);
                    }
                    break;
                case VK_ESCAPE: // Retour au menu
                    gameState = STATE_MENU;
                    InvalidateRect(hWnd, NULL, FALSE);
                    break;
            }
        }
        break;
        
    case WM_LBUTTONDOWN:
        {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            
            RECT clientRect;
            GetClientRect(hWnd, &clientRect);
            int width = clientRect.right;
            int height = clientRect.bottom;
            
            // Si on est dans le menu
            if (gameState == STATE_MENU) {
                int buttonWidth = 400;
                int buttonHeight = 80;
                int buttonSpacing = 30;
                int startY = 400;
                int centerX = width / 2;
                
                RECT playButton = {centerX - buttonWidth/2, startY, centerX + buttonWidth/2, startY + buttonHeight};
                RECT optionsButton = {centerX - buttonWidth/2, startY + buttonHeight + buttonSpacing, 
                                      centerX + buttonWidth/2, startY + 2*buttonHeight + buttonSpacing};
                RECT quitButton = {centerX - buttonWidth/2, startY + 2*(buttonHeight + buttonSpacing), 
                                   centerX + buttonWidth/2, startY + 3*buttonHeight + 2*buttonSpacing};
                
                if (x >= playButton.left && x <= playButton.right &&
                    y >= playButton.top && y <= playButton.bottom) {
                    // Bouton JOUER
                    gameState = STATE_PLAYING;
                    InitializeGame(currentDifficulty);
                    InvalidateRect(hWnd, NULL, FALSE);
                }
                else if (x >= optionsButton.left && x <= optionsButton.right &&
                         y >= optionsButton.top && y <= optionsButton.bottom) {
                    // Bouton OPTIONS
                    MessageBox(hWnd, L"Options à venir !", L"Options", MB_OK | MB_ICONINFORMATION);
                }
                else if (x >= quitButton.left && x <= quitButton.right &&
                         y >= quitButton.top && y <= quitButton.bottom) {
                    // Bouton QUITTER
                    DestroyWindow(hWnd);
                }
                break;
            }
            
            // Si on est en jeu
            if (gameState == STATE_PLAYING) {
                // Vérifier si clic sur bouton d'aide
                int footerY = height - FOOTER_HEIGHT + 10;
                RECT hintButtonRect = {MARGIN + 10, footerY, 
                                       MARGIN + 130, footerY + 60};
                
                if (x >= hintButtonRect.left && x <= hintButtonRect.right &&
                    y >= hintButtonRect.top && y <= hintButtonRect.bottom) {
                    if (!gameOver && hintsRemaining > 0) {
                        ShowHint();
                        InvalidateRect(hWnd, NULL, FALSE);
                    }
                    break;
                }
                
                if (gameOver) {
                    InitializeGame(currentDifficulty);
                    InvalidateRect(hWnd, NULL, FALSE);
                    break;
                }
                
                // Calculer la position de la grille centrée
                int gridWidth = cols * CELL_SIZE;
                int gridHeight = rows * CELL_SIZE;
                int availableHeight = height - HEADER_HEIGHT - FOOTER_HEIGHT - 4 * MARGIN;
                int startX = (width - gridWidth) / 2;
                int startY = HEADER_HEIGHT + MARGIN + (availableHeight - gridHeight) / 2;
                
                int col = (x - startX) / CELL_SIZE;
                int row = (y - startY) / CELL_SIZE;
                
                if (row >= 0 && row < rows && col >= 0 && col < cols && 
                    x >= startX && y >= startY) {
                    if (firstClick) {
                        PlaceMines(row, col);
                        gameStarted = true;
                        startTime = std::chrono::steady_clock::now();
                        firstClick = false;
                    }
                    
                    RevealCell(row, col);
                    CheckWinCondition();
                    UpdateComboMultiplier();
                    CalculateScore();
                    InvalidateRect(hWnd, NULL, FALSE);
                }
            }
        }
        break;
        
    case WM_RBUTTONDOWN:
        {
            if (gameState != STATE_PLAYING || gameOver || firstClick) break;
            
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            
            RECT clientRect;
            GetClientRect(hWnd, &clientRect);
            int width = clientRect.right;
            int height = clientRect.bottom;
            
            // Calculer la position de la grille centrée
            int gridWidth = cols * CELL_SIZE;
            int gridHeight = rows * CELL_SIZE;
            int availableHeight = height - HEADER_HEIGHT - FOOTER_HEIGHT - 4 * MARGIN;
            int startX = (width - gridWidth) / 2;
            int startY = HEADER_HEIGHT + MARGIN + (availableHeight - gridHeight) / 2;
            
            int col = (x - startX) / CELL_SIZE;
            int row = (y - startY) / CELL_SIZE;
            
            if (row >= 0 && row < rows && col >= 0 && col < cols &&
                x >= startX && y >= startY) {
                ToggleFlag(row, col);
                CheckWinCondition();
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        break;
        
    case WM_TIMER:
        {
            switch (wParam) {
                case 1: // Timer principal
                    if (gameStarted && !gameOver && !isPaused) {
                        InvalidateRect(hWnd, NULL, FALSE);
                    }
                    break;
                case 2: // Timer d'animation
                    UpdateParticles();
                    UpdateAnimations();
                    
                    // ??? TOUJOURS mettre à jour les particules du menu ???
                    if (gameState == STATE_MENU) {
                        UpdateMenuParticles();
                        InvalidateRect(hWnd, NULL, FALSE);
                    }
                    else if (gameState == STATE_PLAYING) {
                        // ??? Mettre à jour les particules du fond de jeu ???
                        UpdateGameBackgroundParticles();
                        InvalidateRect(hWnd, NULL, FALSE);
                    }
                    else if (gameConfig.particlesEnabled) {
                        InvalidateRect(hWnd, NULL, FALSE);
                    }
                    break;
            }
        }
        break;
        
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            RECT clientRect;
            GetClientRect(hWnd, &clientRect);
            
            HDC hdcMem = CreateCompatibleDC(hdc);
            HBITMAP hbmMem = CreateCompatibleBitmap(hdc, clientRect.right, clientRect.bottom);
            HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);
            
            // Dessiner selon l'état du jeu
            if (gameState == STATE_MENU) {
                DrawMenu(hdcMem, hWnd);
            }
            else if (gameState == STATE_PLAYING) {
                // ????? PAS DE FillRect gris uni ici, DrawGame() fait le fond animé ?????
                DrawGame(hdcMem, hWnd);
            
                // Particules (confettis et explosions)
                DrawParticles(hdcMem);
                
                // === ZONE HUD EN BAS (FOOTER) ===
                int footerY = clientRect.bottom - FOOTER_HEIGHT + 10;
            
                // Fond du footer style Windows 7
                RECT footerBg = {0, clientRect.bottom - FOOTER_HEIGHT, clientRect.right, clientRect.bottom};
                FillRect(hdcMem, &footerBg, g_brushDarkGray);
                
                // Bordure 3D supérieure
                SelectObject(hdcMem, g_penWhite);
                MoveToEx(hdcMem, 0, clientRect.bottom - FOOTER_HEIGHT, NULL);
                LineTo(hdcMem, clientRect.right, clientRect.bottom - FOOTER_HEIGHT);
                
                SelectObject(hdcMem, g_penBlack);
                MoveToEx(hdcMem, 0, clientRect.bottom - FOOTER_HEIGHT + 1, NULL);
                LineTo(hdcMem, clientRect.right, clientRect.bottom - FOOTER_HEIGHT + 1);
            
                if (gameStarted) {
                    // 1. Bouton AIDE (à gauche)
                    DrawHintButton(hdcMem, MARGIN + 10, footerY);
                    
                    // 2. Barre de PROGRESSION (au centre)
                    int progressWidth = 250;
                    int progressX = (clientRect.right - progressWidth) / 2;
                    float progress = (float)revealedCells / (rows * cols - totalMines);
                    DrawProgressBar(hdcMem, progressX, footerY, progressWidth, progress);
                    
                    // 3. Panneau SCORE (à droite)
                    DrawScorePanel(hdcMem, clientRect.right - 220, footerY);
                    
                    // 4. Indicateur COMBO (flottant au-dessus du jeu si actif)
                    if (comboMultiplier > 1) {
                        DrawComboIndicator(hdcMem, clientRect.right / 2 - 90, HEADER_HEIGHT + MARGIN - 70);
                    }
                } else {
                    // Si jeu pas commencé, juste le bouton d'aide
                    DrawHintButton(hdcMem, MARGIN + 10, footerY);
                }
                
                // Indication de pause (plein écran)
                if (isPaused) {
                    SetBkMode(hdcMem, TRANSPARENT);
                    HFONT font = CreateFont(60, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
                    SelectObject(hdcMem, font);
                    
                    RECT pauseRect = clientRect;
                    
                    // Ombre
                    RECT shadowRect = {pauseRect.left + 4, pauseRect.top + 4, 
                                     pauseRect.right + 4, pauseRect.bottom + 4};
                    SetTextColor(hdcMem, RGB(0, 0, 0));
                    DrawText(hdcMem, L"? PAUSE", -1, &shadowRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                    
                    SetTextColor(hdcMem, RGB(255, 255, 0));
                    DrawText(hdcMem, L"? PAUSE", -1, &pauseRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                    
                    DeleteObject(font);
                }
                
                // Instructions en bas du footer (si pas commencé)
                if (!gameStarted) {
                    SetBkMode(hdcMem, TRANSPARENT);
                    HFONT font = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                        ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
                    SelectObject(hdcMem, font);
                    
                    RECT instructRect = {MARGIN + 150, footerY + 10, clientRect.right - MARGIN, footerY + 30};
                    SetTextColor(hdcMem, RGB(200, 200, 200));
                    DrawText(hdcMem, L"Touches: H=Aide | P=Pause | R=Recommencer | ESC=Menu", 
                            -1, &instructRect, DT_LEFT | DT_SINGLELINE);
                    
                    RECT instruct2Rect = {MARGIN + 150, footerY + 35, clientRect.right - MARGIN, footerY + 55};
                    DrawText(hdcMem, L"Clic gauche=Révéler | Clic droit=Drapeau", 
                            -1, &instruct2Rect, DT_LEFT | DT_SINGLELINE);
                    
                    DeleteObject(font);
                }
            }
            
            BitBlt(hdc, 0, 0, clientRect.right, clientRect.bottom, hdcMem, 0, 0, SRCCOPY);
            
            SelectObject(hdcMem, hbmOld);
            DeleteObject(hbmMem);
            DeleteDC(hdcMem);
            
            EndPaint(hWnd, &ps);
        }
        break;
        
    case WM_DESTROY:
        KillTimer(hWnd, 1);
        KillTimer(hWnd, 2);
        CleanupGDICache(); // Libérer le cache GDI
        PostQuitMessage(0);
        break;
        
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
