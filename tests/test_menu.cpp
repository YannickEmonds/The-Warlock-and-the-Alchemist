#include "menu.h"
#include <gtest/gtest.h>


class OptionTest : public ::testing::Test
{
protected:
    Option option;

public:
    OptionTest() : option("test_option", 
                          std::make_shared<Menu>(Menu("test_menu"))) {} 
};


TEST_F(OptionTest, TestOption)
{
    EXPECT_EQ(option.getName(), "test_option");
}


class MenuTest : public ::testing::Test
{
protected:
    Menu menu;

public:
    MenuTest() : menu("test_menu") {}
};

TEST_F(MenuTest, TestSimpleMenu)
{
    EXPECT_EQ(menu.getName(), "test_menu");
}

TEST_F(MenuTest, SetParameters)
{
    Option option("Quit", std::make_shared<Menu>(menu));
    std::vector<Option> optionVec {option};
    auto nextMenu = std::make_shared<Menu>(Menu("Next"));
    auto quitMenu = std::make_shared<Menu>(Menu("Quit"));
    std::map<std::string, std::shared_ptr<Menu>> reachableMenus = {
        {"Next", nextMenu},
        {"Quit", quitMenu}};
    menu.setOptions(optionVec);
    menu.setReachableMenus(reachableMenus);

    EXPECT_EQ(menu.getOptions(), optionVec);
    EXPECT_EQ(menu.getReachableMenus(), reachableMenus);

    EXPECT_EQ(menu.findReachableMenu("Quit"), quitMenu);
    EXPECT_EQ(menu.findReachableMenu("Test"), nullptr);
}
