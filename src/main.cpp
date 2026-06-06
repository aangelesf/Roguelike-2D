#include "raylib.h"

// Used to track which screen the game is currently on
enum GameScreen
{
    TITLE,
    CHARACTER_SELECT,
    SETTINGS,
    GAMEPLAY
};



GameScreen titleScreen(bool& showQuitPopup, bool& shouldCloseGame)
{
    Vector2 mousePosition = GetMousePosition(); // Gets the position of mouse (x, y)

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    const char* titleText = "Title here"; // Placeholder while I think of a title
    const char* startText = "Start";
    const char* settingsText = "Settings";

    int titleFontSize = 60;
    int menuFontSize = 30;

    int titleY = (screenHeight / 2) - 200;

    // Magic number is used to set how far down Start and Settings appear
    int menuOffsetY = 175;

    int startY = screenHeight / 2 + menuOffsetY;
    int settingsY = startY + 45;

    // Centers the text on the window
    int titleX = screenWidth / 2 - MeasureText(titleText, titleFontSize) / 2;
    int startX = screenWidth / 2 - MeasureText(startText, menuFontSize) / 2;
    int settingsX = screenWidth / 2 - MeasureText(settingsText, menuFontSize) / 2;

    // measures the size of the menu options to detect where to click
    int startWidth = MeasureText(startText, menuFontSize);
    int settingsWidth = MeasureText(settingsText, menuFontSize);

    int buttonHeight = menuFontSize;

    Rectangle startButton = {
        (float)startX,
        (float)startY,
        (float)startWidth,
        (float)buttonHeight
    };

    Rectangle settingsButton = {
        (float)settingsX,
        (float)settingsY,
        (float)settingsWidth,
        (float)buttonHeight
    };

    // Draw title screen first
    DrawText(titleText, titleX, titleY, titleFontSize, WHITE);
    DrawText(startText, startX, startY, menuFontSize, WHITE);
    DrawText(settingsText, settingsX, settingsY, menuFontSize, WHITE);

    // Only allow title screen buttons if the quit popup is not open
    if (!showQuitPopup)
    {
        if (CheckCollisionPointRec(mousePosition, startButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            return CHARACTER_SELECT;
        }

        if (CheckCollisionPointRec(mousePosition, settingsButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            return SETTINGS;
        }
    }

    // Draw and handle quit confirmation popup
    if (showQuitPopup)
    {
        int popupWidth = 500;
        int popupHeight = 250;

        int popupX = screenWidth / 2 - popupWidth / 2;
        int popupY = screenHeight / 2 - popupHeight / 2;

        Rectangle popupBox = {
            (float)popupX,
            (float)popupY,
            (float)popupWidth,
            (float)popupHeight
        };

        DrawRectangleRec(popupBox, DARKGRAY);
        DrawRectangleLines(popupX, popupY, popupWidth, popupHeight, WHITE);

        const char* popupText = "Do you really want to close the game?";
        int popupFontSize = 24;

        int popupTextX = screenWidth / 2 - MeasureText(popupText, popupFontSize) / 2;
        int popupTextY = popupY + 50;

        DrawText(popupText, popupTextX, popupTextY, popupFontSize, WHITE);

        const char* quitText = "Quit Game";
        const char* cancelText = "Cancel";

        int buttonFontSize = 24;

        int quitWidth = MeasureText(quitText, buttonFontSize);
        int cancelWidth = MeasureText(cancelText, buttonFontSize);

        int quitX = popupX + 100;
        int cancelX = popupX + popupWidth - 100 - cancelWidth;
        int buttonY = popupY + 150;

        Rectangle quitButton = {
            (float)quitX,
            (float)buttonY,
            (float)quitWidth,
            (float)buttonFontSize
        };

        Rectangle cancelButton = {
            (float)cancelX,
            (float)buttonY,
            (float)cancelWidth,
            (float)buttonFontSize
        };

        DrawText(quitText, quitX, buttonY, buttonFontSize, WHITE);
        DrawText(cancelText, cancelX, buttonY, buttonFontSize, WHITE);

        if (CheckCollisionPointRec(mousePosition, quitButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            shouldCloseGame = true;
        }

        if (CheckCollisionPointRec(mousePosition, cancelButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            showQuitPopup = false;
        }
    }

    return TITLE;
}




GameScreen characterSelectScreen(int& selectedCharacter)
{ 
    // vector2 basically gets (x, y) cords
    Vector2 mousePosition = GetMousePosition();

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    //placeholder characters
    const char* characterNames[3] = {
        "Warrior",
        "Mage",
        "Rogue"
    };

    //placeholder stats 
    const char* characterStats[3] = {
        "HP: 120  Attack: 12  Speed: 5",
        "HP: 80   Attack: 18  Speed: 4",
        "HP: 90   Attack: 10  Speed: 8"
    };

    //placeholder descriptions 
    const char* characterDescriptions[3] = {
        "A strong melee fighter with high health.",
        "A magic user with powerful attacks but low health.",
        "A fast fighter that relies on speed and movement."
    };

    const char* titleText = "Character Select";
    int titleFontSize = 50;

    int titleX = screenWidth / 2 - MeasureText(titleText, titleFontSize) / 2;
    int titleY = 50;

    DrawText(titleText, titleX, titleY, titleFontSize, WHITE);

    // Character preview box
    int characterBoxWidth = 250;
    int characterBoxHeight = 300;

    int characterBoxX = screenWidth / 2 - characterBoxWidth / 2;
    int characterBoxY = screenHeight / 2 - characterBoxHeight / 2 - 40;

    DrawRectangleLines(characterBoxX, characterBoxY, characterBoxWidth, characterBoxHeight, WHITE);

    // Character name
    int characterNameFontSize = 30;
    int characterNameX = screenWidth / 2 - MeasureText(characterNames[selectedCharacter], characterNameFontSize) / 2;
    int characterNameY = characterBoxY + 30;

    DrawText(characterNames[selectedCharacter], characterNameX, characterNameY, characterNameFontSize, WHITE);

    // Placeholder character shape
    int shapeCenterX = screenWidth / 2;
    int shapeCenterY = characterBoxY + 170;

    if (selectedCharacter == 0)
    {
        // Warrior = square
        DrawRectangle(shapeCenterX - 40, shapeCenterY - 40, 80, 80, WHITE);
    }
    else if (selectedCharacter == 1)
    {
        // Mage = circle
        DrawCircle(shapeCenterX, shapeCenterY, 45, WHITE);
    }
    else if (selectedCharacter == 2)
    {
        // Rogue = triangle
        Vector2 point1 = { (float)shapeCenterX, (float)(shapeCenterY - 50) };
        Vector2 point2 = { (float)(shapeCenterX - 50), (float)(shapeCenterY + 50) };
        Vector2 point3 = { (float)(shapeCenterX + 50), (float)(shapeCenterY + 50) };

        DrawTriangle(point1, point2, point3, WHITE);
    }

    // Left and right arrows buttons 
    const char* leftArrowText = "<";
    const char* rightArrowText = ">";

    int arrowFontSize = 60;

    int leftArrowX = characterBoxX - 90;
    int rightArrowX = characterBoxX + characterBoxWidth + 60;
    int arrowY = characterBoxY + characterBoxHeight / 2 - arrowFontSize / 2;

    int leftArrowWidth = MeasureText(leftArrowText, arrowFontSize);
    int rightArrowWidth = MeasureText(rightArrowText, arrowFontSize);

    Rectangle leftArrowButton = {
        (float)leftArrowX,
        (float)arrowY,
        (float)leftArrowWidth,
        (float)arrowFontSize
    };

    Rectangle rightArrowButton = {
        (float)rightArrowX,
        (float)arrowY,
        (float)rightArrowWidth,
        (float)arrowFontSize
    };

    DrawText(leftArrowText, leftArrowX, arrowY, arrowFontSize, WHITE);
    DrawText(rightArrowText, rightArrowX, arrowY, arrowFontSize, WHITE);

    if (CheckCollisionPointRec(mousePosition, leftArrowButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        selectedCharacter--;

        if (selectedCharacter < 0)
        {
            selectedCharacter = 2;
        }
    }

    if (CheckCollisionPointRec(mousePosition, rightArrowButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        selectedCharacter++;

        if (selectedCharacter > 2)
        {
            selectedCharacter = 0;
        }
    }

    // Description and stats box
    int statsBoxWidth = screenWidth - 200;
    int statsBoxHeight = 130;

    int statsBoxX = screenWidth / 2 - statsBoxWidth / 2;
    int statsBoxY = characterBoxY + characterBoxHeight + 40;

    DrawRectangleLines(statsBoxX, statsBoxY, statsBoxWidth, statsBoxHeight, WHITE);

    DrawText(characterStats[selectedCharacter], statsBoxX + 20, statsBoxY + 25, 25, WHITE);
    DrawText(characterDescriptions[selectedCharacter], statsBoxX + 20, statsBoxY + 70, 22, WHITE);

    // Confirm button
    const char* confirmText = "Confirm";
    int confirmFontSize = 30;

    int confirmWidth = MeasureText(confirmText, confirmFontSize);
    int confirmHeight = confirmFontSize;

    int confirmX = screenWidth / 2 - confirmWidth / 2;
    int confirmY = statsBoxY + statsBoxHeight + 30;

    Rectangle confirmButton = {
        (float)(confirmX - 15),
        (float)(confirmY - 10),
        (float)(confirmWidth + 30),
        (float)(confirmHeight + 20)
    };

    DrawRectangleLines(confirmButton.x, confirmButton.y, confirmButton.width, confirmButton.height, WHITE);
    DrawText(confirmText, confirmX, confirmY, confirmFontSize, WHITE);

    if (CheckCollisionPointRec(mousePosition, confirmButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return GAMEPLAY;
    }
    return CHARACTER_SELECT;
}



GameScreen gameplayScreen(int selectedCharacter)
{
    // make it so the player spawns in the middle of the screen every time 
    static Vector2 playerPosition = {
        (float)GetScreenWidth() / 2,
        (float)GetScreenHeight() / 2
    };

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    float playerSize = 40.0f;
    float playerSpeed = 250.0f;
    float deltaTime = GetFrameTime(); //used so the player moves at a consistent time 

    //declaring the movement keys wasd
    if (IsKeyDown(KEY_W))
    {
        playerPosition.y -= playerSpeed * deltaTime;
    }

    if (IsKeyDown(KEY_S))
    {
        playerPosition.y += playerSpeed * deltaTime;
    }

    if (IsKeyDown(KEY_A))
    {
        playerPosition.x -= playerSpeed * deltaTime;
    }

    if (IsKeyDown(KEY_D))
    {
        playerPosition.x += playerSpeed * deltaTime;
    }

    // Keep player inside the window
    if (playerPosition.x < 0)
    {
        playerPosition.x = 0;
    }

    if (playerPosition.y < 0)
    {
        playerPosition.y = 0;
    }

    if (playerPosition.x + playerSize > screenWidth)
    {
        playerPosition.x = screenWidth - playerSize;
    }

    if (playerPosition.y + playerSize > screenHeight)
    {
        playerPosition.y = screenHeight - playerSize;
    }

    DrawText("Gameplay Screen", 20, 20, 30, WHITE);

    if (selectedCharacter == 0)
    {
        // Warrior = square
        DrawRectangle(
            (int)playerPosition.x,
            (int)playerPosition.y,
            (int)playerSize,
            (int)playerSize,
            WHITE
        );
    }
    else if (selectedCharacter == 1)
    {
        // Mage = circle
        DrawCircle(
            (int)(playerPosition.x + playerSize / 2),
            (int)(playerPosition.y + playerSize / 2),
            playerSize / 2,
            WHITE
        );
    }
    else if (selectedCharacter == 2)
    {
        // Rogue = triangle
        Vector2 point1 = {
            playerPosition.x + playerSize / 2,
            playerPosition.y
        };

        Vector2 point2 = {
            playerPosition.x,
            playerPosition.y + playerSize
        };

        Vector2 point3 = {
            playerPosition.x + playerSize,
            playerPosition.y + playerSize
        };

        DrawTriangle(point1, point2, point3, WHITE);
    }

    return GAMEPLAY;
}



GameScreen settingsScreen()
{
    DrawText("Settings Screen", 300, 300, 60, WHITE);

    return SETTINGS;
}



int main()
{
    // Allows the player to resize the window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    // Initialization
    InitWindow(1280, 720, "Roguelike-2D");

    // Makes it so ESC is not an exit key by default
    SetExitKey(0);

    SetTargetFPS(60);

    bool showQuitPopup = false;
    bool shouldCloseGame = false;
    int selectedCharacter = 0;

    GameScreen currentScreen = TITLE;

    // Main game loop
    while (!WindowShouldClose() && !shouldCloseGame)
    {
        // Handles ESC key behavior
        if (IsKeyPressed(KEY_ESCAPE))
        {
            if (currentScreen == TITLE)
            {
                showQuitPopup = true;
            }
            else if (currentScreen == CHARACTER_SELECT || currentScreen == SETTINGS)
            {
                currentScreen = TITLE;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (currentScreen == TITLE)
        {
            currentScreen = titleScreen(showQuitPopup, shouldCloseGame);
        }
        else if (currentScreen == CHARACTER_SELECT)
        {
            currentScreen = characterSelectScreen(selectedCharacter);
        }
        else if (currentScreen == SETTINGS)
        {
            currentScreen = settingsScreen();
        }
        else if (currentScreen == GAMEPLAY)
        {
            currentScreen = gameplayScreen(selectedCharacter);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}