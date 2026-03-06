#include <Geode/Geode.hpp>
#include <Geode/modify/UILayer.hpp>

using namespace geode::prelude;

class DeathScreen : public CCNode {
protected:
	GJBaseGameLayer* m_gameLayer;
public:
	static DeathScreen* create(GJBaseGameLayer* layer);
	bool init(GJBaseGameLayer* layer);
};