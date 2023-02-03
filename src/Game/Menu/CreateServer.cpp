#include "Menu.hpp"

/**
 * @brief Handle the console display in the CreateServer menu
 * 
 * @param event current event
 */
void Menu::handleConsole(sf::Event event)
{
    if (isTypingPort) {
        if (event.type == sf::Event::KeyReleased) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                isTypingPort = false;
                isTypingHost = false;
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) && (event.key.code >= 26 && event.key.code <= 35)) {
                GETSYSCONS(_systemCreateServer, "consoleport").addChar(event.key.code - 26 + 48);
                return;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            GETSYSCONS(_systemCreateServer, "consoleport").deleteLastChar();
        }
    }
    if (isTypingHost) {
        if (event.type == sf::Event::KeyReleased) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                isTypingPort = true;
                isTypingHost = false;
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) && (event.key.code >= 26 && event.key.code <= 35)) {
                GETSYSCONS(_systemCreateServer, "consolehost").addChar(event.key.code - 26 + 48);
                return;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period) || ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) && event.key.code == sf::Keyboard::Comma)) {
                    GETSYSCONS(_systemCreateServer, "consolehost").addChar('.');
            }
            if (event.key.code == sf::Keyboard::BackSpace) {
                GETSYSCONS(_systemCreateServer, "consolehost").deleteLastChar();
            }
        }
    }
}

/**
 * @brief Create a serverBox when a client add new server to list
 * 
 */
void Menu::createServerBox()
{
    Entity *server = new Entity();
    if (_nbServer > 0)
        server->addComponent<ServerBox>("serverBox" + std::to_string(_nbServer),
                                        _window->getWindow(),
                                        GETSYSCOMP(_systemCreateServer, "consolehost", InputKey).getCommand(),
                                        GETSYSCOMP(_systemCreateServer, "consoleport", InputKey).getCommand(),
                                        _nbServer,
                                        _systemMultiplayer->getManager().getEntity("serverBox" + std::to_string(_nbServer - 1))->getComponent<ServerBox>().getPosition().y);
    else
        server->addComponent<ServerBox>("serverBox" + std::to_string(_nbServer),
                                        _window->getWindow(),
                                        GETSYSCOMP(_systemCreateServer, "consolehost", InputKey).getCommand(),
                                        GETSYSCOMP(_systemCreateServer, "consoleport", InputKey).getCommand(),
                                        _nbServer);


    _systemMultiplayer->getManager().addEntityEmplace(_nbServer + 1, "serverBox" + std::to_string(_nbServer), server);
    std::ofstream file_stream("ServerList.txt", std::ios::app);
    file_stream << std::endl;
    file_stream << GETSYSCOMP(_systemCreateServer, "consolehost", InputKey).getCommand() << " " << GETSYSCOMP(_systemCreateServer, "consoleport", InputKey).getCommand();
    file_stream.close();
    GETSYSCOMP(_systemCreateServer, "consolehost", InputKey).clear();
    GETSYSCOMP(_systemCreateServer, "consoleport", InputKey).clear();
    _nbServer++;
}

/**
 * @brief Handle the event in the CreateServer menu
 * 
 */
void Menu::getEventCreateServer()
{
    sf::Event event;
    while (_window->getWindow().pollEvent(event)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(_window->getWindow());
        if (event.type == sf::Event::Closed)
            _window->getWindow().close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                setScene(MULTIPLAYER);
        }
        GETSYSCOMP(_systemCreateServer, "buttonQuit", Button).handleHover(mousePos);
        GETSYSCOMP(_systemCreateServer, "joinButton", Button).handleHover(mousePos);
        
        if (event.type == sf::Event::MouseButtonReleased) {
            if (GETSYSCOMP(_systemCreateServer, "buttonQuit", Button).getClick(mousePos))
                setScene(MULTIPLAYER);
            if (GETSYSCOMP(_systemCreateServer, "joinButton", Button).getClick(mousePos)) {
                setScene(MULTIPLAYER);
                createServerBox();
                return;
            }
            else if (GETSYSCOMP(_systemCreateServer, "consolehost", InputKey).getClick(mousePos)) {
                isTypingHost = true;
                isTypingPort = false;
            } else if (GETSYSCOMP(_systemCreateServer, "consoleport", InputKey).getClick(mousePos)) {
                isTypingPort = true;
                isTypingHost = false;
            }
        }
        handleConsole(event);
    }
}

/**
 * @brief Loop of the CreateServer menu
 * 
 */
void Menu::loopCreateServer(System &system)
{
    getEventCreateServer();
    _window->clearWindow();
    _window->update(system);
    _window->draw(system);
    _window->refreshWindow();
}