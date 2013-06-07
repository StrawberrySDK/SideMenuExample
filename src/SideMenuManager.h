//
//  SideMenuManager.h
//  SideMenu
//
//  Created by César Guirao on 06/06/13.
//
//

#include "no2gl.h"

#ifndef __SideMenu__SideMenuManager__
#define __SideMenu__SideMenuManager__

class NO2SideMenuManager: public NO2SceneManager {
    NO2AnimationEquation m_animation;
    float m_duration;
    
    bool m_menuOpened;
        
    NO2Scene *m_menuScene;
    NO2Scene *m_visibleScene;
    
public:
    NO2SideMenuManager(NO2Scene *menuScene,  NO2Scene *visibleScene = NULL, NO2AnimationEquation anim = kEaseInOutQuad, float time = 0.45);
    
    void openMenu(bool animated = false);
    void closeMenu(bool animated = false);
    
    bool isMenuOpened() const{
        return m_menuOpened;
    }
    
    NO2Scene *getVisibleScene();
    
    void setVisibleScene(NO2Scene *scn);
    
    void update(double time, double elapsed);
    
    void layout();
    
    virtual void onSceneWillAppear();
    virtual void onSceneDidAppear();
    virtual void onSceneWillDisappear();
    virtual void onSceneDidDisappear();
    
    virtual void onCommand(int command, int subcommand, NO2Object *obj);
    
    virtual void onAccelerometerEvent(float x, float y, float z);
    
    bool shouldStartGesture(NO2GestureDetector *gesture);
    bool onPanGesture(strawberry::NO2PanGestureDetector *gesture);
    bool onTapGesture(NO2TapGestureDetector *gesture);
        
    void onMemoryWarning();
    
    NO2_COMMON_METHODS(NO2NavigationManager);
};

#endif /* defined(__SideMenu__SideMenuManager__) */
