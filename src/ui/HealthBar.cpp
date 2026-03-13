#include "HealthBar.hpp"

HealthBar* HealthBar::create(GJBaseGameLayer* layer) {
    auto ret = new HealthBar();
	if (ret && ret->init(layer)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool HealthBar::init(GJBaseGameLayer* layer) {
	if (!CCNode::init()) return false;
	return true;
}