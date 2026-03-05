#include "StatsFrame.hpp"

using namespace geode::prelude;

StatsFrame* StatsFrame::create(GJBaseGameLayer* layer) {
	auto ret = new StatsFrame();
	if (ret && ret->init(layer)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool StatsFrame::init(GJBaseGameLayer* layer) {
	if (!CCNode::init()) return false;
	m_gameLayer = layer;
	m_playLayer = static_cast<PlayLayer*>(m_gameLayer);

	// frame
	auto winSize = CCDirector::get()->getWinSize();
	CCSprite* blackFrame = CCSprite::create("square.png");
	blackFrame->setID("background");
	blackFrame->setPosition({10.f, winSize.height - 90.f});
	blackFrame->setColor({0, 0, 0});
	blackFrame->setAnchorPoint({0, 0});
	blackFrame->setScaleX(15.f);
	blackFrame->setScaleY(10.f);
	blackFrame->setOpacity(125);
	this->addChild(blackFrame);
	this->setVisible(false);

	// title
	auto levelTitle = CCLabelBMFont::create("", "bigFont.fnt");
	levelTitle->setScale(0.1f);
	levelTitle->setID("level-title");
	levelTitle->setPosition({70.f, winSize.height - 30.f});
	levelTitle->setScale(0.35f);
	levelTitle->limitLabelWidth(0.4f, 0.35f, 0.2f);
	this->addChild(levelTitle);

	// time
	auto timeLabel = CCLabelBMFont::create("Time:", "bigFont.fnt");
	timeLabel->setScale(0.1f);
	timeLabel->setID("time-label");
	timeLabel->setAnchorPoint({0.f,0.f});
	timeLabel->setPosition({20.f, winSize.height - 50.f});
	timeLabel->setScale(0.35f);
	this->addChild(timeLabel);

	auto actualTime = CCLabelBMFont::create("", "bigFont.fnt");
	actualTime->setScale(0.1f);
	actualTime->setID("time-counter");
	actualTime->setAnchorPoint({1.f,0.f});
	actualTime->setPosition({120.f, winSize.height - 50.f});
	actualTime->setScale(0.35f);
	m_timeLabel = actualTime;
	this->addChild(actualTime);

	// attempts
	auto attemptsLabel = CCLabelBMFont::create("Attempts:", "bigFont.fnt");
	attemptsLabel->setScale(0.1f);
	attemptsLabel->setID("attempts-label");
	attemptsLabel->setAnchorPoint({0.f,0.f});
	attemptsLabel->setPosition({20.f, winSize.height - 62.5f});
	attemptsLabel->setScale(0.35f);
	this->addChild(attemptsLabel);

	auto actualAttempts = CCLabelBMFont::create("1", "bigFont.fnt");
	actualAttempts->setScale(0.1f);
	actualAttempts->setID("attempts-counter");
	actualAttempts->setAnchorPoint({1.f,0.f});
	actualAttempts->setPosition({120.f, winSize.height - 62.5f});
	actualAttempts->setScale(0.35f);
	m_attemptLabel = actualAttempts;
	this->addChild(actualAttempts);

	auto coinsLabel = CCLabelBMFont::create("Coins:", "bigFont.fnt");
	coinsLabel->setScale(0.1f);
	coinsLabel->setID("coins-label");
	coinsLabel->setAnchorPoint({0.f,0.f});
	coinsLabel->setPosition({20.f, winSize.height - 75.f});
	coinsLabel->setScale(0.35f);
	this->addChild(coinsLabel);

	auto coinsNode = CCNode::create();
	coinsNode->setID("stats-coins");
	coinsNode->setAnchorPoint({1.f, 0.f});
	coinsNode->setPosition({45.f, winSize.height - 90.f});
	this->addChild(coinsNode);

	auto coin1 = CCSprite::createWithSpriteFrameName("GJ_select_001.png");
	coin1->setScale(0.25f);
	coin1->setID("coin-1");
	coin1->setPosition({70.f, winSize.height - 300.f});
	coinsNode->addChild(coin1);
	coin1->setVisible(false);
	m_coin1 = coin1;

	auto coin2 = CCSprite::createWithSpriteFrameName("GJ_select_001.png");
	coin2->setScale(0.25f);
	coin2->setID("coin-2");
	coin2->setPosition({60.f, winSize.height - 300.f});
	coinsNode->addChild(coin2);
	coin2->setVisible(false);
	m_coin2 = coin2;

	auto coin3 = CCSprite::createWithSpriteFrameName("GJ_select_001.png");
	coin3->setScale(0.25f);
	coin3->setID("coin-3");
	coin3->setPosition({50.f, winSize.height - 300.f});
	coinsNode->addChild(coin3);
	coin3->setVisible(false);
	m_coin3 = coin3;
	// no shit, sherlok

	this->scheduleUpdate();

	// listener
	addEventListener(KeybindSettingPressedEventV3(GEODE_MOD_ID, "level-info"), [this, levelTitle, layer](const Keybind& keybind, bool down, bool repeat, double timestamp) {
		if (down && !layer->m_isEditor) {
			if (layer->m_level->m_normalPercent == 100) {
				levelTitle->setString(layer->m_level->m_levelName.c_str());
				this->setVisible(true);
			}
		} else if (!down) {
			this->setVisible(false);
		}
	});

	return true;
}

void StatsFrame::update(float dt) {
	if (m_gameLayer->m_isEditor) return;
	if (m_playLayer) {
		m_attemptLabel->setString(std::to_string(m_playLayer->m_attempts).c_str());
		m_timeLabel->setString(std::to_string(m_gameLayer->m_timePlayed).c_str());

		int total = m_gameLayer->m_level->m_coins;

		if (total == 0) {
			this->getChildByID("coins-label")->setVisible(false);
			return;
		}
		if (m_coin1 && m_coin2 && m_coin3) {
			if (total == 1) {
				m_coin1->setVisible(true);
			} else if (total == 2) {
				m_coin1->setVisible(true);
				m_coin2->setVisible(true);
			} else {
				m_coin1->setVisible(true);
				m_coin2->setVisible(true);
				m_coin3->setVisible(true);
			}
		}
	}
}