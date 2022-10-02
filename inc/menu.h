#include <vector>
#include <string>
#include <memory>
#include <map>


class Option
{
protected:
    const std::string name;
    const std::shared_ptr<Menu> menu;

public:
    Option(std::string name, std::shared_ptr<Menu> _menu);

    std::string getName() const;
    virtual void performAction() const;
};


class MenuSwitchOption : public Option
{
private:
    const std::string destMenuName;
public:
    MenuSwitchOption(std::string _name, std::shared_ptr<Menu> _menu, 
                     std::string _destMenuName);

    void performAction() const override;
};


class ParameterSetOption : Option
{
public:
    ParameterSetOption();

    void performAction() const override;
};


class Menu
{
private:
    const std::string name;
    std::string menuText;
    std::vector<Option> options;
    std::map<std::string, std::shared_ptr<Menu>> reachableMenus;
public:
    Menu(std::string _name,
         std::vector<Option> _options, 
         std::map<std::string, std::shared_ptr<Menu>> _reachableMenus);

    void createMenuText(std::string _text);
    void show() const;
    void close();
    std::vector<Option> getOptions() const;
    std::map<std::string, std::shared_ptr<Menu>> getReachableMenus() const;
    std::shared_ptr<Menu> findReachableMenu(std::string menuName) const;
};
