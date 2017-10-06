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
// DESCRIPTION: Appwizard generated plugin
// AUTHOR: Paul Wolff
//***************************************************************************/

#include "RealtimeReferencingUtility.h"





#define RealtimeReferencingUtility_CLASS_ID	Class_ID(0x658d5daf, 0x48191fb5)
#define Controller SceneController::Instance()


#define ID_ACTION1 1
#define ID_ACTION2 2
//Generate IDs with gencid.exe
const ActionTableId kMyActions = 0x6b11896;
const ActionContextId kMyContext = 0x45386acd;
//MenuContextID created with Autodesk Class ID generator
#define rtMainMenuContextID 0x35ca2db5

// Action Table Setup

// This packages up our actions into an ActionDescription for our ActionTable
static ActionDescription spActions[] = {
	ID_ACTION1, // ID
	IDS_ACTION_POPUP_DESC, // menu1
	IDS_ACTION_POPUP,
	IDS_AT_CATEGORY,

	ID_ACTION2,
	IDS_ACTION_ABOUT_DESC,
	IDS_ACTION_ABOUT,
	IDS_AT_CATEGORY
};


class RealtimeReferencingActionTable : public ActionTable {
public:
	RealtimeReferencingActionTable() : ActionTable(kMyActions, kMyContext, TSTR(GetString(IDS_AT_CATEGORY))) {
		BuildActionTable(NULL, sizeof(spActions) / sizeof(spActions[0]), spActions, hInstance);
	};

	~RealtimeReferencingActionTable() {
	}
};




class RealtimeReferencingUtility : public GUP, ActionCallback
{
public:
		
	//Constructor/Destructor
	RealtimeReferencingUtility();
	virtual ~RealtimeReferencingUtility();
	HWND hMapper;
	
	// GUP Methods
	virtual DWORD     Start();
	virtual void      Stop();
	virtual DWORD_PTR Control(DWORD parameter);
	virtual void      DeleteThis();

	// Loading/Saving
	virtual IOResult Save(ISave* isave);
	virtual IOResult Load(ILoad* iload);


	BOOL ExecuteAction(int id) override;

private:

	void OpenRefMenu();

	void InstallMenu();

	void RemoveMenu();

	HWND   hPanel;
	IUtil* iu;
	
	IRollupWindow* rWindow;
	RefMenu * refMenu;
	about_popup * aboutPopup;

	// CUstom Variables
};

static bool menuActive;

class RealtimeReferencingUtilityClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 	{ return new RealtimeReferencingUtility(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return GUP_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return RealtimeReferencingUtility_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("RealtimeReferencingUtility"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle
	
	int NumActionTables() override { return 1; }
	ActionTable* GetActionTable(int) override
	{
		if (s_actionTable == nullptr)
		{
			s_actionTable = new RealtimeReferencingActionTable();
		}
		return s_actionTable;
	}

private:
	ActionTable* s_actionTable = nullptr;
};


ClassDesc2* GetRealtimeReferencingUtilityDesc() { 
	static RealtimeReferencingUtilityClassDesc RealtimeReferencingUtilityDesc;
	return &RealtimeReferencingUtilityDesc; 
}



//--- RealtimeReferencingUtility -------------------------------------------------------
RealtimeReferencingUtility::RealtimeReferencingUtility()
{

}

RealtimeReferencingUtility::~RealtimeReferencingUtility()
{
}

DWORD RealtimeReferencingUtility::Start()
{
	if (refMenu == nullptr) {
		refMenu = new RefMenu();
		refMenu->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::WindowStaysOnTopHint);
	}
	if (aboutPopup == nullptr) {
		aboutPopup = new about_popup();
		aboutPopup->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
	}
	InstallMenu();
	return GUPRESULT_KEEP;
}

void RealtimeReferencingUtility::Stop()
{
	RemoveMenu();
}

DWORD_PTR RealtimeReferencingUtility::Control(DWORD parameter)
{
	return DWORD_PTR();
}

void RealtimeReferencingUtility::DeleteThis()
{
	delete this;
}

IOResult RealtimeReferencingUtility::Save(ISave * isave)
{
	return IO_OK;
}

IOResult RealtimeReferencingUtility::Load(ILoad * iload)
{
	return IO_OK;
}


BOOL RealtimeReferencingUtility::ExecuteAction(int id)
{
	switch (id)
	{
	case ID_ACTION1:
		this->refMenu->show();
		return true;

	case ID_ACTION2:
		this->aboutPopup->show();
		return true;
	}
	return false;
}


void RealtimeReferencingUtility::InstallMenu() {
	//Get MenuManager from CoreInterface und look for our custom menu
	IMenuManager* manager = GetCOREInterface()->GetMenuManager();
	IMenu* menu = manager->FindMenu(GetString(IDS_MAIN_MENU_NAME));

	//If menu is not found a new menu will be created
	if (menu == NULL) {
		GetCOREInterface()->PushPrompt(L"Menu Not Found");

		IMenuBarContext* menuContext = (IMenuBarContext*)manager->GetContext(kMainMenuBar);
		IMenu* mainMenu = menuContext->GetMenu();

		// Make sure context is registered
		manager->RegisterMenuBarContext(rtMainMenuContextID, GetString(IDS_MAIN_MENU_NAME));

		// add menu itself
		IMenu* menuEx = GetIMenu();
		menuEx->SetTitle(GetString(IDS_MAIN_MENU_NAME));
		manager->RegisterMenu(menuEx, 0);
		IMenuBarContext* context = (IMenuBarContext*)manager->GetContext(rtMainMenuContextID);
		context->SetMenu(menuEx);

		// Set up our actions / callbacks
		IActionManager* actionMgr = GetCOREInterface()->GetActionManager();
		if (actionMgr)
		{
			actionMgr->ActivateActionTable(this, kMyActions);
		}

		ActionTable* table = GetRealtimeReferencingUtilityDesc()->GetActionTable(0);
		TSTR s = table->GetName();
		//MenuDemoActionManager::SetUpActions();
		IMenuItem* itemSub3 = GetIMenuItem();
		ActionItem* action = table->GetAction(ID_ACTION1);
		itemSub3->SetActionItem(action);
		//itemSub3->SetUseCustomTitle(true);
		//itemSub3->SetTitle(_T("Menu Example: Print something 1"));
		menuEx->AddItem(itemSub3);

		IMenuItem* itemSub4 = GetIMenuItem();
		action = table->GetAction(ID_ACTION2);
		itemSub4->SetActionItem(action);
		//itemSub4->SetUseCustomTitle(true);
		//itemSub4->SetTitle(_T("Menu Example: Print something 2"));
		menuEx->AddItem(itemSub4);


		// Make a new "sub" menu item that will be installed to the menu bar
		IMenuItem* itemMainEx = GetIMenuItem();
		itemMainEx->SetSubMenu(menuEx);

		// Add the menu and update the bar to see it.
		mainMenu->AddItem(itemMainEx, -1);
		manager->UpdateMenuBar();
	}
	else {
		GetCOREInterface()->PushPrompt(L"Menu Found");
	}
	return;
}


void RealtimeReferencingUtility::RemoveMenu()
{
	IMenuManager* manager = GetCOREInterface()->GetMenuManager();
	IMenu* menu = manager->FindMenu(GetString(IDS_MAIN_MENU_NAME));

	if (menu)
	{
		while (menu->NumItems() > 0)
		{
			menu->RemoveItem(0);
		}

		// Remove menu from context
		IMenuBarContext* context = (IMenuBarContext*)manager->GetContext(rtMainMenuContextID);
		context->SetMenu(NULL);
		manager->UnRegisterMenu(menu);

		manager->UpdateMenuBar();
	}
}
