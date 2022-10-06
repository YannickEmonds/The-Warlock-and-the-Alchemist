#include "menu.h"
#include <iostream>


Option::Option(std::string _name, std::shared_ptr<Menu> _menu) 
    : name(_name), menu(_menu) {}


Option::Option(const Option& op)
    : name(op.name), menu(op.menu) {}


Option& Option::operator=(const Option& op)
{
    name = op.name;
    menu = op.menu;
    return *this;
}

Option::~Option() {}

bool Option::operator==(const Option& other) const
{
    return name == other.name && menu == other.menu;
}

std::string Option::getName() const
{
    return name;
}


std::shared_ptr<Menu> Option::getMenu() const
{
    return menu;
}


void Option::performAction() const {}


MenuSwitchOption::MenuSwitchOption(const std::string& _name,
                                   std::shared_ptr<Menu> _menu,
                                   const std::string& _destMenuName)
    : Option(_name, _menu), destMenuName(_destMenuName) {}


MenuSwitchOption& MenuSwitchOption::operator=(const MenuSwitchOption& op)
{
    name = op.name;
    menu = op.menu;
    destMenuName = op.destMenuName;
    return *this;
}


void MenuSwitchOption::performAction() const
{
    auto destMenu = menu->findReachableMenu(destMenuName);
    destMenu->show();
}


Menu::Menu(std::string _name) : name(_name) {}


Menu::Menu(std::string _name,
         std::vector<Option> _options, 
         std::map<std::string, std::shared_ptr<Menu>> _reachableMenus)
    : name(_name), options(_options), reachableMenus(_reachableMenus) {}


void Menu::createMenuText(std::string _text)
{
    menuText = _text;
}


void Menu::show() const
{
    std::cout << menuText << '\n';
    for (std::size_t i=0; i<options.size(); ++i)
    {
        std::cout << "  " << i+1 << ") " << options[i].getName() << '\n';
    }
}


std::string Menu::getName() const
{
    return name;
}


void Menu::setOptions(const std::vector<Option>& newOptions)
{
    options = newOptions;
}


std::vector<Option> Menu::getOptions() const
{
    return options;
}


void Menu::setReachableMenus(std::map<std::string, std::shared_ptr<Menu>> menus)
{
    reachableMenus = menus;
}


std::map<std::string, std::shared_ptr<Menu>> Menu::getReachableMenus() const
{
    return reachableMenus;
}


std::shared_ptr<Menu> Menu::findReachableMenu(std::string menuName) const
{
    auto menuToFind = reachableMenus.find(menuName);
    if (menuToFind != reachableMenus.end())
        return menuToFind->second;
    else
        return nullptr;
}
