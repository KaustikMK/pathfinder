#include <Orb.hpp>
#include <Player.hpp>

Orb::Orb(Vec2D size, std::unordered_map<int, std::string>&& fields) : EffectObject(size, std::move(fields)) {
	switch (std::stoi(fields[1])) {
		case 36:
			type = OrbType::Yellow;
			break;
		case 84:
			type = OrbType::Blue;
			break;
		case 141:
			type = OrbType::Pink;
			break;
		default:
			type = OrbType::Yellow;
			break;
	};
}

bool Orb::touching(Player const& p) const {
	return EffectObject::touching(p) || EffectObject::touching(p.prevPlayer());
}

const velocity_map<OrbType, VehicleType, bool> orb_velocities = {
        {{OrbType::Yellow, VehicleType::Cube, false}, {573.48,      603.72,     616.68,    606.42}},
        {{OrbType::Yellow, VehicleType::Cube, true},  {458.784,     482.976,    481.734,   485.136}},
        {{OrbType::Yellow, VehicleType::Robot, false}, {573.48,      603.72,     616.68,    606.42}},
        {{OrbType::Yellow, VehicleType::Robot, true},  {458.784,     482.976,    481.734,   485.136}},
        {{OrbType::Yellow, VehicleType::Spider, false}, {573.48,      603.72,     616.68,    606.42}},
        {{OrbType::Yellow, VehicleType::Spider, true},  {458.784,     482.976,    481.734,   485.136}},
        {{OrbType::Yellow, VehicleType::Swing, false}, {573.48,      603.72,     616.68,    606.42}},
        {{OrbType::Yellow, VehicleType::Swing, true},  {458.784,     482.976,    481.734,   485.136}},

	{{OrbType::Yellow, VehicleType::Ship, false}, {573.48,      603.72,     616.68,    606.42}},
	{{OrbType::Yellow, VehicleType::Ship, true},  {458.784,     482.976,    481.734,   485.136}},

	{{OrbType::Yellow, VehicleType::Ball, false}, {401.435993,  422.60399,  431.67599, 424.493993}},
	{{OrbType::Yellow, VehicleType::Ball, true},  {321.148795,  338.08319,  345.34079, 339.59519}},

	{{OrbType::Yellow, VehicleType::Ufo, false},  {573.48,      603.72,     616.68,    606.42}},
	{{OrbType::Yellow, VehicleType::Ufo, true},   {458.784,     482.976,    481.734,   485.136}},


        {{OrbType::Blue, VehicleType::Cube, false},   {-229.392,    -241.488,   -246.672,  -242.568}},
        {{OrbType::Blue, VehicleType::Cube, true},    {-183.519,    -193.185,   -197.343,  -194.049}},
        {{OrbType::Blue, VehicleType::Robot, false},   {-229.392,    -241.488,   -246.672,  -242.568}},
        {{OrbType::Blue, VehicleType::Robot, true},    {-183.519,    -193.185,   -197.343,  -194.049}},
        {{OrbType::Blue, VehicleType::Spider, false},   {-229.392,    -241.488,   -246.672,  -242.568}},
        {{OrbType::Blue, VehicleType::Spider, true},    {-183.519,    -193.185,   -197.343,  -194.049}},
        {{OrbType::Blue, VehicleType::Swing, false},   {-229.392,    -241.488,   -246.672,  -242.568}},
        {{OrbType::Blue, VehicleType::Swing, true},    {-183.519,    -193.185,   -197.343,  -194.049}},

	{{OrbType::Blue, VehicleType::Ship, false},   {-229.392,    -241.488,   -246.672,  -242.568}},
	{{OrbType::Blue, VehicleType::Ship, true},    {-183.519,    -193.185,   -197.343,  -194.049}},

	{{OrbType::Blue, VehicleType::Ball, false},   {-160.574397, -169.04160, -172.6704, -169.7976}},
	{{OrbType::Blue, VehicleType::Ball, true},    {-128.463298, -135.2295,  -138.1401, -135.8343}},

	{{OrbType::Blue, VehicleType::Ufo, false},    {-229.392,    -241.48,    -246.672,  -242.568}},
	{{OrbType::Blue, VehicleType::Ufo, true},     {-183.519,    -193.185,   -197.343,  -194.049}},


        {{OrbType::Pink, VehicleType::Cube, false},   {412.884,     434.7,      443.988,   436.644}},
        {{OrbType::Pink, VehicleType::Cube, true},    {330.318,     347.76,     355.212,   349.272}},
        {{OrbType::Pink, VehicleType::Robot, false},   {412.884,     434.7,      443.988,   436.644}},
        {{OrbType::Pink, VehicleType::Robot, true},    {330.318,     347.76,     355.212,   349.272}},
        {{OrbType::Pink, VehicleType::Spider, false},   {412.884,     434.7,      443.988,   436.644}},
        {{OrbType::Pink, VehicleType::Spider, true},    {330.318,     347.76,     355.212,   349.272}},
        {{OrbType::Pink, VehicleType::Swing, false},   {412.884,     434.7,      443.988,   436.644}},
        {{OrbType::Pink, VehicleType::Swing, true},    {330.318,     347.76,     355.212,   349.272}},

	{{OrbType::Pink, VehicleType::Ship, false},   {212.166,     223.398,    228.15,    224.37}},
	{{OrbType::Pink, VehicleType::Ship, true},    {169.776,     178.686,    182.52,    179.496}},

	{{OrbType::Pink, VehicleType::Ball, false},   {309.090595,  325.42019,  332.37539, 326.85659}},
	{{OrbType::Pink, VehicleType::Ball, true},    {247.287596,  260.3286,   265.923,   261.5004}},

	{{OrbType::Pink, VehicleType::Ufo, false},    {240.84,      253.584,    258.984,   254.718}},
	{{OrbType::Pink, VehicleType::Ufo, true},     {192.672,     202.824,    207.198,   203.742}}
};

void Orb::collide(Player& p) const {
	if (p.buffer || (p.prevPlayer().buffer && !p.button) || (p.vehicle.type == VehicleType::Ball && p.vehicleBuffer)) {
		p.buffer = false;
		p.vehicleBuffer = false;

		EffectObject::collide(p);

		if (p.vehicle.type != VehicleType::Wave) {
			p.velocity = orb_velocities.get(type, p.vehicle.type, p.small , p.speed);
			p.grounded = false;
		}

		if (type == OrbType::Blue) {
			p.upsideDown = !p.upsideDown;
		}

		if (p.vehicle.type == VehicleType::Ball)
			p.input = false;
	}
}