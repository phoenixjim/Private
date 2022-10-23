#ifndef _Private_sqlIncludes_h_
#define _Private_sqlIncludes_h_

#include <SqlCtrl/SqlCtrl.h>
#include <plugin/sqlite3/Sqlite3.h>

using namespace Upp;

#define SCHEMADIALECT <plugin/sqlite3/Sqlite3Schema.h>
#define MODEL "Private/Tables/Private.sch"
#include <Sql/sch_header.h>
#undef MODEL

#endif
