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

Secrets::Secrets()
{
	CtrlLayout(*this, "Secrets");
	
	btnAddSite << [=] {
    	if(!newsite.IsOpen()) {
    		// newsite.sqlPrivate.ReQuery();
    		newsite.Open(this); 
    		}
    };
}

GUI_APP_MAIN
{
	Unlock dlg;
	if(dlg.Run() != IDOK) return;
	String password = dlg.txtPW.GetData().ToString();
	dlg.Close();
	
	Sqlite3Session sqlite3;
	if(!sqlite3.Open("private.db", password, Sqlite3Session::CIPHER_SQLCIPHER)) {
		int errCode = sqlite3.GetErrorCode();
		String errMsg = Format("[ %s&&Error: %d (%s)]", t_("Loading the database has failed!"), errCode, sqlite3.GetErrorCodeString());
		if (errCode == 26 /* SQLITE_NOTADB */) {
			errMsg = t_("The database is encrypted but decryption failed!&[= Did you use the correct password?");
		}
 		ErrorOK(errMsg);
		return;
	}
	
	SQL = sqlite3;

	SqlSchema sch(SQLITE3);
	All_Tables(sch);
	SqlPerformScript(sch.Upgrade());
	SqlPerformScript(sch.Attributes());
	SQL.ClearError();

	Secrets().Run();
}
