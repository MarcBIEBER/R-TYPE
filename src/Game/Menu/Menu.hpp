/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-rtype-arnaud.issoire
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "../Window.hpp"

enum MenuScene {
    MAIN,
    SINGLEPLAYER,
    MULTIPLAYER,
    CREATESERVER,
    JOINSERVER,
    QUIT
};

enum ClockMenu {
    PARA_ONE,
    PARA_TWO,
    PARA_THREE,
    PARA_FOUR,
    CLOCK_NB
};

#define GETSYSCOMP(sys, ennemyID, compType) sys->getManager().getEntity(ennemyID).get()->getComponent<compType>()
#define GETSYSCONS(sys, type) sys->getManager().getEntity(type).get()->getComponent<InputKey>()


class Menu {
    public:
        Menu(client &client, Window &window);
        ~Menu();
        void loop();
        void init();
        void initMain();
        void initSingleplayer();
        void initMultiplayer();
        void initCreateServer();
        void initJoinServer();

        void initAsset();

        /**
         * @brief Set the Scene object
         * 
         * @param scene 
         */
        void setScene(MenuScene scene) { _scene = scene; }

        void getEventMain();
        void getEventSingleplayer();
        void getEventMultiplayer();
        void getEventCreateServer();
        void getEventJoinServer();

        void handleParallax(System *sys);

        void connectClient(std::string host, std::string port);

        void handleConsole(sf::Event event);

        void createServerBox();

        void loopMain(System &system);
        void loopSingleplayer(System &system);
        void loopMultiplayer(System &system);
        void loopCreateServer(System &system);
        void loopJoinServer(System &system);

    protected:
    private:
        MenuScene _scene;
        Window *_window;
        System *_systemMain;
        System *_systemSingleplayer;
        System *_systemMultiplayer;
        System *_systemCreateServer;
        System *_systemJoinServer;

        std::string _host = "127.0.0.1";
        std::string _port = "4242";

        std::vector<sf::Clock> _clocks;
        std::vector<sf::Time> _times;

        bool isTypingHost;
        bool isTypingPort;
        bool _volume_set = true;
        int _currentClick = 0;
        int _nbServer;
};

#endif /* !MENU_HPP_ */
