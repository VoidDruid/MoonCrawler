#pragma once

#include "Game/StaticEntity.h"
#include "Resources/Texture.hpp"

namespace MoonCrawler {
// Spawn methods
// This mechanism should be REPLACED by something better, but I don't have time

std::shared_ptr<StaticEntity> createStaticObject(
        const std::shared_ptr<Scene> &scene,
        const Transform &transform,
        const std::string &textureName);

std::shared_ptr<StaticEntity> createStaticObject(
        const std::shared_ptr<Scene> &scene,
        const Transform &transform,
        const Collider &collider,
        const std::string &textureName);

std::shared_ptr<StaticEntity> createPlayer(
        const std::shared_ptr<Scene> &scene,
        const Transform &transform);

std::shared_ptr<StaticEntity> createEnemy(
        const std::shared_ptr<Scene> &scene,
        const Transform &transform);

}