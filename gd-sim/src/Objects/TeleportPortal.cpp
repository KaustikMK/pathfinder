#include <Portals.hpp>
#include <Player.hpp>
#include <unordered_map>

static std::unordered_map<int, TeleportPortal*> s_portalPairs;

TeleportPortal::TeleportPortal(Vec2D size, std::unordered_map<int, std::string>&& fields)
    : EffectObject(size, std::move(fields)), group(0), target(nullptr) {
    auto it = fields.find(28);
    if (it != fields.end()) {
        group = std::stoi(it->second);
        auto it2 = s_portalPairs.find(group);
        if (it2 == s_portalPairs.end()) {
            s_portalPairs[group] = this;
        } else {
            target = it2->second;
            it2->second->target = this;
        }
    }
}

void TeleportPortal::collide(Player& p) const {
    EffectObject::collide(p);
    if (target) {
        p.pos = target->pos;
    }
}
