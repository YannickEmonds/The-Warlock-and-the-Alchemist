#include <vector>
#include <string>


class Option
{
private:
    const std::string name;

public:
    Option();

    std::string getName() const;

};


class Menu
{
private:
    std::vector<Option> options;
public:
    Menu();

    void show();
    void close();
    void waitForInput();
};
