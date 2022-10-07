#include <iostream>
#include "game.h"


Game::Game()
{
    auto mainMenu = std::make_shared<Menu>("mainMenu");
    auto quickFightMenu = std::make_shared<Menu>("quickFight");

    mainMenu->createMenuText("*** Main Menu ***\n");
    quickFightMenu->createMenuText("*** Quick Fight ***\n");

    MenuSwitchOption switchToQuickFight("toQuickFight", mainMenu, "quickFight");
    std::vector<Option> mainMenuOptions = {switchToQuickFight};

    mainMenu->setOptions(mainMenuOptions);
    menuMap = {{"mainMenu", mainMenu}, {"quickFight", quickFightMenu}};
    gameActive = true;
}


void Game::play()
{
    auto activeMenu = menuMap["mainMenu"];
    std::string userInput;
    while (gameActive)
    {
        activeMenu->show();
        std::cin >> userInput;
        if (userInput == "1")
        {
            activeMenu->getOptions()[0].performAction();
        }
        else
        {
            gameActive = false;
        }
    }

    std::cout << "Quit game.\n";
}
