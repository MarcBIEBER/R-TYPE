// /*
// ** EPITECH PROJECT, 2022
// ** B-CPP-500-MLH-5-1-rtype-arnaud.issoire
// ** File description:
// ** Menu
// */

#include "Menu.hpp"

/**
 * @brief Construct a new Menu:: Menu object
 * 
 * @param client the current client of the game
 * @param window the current window of the game
 */
Menu::Menu(client &client, Window &window)
{
    this->_window = &window;
    _systemMain = new System(_window->getWindow());
    _systemSingleplayer = new System(_window->getWindow());
    _systemMultiplayer = new System(_window->getWindow());
    _systemCreateServer = new System(_window->getWindow());
    _systemJoinServer = new System(_window->getWindow());

    _systemMain->init();
    _systemSingleplayer->init();
    _systemMultiplayer->init();
    _systemCreateServer->init();
    _systemJoinServer->init();

    for (int i = 0; i < CLOCK_NB; i++) {
        _clocks.push_back(sf::Clock());
        _times.push_back(sf::Time());
    }


    isTypingHost = false;
    isTypingPort = false;
    _nbServer = 0;
    // todo: Change JOINSERVER to MAIN before pushing last version
    this->_scene = MAIN;
}

Menu::~Menu()
{
}

/**
 * @brief Connect the client to the server
 * @param host the host of the server
 * @param port the port of the server
 * 
 */
void Menu::connectClient(std::string host = "127.0.0.1", std::string port = "4242")
{
    _host = host;
    _port = port;
    std::cout << "host: " << host << " port: " << port << std::endl;
    _window->getClient().init(_host, _port);
}

/**
 * @brief Handle parallax
 * 
 */
void Menu::handleParallax(System *sys)
{
    //actualize time
    for (int i = 0; i < CLOCK_NB; i++)
        _times[i] = _clocks[i].getElapsedTime();
    
    if (_times[PARA_ONE].asMilliseconds() > 1) {
        GETSYSCOMP(sys, "para1_1", Parallax).move(-1, 0);
        if (GETSYSCOMP(sys, "para1_1", Parallax).getSprite().getPosition().x <= -1920)
            GETSYSCOMP(sys, "para1_1", Parallax).getSprite().setPosition(1920, 0);
        _clocks[PARA_ONE].restart();
    }
    if (_times[PARA_TWO].asMilliseconds() > 1) {
        GETSYSCOMP(sys, "para1_2", Parallax).move(-2, 0);
        if (GETSYSCOMP(sys, "para1_2", Parallax).getSprite().getPosition().x <= -1920)
            GETSYSCOMP(sys, "para1_2", Parallax).getSprite().setPosition(1920, 0);
        _clocks[PARA_TWO].restart();
    }
    if (_times[PARA_THREE].asMilliseconds() > 1) {
        GETSYSCOMP(sys, "para1_3", Parallax).move(-3, 0);
        if (GETSYSCOMP(sys, "para1_3", Parallax).getSprite().getPosition().x <= -1920)
            GETSYSCOMP(sys, "para1_3", Parallax).getSprite().setPosition(1920, 0);
        _clocks[PARA_THREE].restart();
    }
    if (_times[PARA_FOUR].asMilliseconds() > 1) {
        GETSYSCOMP(sys, "para1_4", Parallax).move(-4, 0);
        if (GETSYSCOMP(sys, "para1_4", Parallax).getSprite().getPosition().x <= -1920)
            GETSYSCOMP(sys, "para1_4", Parallax).getSprite().setPosition(1920, 0);
        _clocks[PARA_FOUR].restart();
    }
}

/**
 * @brief Get the events of the Main menu scene
 * 
 */
void Menu::getEventMain()
{
    handleParallax(_systemMain);
    sf::Event event;
    while (_window->getWindow().pollEvent(event)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(_window->getWindow());
        if (event.type == sf::Event::Closed)
            _window->getWindow().close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                _window->getWindow().close();
        }
        GETSYSCOMP(_systemMain, "playMulti", Button).handleHover(mousePos);
        GETSYSCOMP(_systemMain, "quitButton", Button).handleHover(mousePos);
        if (event.type == sf::Event::MouseButtonReleased) {
            // if (GETSYSCOMP(_systemMain, "playButton", Button).getClick(mousePos))
            //     _window->setGameScene(GAME);
            if (GETSYSCOMP(_systemMain, "quitButton", Button).getClick(mousePos))
                _window->getWindow().close();
            if (GETSYSCOMP(_systemMain, "playMulti", Button).getClick(mousePos))
                setScene(MULTIPLAYER);
            if (GETSYSCOMP(_systemMain, "buttonVolume", Button).getClick(mousePos)) {
                _volume_set = !_volume_set;
                if (_volume_set){
                    GETSYSCOMP(_systemMain, "blueCross", Button).setDrawable(false);
                    _window->getMusic()->setVolume(7.f);
                } else {
                    GETSYSCOMP(_systemMain, "blueCross", Button).setDrawable(true);
                    _window->getMusic()->setVolume(0.f);
                }
            }
        }
    }
}

/**
 * @brief loop of the Main menu scene
 * 
 * @param system current system for the Main menu scene
 */
void Menu::loopMain(System &system)
{
    getEventMain();
    _window->clearWindow();
    _window->update(system);
    _window->draw(system);
    _window->refreshWindow();
}

/**
 * @brief Loop in main to control the scene to display the right scene
 * 
 */
void Menu::loop()
{
    switch (_scene) {
        case MAIN:
            // std::cout << "MAIN" << std::endl;
            loopMain(*_systemMain);
            break;
        case SINGLEPLAYER:
            // std::cout << "SINGLEPLAYER" << std::endl;
            loopSingleplayer(*_systemSingleplayer);
            break;
        case MULTIPLAYER:
            // std::cout << "MULTIPLAYER" << std::endl;
            loopMultiplayer(*_systemMultiplayer);
            break;
        case CREATESERVER:
            // std::cout << "CREATESERVER" << std::endl;
            loopCreateServer(*_systemCreateServer);
            break;
        case JOINSERVER:
            // std::cout << "JOINSERVER" << std::endl;
            loopJoinServer(*_systemJoinServer);
            break;
        default:
            break;
    }
}

/**
 * @brief Init all the assets of the menu
 * 
 */
void Menu::initAsset()
{
    AssetManager::getInstance().loadTexture("para1_1", "./assets/Parallax/background_1.png");
    AssetManager::getInstance().loadTexture("para1_2", "./assets/Parallax/background_2.png");
    AssetManager::getInstance().loadTexture("para1_3", "./assets/Parallax/background_3.png");
    AssetManager::getInstance().loadTexture("para1_4", "./assets/Parallax/background_4.png");

    AssetManager::getInstance().loadTexture("menubg", "./assets/sprites/back_menu.png");
    AssetManager::getInstance().loadTexture("menubgclear", "./assets/Menu/BackMulti.png");
    AssetManager::getInstance().loadTexture("buttonPlay", "./assets/Menu/Play.png");
    AssetManager::getInstance().loadTexture("buttonCreate", "./assets/Menu/createServer.png");
    AssetManager::getInstance().loadTexture("buttonQuit", "./assets/Menu/cancel.png");
    AssetManager::getInstance().loadTexture("continuebutton", "./assets/Menu/continue.png");

    AssetManager::getInstance().loadTexture("buttonPlayHover", "./assets/Menu/PlayHover.png");
    AssetManager::getInstance().loadTexture("buttonCreateHover", "./assets/Menu/createServerHover.png");
    AssetManager::getInstance().loadTexture("buttonQuitHover", "./assets/Menu/cancelHover.png");
    AssetManager::getInstance().loadTexture("continuebuttonHover", "./assets/Menu/continueHover.png");

    AssetManager::getInstance().loadTexture("consolemenu", "./assets/Menu/textBox.png");

    AssetManager::getInstance().loadTexture("buttonVolume", "./assets/Menu/volume_button.png");
    AssetManager::getInstance().loadTexture("blueCross", "./assets/Menu/blue_cross.png");

    AssetManager::getInstance().loadSprite("menubgclear", "menubgclear");
    AssetManager::getInstance().loadSprite("menubg", "menubg");

    AssetManager::getInstance().loadSprite("para1_1", "para1_1");
    AssetManager::getInstance().loadSprite("para1_2", "para1_2");
    AssetManager::getInstance().loadSprite("para1_3", "para1_3");
    AssetManager::getInstance().loadSprite("para1_4", "para1_4");

    AssetManager::getInstance().loadSprite("consolemenu", "consolemenu");
    AssetManager::getInstance().loadSprite("continuebutton", "continuebutton");
    AssetManager::getInstance().loadSprite("buttonCreate", "buttonCreate");
    AssetManager::getInstance().loadSprite("buttonPlay", "buttonPlay");
    AssetManager::getInstance().loadSprite("buttonQuit", "buttonQuit");

    AssetManager::getInstance().loadSprite("continuebuttonHover", "continuebuttonHover");
    AssetManager::getInstance().loadSprite("buttonCreateHover", "buttonCreateHover");
    AssetManager::getInstance().loadSprite("buttonPlayHover", "buttonPlayHover");
    AssetManager::getInstance().loadSprite("buttonQuitHover", "buttonQuitHover");

    AssetManager::getInstance().loadSprite("buttonVolume", "buttonVolume");
    AssetManager::getInstance().loadSprite("blueCross", "blueCross");
    AssetManager::getInstance().loadFont("font", "./assets/font/Aloevera-OVoWO.ttf");
}

/**
 * @brief Init all the components of the menu
 * 
 */
void Menu::init()
{
    initAsset();
    initMain();
    initSingleplayer();
    initMultiplayer();
    initCreateServer();
    initJoinServer();
    if (_nbServer != 0)
        _systemMultiplayer->getManager().getEntity("serverBox0").get()->getComponent<ServerBox>().setIsClick(true);
}