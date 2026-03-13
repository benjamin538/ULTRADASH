#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(PauseLayer) {
    struct PauseLayer* create(bool unfocused) {
        auto layer = PauseLayer::create(unfocused);
        if (!layer) return nullptr;
        return layer;
    };

    void onRestart(CCObject* sender) {
        removeDeathScreen();
        PauseLayer::onRestart(sender);
    }

    void onRestartFull(CCObject* sender) {
        removeDeathScreen();
        PauseLayer::onRestartFull(sender);
    }

    void onPracticeMode(CCObject* sender) {
        removeDeathScreen();
        PauseLayer::onPracticeMode(sender);
    }

    void onNormalMode(CCObject* sender) {
        removeDeathScreen();
        PauseLayer::onNormalMode(sender);
    }

    void removeDeathScreen() {
        auto deathScreen = PlayLayer::get()->getChildByID("UILayer")->getChildByID("death-screen");
        if (deathScreen) {
            deathScreen->removeFromParent();
            if (PlayLayer::get()->m_isPracticeMode) {
                PlayLayer::get()->resetLevel();
            }
        }
    }
};