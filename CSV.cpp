// Made by Rahim Sarpas

// Separate Class files created to manage CSV Handling
// Without conflicting with UE4 core definitions
// and lack of CSV file handling within UE4 C++ API

#include "CSV.h"
#include <iostream> // IO Library 
#include <fstream> // File Handling Library

// No global namespace used to comply with UE4 documentation standards

// Initializes Dynamic Vector of Int Vectors and String Vector
// - Dynamic data used to reduce memory utilization
CSV::CSV()
{
	other = new std::vector<std::vector<int>>;
	text = new std::vector<std::string>;
}

/*
* Gets the vector of vector ints from CSV Class
* @return A vector of vector ints
*/
std::vector<std::vector<int>>* CSV::getTable()
{
	return other;
}

/*
* Gets the vector of text from CSV Class
* @return A vector of strings
*/
std::vector<std::string>* CSV::getText()
{
	return text;
}

/*
* Gets the position of the row with the highest priority
* Assumptions:
*	- Priorities range from 1 to 100 with 1 being the highest
*	- Num returned will reflect 1st position notation according to c++
*	- Three vectors of type int are within other at all times
* @return An int for position
*/
int CSV::getPriority(int pos)
{
	// The priority of the row, defaulted to returning -1 if empty
	int priority = -1;

	// If size is less than or equal to 0, return 0 to show that its empty
	if (other->size() <= 0)
		return 0;
	else
	{
		// Get the duration
		priority = other->at(0).at(pos);
		// Return the priority
		return priority;
	}
	// Defaults to returning -1 if empty
	return -1;
}

/*
* Gets the position of the row with the highest priority
* Assumptions:
*	- Priorities range from 1 to 100 with 1 being the highest
*	- Num returned will reflect 1st position notation according to c++
*	- Three vectors of type int are within other at all times
* @return An int for position
*/
int CSV::getPriorityRow()
{
	// Variable for min priority, set to 100 since range is from 1 to 100
	int min = 100;
	// The position of the highest priority row, set to -1 incase empty
	int position = -1;

	// If size is less than or equal to 0, return a negative number
	// to show that its empty
	if (other->size() <= 0)
		return -1;
	else
	{
		// Loop and get the position of the row with highest priority
		for (int i = 0; i < other->at(0).size(); i++)
		{
			if ((other->at(0).at(i)) < min)
			{
				min = other->at(0).at(i);
				position = i;
			}
		}
		// Return the row position of the highest priority
		return position;
	}

	// Catch statement in case no return is called
	return -1;
}

/*
* Gets the value of a given row's duration
* Assumptions:
*	- Num returned will reflect 1st position notation according to c++
*	- Three vectors of type int are within other at all times
* @param pos The position of the row
* @return An int for duration
*/
int CSV::getDur(int pos)
{
	// The duration of the row, defaulted to returning zero if empty
	int duration = 0;

	// If size is less than or equal to 0, return 0 to show that its empty
	if (other->size() <= 0)
		return 0;
	else
	{
		// Get the duration
		duration = other->at(1).at(pos);
		// Return the duration
		return duration;
	}
	// Defaults to returning zero if empty
	return 0;
}

/*
* Gets the position of the row with the earliest start
* Assumptions:
*	- Start times are in miliseconds
*	- Start times wont go past a million squared
*	- Num returned will reflect 1st position notation according to c++
*	- Three vectors of type int are within other at all times
* @return An int for position
*/
int CSV::getEarlyStart()
{	
	// Variable for earliest start, set to a million squared
	int min = 1000000 * 100000;
	// The position of the earliest start row, set to -1 incase empty
	int position = -1;

	// If size is less than or equal to 0, return a negative number
	// to show that its empty
	if (other->size() <= 0)
		return -1;
	else
	{
		// Loop and get the position of the row with the earliest start
		for (int i = 0; i < other->at(2).size(); i++)
		{
			if ((other->at(2).at(i)) < min)
			{
				min = other->at(2).at(i);
				position = i;
			}
		}
		// Return the row position of the earliest start
		return position;
	}

	// Catch statement in case no return is called
	return -1;
}

/*
* Gets the value of a given row's start time
* Assumptions:
*	- Start times are in miliseconds
*	- Start times wont go past a million
*	- Num returned will reflect 1st position notation according to c++
*	- Three vectors of type int are within other at all times
* @param pos The position of the row
* @return An int for position
*/
int CSV::getStart(int pos)
{
	// The start time of the row, defaulted to returning zero if empty
	int startTime = 0;

	// If size is less than or equal to 0, return 0 to show that its empty
	if (other->size() <= 0)
		return 0;
	else
	{
		// Get the duration
		startTime = other->at(2).at(pos);
		// Return the row position of the highest priority
		return startTime;
	}
	// Defaults to returning zero if empty
	return 0;
}

/*
* Gets the position of the row that should be displayed first
* Assumptions:
*	- Priorities range from 1 to 100 with 1 being the highest
*	- Start times are in miliseconds
*	- Start times wont go past a million
*	- Num returned will reflect 1st position notation according to c++
*	- Three vectors of type int are within other at all times
* @return An int for position
*/
int CSV::getPrintRow()
{
	// If size is less than or equal to 0, return a negative number
	// to show that its empty
	if (other->size() <= 0)
		return -1;
	else
	{
		// The row position for the earliest start time 
		int earlyStart = getEarlyStart();
		// The row position for the highest priority row
		int highPriority = getPriorityRow();

		// Sort through each position and return the row position 
		// with the earliest start time and highest priority
		// favoring start time first then priority
		if (getStart(earlyStart) < getStart(highPriority))
			return earlyStart;
		else if (getStart(earlyStart) > getStart(highPriority))
			return highPriority;
		else
		{
			// Since the start times are the same, we filter them by priority
			if (getPriority(earlyStart) < getPriority(highPriority))
				return earlyStart;
			else if (getPriority(earlyStart) > getPriority(highPriority))
				return highPriority;
			else
			{
				// Since the priorities are the same, we filter by short duration
				if (getDur(earlyStart) < getDur(highPriority))
					return earlyStart;
				else if (getDur(earlyStart) > getDur(highPriority))
					return highPriority;
				else
				{
					// Since all 3 criteria were equal, 
					// this means that they're the same row
					return (earlyStart = highPriority);
				}
			}
		}
	}

	// Catch statement in case no return is called
	return -1;
}

/*
* Returns the size of the text vector
* Used to return the number of rows
* Assosicated with the table
* @return int The size of the text vector
*/
int CSV::getTextSize()
{
	return text->size();
}

/*
* Returns the size of the other vector
* Used to return the number of columns
* Assosicated with the table
* @return int The size of the other vector
*/
int CSV::getTableSize()
{
	return other->size();
}

/*
* Populates CSV Class Constructor object with CSV Data
* Assumptions:
*	- Data will contain a column of string objects
*	- Data will contain multiple rows and columns of integer objects
*	- Must ignore storing column labels if any are present 
*	- Must allow design for further additions of CSV columns and rows
*	  Beyond what was provided
*	- Delmiter of "," is 1 in length
*	- Column 1 is always a text column
* @param fileName	Name of the file and or filepath
*/
void CSV::updateCSV(std::string fileName)
{
	// Initialize file pointer
	std::fstream file;
	// Open said file with filename and stream of inwards data
	file.open(fileName, std::fstream::in);

	// Variable to be set true if the first line contains labels.
	bool firstLabel = false;

	// If File is successfully opened, continue execution.
	// Otherwise log an error message.
	if (file.is_open())
	{
		// Grabs first line of file and stores it inside a variable.
		std::string Line;
		std::getline(file, Line, '\n');
		
		// Increment position count right before a comma. 
		int pos = 0;
		while (Line[pos] != ',')
			pos++;

		// If Character beyond comma is alpabetical,
		// set firstLabel to true since row 1 is a label row.
		if (isalpha(Line[pos + 2]))
			firstLabel = true;

		// Token count
		int tCount = 0;

		// Reset old position variable
		pos = 0;
		
		// Save Line data in the case its not a label line
		std::string backLine = Line;

		// Find the number of tokens present in a line
		// Excluding the first
		while ((pos = Line.find(',')) != std::string::npos)
		{
			Line.erase(0, (Line.find(',') + 1));
			tCount++;
		}

		// Holder for vector holder
		std::vector<std::vector<int>> hold = createIntVector(tCount);

		// If Row 1 is a label row, ignore row 1 else continue.
		if (firstLabel) 
		{
			// Loop through all csv rows and input data into 
			// CSV class data types.
			while (getline(file, Line))
			{
				// Temp holder for int csv data values
				std::vector<int> temp;

				// Set to true if the text for a row is processed
				bool lineTextProcessed = false;

				// Current position of loop pointer
				int curr = 0;
				
				// Loop through a line
				while (((curr = Line.find(',')) <= std::string::npos) && temp.size() < tCount)
				{	
					if (lineTextProcessed)
					{
						// Add Token to temp vector and increase token count
						temp.push_back(std::stoi(Line.substr(0, Line.find(','))));
					}
					else
					{
						// Add Text Token to CSV string vector
						// And mark lineTextProcessed to true
						text->push_back(Line.substr(0, Line.find(',')));
						lineTextProcessed = true;
					}

					// If ',' present and current pointer isnt out of range
					// Delete one token & shift text foward
					if (Line.find(',') && curr != -1)
					{
						// Shorten string for next loop
						Line.erase(0, Line.find(',') + 1);
					}
					else
						Line.clear(); // Empties string
				}
				// Reset label boolean
				lineTextProcessed = false;
				
				// Move Temp data to hold
				hold = copyData(hold, temp);
			}
		}
		else 
		{
			// Use Line data before calling getline again

			// Add Text Token to CSV string vector
			// And mark lineTextProcessed to true
			text->push_back(backLine.substr(0, backLine.find(',')));
			
			// Shorten string for next loop
			backLine.erase(0, backLine.find(',') + 1);

			// Reset old position variable
			pos = 0;

			// Separate from rest of solution to prevent 
			{
				// Use Instanced vector to hold data
				std::vector<int> temp;

				// Loop until token count is reached
				while (pos < tCount)
				{
					// Store token in temp
					temp.push_back(std::stoi(backLine.substr(0, backLine.find(','))));
					pos++; // increment position
					// Delete previous token
					backLine.erase(0, backLine.find(',') + 1);
				}

				// Store data in hold from temp
				hold = copyData(hold, temp);
			}

			// Loop through all csv rows and input data into 
			// CSV class data types.
			while (getline(file, Line))
			{
				// Temp holder for int csv data values
				std::vector<int> temp;

				// Set to true if the text for a row is processed
				bool lineTextProcessed = false;

				// Current position of loop pointer
				int curr = 0;

				// Loop through a line
				while (((curr = Line.find(',')) <= std::string::npos) && temp.size() < tCount)
				{
					if (lineTextProcessed)
					{
						// Add Token to temp vector and increase token count
						temp.push_back(std::stoi(Line.substr(0, Line.find(','))));
					}
					else
					{
						// Add Text Token to CSV string vector
						// And mark lineTextProcessed to true
						text->push_back(Line.substr(0, Line.find(',')));
						lineTextProcessed = true;
					}

					// If ',' present and current pointer isnt out of range
					// Delete one token & shift text foward
					if (Line.find(',') && curr != -1)
					{
						// Shorten string for next loop
						Line.erase(0, Line.find(',') + 1);
					}
					else
						Line.clear(); // Empties string
				}

				// Reset label boolean
				lineTextProcessed = false;

				// Move Temp data to hold
				hold = copyData(hold, temp);

			}
		}
		
		// Loop through hold and add each vector to other
		for (int i = 0; i < hold.size(); i++)
			other->push_back(hold.at(i));
	}
	else 
	{
		std::cerr << "Error opening CSV File."
			<< " Please check console log and debug as necessary" << std::endl;
	}
}

/*
* Takes a row position and then returns the text in that row
* @param pos A row position
* @return A string from the position given row
*/
std::string CSV::printText(int pos)
{
	return (text->at(pos));
}

/*
* Takes a row position and then returns the duration in that row
* Assumption:
*	- Time given is in miliseconds
* @param pos A row position
* @return A int of duration
*/
int CSV::printDuration(int pos)
{
	return (other->at(1).at(pos));
}

/*
* Takes a row position and then returns the start time in that row
* Assumption:
*	- Time given is in miliseconds
* @param pos A row position
* @return A int of Start Time
*/
int CSV::printStartTime(int pos)
{
	return (other->at(2).at(pos));
}

/*
* Clears the to be printed row from the table
* @param pos The row to be cleared
*/
void CSV::clearPrintRow(int pos)
{
	if (pos < 0)
		std::cerr << "Position for row cannot exist. Try again." << std::endl;
	else 
	{
		// Clear the data stored for the text at the row position
		text->at(pos).clear();
		
		// Loop and set all numeric data to 2,147,483,647
		// Indicates that the data can't have been added normally
		for (int i = 0; i < other->size(); i++)
			other->at(i).at(pos) = 2147483647;
	}
}

// Deletes dynamic data and resets memory pointers
CSV::~CSV()
{
	delete other, text;
	other, text = nullptr;
}

/*
* Creates vectors of type int up to the specified amount
* @param total	The total number of int vectors created
* @returns a vector containing the created vectors
*/
std::vector<std::vector<int>> createIntVector(int total) 
{
	// Container to hold vectors
	std::vector<std::vector<int>> cont;
	std::vector<int> elem;
	
	//	Add empty vector to vector of vectors and loop if necessary
	for (int count = 0; count < total; count++)
		cont.push_back(elem);

	return cont;
}

/*
* Takes data from vector of ints and 
* adds it to a vector that holds vector of ints
* @param table	Vector that holds vector of ints
* @param temp	Vector that holds ints
* @returns a vector containing the created vectors
*/
std::vector<std::vector<int>> copyData(std::vector<std::vector<int>> table,
	std::vector<int> temp)
{
	if (table.size() != temp.size())
		std::cerr << "Sizes differ and aren't compatible for copy." << std::endl;
	else 
		for (int i = 0; i < table.size(); i++)
			table[i].push_back(temp[i]);

	return table;
}