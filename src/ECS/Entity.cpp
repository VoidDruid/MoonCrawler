#include "Entity.h"

namespace MoonCrawler {
GID generateId() {
    static GID id = NO_ID;  // starting id is never used
    return ++id;
}
}