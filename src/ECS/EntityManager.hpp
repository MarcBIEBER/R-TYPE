/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-bsrtype-marc.bieber
** File description:
** EntityManager
*/

#ifndef EntityManager_HPP_
#define EntityManager_HPP_

#include "Entity.hpp"
#include "../AssetManager/AssetManager.hpp"
//Rajouter les includes entity quand une nouvelle est crée
#include "Entity/Sprite.hpp"
#include "Entity/Life.hpp"
#include "Entity/SpaceShip.hpp"
#include "Entity/Ennemy.hpp"
#include "Entity/ParallaxScrolling.hpp"
#include "Entity/Button.hpp"
#include "Entity/Text.hpp"
#include "Entity/Progress.hpp"
#include "Entity/LifeBar.hpp"
#include "Entity/Sound.hpp"
#include "Entity/consoleInGame.hpp"
#include "Entity/FinalBoss.hpp"
#include "Entity/InputKey.hpp"
#include "Entity/ServerBox.hpp"
#include "Entity/WaitingSprite.hpp"
#include "Entity/SemiBoss.hpp"
#include "Entity/LobbyBoard.hpp"


class Entity;

/**
 * @brief Class containing all the entities of the game
 */
class EntityManager {
    public:
        EntityManager() = default;
        ~EntityManager() = default;

        void draw();
        void update();
        void addEntity(std::string name, Entity *entity);
        void addEntityEmplace(int place, std::string name, Entity *entity);
        void removeEntity(Entity *entity);



        std::unique_ptr<Entity> &getEntity(std::string name);

    protected:
    private:
        std::vector<std::pair<std::string, std::unique_ptr<Entity>>> _entities;
};
#endif /* !EntityManager_HPP_ */
