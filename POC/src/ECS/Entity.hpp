/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-bsrtype-marc.bieber
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "Component.hpp"
#include "IComponent.hpp"

/**
 * @brief Class containing all the components of an entity
 */
class Entity {
    public:
        Entity() {};
        virtual ~Entity() = default;

        template <typename T, typename... TArgs>
        inline T &addComponent(TArgs &&...args)
        {
            T *component = new T(std::forward<TArgs>(args)...);
            std::unique_ptr<IComponent> uPtr{component};
            components.emplace_back(std::move(uPtr));

            if (component->init())
            {
                comptList[getComponentId<T>()] = component;
                compBitset[getComponentId<T>()] = true;
                return *component;
            }
            std::cout << "Error: Component not initialized" << std::endl;
            return *component;
        }

        template <typename T>
        inline T &getComponent() const
        {
            auto ptr(comptList[getComponentId<T>()]);
            return *static_cast<T *>(ptr);
        }

        template <typename T>
        inline bool hasComponent() const
        {
            return compBitset[getComponentId<T>()];
        }

        inline bool isActive() const
        {
            return active;
        }

        inline void destroy()
        {
            active = false;
        }

        inline void draw()
        {
            for (auto &component : components) {
                component->draw();
            }
        }

        inline void update()
        {
            for (auto &component : components) {
                component->update();
            }
        }

    protected:
    private:
        bool active;
        ComponentList comptList;
        ComponentBitset compBitset;
        std::vector<std::unique_ptr<IComponent>> components;
};

#endif /* !ENTITY_HPP_ */
