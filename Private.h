#ifndef _Private_Private_h
#define _Private_Private_h

#include <CtrlLib/CtrlLib.h>

#include <plugin/sqlite3/Sqlite3.h>

using namespace Upp;

#define LAYOUTFILE <Private/Private.lay>
#include <CtrlCore/lay.h>
#define SCHEMADIALECT <plugin/sqlite3/Sqlite3Schema.h>
#define MODEL "Private/Private.sch"
#include "Sql/sch_header.h"


class Private : public WithPrivateLayout<TopWindow> {
public:
	Private();
};

#endif
