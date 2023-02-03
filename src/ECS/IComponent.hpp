/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-bsrtype-marc.bieber
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <map>
#include <array>
#include <bitset>
#include <fstream>
#include <iostream>

enum spritesEnum {
    BACKGROUND,
    STARSHIP
};

enum buffBonus {
    BONUS_HEALTH,
    BONUS_DAMAGE,
    BONUS_SPEED
};

enum sceneEnum {
    MENU,
    GAME,
    END
};

class Entity;

/**
 * @brief Interface for all components
 */
class IComponent {
    public:
        IComponent() = default;
        virtual ~IComponent() = default;

        virtual bool init() = 0;
        virtual void draw() = 0;
        virtual void update() = 0;

    protected:
    private:
};

#endif /* !ICOMPONENT_HPP_ */
