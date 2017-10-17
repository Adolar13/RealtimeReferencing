#pragma once

//**************************************************************************/
// Copyright (c) 1998-2007 Autodesk, Inc.
// All rights reserved.
// 
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: Includes for Plugins
// AUTHOR: 
//***************************************************************************/

#include "3dsmaxsdk_preinclude.h"
#include "resource.h"
#include "RefObject.h"
#include "RefMenu.h"
#include "about_popup.h"


#include <istdplug.h>
#include <iparamb2.h>
#include <iparamm2.h>
#include <maxtypes.h>
#include <imenus.h>
#include <imenuman.h>
#include <actiontable.h>
#include <triobj.h>
#include <custcont.h>

#include <Qt/QMaxParamBlockWidget.h>


//SIMPLE TYPE

#include <utilapi.h>
#include <guplib.h>


extern TCHAR *GetString(int id);

extern HINSTANCE hInstance;
