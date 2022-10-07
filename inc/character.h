#pragma once

#include <vector>
#include <string>
#include "action.h"


enum class Race
{
    human, elf, dwarf, orc
};


struct CharacterStats
{
    unsigned strength;
    unsigned dexterity;
    unsigned agility;
    unsigned initiative;
};


class Character
{
private:
    const std::string name;
    const Race race;
    unsigned healthPoints;
    unsigned stamina;
    CharacterStats stats;
    std::vector<Action> actions;
public:
    std::string getName() const;
};


class Mage : private Character
{
private:
    unsigned mana;
};


class Warlock : private Mage
{
public:
    Warlock(std::string name, Race race);
};
