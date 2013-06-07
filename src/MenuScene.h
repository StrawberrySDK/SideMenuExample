/*
 *  NO2 Web and Mobile Applications, S.L CONFIDENTIAL
 *
 *  Strawberry SDK ( OpenGL + HTML + CSS  cross-platform framework )
 *  Copyright © 2013 by NO2 Web and Mobile Applications, S.L. All rights reserved.
 *  
 *  File name: MenuScene.h
 *  Created by César Guirao on 06/06/13
 */ 
#ifndef SideMenu_MenuScene
#define SideMenu_MenuScene

#include "NO2GL.h"

class MenuScene : public NO2Scene, public NO2DataSource {
public:
    MenuScene();
    
    // ******** Begin of Scene methods ********
    virtual void onCommand(int command, int subcommand, NO2Object *object);
    // ****************************************
    
    virtual int numberOfSections(NO2Drawable *container);
    virtual int numberOfItemsInSection(NO2Drawable *container, int section) ;
    virtual NO2String *templateForIndex(NO2Drawable *container, const NO2IndexPath &indexPath);

protected:
    ~MenuScene();
    
    NO2_COMMON_METHODS(MenuScene);
};

#endif