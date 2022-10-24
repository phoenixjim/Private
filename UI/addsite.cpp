#include "Private.h"
struct AddNew : public WithNewSiteLayout<TopWindow> {
	SqlCtrls ctrls;
	AddNew();
};
AddNew::AddNew()
{
		CtrlLayoutOKCancel(*this, "Add Site");
		cancel << [=] { Close(); };
		// ok << [=] { // insert new site };
		ctrls
			(PID, edtPID)
			(SITENAME, edtSite)
			(USERNAME, edtUName)
			(PASSWORD, edtPWord)
			;
}

AddSite::AddSite() {
	CtrlLayout(*this, "Sites");
	sqlPrivate.Appending().Removing();
	sqlPrivate.SetTable(SITEINFO);
	sqlPrivate.AddColumn(PID, "ID");
	sqlPrivate.AddColumn(SITENAME, "Site");
	sqlPrivate.AddColumn(USERNAME, "User");
	sqlPrivate.AddColumn(PASSWORD, "PW");
	
	btnNewSite << [=] {
		addNewSite();
    	sqlPrivate.ReQuery();
	};
	cancel << [=] { Close(); };
}
void AddSite::addNewSite()
{
	// check for nulls then
	AddNew dlg;
	if(dlg.Run() == IDOK)
		SQL * dlg.ctrls.Insert(SITEINFO); 
}