// Made by Rahim Sarpas

#pragma once
#include <vector> // STL Data Structure Library
#include <string> // Text Data Type Library

// Class defninition for CSV Class Objects
// - Function descriptions in CSV.cpp file
class CSV {
public:
	CSV();
	//	Accessors
	std::vector<std::vector<int>>* getTable();
	std::vector<std::string>* getText();
	int getPriority(int pos);
	int getPriorityRow();
	int getDur(int pos);
	int getEarlyStart();
	int getStart(int pos);
	int getPrintRow();
	int getTextSize();
	int getTableSize();
	//	Mutator
	void updateCSV(std::string fileName);
	// Functions
	std::string printText(int pos);
	int printDuration(int pos);
	int printStartTime(int pos);
	void clearPrintRow(int pos);
	//	Destructor
	~CSV();
private:
	std::vector<std::vector<int>>* other;
	std::vector<std::string>* text;
};

// Helper Function declarations
std::vector<std::vector<int>> createIntVector(int total);
std::vector<std::vector<int>> copyData(std::vector<std::vector<int>> table, std::vector<int> temp);