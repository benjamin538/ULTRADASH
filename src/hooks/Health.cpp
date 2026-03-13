#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "../ui/DeathScreen.hpp"

using namespace geode::prelude;

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
		if (Mod::get()->getSettingValue<bool>("enable-death-screen")) {
			if (Mod::get()->getSettingValue<bool>("disable-in-practice") && m_fields->m_layer->m_isPracticeMode) return;
			auto deathScreen = DeathScreen::create(m_fields->m_layer);
			deathScreen->setZOrder(6996699696699696969);
			m_fields->m_layer->m_uiLayer->addChild(deathScreen);
			deathScreen->runAction(CCFadeIn::create(5.f));
		}
	}

	void resetObject() {
		PlayerObject::resetObject();
		m_fields->m_layer->m_uiLayer->removeChildByID("death-screen");
	}
};

class $modify(PlayLayer) {
	struct Fields {
		int m_health;
		float m_timer;
	};

	bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
		if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
		m_fields->m_health = 100;
		m_fields->m_timer = .0f;
		return true;
	}

	void postUpdate(float dt) {
		PlayLayer::postUpdate(dt);
		if (m_fields->m_timer > 0) {
			m_fields->m_timer -= dt;
			return;
		}
		m_fields->m_timer = .0f;
	}

	void destroyPlayer(PlayerObject* player, GameObject* object) {
		if (m_fields->m_timer > 0) return;
		if (m_fields->m_health <= 0 || Mod::get()->getSettingValue<bool>("enable-health")) {
			PlayLayer::destroyPlayer(player, object);
			return;
		}
		m_fields->m_health -= 15;
		m_fields->m_timer = .5f;
		log::info("hp {}", m_fields->m_health);
	}

	void resetLevelFromStart() {
		m_fields->m_health = 100;
		m_fields->m_timer = .0f;
		PlayLayer::resetLevelFromStart();
	}
};