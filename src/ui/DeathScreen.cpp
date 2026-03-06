#include "DeathScreen.hpp"

DeathScreen* DeathScreen::create(GJBaseGameLayer* layer) {
	auto ret = new DeathScreen();
	if (ret && ret->init(layer)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool DeathScreen::init(GJBaseGameLayer* layer) {
	if (!CCNode::init()) return false;
	m_gameLayer = layer;

	this->setID("death-screen");

	auto winSize = CCDirector::get()->getWinSize();

	auto blackCover = CCSprite::create("square.png");
	blackCover->setPosition(winSize / 2);
	blackCover->setScale(500.f);
	blackCover->setID("background");
	blackCover->setZOrder(-1);
	blackCover->setOpacity(0);
	blackCover->setColor({0, 0, 0});
	this->addChild(blackCover);

	auto youarded = CCLabelBMFont::create("[YOU ARE DEAD]", "bigFont.fnt");
	youarded->setPosition({winSize.width / 2, winSize.height - 20.f});
	youarded->setOpacity(0);
	this->addChild(youarded);

	auto torestart = CCLabelBMFont::create("[Press R to restart]", "bigFont.fnt");
	torestart->setPosition({winSize.width / 2, 20.f});
	torestart->setOpacity(0);
	this->addChild(torestart);

	auto skull = CCSprite::createWithSpriteFrameName("miniSkull_001.png");
	skull->setScale(2.f);
	skull->setID("skull");
	skull->setOpacity(0);
	skull->setPosition(winSize / 2);
	this->addChild(skull);

	blackCover->runAction(CCFadeIn::create(5.f));
	youarded->runAction(CCFadeIn::create(5.f));
	torestart->runAction(CCFadeIn::create(5.f));
	skull->runAction(CCFadeIn::create(5.f));

	addEventListener(KeybindSettingPressedEventV3(GEODE_MOD_ID, "restart-level"), [this, layer](const Keybind& keybind, bool down, bool repeat, double timestamp) {
		geode::Loader::get()->queueInMainThread([this, layer]() {
			this->removeFromParent();
			layer->resetLevel();
		});
	});

	return true;
}