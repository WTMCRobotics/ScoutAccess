#include <iostream>
#include <string>
#include <afxdb.h>			// For the database
#include <SFML/Graphics.hpp>		// For the joysticks and window

const int WIN_WIDTH = 999;
const int WIN_HEIGHT = 700;

const int BORDER_WIDTH = 2;

const int HEAD_HEIGHT = 50;
const int BOX_HEIGHT = 325;
const int BOX_WIDTH = 333;

int main()
{
	// Variables to store values read from the database
	CString red3Team;
	CString currentTeamMatch;
	
	// Integer variable for storing in database
	int autoGearRed3 = 5;
	// String variable that will store the converted integer
	std::string autoGearRed3Str;
	
	// Database object
	CDatabase database;
	// Object that can store records
	CRecordset results(&database);
	// Variable that store path to the Microsoft Access file
	CString file = L"C:\\Users\\Test\\Desktop\\ScoutAccess-master\\scouting.accdb";
	// Variable for storing the driver that will allow Access files to be used in a program
	CString driver = L"MICROSOFT ACCESS DRIVER (*.mdb, *.accdb)";
	// Variable to store the connection information
	CString dSN;
	// Formats the connection information with the driver and file values
	dSN.Format(L"ODBC;DRIVER={%s};DSN='';DBQ=%s", driver, file);
	// Opens the database
	database.Open(NULL, false, false, dSN);

	// SQL query for grabbing the teams from the matches table
	// SELECT TOP [Number of Records] [List of Columns] FROM [table] WHERE [column]=[value] ORDER BY [column] [ASC, DESC]
	CString selectTeamsQuery = "SELECT TOP 1 red1, red2, red3, blue1, blue2, blue3 FROM matches WHERE hasPlayed=false ORDER BY matchNumber ASC";
	// Execute the query and save the matching record in the object called results
	results.Open(CRecordset::forwardOnly, selectTeamsQuery, CRecordset::readOnly);
	// Get the value in the column "red3" and store it in "red3Team" (for the first record in results [only record since TOP 1])
	results.GetFieldValue(L"red3", red3Team);
	// Clear the object of the records from the last query
	results.Close();

	// Print the value from red3Team to the console
	std::wcout << red3Team.GetString() << std::endl;

	// SQL query for grabbing red 3's next match (Match 1 through Match 12)
	// SELECT TOP [Number of Records] [List of Columns] FROM [table] WHERE [column]=[value] ORDER BY [column] [ASC, DESC]
	CString selectNextTeamMatchQuery = "SELECT TOP 1 match FROM " + red3Team + " WHERE hasPlayed=false ORDER BY match ASC";
	// Execute the query and save the matching record in the object called results
	results.Open(CRecordset::forwardOnly, selectNextTeamMatchQuery, CRecordset::readOnly);
	// Get the value in the column "match" and store it in "currentTeamMatch" (for the first record in results [only record since TOP 1])
	results.GetFieldValue(L"match", currentTeamMatch);
	// Clear the object of the records from the last query
	results.Close();
	
	// Print the value from currentTeamMatch to the console
	std::wcout << currentTeamMatch.GetString() << std::endl;

	// Convert the integer to a string
	autoGearRed3Str = std::to_string(autoGearRed3);
	// Update the record for a team
	// UPDATE [table] SET [column]=[value], [column]=[value] WHERE [column]=[value]
	// .c_str() function converts the string to a CString
	CString updateRed3Query = "UPDATE " + red3Team + " SET hasPlayed=true, autoGear=" + autoGearRed3Str.c_str() + " WHERE match=" + currentTeamMatch;
	// Execute the update query
	database.ExecuteSQL(updateRed3Query);

	// Close the connection to the database
	database.Close();
	

	// Make a new window that you can close and has a titlebar
	sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Scouting Program", sf::Style::Close | sf::Style::Titlebar);

	// 0,0 is at the top left and the bottom right is WIN_WIDTH, WIN_HEIGHT
	// Create a rectangle called header that is a thin rectangle at the top of the window
	sf::RectangleShape header(sf::Vector2f(WIN_WIDTH, HEAD_HEIGHT));
	// Set the position of the rectangle to all the way left and down BORDER_WIDTH
	header.setPosition(sf::Vector2f(0, BORDER_WIDTH));
	// Set fill color to a gray (r,g,b)
	header.setFillColor(sf::Color::Color(248, 248, 248));
	// Set the outline color to black
	header.setOutlineColor(sf::Color::Black);
	// Set the outline thickness to BORDER_WIDTH
	header.setOutlineThickness(BORDER_WIDTH);

	// Create a rectangle that will be one of six boxes
	sf::RectangleShape r1Box(sf::Vector2f(BOX_WIDTH, BOX_HEIGHT));
	// Top left box
	r1Box.setPosition(sf::Vector2f(0, HEAD_HEIGHT + (BORDER_WIDTH * 2)));
	r1Box.setFillColor(sf::Color::Color(248, 248, 248));
	r1Box.setOutlineColor(sf::Color::Black);
	r1Box.setOutlineThickness(BORDER_WIDTH);

	// Create a rectangle that will be one of six boxes
	sf::RectangleShape r2Box(sf::Vector2f(BOX_WIDTH, BOX_HEIGHT));
	// Top middle box
	r2Box.setPosition(sf::Vector2f(BOX_WIDTH + BORDER_WIDTH, HEAD_HEIGHT + (BORDER_WIDTH * 2)));
	r2Box.setFillColor(sf::Color::Color(248, 248, 248));
	r2Box.setOutlineColor(sf::Color::Black);
	r2Box.setOutlineThickness(BORDER_WIDTH);

	// Create a rectangle that will be one of six boxes
	sf::RectangleShape r3Box(sf::Vector2f(BOX_WIDTH, BOX_HEIGHT));
	// Top right box
	r3Box.setPosition(sf::Vector2f((BOX_WIDTH + BORDER_WIDTH) * 2, HEAD_HEIGHT + (BORDER_WIDTH * 2)));
	r3Box.setFillColor(sf::Color::Color(248, 248, 248));
	r3Box.setOutlineColor(sf::Color::Black);
	r3Box.setOutlineThickness(BORDER_WIDTH);

	// Create a rectangle that will be one of six boxes
	sf::RectangleShape b1Box(sf::Vector2f(BOX_WIDTH, BOX_HEIGHT));
	// Bottom left box
	b1Box.setPosition(sf::Vector2f(0, HEAD_HEIGHT + BOX_WIDTH - BORDER_WIDTH));
	b1Box.setFillColor(sf::Color::Color(248, 248, 248));
	b1Box.setOutlineColor(sf::Color::Black);
	b1Box.setOutlineThickness(BORDER_WIDTH);

	// Create a rectangle that will be one of six boxes
	sf::RectangleShape b2Box(sf::Vector2f(BOX_WIDTH, BOX_HEIGHT));
	// Bottom middle box
	b2Box.setPosition(sf::Vector2f(BOX_WIDTH + BORDER_WIDTH, HEAD_HEIGHT + BOX_WIDTH - BORDER_WIDTH));
	b2Box.setFillColor(sf::Color::Color(248, 248, 248));
	b2Box.setOutlineColor(sf::Color::Black);
	b2Box.setOutlineThickness(BORDER_WIDTH);

	// Create a rectangle that will be one of six boxes
	sf::RectangleShape b3Box(sf::Vector2f(BOX_WIDTH, BOX_HEIGHT));
	// Bottom right box
	b3Box.setPosition(sf::Vector2f((BOX_WIDTH + BORDER_WIDTH) * 2, HEAD_HEIGHT + BOX_WIDTH - BORDER_WIDTH));
	b3Box.setFillColor(sf::Color::Color(248, 248, 248));
	b3Box.setOutlineColor(sf::Color::Black);
	b3Box.setOutlineThickness(BORDER_WIDTH);

	// for loop that runs 8 times (8 joysticks possible with SFML)
	for (int i = 0; i < 8; i++)
	{
		// Prints label for each Joystick 0-7
		std::cout << "Joystick " << i << " : ";
		// if statement testing if joystick is connected
		if (sf::Joystick::isConnected(i))
			// if connected, print true
			std::cout << "true\n";
		else
			// if not connected, print false
			std::cout << "false\n";
	} // END of for loop for joystick connections
	
	// Event object that can be used in a switch statement
	sf::Event event;
	// while loop that runs as long as the window is open
	while (window.isOpen())
	{
		// while loop that runs as long as there are pending events
		while (window.pollEvent(event))
		{
			// switch statement that depends on the event type
			switch(event.type)
			{
				// if window closed
				case sf::Event::Closed:
					// close window
					window.close();
					break;
			} // END of event switch statement
		} // END of while loop when there are pending events
		
		// Clear the window where blank space will be blue
		window.clear(sf::Color::Blue);
		
		// Draw all the rectangles created
		window.draw(header);
		window.draw(r1Box);
		window.draw(r2Box);
		window.draw(r3Box);
		window.draw(b1Box);
		window.draw(b2Box);
		window.draw(b3Box);
		// Display everything drawn
		window.display();
	} // END of whle loop when window is open

	return 0;
}
