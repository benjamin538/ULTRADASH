#include <Geode/Geode.hpp>
#include <Geode/modify/UILayer.hpp>

using namespace geode::prelude;

class StatsFrame : public CCNode {
protected:
	GJBaseGameLayer* m_gameLayer;
	PlayLayer* m_playLayer;
	CCLabelBMFont* m_attemptLabel;
	CCLabelBMFont* m_timeLabel;
	CCSprite* m_coin1;
	CCSprite* m_coin2;
	CCSprite* m_coin3;
public:
	static StatsFrame* create(GJBaseGameLayer* layer);
	bool init(GJBaseGameLayer* layer);
	void update(float dt);
};