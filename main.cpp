#include "Private.h"

#include <Sql/sch_schema.h>
#include <Sql/sch_source.h>

Private::Private()
{
	CtrlLayout(*this, "Private");
}

GUI_APP_MAIN
{
	Sqlite3Session sqlite3;
	if(!sqlite3.Open(ConfigFile("private.db"))) {
		PromptOK("Can't create or open database file\n");
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
