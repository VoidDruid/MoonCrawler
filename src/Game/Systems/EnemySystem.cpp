#include "EnemySystem.h"

#include "Game/Scene.h"
#include "Subsystems/Collisions.h"

void
MoonCrawler::EnemySystem::operator()(std::shared_ptr<Scene> scene, std::shared_ptr<EntityBase> entity, MoonCrawler::Components &components) {
    auto player = scene->getPlayer();
    if(not player) {
        return;
    }
    const float speed = 0.2;  // TODO: move to component

    // TODO optimize??
    auto& thisTransform = components.get<Transform>(entity->ID);
    const auto& playerTransform = components.get<Transform>(player->ID);

    auto direction = playerTransform.position - thisTransform.position;
    auto shift = speed * direction / length(direction);

    thisTransform.position  += shift;

    if (not entity->has<MeleeAttack>()) {
        return;
    }

    auto& meleeAttack = components.get<MeleeAttack>(entity->ID);
    auto elapsedTime = scene->getElapsedMicros();

    if (meleeAttack._lastStrikeMicros + meleeAttack.rechargeTimeSecs * MILSECS_TO_SECS > elapsedTime) {
        return;
    }

    if (areColliding(thisTransform, playerTransform)) {
        meleeAttack._lastStrikeMicros = elapsedTime;
        auto& playerHealth = components.get<Health>(player->ID);
        playerHealth.current -= meleeAttack.damage;
        qDebug() << playerHealth.current;
    }
}