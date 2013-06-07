//
//  SideMenuManager.cpp
//  SideMenu
//
//  Created by César Guirao on 06/06/13.
//
//

#include "SideMenuManager.h"

NO2SideMenuManager::NO2SideMenuManager(NO2Scene *menuScene, NO2Scene *visibleScene, NO2AnimationEquation anim, float time):NO2SceneManager() {

    m_multiTouch = true;
    m_menuScene = RETAIN(menuScene);
    m_menuScene->setSceneManager(this);
    m_menuScene->onSceneWillAppear();
    m_menuScene->onSceneDidAppear();
    m_menuScene->setEnterTransitionFinished(true);
    m_menuScene->setZOrder(0);
    
    NO2Rect r = m_menuScene->getFrame();
    addDrawable(menuScene)->setPosition(r.size.width*0.5f, r.size.height*0.5f);
    if(visibleScene) {
        m_visibleScene = RETAIN(visibleScene);
        m_visibleScene->setSceneManager(this);
        m_visibleScene->onSceneWillAppear();
        m_visibleScene->onSceneDidAppear();
        m_visibleScene->setEnterTransitionFinished(true);
        m_visibleScene->setZOrder(1);

        
        NO2Rect v = m_visibleScene->getFrame();
        addDrawable(m_visibleScene)->setPosition(v.size.width*0.5f, v.size.height*0.5f);
        

    } else {
        m_visibleScene = NULL;
    }
    
    m_menuOpened = false;
    m_menuScene->setHidden(true);
    
    m_animation = anim;
    m_duration = time;
    
    NO2PanGestureDetector *pan = new NO2PanGestureDetector(this);
    addGesture(pan);
    RELEASE(pan);
    NO2TapGestureDetector *tap = new NO2TapGestureDetector(this,1);
    addGesture(tap);
    RELEASE(tap);
}

void NO2SideMenuManager::openMenu(bool animated) {
    if(animated) {
        clearAnimators(m_menuScene);
        NO2Rect r = m_menuScene->getFrame();
        m_menuScene->setPosition(r.size.width*0.5f, r.size.height*0.5f);
        if(m_visibleScene) {
            clearAnimators(m_visibleScene);
            NO2Rect v = m_visibleScene->getFrame();
            m_visibleScene->animate(m_animation, 0, m_duration)->setPosition(r.size.width + v.size.width*0.5f, v.size.height*0.5f);
        }
        m_menuOpened = true;
        m_menuScene->onSceneWillAppear();
        m_menuScene->onSceneDidAppear();
        m_menuScene->setEnterTransitionFinished(true);
        m_menuScene->runAction("open");
    } else {
        NO2Rect r = m_menuScene->getFrame();
        m_menuScene->setPosition(r.size.width*0.5f, r.size.height*0.5f);
        if(m_visibleScene) {
            NO2Rect v = m_visibleScene->getFrame();
            m_visibleScene->setPosition(r.size.width + v.size.width*0.5f, v.size.height*0.5f);
        }
        m_menuOpened = true;
        m_menuScene->onSceneWillAppear();
        m_menuScene->onSceneDidAppear();
        m_menuScene->setEnterTransitionFinished(true);
    }
}

void NO2SideMenuManager::closeMenu(bool animated) {
    if(animated) {
        clearAnimators(m_menuScene);
        NO2Rect r = m_menuScene->getFrame();
        m_menuScene->setPosition(r.size.width*0.5f, r.size.height*0.5f);
        if(m_visibleScene) {
            clearAnimators(m_visibleScene);
            NO2Rect v = m_visibleScene->getFrame();
            m_visibleScene->animate(m_animation, 0, m_duration)->setPosition(v.size.width*0.5f, v.size.height*0.5f);
        }
        m_menuOpened = false;
        m_menuScene->onSceneWillDisappear();
        m_menuScene->onSceneDidDisappear();
        m_menuScene->runAction("close");
    } else {
        NO2Rect r = m_menuScene->getFrame();
        m_menuScene->setPosition(r.size.width*0.5f, r.size.height*0.5f);
        if(m_visibleScene) {
            NO2Rect v = m_visibleScene->getFrame();
            m_visibleScene->setPosition(v.size.width*0.5f, v.size.height*0.5f);
        }
        m_menuOpened = false;
        m_menuScene->onSceneWillDisappear();
        m_menuScene->onSceneDidDisappear();
    }
}


NO2Scene *NO2SideMenuManager::getVisibleScene() {
    return m_visibleScene;
}

void NO2SideMenuManager::setVisibleScene(NO2Scene *scn) {
    if(scn == m_visibleScene) {
        return;
    }
    
    if(m_visibleScene) {
        m_visibleScene->onSceneWillDisappear();
        m_visibleScene->onSceneDidDisappear();
        removeDrawable(m_visibleScene);
        RELEASE(m_visibleScene);
        m_visibleScene = NULL;
    }
    if(scn) {
        m_visibleScene = RETAIN(scn);
        m_visibleScene->setSceneManager(this);
        NO2Rect r = m_menuScene->getFrame();
        NO2Rect v = m_visibleScene->getFrame();
        if(isMenuOpened()) {
            addDrawable(m_visibleScene)->setPosition(r.size.width + v.size.width*0.5f, v.size.height*0.5f);
        } else {
            addDrawable(m_visibleScene)->setPosition(v.size.width*0.5f, v.size.height*0.5f);
        }
        m_visibleScene->setZOrder(1);
        m_visibleScene->onSceneWillAppear();
        m_visibleScene->onSceneDidAppear();
        m_visibleScene->setEnterTransitionFinished(true);
    }
}


void NO2SideMenuManager::update(double time, double elapsed) {
    NO2SceneManager::update(time, elapsed);
    
    if(!isMenuOpened() && m_visibleScene) {
        NO2Rect v = m_visibleScene->getFrame();
        if(m_visibleScene->getPosition().x < v.size.width*0.5f) {
            m_menuScene->setHidden(true);
        } else {
            m_menuScene->setHidden(false);
        }
    } else {
        m_menuScene->setHidden(false);
    }
}

void NO2SideMenuManager::layout() {
    NO2SceneManager::layout();
    
    NO2Rect r = m_menuScene->getFrame();
    m_menuScene->setPosition(r.size.width*0.5f, r.size.height*0.5f);

    if(m_visibleScene) {
        NO2Rect v = m_visibleScene->getFrame();
        if(isMenuOpened()) {
            m_visibleScene->setPosition(r.size.width + v.size.width*0.5f, v.size.height*0.5f);
        } else {
            m_visibleScene->setPosition(v.size.width*0.5f, v.size.height*0.5f);
        }
    }
}

void NO2SideMenuManager::onSceneWillAppear() {
    if(getVisibleScene())
        getVisibleScene()->onSceneWillAppear();
}

void NO2SideMenuManager::onSceneDidDisappear() {
    if(getVisibleScene())
        getVisibleScene()->onSceneDidDisappear();
}

void NO2SideMenuManager::onSceneDidAppear() {
    if(getVisibleScene()) {
        getVisibleScene()->onSceneDidAppear();
        getVisibleScene()->setEnterTransitionFinished(true);
    }
}

void NO2SideMenuManager::onSceneWillDisappear() {
    if(getVisibleScene())
        getVisibleScene()->onSceneWillDisappear();
}

void NO2SideMenuManager::onCommand(int command, int subcommand, NO2Object *obj) {
    LOG("Scene manager on command: %d", command);
    switch (command) {
        case COMMAND_MENU_KEY:
        case COMMAND_BACK_KEY:
            if(isMenuOpened()) {
                closeMenu(true);
            } else {
                getVisibleScene()->onCommand(command, subcommand, obj);
            }
            break;
        default:
            if(isMenuOpened()) {
                m_menuScene->onCommand(command, subcommand, obj);
            } else {
                getVisibleScene()->onCommand(command, subcommand, obj);
            }
            break;
    }
}

void NO2SideMenuManager::onAccelerometerEvent(float x, float y, float z) {
    if(isMenuOpened()) {
        m_menuScene->onAccelerometerEvent(x, y, z);
    } else {
        getVisibleScene()->onAccelerometerEvent(x, y, z);
    }
}

void NO2SideMenuManager::onMemoryWarning() {
    m_menuScene->onMemoryWarning();
    if (m_visibleScene) {
        m_visibleScene->onMemoryWarning();
    }
    NO2Scene::onMemoryWarning();
}

bool NO2SideMenuManager::shouldStartGesture(NO2GestureDetector *gesture) {
    if(!isMenuOpened()) {
        return false;
    }
        
    NO2PanGestureDetector *pan = dynamic_cast<NO2PanGestureDetector *>(gesture);
    if(pan) {
        if(isPointInRect(pan->getLocation()- pan->getTranslation(), m_menuScene->getFrame())) {
            return false;
        }
    } else {
        if(isPointInRect(gesture->getLocation(), m_menuScene->getFrame())) {
            return false;
        }
    }
    return true;
}

bool NO2SideMenuManager::onPanGesture(NO2PanGestureDetector *gesture) {
    if(isMenuOpened()) {
        closeMenu(true);
    }
    return true;
}

bool NO2SideMenuManager::onTapGesture(NO2TapGestureDetector *gesture) {
    if(isMenuOpened()) {
        closeMenu(true);
    }
    return true;
}

