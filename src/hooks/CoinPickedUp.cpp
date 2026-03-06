#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>

using namespace geode::prelude;

class IDontKnowHowToNameThis : public CCObject {
public:
	void resume(float dt) {
		FMODAudioEngine::sharedEngine()->resumeAllAudio();
		CCDirector::get()->getScheduler()->setTimeScale(1.0f);
		this->release();
	}

	static IDontKnowHowToNameThis* create() {
		auto ret = new IDontKnowHowToNameThis();
		ret->autorelease();
		ret->retain();
		return ret;
	}
};

class $modify(GJBaseGameLayer) {
	bool init() {
		if (!GJBaseGameLayer::init()) return false;
		return true;
	}

	void destroyObject(GameObject* obj) {
		GJBaseGameLayer::destroyObject(obj);
		if (!Mod::get()->getSettingValue<bool>("enable-flashes")) return;

		if (obj->m_objectID == 1322 || obj->m_objectID == 1329 || obj->m_objectID == 142) {
			log::info("coin");
			// freeze
			CCDirector::get()->getScheduler()->setTimeScale(0.00001f);
			FMODAudioEngine::sharedEngine()->pauseAllAudio();

			auto bigWhiteFrame = CCSprite::create("square.png");
			bigWhiteFrame->setScale(500.f);
			bigWhiteFrame->setZOrder(676767676767676767);
			bigWhiteFrame->setID("a-really-big-white-frame");
			bigWhiteFrame->setOpacity(Mod::get()->getSettingValue<float>("flash-opacity") / 100 * 255);
			bigWhiteFrame->setPosition(CCDirector::get()->getWinSize()/2);
			this->m_uiLayer->addChild(bigWhiteFrame);

			auto idk = IDontKnowHowToNameThis::create();
			CCDirector::get()->getScheduler()->scheduleSelector(schedule_selector(IDontKnowHowToNameThis::resume), idk, Mod::get()->getSettingValue<float>("flashes-length") * 0.00001f, 0, 0.0f, false);
			bigWhiteFrame->runAction(CCSequence::create(CCDelayTime::create(0.01f), CCRemoveSelf::create(), nullptr));
		}
	}
};