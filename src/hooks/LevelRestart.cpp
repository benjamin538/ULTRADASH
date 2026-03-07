#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "../ui/DeathScreen.hpp"

using namespace geode::prelude;

class $modify(PlayLayer) {
	bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
		if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
		return true;
	}

	void resetLevel() {
		if (m_uiLayer->getChildByID("death-screen")) return;
		PlayLayer::resetLevel();
		if (PlayLayer::get()->m_level->m_normalPercent == 100 && !Mod::get()->getSavedValue<bool>("stats-hint")) {
			Notification::create("Tip: press stats key to show stats of run (only on beaten levels)", NotificationIcon::Info)->show();
			Mod::get()->setSavedValue("stats-hint", true);
		}
	}
};