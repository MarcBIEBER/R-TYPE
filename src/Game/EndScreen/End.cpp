#include "End.hpp"

/**
 * @brief Construct a new End:: End object
 * 
 * @param client 
 * @param window 
 */
End::End(client &client, Window &window)
{
    this->_window = &window;
    _system = new System(_window->getWindow());
    _system->init();
    _clock = sf::Clock();
    _time = sf::Time();
}

/**
 * @brief Destroy the End:: End object
 * 
 */
End::~End()
{
}

/**
 * @brief Main loop of the end scene
 * 
 */
void End::loop()
{
    getEvent();

    _system->getManager().getEntity("score")->getComponent<Text>().setText("Score : " + std::to_string(_window->getScore()));
    _system->getManager().getEntity("nb_boss_kill")->getComponent<Text>().setText("Number of boss killed : " + std::to_string(_window->getBossKilled()));
    _window->clearWindow();
    _window->update(*_system);
    _window->draw(*_system);
    _window->refreshWindow();
}

/**
 * @brief Init all the asset and component of the end scene
 * 
 */
void End::init()
{
    initAsset();
    EntityManager &manager = _system->getManager();

    Entity *back = new Entity();

    Entity *para1 = new Entity();
    Entity *para2 = new Entity();
    Entity *para3 = new Entity();
    Entity *para4 = new Entity();

    Entity *score = new Entity();
    Entity *nbBossKill = new Entity();

    Entity *restart = new Entity();

    restart->addComponent<Button>("restart", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());


    back->addComponent<Sprite>("menubg", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());

    para1->addComponent<Parallax>("para1_1", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());
    para2->addComponent<Parallax>("para1_2", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());
    para3->addComponent<Parallax>("para1_3", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());
    para4->addComponent<Parallax>("para1_4", sf::Vector2f(0, 0), sf::Vector2f(1, 1), _window->getWindow());

    score->addComponent<Text>("score", "Score : todo: place score here", _window->getWindow());
    nbBossKill->addComponent<Text>("nb_boss_kill", "Number of boss kill: todo: place score here", _window->getWindow());
    
    manager.addEntity("menubg", back);

    manager.addEntity("para1_1", para1);
    manager.addEntity("para1_2", para2);
    manager.addEntity("para1_3", para3);
    manager.addEntity("para1_4", para4);

    manager.addEntity("score", score);
    manager.addEntity("nb_boss_kill", nbBossKill);
    manager.addEntity("restart", restart);

    manager.getEntity("para1_1")->getComponent<Parallax>().setScale(10, 10);
    manager.getEntity("para1_2")->getComponent<Parallax>().setScale(10, 10);
    manager.getEntity("para1_3")->getComponent<Parallax>().setScale(10, 10);
    manager.getEntity("para1_4")->getComponent<Parallax>().setScale(10, 10);

    manager.getEntity("score")->getComponent<Text>().setPosition(1920 / 2 - 300, 1080 / 2 - 100);
    manager.getEntity("score")->getComponent<Text>().setFont("font");
    manager.getEntity("score")->getComponent<Text>().setFontSize(100);
    manager.getEntity("score")->getComponent<Text>().setText("Score : " + std::to_string(_window->getScore()));
    manager.getEntity("score")->getComponent<Text>().setStyle(sf::Text::Bold);
    manager.getEntity("score")->getComponent<Text>().getText()->setOutlineThickness(4);
    manager.getEntity("score")->getComponent<Text>().getText()->setOutlineColor(sf::Color::Black);

    manager.getEntity("nb_boss_kill")->getComponent<Text>().setPosition(1920 / 2 - 500, 1080 / 2 + 100);
    manager.getEntity("nb_boss_kill")->getComponent<Text>().setFont("font");
    manager.getEntity("nb_boss_kill")->getComponent<Text>().setFontSize(100);
    manager.getEntity("nb_boss_kill")->getComponent<Text>().setText("Number of boss killed : " + std::to_string(_window->getBossKilled()));
    manager.getEntity("nb_boss_kill")->getComponent<Text>().setStyle(sf::Text::Bold);
    manager.getEntity("nb_boss_kill")->getComponent<Text>().getText()->setOutlineThickness(4);
    manager.getEntity("nb_boss_kill")->getComponent<Text>().getText()->setOutlineColor(sf::Color::Black);

    //set origin to center
    manager.getEntity("restart")->getComponent<Button>().setOrigin(manager.getEntity("restart")->getComponent<Button>().getButton().getGlobalBounds().width / 2, manager.getEntity("restart")->getComponent<Button>().getButton().getGlobalBounds().height / 2);
    manager.getEntity("restart")->getComponent<Button>().setPosition(1920 / 2, 1080 - 200);
}

/**
 * @brief Use to handle parallax movement
 * 
 */
void End::handleParallax()
{
    _time = _clock.getElapsedTime();
    if (_time.asMilliseconds() > 1) {
        GETSYSCOMP(_system, "para1_1", Parallax).move(-1, 0);
        if (GETSYSCOMP(_system, "para1_1", Parallax).getSprite().getPosition().x <= -1920)
            GETSYSCOMP(_system, "para1_1", Parallax).getSprite().setPosition(1920, 0);
        GETSYSCOMP(_system, "para1_2", Parallax).move(-2, 0);
        if (GETSYSCOMP(_system, "para1_2", Parallax).getSprite().getPosition().x <= -1920)
            GETSYSCOMP(_system, "para1_2", Parallax).getSprite().setPosition(1920, 0);
        GETSYSCOMP(_system, "para1_3", Parallax).move(-3, 0);
        if (GETSYSCOMP(_system, "para1_3", Parallax).getSprite().getPosition().x <= -1920)
            GETSYSCOMP(_system, "para1_3", Parallax).getSprite().setPosition(1920, 0);
        GETSYSCOMP(_system, "para1_4", Parallax).move(-4, 0);
        if (GETSYSCOMP(_system, "para1_4", Parallax).getSprite().getPosition().x <= -1920)
            GETSYSCOMP(_system, "para1_4", Parallax).getSprite().setPosition(1920, 0);
        _clock.restart();
    }
}

/**
 * @brief Init all the asset of the end scene
 * 
 */
void End::initAsset()
{
    // AssetManager::getInstance().loadTexture("menubg", "./assets/sprites/back_menu.png");

    // AssetManager::getInstance().loadTexture("para1_1", "./assets/Parallax/background_1.png");
    // AssetManager::getInstance().loadTexture("para1_2", "./assets/Parallax/background_2.png");
    // AssetManager::getInstance().loadTexture("para1_3", "./assets/Parallax/background_3.png");
    // AssetManager::getInstance().loadTexture("para1_4", "./assets/Parallax/background_4.png");

    AssetManager::getInstance().loadTexture("restart", "./assets/End/restart.png");
    AssetManager::getInstance().loadSprite("restart", "restart");

    AssetManager::getInstance().loadTexture("restartHover", "./assets/End/restartHover.png");
    AssetManager::getInstance().loadSprite("restartHover", "restartHover");


}

/**
 * @brief Get the event of the end scene
 * 
 */
void End::getEvent()
{
    sf::Event event;
    handleParallax();
    while (_window->getWindow().pollEvent(event)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(_window->getWindow());
        if (event.type == sf::Event::Closed)
            sendQuitAndClose();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                sendQuitAndClose();
            if (event.key.code == sf::Keyboard::Return) {
                sendChangeScene();
            }
        }
        GETSYSCOMP(_system, "restart", Button).handleHover(mousePos);
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (GETSYSCOMP(_system, "restart", Button).getClick(mousePos)) {
                    sendChangeScene();
                }
            }
        }
    }
}


/**
 * @brief Send to the server the player leave message
 *
 */
void End::sendQuitAndClose()
{
    leaderBoardHandler();
    _window->getWindow().close();
        _window->getClient().sender('Q' + std::to_string(_window->getClient().getPlayerId()));
    _window->getClient().setClientConnected(false);
}

void End::sendChangeScene()
{
    leaderBoardHandler();
    _window->getClient().sender('Q' + std::to_string(_window->getClient().getPlayerId()));
    _window->getClient().setClientConnected(false);
    _window->setLobbyFull(false);
    _window->setGameScene(MENU);
}

void End::leaderBoardHandler()
{
    //Read File and add to leaderboard
    std::ifstream file_stream("LeaderBoard.txt");
    std::string line;
    std::vector<std::string> list;
    int bestScore;
    int bestBossKill;
    int currentScore = _window->getScore();
    int currentBossKill = _window->getBossKilled();

    while (std::getline(file_stream, line)) {
        list.push_back(line);
    }
    file_stream.close();
    if (list.size() == 0) {
        bestScore = 0;
        bestBossKill = 0;
    } else {
        if (list[0].size() != 0)
            bestScore = std::atoi(list[0].c_str());
        if (list[1].size() != 0)
            bestBossKill = std::atoi(list[1].c_str());
    }
    if (currentScore > bestScore) {
        std::ofstream ofs;
        ofs.open("LeaderBoard.txt", std::ofstream::out | std::ofstream::trunc);
        ofs.close();
        std::ofstream file_stream("LeaderBoard.txt");
        file_stream << currentScore << std::endl;
        file_stream << currentBossKill << std::endl;
        file_stream.close();
    }
}