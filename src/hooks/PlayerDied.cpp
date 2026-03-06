#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
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
	}
};

class $modify(PlayerObject) {
	struct Fields {
		GJBaseGameLayer* m_layer;
	};
	bool init(int player, int ship, GJBaseGameLayer* gameLayer, CCLayer* layer, bool playLayer) {
		if (!PlayerObject::init(player, ship, gameLayer, layer, playLayer)) return false;
		m_fields->m_layer = gameLayer;
		return true;
	}

	void playerDestroyed(bool noEffects) {
		PlayerObject::playerDestroyed(noEffects);
		log::info("dead");
		auto deathScreen = DeathScreen::create(m_fields->m_layer);
		deathScreen->setZOrder(6996699696699696969);
		m_fields->m_layer->m_uiLayer->addChild(deathScreen);
		deathScreen->runAction(CCFadeIn::create(5.f));
	}

	void resetObject() {
		PlayerObject::resetObject();
		m_fields->m_layer->m_uiLayer->removeChildByID("death-screen");
	}
};