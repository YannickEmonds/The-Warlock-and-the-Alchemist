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
    std::shared_ptr<Menu> menu;

public:
    MenuTest() : menu(std::make_shared<Menu>(Menu("test_menu"))) {}
};

TEST_F(MenuTest, TestSimpleMenu)
{
    EXPECT_EQ(menu->getName(), "test_menu");
}

TEST_F(MenuTest, SetParameters)
{
    Option option("Quit", menu);
    std::vector<Option> optionVec {option};
    auto nextMenu = std::make_shared<Menu>(Menu("Next"));
    auto quitMenu = std::make_shared<Menu>(Menu("Quit"));
    std::map<std::string, std::shared_ptr<Menu>> reachableMenus = {
        {"Next", nextMenu},
        {"Quit", quitMenu}};
    menu->setOptions(optionVec);
    menu->setReachableMenus(reachableMenus);

    EXPECT_EQ(menu->getOptions(), optionVec);
    EXPECT_EQ(menu->getReachableMenus(), reachableMenus);

    EXPECT_EQ(menu->findReachableMenu("Quit"), quitMenu);
    EXPECT_EQ(menu->findReachableMenu("Test"), nullptr);
}

TEST_F(MenuTest, TestMenuSwitchOption)
{
    auto nextMenu = std::make_shared<Menu>(Menu("Next"));
    nextMenu->createMenuText("This is the next menu.");
    std::map<std::string, std::shared_ptr<Menu>> reachableMenus = {
        {"Next", nextMenu}
    };

    MenuSwitchOption option("toNext", menu, "Next");
    std::vector<Option> optionVec {option};

    menu->createMenuText("*** Main Menu ***\n  Choose an option:\n");
    menu->setReachableMenus(reachableMenus);
    menu->setOptions(optionVec);

    EXPECT_EQ(menu->getReachableMenus(), reachableMenus);
    EXPECT_EQ(menu->findReachableMenu("Next"), nextMenu);
    EXPECT_EQ(option.getMenu().get(), menu.get());
    EXPECT_EQ(option.getMenu()->getReachableMenus(), menu->getReachableMenus());

    testing::internal::CaptureStdout();
    menu->show();
    std::string output1 = testing::internal::GetCapturedStdout();

    testing::internal::CaptureStdout();
    option.performAction();
    std::string output2 = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output1, "*** Main Menu ***\n  Choose an option:\n\n  1) toNext\n");
    EXPECT_EQ(output2, "This is the next menu.\n");
}
