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
