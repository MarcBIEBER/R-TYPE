#include "Window.hpp"

Window::Window()
{
    this->_window.create(sf::VideoMode(1920, 1080), "Duck Hunt");
    this->_window.setFramerateLimit(60);
	this->_window.setVerticalSyncEnabled(true);
	this->_window.setKeyRepeatEnabled(true);
    this->_window.setMouseCursorVisible(false);
    this->_window.requestFocus();
    this->_scene = sceneEnum::GAME;

    getMusic()->openFromFile("./assets/sound/Forest.ogg");
    getMusic()->setLoop(true);
    getMusic()->setVolume(7.f);
    getMusic()->play();
}

Window::~Window()
{
    gameSound.stop();
}

void Window::clearWindow()
{
    this->_window.clear();
}

void Window::refreshWindow()
{
    if (this->_window.isOpen())
        this->_window.display();
}

void Window::update(System &system)
{
    system.update();
}

void Window::draw(System &system)
{
    system.draw();
}
