#include <iostream>
#include <string>
#include <afxdb.h>
int main()
{
	CString red3Team;
	CString currentMatch;
	CDatabase database;
	CRecordset results(&database);
	CString file = L"C:\\Users\\Test\\Documents\\Visual Studio 2013\\Projects\\ScoutingWithAccess\\scouting.accdb";
	CString driver = L"MICROSOFT ACCESS DRIVER (*.mdb, *.accdb)";
	CString dSN;
	dSN.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s", driver, file);
	database.Open(NULL, false, false, dSN);
	CString selectTeamsQuery = "SELECT TOP 1 red1, red2, red3, blue1, blue2, blue3 FROM matches WHERE hasPlayed=false ORDER BY matchNumber ASC";
	results.Open(CRecordset::forwardOnly, selectTeamsQuery, CRecordset::readOnly);
	results.GetFieldValue(L"red3", red3Team);
	results.Close();
	CString selectNextTeamMatchQuery = "SELECT Min(match) AS currentMatch FROM 6101 WHERE hasPlayed=false";
	results.Open(CRecordset::forwardOnly, selectNextTeamMatchQuery, CRecordset::readOnly);
	results.GetFieldValue(L"currentMatch", currentMatch);
	CString updateRed3Query = "UPDATE " + red3Team + " SET hasPlayed=true, autoGear=1 WHERE match=" + currentMatch;
	database.ExecuteSQL(updateRed3Query);
	
	std::wcout << currentMatch.GetString() << std::endl;
	std::wcout << selectNextTeamMatchQuery.GetString();

	database.Close();

	return 0;
}