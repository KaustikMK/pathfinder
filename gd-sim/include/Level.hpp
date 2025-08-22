#pragma once
#include <Object.hpp>
#include <Player.hpp>
#include <vector>
#include <cstdint>

class Level {
	void initLevelSettings(std::string const& lvlSettings, Player& player);
 public:
	std::vector<Player> gameStates;
	size_t objectCount = 0;
	std::vector<std::vector<ObjectContainer>> sections;
	float length = 0.0;

 	static constexpr uint32_t sectionSize = 100;
 	bool debug = false;

 	Level(std::string const& lvlString);
 	Player& runFrame(bool pressed, float dt = 1/240.);
 	void rollback(int frame);
 	int currentFrame() const;
 	Player const& getState(int frame) const;
 	Player& latestFrame();
};
