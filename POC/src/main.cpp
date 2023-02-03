#include "Game/Window.hpp"
#include "Game/GamePlay/GamePlay.hpp"

void luncher()
{
    Window window;

    // Menu menu(window);
    // menu.init();

    GamePlay gamePlay(window);
    gamePlay.init();

    window.getWindow().setActive(false);
    window.getWindow().setActive(true);

    while (window.getWindow().isOpen()) {
        switch (window.getScene()) {
            case sceneEnum::MENU:
                // window.getWindow().setActive(false);
                // window.getWindow().setActive(true);
                // menu.loop();
                break;
            case sceneEnum::GAME:
                window.getWindow().setActive(false);
                window.getWindow().setActive(true);
                gamePlay.loop();
                break;
            case sceneEnum::END:
                window.getWindow().setActive(false);
                window.getWindow().setActive(true);
                break;
        }
    }
}

int main()
{
    try {
        luncher();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}