#include <Geode/Geode.hpp>
#include <Geode/modify/UILayer.hpp>

using namespace geode::prelude;

class HealthBar : public CCNode {
protected:
    GJBaseGameLayer* m_gameLayer;
public:
    static HealthBar* create(GJBaseGameLayer* layer);
    bool init(GJBaseGameLayer* layer);
};