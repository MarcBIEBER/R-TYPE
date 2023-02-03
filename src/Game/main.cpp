/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-rtype-arnaud.issoire
** File description:
** Main
*/

#include "Window.hpp"
#include "Menu/Menu.hpp"
#include "GamePlay/GamePlay.hpp"
#include "EndScreen/End.hpp"

/**
 * @brief Thread use to load all asset who are not needed for the menu (better lunch time)
 * 
 */
void threadInitLuncher(GamePlay *gamePlay, End *end)
{
    gamePlay->init();
    end->init();
}

/**
 * @brief lunch the game: init all window, scnenes, etc...
 * 
 */
void luncher()
{
    std::thread initThread;
    client client;
    Window window(client);

    Menu menu(client, window);
    menu.init();


    GamePlay gamePlay(client, window);
    End end(client, window);

    //thread to init the gamePlay and end scene:
    initThread = std::thread(threadInitLuncher, &gamePlay, &end);

    window.getWindow().setActive(false);
    window.getWindow().setActive(true);

    bool tmp = false;
    while (window.getWindow().isOpen()) {
        switch (window.getScene()) {
            case sceneEnum::MENU:
                window.getWindow().setActive(false);
                window.getWindow().setActive(true);
                menu.loop();
                break;
            case sceneEnum::GAME:
                if (tmp == false) {
                    window.getMusicShip()->setVolume(10);
                    window.getMusic()->setVolume(2.f); 
                    tmp = true;
                }
                window.getWindow().setActive(false);
                window.getWindow().setActive(true);
                gamePlay.loop();
                break;
            case sceneEnum::END:
                window.getWindow().setActive(false);
                window.getWindow().setActive(true);
                end.loop();
                break;
        }
    }
    if (initThread.joinable())
        initThread.join();
}

int main()
{
    try {
        luncher();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}