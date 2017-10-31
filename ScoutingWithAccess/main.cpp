#include <iostream>
#include <string>
#include <afxdb.h>
#include <SFML/Graphics.hpp>

const int WIN_WIDTH = 999;
const int WIN_HEIGHT = 700;

const int BORDER_WIDTH = 2;

const int HEAD_HEIGHT = 50;
const int BOX_HEIGHT = 325;
const int BOX_WIDTH = 333;


int main()
{
	sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Scouting Program", sf::Style::Close | sf::Style::Titlebar);

	sf::RectangleShape header(sf::Vector2f(WIN_WIDTH, HEAD_HEIGHT));
	header.setPosition(sf::Vector2f(0, BORDER_WIDTH));
	header.setFillColor(sf::Color::Color(248, 248, 248));
	header.setOutlineColor(sf::Color::Black);
	header.setOutlineThickness(BORDER_WIDTH);

	sf::RectangleShape r1Box(sf::Vector2f(BOX_WIDTH, BOX_HEIGHT));
	r1Box.setPosition(sf::Vector2f(0, HEAD_HEIGHT + (BORDER_WIDTH * 2)));
	r1Box.setFillColor(sf::Color::Color(248, 248, 248));
	r1Box.setOutlineColor(sf::Color::Black);
	r1Box.setOutlineThickness(BORDER_WIDTH);

	sf::RectangleShape r2Box(sf::Vector2f(BOX_WIDTH, BOX_HEIGHT));
	r2Box.setPosition(sf::Vector2f(BOX_WIDTH + BORDER_WIDTH, HEAD_HEIGHT + (BORDER_WIDTH * 2)));
	r2Box.setFillColor(sf::Color::Color(248, 248, 248));
	r2Box.setOutlineColor(sf::Color::Black);
	r2Box.setOutlineThickness(BORDER_WIDTH);

	sf::RectangleShape r3Box(sf::Vector2f(BOX_WIDTH, BOX_HEIGHT));
	r3Box.setPosition(sf::Vector2f((BOX_WIDTH + BORDER_WIDTH) * 2, HEAD_HEIGHT + (BORDER_WIDTH * 2)));
	r3Box.setFillColor(sf::Color::Color(248, 248, 248));
	r3Box.setOutlineColor(sf::Color::Black);
	r3Box.setOutlineThickness(BORDER_WIDTH);

	sf::RectangleShape b1Box(sf::Vector2f(BOX_WIDTH, BOX_HEIGHT));
	b1Box.setPosition(sf::Vector2f(0, HEAD_HEIGHT + BOX_WIDTH - BORDER_WIDTH));
	b1Box.setFillColor(sf::Color::Color(248, 248, 248));
	b1Box.setOutlineColor(sf::Color::Black);
	b1Box.setOutlineThickness(BORDER_WIDTH);

	sf::RectangleShape b2Box(sf::Vector2f(BOX_WIDTH, BOX_HEIGHT));
	b2Box.setPosition(sf::Vector2f(BOX_WIDTH + BORDER_WIDTH, HEAD_HEIGHT + BOX_WIDTH - BORDER_WIDTH));
	b2Box.setFillColor(sf::Color::Color(248, 248, 248));
	b2Box.setOutlineColor(sf::Color::Black);
	b2Box.setOutlineThickness(BORDER_WIDTH);

	sf::RectangleShape b3Box(sf::Vector2f(BOX_WIDTH, BOX_HEIGHT));
	b3Box.setPosition(sf::Vector2f((BOX_WIDTH + BORDER_WIDTH) * 2, HEAD_HEIGHT + BOX_WIDTH - BORDER_WIDTH));
	b3Box.setFillColor(sf::Color::Color(248, 248, 248));
	b3Box.setOutlineColor(sf::Color::Black);
	b3Box.setOutlineThickness(BORDER_WIDTH);

	for (int i = 0; i < 8; i++)
	{
		std::cout << "Joystick " << i << " : ";
		if (sf::Joystick::isConnected(i))
			std::cout << "true\n";
		else
			std::cout << "false\n";
	}

	CString red3Team;
	CString currentTeamMatch;
	CDatabase database;
	CRecordset results(&database);
	CString file = L"C:\\Users\\cyham\\Documents\\Visual Studio 2013\\Projects\\ScoutingProgramAccess\\scouting.accdb";
	CString driver = L"MICROSOFT ACCESS DRIVER (*.mdb, *.accdb)";
	CString dSN;
	dSN.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s", driver, file);
	database.Open(NULL, false, false, dSN);

	CString selectTeamsQuery = "SELECT TOP 1 red1, red2, red3, blue1, blue2, blue3 FROM matches WHERE hasPlayed=false ORDER BY matchNumber ASC";
	results.Open(CRecordset::forwardOnly, selectTeamsQuery, CRecordset::readOnly);
	results.GetFieldValue(L"red3", red3Team);
	results.Close();

	std::wcout << red3Team.GetString() << std::endl;

	
	CString selectNextTeamMatchQuery = "SELECT TOP 1 match FROM " + red3Team + " WHERE hasPlayed=false ORDER BY match ASC";
	results.Open(CRecordset::forwardOnly, selectNextTeamMatchQuery, CRecordset::readOnly);
	results.GetFieldValue(L"match", currentTeamMatch);
	results.Close();
	std::wcout << currentTeamMatch.GetString() << std:: endl;

	int autoGearRed3 = 5;
	std::string autoGearRed3Str = std::to_string(autoGearRed3);
	CString updateRed3Query = "UPDATE " + red3Team + " SET hasPlayed=true, autoGear=" + autoGearRed3Str.c_str() + " WHERE match=" + currentTeamMatch;
	database.ExecuteSQL(updateRed3Query);

	std::wcout << currentTeamMatch.GetString() << std::endl;

	database.Close();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Blue);
		window.draw(header);
		window.draw(r1Box);
		window.draw(r2Box);
		window.draw(r3Box);
		window.draw(b1Box);
		window.draw(b2Box);
		window.draw(b3Box);
		window.display();
	}

	return 0;
}