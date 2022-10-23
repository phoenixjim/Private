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
	// Check if file exists, if not, use to set initial password instead
	CtrlLayoutOKCancel(*this, "Unlock");
	txtPW.Password(true);
	cancel << [=] { Close(); };
	optShowPW.WhenAction << [=] { txtPW.Password(!(bool)optShowPW.Get()); };
	optShowPW.Set(false);
}

Private::Private()
{
	CtrlLayout(*this, "Private");
	sqlPrivate.Appending().Removing();
	sqlPrivate.SetTable(PRIVATE);
}

GUI_APP_MAIN
{
	Unlock dlg;
	if(dlg.Run() != IDOK) return;
	String password = dlg.txtPW.GetData().ToString();
	dlg.Close();
	
	Sqlite3Session sqlite3;
	// AES 256 isn't supported? Only Chaha variants? I'll look deeper into that...
	if(!sqlite3.Open("private.db", password)) {
		PromptOK("Can't create or open database file, or bad password.");
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
