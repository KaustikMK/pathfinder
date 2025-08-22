#include <Pad.hpp>
#include <Player.hpp>

Pad::Pad(Vec2D size, std::unordered_map<int, std::string>&& fields) : EffectObject(size, std::move(fields)) {
	switch (atoi(fields[1].c_str())) {
		case 35:
			type = PadType::Yellow;
			break;
		case 67:
			type = PadType::Blue;
			break;
		case 140:
			type = PadType::Pink;
			break;
		/*case 1332:
			type = PadType::Red;
			break;*/
		default:
			type = PadType::Yellow;
			break;
	}

	if (atoi(fields[5].c_str()) == 1) {
		rotation += deg2rad(180);
	}
}

const velocity_map<PadType, VehicleType, bool> pad_velocities = {
        {{PadType::Yellow, VehicleType::Cube, false}, {864,         864,        864}},
        {{PadType::Yellow, VehicleType::Cube, true},  {691.2,       691.2,      691.2}},
        {{PadType::Yellow, VehicleType::Robot, false}, {864,         864,        864}},
        {{PadType::Yellow, VehicleType::Robot, true},  {691.2,       691.2,      691.2}},
        {{PadType::Yellow, VehicleType::Spider, false}, {864,         864,        864}},
        {{PadType::Yellow, VehicleType::Spider, true},  {691.2,       691.2,      691.2}},
        {{PadType::Yellow, VehicleType::Swing, false}, {864,         864,        864}},
        {{PadType::Yellow, VehicleType::Swing, true},  {691.2,       691.2,      691.2}},

	{{PadType::Yellow, VehicleType::Ship, false}, {432,         432,        432}},
	{{PadType::Yellow, VehicleType::Ship, true},  {691.2,       691.2,      691.2}},

	{{PadType::Yellow, VehicleType::Ball, false}, {518.4,  518.4,    518.4}},
	{{PadType::Yellow, VehicleType::Ball, true},  {414.72002,  414.72002,  414.72002}},

	{{PadType::Yellow, VehicleType::Ufo, false},  {573.48,      432,        432}},
	{{PadType::Yellow, VehicleType::Ufo, true},   {458.784,     691.2,      691.2}},


        {{PadType::Blue, VehicleType::Cube, false},   {-345.6,    -345.6,     -345.6}},
        {{PadType::Blue, VehicleType::Cube, true},    {-276.48,    -276.48,    -276.48}},
        {{PadType::Blue, VehicleType::Robot, false},   {-345.6,    -345.6,     -345.6}},
        {{PadType::Blue, VehicleType::Robot, true},    {-276.48,    -276.48,    -276.48}},
        {{PadType::Blue, VehicleType::Spider, false},   {-345.6,    -345.6,     -345.6}},
        {{PadType::Blue, VehicleType::Spider, true},    {-276.48,    -276.48,    -276.48}},
        {{PadType::Blue, VehicleType::Swing, false},   {-345.6,    -345.6,     -345.6}},
        {{PadType::Blue, VehicleType::Swing, true},    {-276.48,    -276.48,    -276.48}},

	{{PadType::Blue, VehicleType::Ship, false},   {-229.392,    -345.6,     -345.6}},
	{{PadType::Blue, VehicleType::Ship, true},    {-183.519,    -276.48,    -276.48}},

	{{PadType::Blue, VehicleType::Ball, false},   {-160.574397, -207.36001, -207.36001}},
	{{PadType::Blue, VehicleType::Ball, true},    {-128.463298, -165.88801, -165.88801}},

	{{PadType::Blue, VehicleType::Ufo, false},    {-229.392,    -345.6,     -345.6}},
	{{PadType::Blue, VehicleType::Ufo, true},     {-183.519,    -276.48,    -276.48}},


        {{PadType::Pink, VehicleType::Cube, false},   {561.6,       561.6,      561.6}},
        {{PadType::Pink, VehicleType::Cube, true},    {449.28,      449.28,     449.28}},
        {{PadType::Pink, VehicleType::Robot, false},   {561.6,       561.6,      561.6}},
        {{PadType::Pink, VehicleType::Robot, true},    {449.28,      449.28,     449.28}},
        {{PadType::Pink, VehicleType::Spider, false},   {561.6,       561.6,      561.6}},
        {{PadType::Pink, VehicleType::Spider, true},    {449.28,      449.28,     449.28}},
        {{PadType::Pink, VehicleType::Swing, false},   {561.6,       561.6,      561.6}},
        {{PadType::Pink, VehicleType::Swing, true},    {449.28,      449.28,     449.28}},

	{{PadType::Pink, VehicleType::Ship, false},   {302.4,       302.4,      302.4}},
	{{PadType::Pink, VehicleType::Ship, true},    {241.92,      241.92,     241.92}},

	{{PadType::Pink, VehicleType::Ball, false},   {362.88001,  362.88001,  362.88001}},
	{{PadType::Pink, VehicleType::Ball, true},    {290.30401,   290.30401,  290.30401}},

	{{PadType::Pink, VehicleType::Ufo, false},    {345.6,      345.6,      345.6}},
	{{PadType::Pink, VehicleType::Ufo, true},     {276.48,     276.48,     276.48}}
};

void Pad::collide(Player& p) const {
	if (type == PadType::Blue) {
		auto rot = rad2deg(std::abs(rotation));
		if ((rot > 90 && !p.upsideDown) || (rot < 90 && p.upsideDown))
			return;

		if (p.upsideDown != p.prevPlayer().upsideDown)
			return;

		p.upsideDown = !p.upsideDown;
		//p.pad = true;
	}

	p.velocity = pad_velocities.get(type, p.vehicle.type, p.small, p.speed);
	p.grounded = false;
	p.gravityPortal = false;

	EffectObject::collide(p);

}
