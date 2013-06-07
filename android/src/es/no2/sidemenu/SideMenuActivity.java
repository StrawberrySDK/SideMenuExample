/*
 *  NO2 Web and Mobile Applications, S.L CONFIDENTIAL
 *
 *  Strawberry SDK ( OpenGL + HTML + CSS  cross-platform framework )
 *  Copyright 2010-2012 NO2 Web and Mobile Applications, S.L. All rights reserved.
 *
 * 
 *  NOTICE:  All information contained herein is, and remains
 *  the property of NO2 Web and Mobile Applications, S.L and its suppliers,
 *  if any.  The intellectual and technical concepts contained
 *  herein are proprietary to NO2 Web and Mobile Applications, S.L
 *  and its suppliers, and are protected by trade secret or copyright law.
 *  Dissemination of this information or reproduction of this material
 *  is strictly forbidden unless prior written permission is obtained
 *  from NO2 Web and Mobile Applications, S.L.
 */ 

package es.no2.sidemenu;

import es.no2.no2gl.MainActivity;
import android.os.Bundle;

public class SideMenuActivity extends MainActivity
{
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState, R.layout.main, R.id.glview);
    }
}

