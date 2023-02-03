/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-bsrtype-marc.bieber
** File description:
** EntityManager
*/

#include "EntityManager.hpp"

/**
 * @brief Draw all the entities
 */
void EntityManager::draw()
{
    for (auto &entity : _entities)
        entity.second.get()->draw();
}

/**
 * @brief Update all the entities
 */
void EntityManager::update()
{
    for (auto &entity : _entities)
        entity.second->update();
}

/**
 * @brief Add an entity to the list
 * @param name id of the entity
 * @param entity entity to add
 */
void EntityManager::addEntity(std::string name, Entity *player)
{
    std::unique_ptr<Entity> uPtr{player};
    _entities.push_back(std::make_pair(name, std::move(uPtr)));
}

/**
 * @brief Add an entity to the list with emplace
 * @param name id of the entity
 * @param entity entity to add
 */
void EntityManager::addEntityEmplace(int place, std::string name, Entity *player)
{
    std::unique_ptr<Entity> uPtr{player};
    _entities.emplace(_entities.begin() + place, std::make_pair(name, std::move(uPtr)));
}

/**
 * @brief Return an entity from the list
 * @param entity id of the entity to return
 * 
 * @return std::unique_ptr<Entity> ptr to the entity needed
 */
std::unique_ptr<Entity> &EntityManager::getEntity(std::string name)
{
    for (auto &entity : _entities) {
        if (entity.first == name)
            return entity.second;
    }
    return _entities[0].second;
    // return _entities[name];
}

/**
 * @brief Remove an entity from the list
 * @param entity entity to remove
 */
void EntityManager::removeEntity(Entity *player)
{
    // for (auto &entity : _entities) {
    //     if (entity.second == player) {
    //         _entities.erase(entity);
    //         break;
    //     }
    // }
}