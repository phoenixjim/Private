#include "Private.h"

#define MODEL "Private/Tables/Private.sch"
#include <Sql/sch_schema.h>
#include <Sql/sch_source.h>
#undef MODEL


class Unlock : public WithGetPassLayout<TopWindow> {
	public:
		Unlock();
};


Unlock::Unlock()
{
	CtrlLayoutOKCancel(*this, "Unlock");
	txtPW.Password();
	cancel << [=] { Close(); };
	ok << [=] { AddItem(); };

}

AddPass::AddPass()
{
	CtrlLayoutOKCancel(*this, "Add Password Entry");
	ctrls
		(PID, edtPID)
		(SITENAME, edtSite)
		(USERNAME, edtUName)
		(PASSWORD, edtPWord)
		;
	
}

AddPass::AddItem()
{
	AddProduct dlg("Add Product");
	if(dlg.Run() != IDOK)
		return;
	SQL * dlg.ctrls.Insert(PRODUCTS);

    int id = SQL.GetInsertedId();

    ProductArray.ReQuery();
    ProductArray.FindSetCursor(id);

}

Private::Private()
{
	CtrlLayout(*this, "Private");
	sqlPrivate.Appending().Removing();
	sqlPrivate.SetTable(PRIVATE);
	txtAddPass << [=] { AddPW(); };

}

void Private::AddPW()
{
	if(!ap.IsOpen()) {
		ap.Open(this); 
		}
	
	sqlPrivate.ReQuery();
}

GUI_APP_MAIN
{
	Unlock dlg;
	if(dlg.Run(true) != IDOK) return;
	String password = dlg.txtPW.GetData().ToString();
	Sqlite3Session sqlite3;
	if(!sqlite3.Open("private.db", password)) {
		PromptOK("Can't create or open database file");
		return;
	}
	
	SQL = sqlite3;

	SqlSchema sch(SQLITE3);
	All_Tables(sch);
	SqlPerformScript(sch.Upgrade());
	SqlPerformScript(sch.Attributes());
	SQL.ClearError();

	Private().Run();
}
