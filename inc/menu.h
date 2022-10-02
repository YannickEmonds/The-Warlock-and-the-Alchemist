#include <vector>
#include <string>
#include <memory>
#include <map>


class Option
{
private:
    const std::string name;
    const std::shared_ptr<Menu> menu;

public:
    Option(std::shared_ptr<Menu> _menu);

    std::string getName() const;
    void performAction() const;
};


class Menu
{
private:
    const std::string name;
    std::vector<Option> options;
    std::map<std::string, std::shared_ptr<Menu>> reachableMenus;
public:
    Menu(std::vector<Option> _options, 
         std::map<std::string, Menu> _reachableMenus);

    void show();
    void close();
    std::vector<Option> getOptions() const;
    std::map<std::string, std::shared_ptr<Menu>> getReachableMenus() const;
};
