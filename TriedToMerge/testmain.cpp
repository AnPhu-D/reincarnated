#include <iostream>
#include <vector>
#include <stdio.h>
#include "./Text.h"
#include "./Button.h"
#include "./GameManager.h"
#include "./Screen.h"
#include "./Image.h"
#include "./marketImageArray.h"
#include "./adventureImageArray.h"
#include "./guildImageArray.h"
#include "./DisplayHero.h"
#include "./SelectTeam.h"
#include "./BattleSession.h"

GameManager setup()
{
    GameManager gameManager = GameManager(120, 30);

    // start Screen
    Screen *startScreen = new Screen(&gameManager);
    Button *startButton = new Button(&gameManager, 58, 15, "Start", true);
    Text *startText = new Text(&gameManager, 60, 6, "R'PG");
    startScreen->addEventComponents(startButton);
    startScreen->currentSelectedEvent = 0;
    startScreen->addComponent(startText);
    gameManager.addScreen(startScreen);
    // town Screen
    Screen *townScreen = new Screen(&gameManager);
    Text *townText = new Text(&gameManager, 58, 3, "Town");
    Button *marketButton = new Button(&gameManager, 12, 20, "Market", true);
    Button *guildButton = new Button(&gameManager, 58, 20, "Guild", false);
    Button *adventureButton = new Button(&gameManager, 95, 20, "Advendture", false);
    Image *marketImage = new Image(&gameManager, 10, 6, marketImageArray().ImageArray);
    Image *guildtImage = new Image(&gameManager, 58, 7, guildImageArray().ImageArray);
    Image *adventuretImage = new Image(&gameManager, 98, 6, adventureImageArray().ImageArray);
    townScreen->addEventComponents(marketButton);
    townScreen->addEventComponents(guildButton);
    townScreen->addEventComponents(adventureButton);
    townScreen->currentSelectedEvent = 0;
    townScreen->addComponent(marketImage);
    townScreen->addComponent(guildtImage);
    townScreen->addComponent(adventuretImage);
    townScreen->addComponent(townText);
    gameManager.addScreen(townScreen);

    Button *backtoTown = new Button(&gameManager, 2, 2, "Back To Town", false);
    // adventure screen
    Screen *adventrueScreen = new Screen(&gameManager);
    Button *level1Button = new Button(&gameManager, 3, 20, "Level 1", true);
    Button *level2Button = new Button(&gameManager, 30, 20, "Level 2", false);
    Button *level3Button = new Button(&gameManager, 57, 20, "Level 3", false);
    Button *level4Button = new Button(&gameManager, 84, 20, "Level 4", false);
    Button *level5Button = new Button(&gameManager, 111, 20, "Level 5", false);
    adventrueScreen->addEventComponents(level1Button);
    adventrueScreen->addEventComponents(level2Button);
    adventrueScreen->addEventComponents(level3Button);
    adventrueScreen->addEventComponents(level4Button);
    adventrueScreen->addEventComponents(level5Button);
    adventrueScreen->addEventComponents(backtoTown);
    adventrueScreen->currentSelectedEvent = 0;
    gameManager.addScreen(adventrueScreen);

    // guild screen
    backtoTown = new Button(&gameManager, 2, 2, "Back To Town", false);
    Screen *GuildScreen = new Screen(&gameManager);
    DisplayHero *displayHero = new DisplayHero(&gameManager);
    GuildScreen->addEventComponents(displayHero);
    GuildScreen->addEventComponents(backtoTown);
    gameManager.addScreen(GuildScreen);

    // // select Hero
    backtoTown = new Button(&gameManager, 2, 2, "Back To Town", false);
    Screen *SelectHeroScreen = new Screen(&gameManager);
    SelectTeam *selectTeam = new SelectTeam(&gameManager, 2, 2);
    SelectHeroScreen->addEventComponents(selectTeam);
    SelectHeroScreen->addEventComponents(backtoTown);
    gameManager.addScreen(SelectHeroScreen);

    // battle session
    Screen *battleScreen = new Screen(&gameManager);
    BattleSession *battleSession = new BattleSession(&gameManager);
    battleScreen->addEventComponents(battleSession);
    gameManager.addScreen(battleScreen);
    // Win Screen
    backtoTown = new Button(&gameManager, 2, 2, "Back To Town", false);
    Screen *winScreen = new Screen(&gameManager);
    winScreen->addEventComponents(backtoTown);
    Text *youWin = new Text(&gameManager, 50, 10, "Battle Finished");
    winScreen->addComponent(youWin);
    gameManager.addScreen(winScreen);
    // Lose Screen
    backtoTown = new Button(&gameManager, 2, 2, "Back To Town", false);
    Screen *loseScreen = new Screen(&gameManager);
    loseScreen->addEventComponents(backtoTown);
    Text *youLose = new Text(&gameManager, 50, 10, "You Lose");
    loseScreen->addComponent(youLose);
    gameManager.addScreen(loseScreen);

    return gameManager;
}

int main()
{
    GameManager gameManager = setup();
    while (true)
    {
        if (gameManager.keydown())
        {
            char cha = getchar();
            if ((int)cha == 126)
                break;
            gameManager.keyEvent(cha);
        }
        gameManager.render();
    }
}
