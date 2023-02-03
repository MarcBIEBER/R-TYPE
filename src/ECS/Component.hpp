/*
** EPITECH PROJECT, 2022
** B-CPP-500-MLH-5-1-bsrtype-marc.bieber
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include "IComponent.hpp"

static size_t lastId = 0;

inline size_t getUniqueComponentId()
{
    return lastId += 1;
};

/**
 * @brief Class containing all the components of an entity
 */
template <typename T>
inline size_t getComponentId() noexcept
{
    static_assert(std::is_base_of<IComponent, T>::value, "T must be a Component");
    static const size_t id = getUniqueComponentId();
    return id;
};

constexpr size_t maxComponents = 64;
constexpr size_t maxEntities = 5000;

using ComponentBitset = std::bitset<maxComponents>;
using ComponentList = std::array<IComponent *, maxComponents>;


#endif /* !COMPONENT_HPP_ */
