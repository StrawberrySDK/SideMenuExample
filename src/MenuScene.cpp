/*
 *  NO2 Web and Mobile Applications, S.L CONFIDENTIAL
 *
 *  Strawberry SDK ( OpenGL + HTML + CSS  cross-platform framework )
 *  Copyright © 2013 by NO2 Web and Mobile Applications, S.L. All rights reserved.
 *  
 *  File name: MenuScene.cpp
 *  Created by César Guirao on 06/06/13
 */

#include "MenuScene.h"

MenuScene::MenuScene():NO2Scene() {
    
    setLayoutWidth(_NO2STRING("85%"));

	loadHTML("example9.html");
    
    ((NO2GridView *)getElementById("gridview_example9"))->setDataSource(this);
}

MenuScene::~MenuScene() {
}

// ******** Begin of Scene methods ********

void MenuScene::onCommand(int command, int subcommand, NO2Object *object) {
	switch (command) {
		default: {
			break;
		}
	}
}
// ****************************************


int MenuScene::numberOfSections(NO2Drawable *container) {
    return 1;
}

int MenuScene::numberOfItemsInSection(NO2Drawable *container, int section) {
    return 10;
}

NO2String *MenuScene::templateForIndex(NO2Drawable *container, const NO2IndexPath &indexPath) {
    return _NO2STRING("example9_cell.html");
}
