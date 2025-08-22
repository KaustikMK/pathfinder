#pragma once

#include <functional>

enum class VehicleType {
        Cube,
        Ship,
        Ball,
        Ufo,
        Wave,
        Robot,
        Spider,
        Swing
};

struct Player;
struct Object;

struct Vehicle {
	VehicleType type;

	std::function<void(Player&, Object const*, bool)> enter;
	std::function<void(Player&)> clamp;
	std::function<void(Player&)> update;

	static Vehicle from(VehicleType v);
};
