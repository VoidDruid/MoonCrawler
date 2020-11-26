#include "Entity.h"

namespace MoonCrawler {
EntityID generateId() {
    static EntityID id = 0;
    return ++id;
}
}