#include <Geode/Geode.hpp>
#include <Geode/modify/UILayer.hpp>
#include "../ui/StatsFrame.hpp"

using namespace geode::prelude;

class $modify(UILayer) {
	bool init(GJBaseGameLayer* layer) {
		if (!UILayer::init(layer)) return false;
		auto frame = StatsFrame::create(layer);
		
		if (frame) {
			this->addChild(frame);
		}
		return true;
	}
};