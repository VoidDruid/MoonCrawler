#include "Scene.h"

using namespace MoonCrawler;

Scene::Scene(MoonCrawler::Canvas *canvas) :
    m_canvas{canvas}
{}

void Scene::addDrawable(const std::shared_ptr<IDrawable> &drawable) {

}
