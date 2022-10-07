#pragma once

#include <map>
#include <memory>

#include "menu.h"


class Game
{
private:
    std::map<std::string, std::shared_ptr<Menu>> menuMap;
    bool gameActive;
public:
    Game();

    void play();
};
