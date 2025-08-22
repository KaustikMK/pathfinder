#pragma once

#undef small
#include <util.hpp>
#include <Vehicle.hpp>
#include <Slope.hpp>
#include <vector>
#include <functional>
#include <optional>

inline double player_speeds[5] = {
        251.16007972276924,
        311.580093712804,
        387.42014039710523,
        468.0001388338566,
        623.160187425608
};

struct Object;
class Level;
struct Slope;
struct Player : public Entity {
	Level* level;
	int frame;
	double timeElapsed;
	float dt;
	bool dead;

	Vehicle vehicle;

	float ceiling;
	float floor;
	bool grounded;
	unsigned int coyoteFrames;

	double acceleration;
	double velocity;
	double rotVelocity;
	bool velocityOverride;

	bool button; // Button is direct, input is indirect and can be disabled if needed
	bool input;
	bool buffer;
	bool vehicleBuffer; // When buffering a click when transitioning to a vehicle

        bool upsideDown;
        bool small;
        bool dual;

	bool gravityPortal; // some vehicles have weird edge cases

	int speed;

	cow_set<int> usedEffects;
	std::vector<std::function<void(Player&)>> actions;

	struct {
		Entity object;
		int playerFrame = 0;
	} snapData;

	struct {
		std::optional<Slope> slope;
		double elapsed;
		bool snapDown; // downhill slopes, approaching with >0 velocity.
	} slopeData;

	Player();

	void preCollision(bool input);
	void postCollision();

	
	Entity unrotatedHitbox() const;
	Entity innerHitbox() const;
	Player const& prevPlayer() const;
	Player const* nextPlayer() const;

	template <typename T>
	T grav(T value) const { return upsideDown ? -value : value; }
	inline float gravBottom(Entity const& e) const { return upsideDown ? -e.getTop() : e.getBottom(); }
	inline float gravTop(Entity const& e) const { return upsideDown ? -e.getBottom() : e.getTop(); }
	inline float gravFloor() const { return upsideDown ? -ceiling : floor; }
	inline float gravCeiling() const { return upsideDown ? -floor : ceiling; }

	void setVelocity(double v, bool override=false);
};