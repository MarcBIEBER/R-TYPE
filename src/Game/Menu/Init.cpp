#include "Menu.hpp"

/**
 * @brief Init the Main scene of the menu
 * 
 */
void Menu::initMain()
{
    EntityManager &manager = _systemMain->getManager();
    Entity *background = new Entity();

    Entity *para1 = new Entity();
    Entity *para2 = new Entity();
    Entity *para3 = new Entity();
    Entity *para4 = new Entity();


    // Entity *play = new Entity();
    Entity *playMulti = new Entity();
    Entity *quit = new Entity();
    Entity *buttonVolume = new Entity();
    Entity *title = new Entity();
    Entity *blueCross = new Entity();

    background->addComponent<Sprite>("menubg", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());

    para1->addComponent<Parallax>("para1_1", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());
    para2->addComponent<Parallax>("para1_2", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());
    para3->addComponent<Parallax>("para1_3", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());
    para4->addComponent<Parallax>("para1_4", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());

    // play->addComponent<Button>("buttonPlay", sf::Vector2f(400, 200), sf::Vector2f(1, 1), _window->getWindow());
    playMulti->addComponent<Button>("buttonPlay", sf::Vector2f(400, 400), sf::Vector2f(1, 1), _window->getWindow());
    quit->addComponent<Button>("buttonQuit", sf::Vector2f(400, 800), sf::Vector2f(1, 1), _window->getWindow());
    buttonVolume->addComponent<Button>("buttonVolume", sf::Vector2f(50, 50), sf::Vector2f(0.3, 0.3), _window->getWindow());
    title->addComponent<Text>("title_screen", "R-Type", _window->getWindow());

    blueCross->addComponent<Button>("blueCross", sf::Vector2f(50, 50), sf::Vector2f(0.3, 0.3), _window->getWindow());

    manager.addEntity("menubg", background);
    manager.addEntity("para1_1", para1);
    manager.addEntity("para1_2", para2);
    manager.addEntity("para1_3", para3);
    manager.addEntity("para1_4", para4);

    // manager.addEntity("playButton", play);
    manager.addEntity("playMulti", playMulti);
    manager.addEntity("quitButton", quit);
    manager.addEntity("buttonVolume", buttonVolume);
    manager.addEntityEmplace(3, "title_screen", title);

    manager.addEntity("blueCross", blueCross);

    //set the origine in center of the sprite
    manager.getEntity("title_screen")->getComponent<Text>().setFont("font");
    manager.getEntity("title_screen")->getComponent<Text>().setFontSize(200);
    manager.getEntity("title_screen")->getComponent<Text>().setText("R-Type");
    manager.getEntity("title_screen")->getComponent<Text>().setStyle(sf::Text::Bold);
    // manager.getEntity("title_screen")->getComponent<Text>().setOrigin(manager.getEntity("title")->getComponent<Text>().getText().getGlobalBounds().width / 2, manager.getEntity("title")->getComponent<Text>().getText().getGlobalBounds().height / 2);
    manager.getEntity("title_screen")->getComponent<Text>().setPosition(1920 / 2 - 310, 120);
    manager.getEntity("title_screen")->getComponent<Text>().getText()->setOutlineThickness(10);
    manager.getEntity("title_screen")->getComponent<Text>().getText()->setOutlineColor(sf::Color::Black);


    manager.getEntity("para1_1")->getComponent<Parallax>().setScale(10, 10);
    manager.getEntity("para1_2")->getComponent<Parallax>().setScale(10, 10);
    manager.getEntity("para1_3")->getComponent<Parallax>().setScale(10, 10);
    manager.getEntity("para1_4")->getComponent<Parallax>().setScale(10, 10);

    // manager.getEntity("playButton")->getComponent<Button>().setScale(1.5, 1.5);
    // manager.getEntity("playButton")->getComponent<Button>().setPosition((1920 / 2) - (play->getComponent<Button>().getSize().x / 2), 250);
    manager.getEntity("playMulti")->getComponent<Button>().setOrigin(manager.getEntity("playMulti")->getComponent<Button>().getSize().x / 2, manager.getEntity("playMulti")->getComponent<Button>().getSize().y / 2);
    manager.getEntity("playMulti")->getComponent<Button>().setScale(1.5, 1.5);
    manager.getEntity("playMulti")->getComponent<Button>().setPosition(1920 / 2, 500);

    manager.getEntity("quitButton")->getComponent<Button>().setOrigin(quit->getComponent<Button>().getSize().x / 2, quit->getComponent<Button>().getSize().y / 2);
    manager.getEntity("quitButton")->getComponent<Button>().setScale(1.5, 1.5);
    manager.getEntity("quitButton")->getComponent<Button>().setPosition(1920 / 2, 700);

    manager.getEntity("buttonVolume")->getComponent<Button>().setScale(0.6, 0.6);
    manager.getEntity("buttonVolume")->getComponent<Button>().setPosition(30, 30);

    manager.getEntity("blueCross")->getComponent<Button>().setDrawable(false);
    manager.getEntity("blueCross")->getComponent<Button>().setPosition(42, 42);
    manager.getEntity("blueCross")->getComponent<Button>().setScale(0.2, 0.2);
}

/**
 * @brief Init the Singleplayer scene of the menu
 * 
 */
void Menu::initSingleplayer()
{
    EntityManager &manager = _systemSingleplayer->getManager();
}

/**
 * @brief Init the Multiplayer scene of the menu
 * 
 */
void Menu::initMultiplayer()
{

    //Read in LeaderBoard file
    std::ifstream file("LeaderBoard.txt");
    std::string str;
    std::vector<std::string> leaderboard;
    while (std::getline(file, str))
    {
        leaderboard.push_back(str);
    }
    file.close();

    EntityManager &manager = _systemMultiplayer->getManager();

    Entity *background = new Entity();
    Entity *backgroundClear = new Entity();
    Entity *join = new Entity();
    Entity *create = new Entity();
    Entity *back = new Entity();

    Entity *para1 = new Entity();
    Entity *para2 = new Entity();
    Entity *para3 = new Entity();
    Entity *para4 = new Entity();

    Entity *bestScore = new Entity();
    Entity *bestBossKilled = new Entity();

    para1->addComponent<Parallax>("para1_1", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());
    para2->addComponent<Parallax>("para1_2", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());
    para3->addComponent<Parallax>("para1_3", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());
    para4->addComponent<Parallax>("para1_4", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());
    
    
    backgroundClear->addComponent<Sprite>("menubgclear", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());
    background->addComponent<Sprite>("menubg", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());
    join->addComponent<Button>("continuebutton", sf::Vector2f(1920 / 2 - 500, 1080 - 300), sf::Vector2f(1.5, 1.5), _window->getWindow());
    create->addComponent<Button>("buttonCreate", sf::Vector2f(1920 / 2, 1080 - 300), sf::Vector2f(1.5, 1.5), _window->getWindow());
    back->addComponent<Button>("buttonQuit", sf::Vector2f(1920 / 2 + 500, 1080 - 300), sf::Vector2f(1.5, 1.5), _window->getWindow());

    bestScore->addComponent<Text>("font", "Best score: ", _window->getWindow());
    bestBossKilled->addComponent<Text>("font", "Best boss killed: ", _window->getWindow());

    manager.addEntity("menubg", background);


    //Read File and add to list server
    std::ifstream file_stream("ServerList.txt");
    std::string line;
    while (std::getline(file_stream, line)) {
        if (line.empty())
            continue;
        Entity *server = new Entity();
        std::string host = line.substr(0, line.find(" "));
        std::string port = line.substr(line.find(" ") + 1, line.size());
        server->addComponent<ServerBox>("serverBox" + std::to_string(_nbServer),
                                        _window->getWindow(),
                                        host,
                                        port,
                                        _nbServer);
        _systemMultiplayer->getManager().addEntity("serverBox" + std::to_string(_nbServer), server);
        _nbServer++;
    }
    file_stream.close();

    manager.addEntity("menubgclear", backgroundClear);

    manager.addEntity("para1_1", para1);
    manager.addEntity("para1_2", para2);
    manager.addEntity("para1_3", para3);
    manager.addEntity("para1_4", para4);

    manager.addEntity("joinButton", join);
    manager.addEntity("createButton", create);
    manager.addEntity("buttonQuit", back);

    manager.addEntity("bestScore", bestScore);
    manager.addEntity("bestBossKilled", bestBossKilled);

    manager.getEntity("para1_1")->getComponent<Parallax>().setScale(10, 10);
    manager.getEntity("para1_2")->getComponent<Parallax>().setScale(10, 10);
    manager.getEntity("para1_3")->getComponent<Parallax>().setScale(10, 10);
    manager.getEntity("para1_4")->getComponent<Parallax>().setScale(10, 10);


    manager.getEntity("joinButton")->getComponent<Button>().setOrigin(join->getComponent<Button>().getSize().x / 2, join->getComponent<Button>().getSize().y / 2);
    manager.getEntity("createButton")->getComponent<Button>().setOrigin(create->getComponent<Button>().getSize().x / 2, create->getComponent<Button>().getSize().y / 2);
    manager.getEntity("buttonQuit")->getComponent<Button>().setOrigin(back->getComponent<Button>().getSize().x / 2, back->getComponent<Button>().getSize().y / 2);
    
    manager.getEntity("joinButton")->getComponent<Button>().setScale(1.5, 1.5);
    manager.getEntity("createButton")->getComponent<Button>().setScale(1.5, 1.5);
    manager.getEntity("buttonQuit")->getComponent<Button>().setScale(1.5, 1.5);

    manager.getEntity("joinButton")->getComponent<Button>().setPosition(1920 / 2 - 500, 1080 - (join->getComponent<Button>().getSize().y));
    manager.getEntity("createButton")->getComponent<Button>().setPosition(1920 / 2, 1080 - (create->getComponent<Button>().getSize().y));
    manager.getEntity("buttonQuit")->getComponent<Button>().setPosition(1920 / 2 + 500, 1080 - (back->getComponent<Button>().getSize().y));


    manager.getEntity("bestScore")->getComponent<Text>().setStyle(sf::Text::Regular);
    manager.getEntity("bestScore")->getComponent<Text>().setFont("font");
    manager.getEntity("bestScore")->getComponent<Text>().getText()->setCharacterSize(50);
    manager.getEntity("bestScore")->getComponent<Text>().getText()->setFillColor(sf::Color::White);
    manager.getEntity("bestScore")->getComponent<Text>().getText()->setOutlineColor(sf::Color::Black);
    manager.getEntity("bestScore")->getComponent<Text>().getText()->setOutlineThickness(2);
    manager.getEntity("bestScore")->getComponent<Text>().setPosition(40, 40);
    if (leaderboard[0].size() != 0)
        manager.getEntity("bestScore")->getComponent<Text>().getText()->setString("Best score: " + leaderboard[0]);
    else
        manager.getEntity("bestScore")->getComponent<Text>().getText()->setString("Best score: 0");


    manager.getEntity("bestBossKilled")->getComponent<Text>().getText()->setStyle(sf::Text::Regular);
    manager.getEntity("bestBossKilled")->getComponent<Text>().setFont("font");
    manager.getEntity("bestBossKilled")->getComponent<Text>().getText()->setCharacterSize(50);
    manager.getEntity("bestBossKilled")->getComponent<Text>().getText()->setOutlineColor(sf::Color::Black);
    manager.getEntity("bestBossKilled")->getComponent<Text>().getText()->setOutlineThickness(2);
    manager.getEntity("bestBossKilled")->getComponent<Text>().getText()->setFillColor(sf::Color::White);
    manager.getEntity("bestBossKilled")->getComponent<Text>().getText()->setPosition(40, 100);
    if (leaderboard[1].size() != 0)
        manager.getEntity("bestBossKilled")->getComponent<Text>().getText()->setString("Best boss killed: " + leaderboard[1]);
    else
        manager.getEntity("bestBossKilled")->getComponent<Text>().getText()->setString("Best boss killed: 0");
}

/**
 * @brief Init the CreateServer scene of the menu
 * 
 */
void Menu::initCreateServer()
{
    EntityManager &manager = _systemCreateServer->getManager();

    Entity *background = new Entity();
    Entity *join = new Entity();
    Entity *back = new Entity();
    Entity *host = new Entity();
    Entity *port = new Entity();

    background->addComponent<Sprite>("menubg", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());
    join->addComponent<Button>("buttonPlay", sf::Vector2f(400, 200), sf::Vector2f(1, 1), _window->getWindow());
    back->addComponent<Button>("buttonQuit", sf::Vector2f(400, 800), sf::Vector2f(1, 1), _window->getWindow());
    host->addComponent<InputKey>("consolemenu", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());
    port->addComponent<InputKey>("consolemenu", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());

    manager.addEntity("menubg", background);
    manager.addEntity("joinButton", join);
    manager.addEntity("buttonQuit", back);
    manager.addEntity("consolehost", host);
    manager.addEntity("consoleport", port);

    manager.getEntity("joinButton")->getComponent<Button>().setOrigin(join->getComponent<Button>().getSize().x / 2, join->getComponent<Button>().getSize().y / 2);
    manager.getEntity("buttonQuit")->getComponent<Button>().setOrigin(back->getComponent<Button>().getSize().x / 2, back->getComponent<Button>().getSize().y / 2);

    manager.getEntity("joinButton")->getComponent<Button>().setScale(1.5, 1.5);
    manager.getEntity("buttonQuit")->getComponent<Button>().setScale(1.5, 1.5);

    manager.getEntity("joinButton")->getComponent<Button>().setPosition((1920 / 2) - 300, 1080 - (join->getComponent<Button>().getSize().y) - 40);
    manager.getEntity("buttonQuit")->getComponent<Button>().setPosition(1920 / 2 + 300, 1080 - (back->getComponent<Button>().getSize().y) - 40);

    GETSYSCONS(_systemCreateServer, "consolehost").setScale(1, 1.5);
    GETSYSCONS(_systemCreateServer, "consolehost").setOrigine(GETSYSCONS(_systemCreateServer, "consolehost").getSize().x / 2, GETSYSCONS(_systemCreateServer, "consolehost").getSize().y / 2);
    GETSYSCONS(_systemCreateServer, "consolehost").setPosition(1920 / 2, 1080 / 2 - 100);

    GETSYSCONS(_systemCreateServer, "consoleport").setScale(1, 1.5);
    GETSYSCONS(_systemCreateServer, "consoleport").setOrigine(GETSYSCONS(_systemCreateServer, "consoleport").getSize().x / 2, GETSYSCONS(_systemCreateServer, "consoleport").getSize().y / 2);
    GETSYSCONS(_systemCreateServer, "consoleport").setPosition(1920 / 2, 1080 / 2 + 100);

    GETSYSCONS(_systemCreateServer, "consolehost").setTextPosition(((1920 / 2) - (GETSYSCONS(_systemCreateServer, "consolehost").getSize().x / 2) + 20), 1080 / 2 - 100 + 10);
    GETSYSCONS(_systemCreateServer, "consoleport").setTextPosition(((1920 / 2) - (GETSYSCONS(_systemCreateServer, "consoleport").getSize().x / 2) + 20), 1080 / 2 + 100 + 10);
}

/**
 * @brief Init the JoinServer scene of the menu
 * 
 */
void Menu::initJoinServer()
{
    EntityManager &manager = _systemJoinServer->getManager();



    Entity *background = new Entity();
    Entity *join = new Entity();
    Entity *back = new Entity();
    // Entity *host = new Entity();
    // Entity *port = new Entity();


    background->addComponent<Sprite>("menubg", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());
    join->addComponent<Button>("buttonPlay", sf::Vector2f(400, 200), sf::Vector2f(1, 1), _window->getWindow());
    back->addComponent<Button>("buttonQuit", sf::Vector2f(400, 800), sf::Vector2f(1, 1), _window->getWindow());

    manager.addEntity("menubg", background);
    manager.addEntity("joinButton", join);
    manager.addEntity("buttonQuit", back);

    manager.getEntity("joinButton")->getComponent<Button>().setScale(1.5, 1.5);
    manager.getEntity("joinButton")->getComponent<Button>().setPosition((1920 / 2) - (join->getComponent<Button>().getSize().x / 2), 1080 - (join->getComponent<Button>().getSize().y) - 40);
    manager.getEntity("buttonQuit")->getComponent<Button>().setScale(1.5, 1.5);
    manager.getEntity("buttonQuit")->getComponent<Button>().setPosition(1500, 1080 - (back->getComponent<Button>().getSize().y) - 40);
}