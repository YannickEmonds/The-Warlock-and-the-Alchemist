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

TEST_F(MenuTest, TestMenuSwitchOption)
{
    auto nextMenu = std::make_shared<Menu>(Menu("Next"));
    nextMenu->createMenuText("This is the next menu.");
    std::map<std::string, std::shared_ptr<Menu>> reachableMenus = {
        {"Next", nextMenu}
    };

    MenuSwitchOption option("toNext", std::make_shared<Menu>(menu), "Next");
    std::vector<Option> optionVec {option};

    menu.setReachableMenus(reachableMenus);
    menu.setOptions(optionVec);

    EXPECT_EQ(menu.getReachableMenus(), reachableMenus);
    EXPECT_EQ(menu.findReachableMenu("Next"), nextMenu);
    EXPECT_EQ(option.getMenu().get(), &menu);
    EXPECT_EQ(option.getMenu()->getReachableMenus(), menu.getReachableMenus());

    menu.show();
    // option.performAction();
}