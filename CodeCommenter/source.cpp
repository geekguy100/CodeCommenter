#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "dirent.h"

using namespace std;


int writeToFile(const string &fileName);
int main()
{
	const string FILETYPE = ".cs";
	const char DIRECTORY[] = "./FILES";


	DIR *dr;
	struct dirent *en;
	dr = opendir(DIRECTORY);

	if (dr)
	{
		while ((en = readdir(dr)) != NULL)
		{
			// Make sure the name of the file contains the file type
			// we're looking for.

			string fileName(en->d_name);

			if (fileName.find(FILETYPE) != string::npos)
			{
				writeToFile(string(DIRECTORY) + "/" + fileName);
			}
		}

		closedir(dr);
	}

	cout << endl << endl;
	cout << "~~~~PROGRAM DONE~~~~";
	getchar();
	return 0;
}

int writeToFile(const string &filePath)
{
	fstream file;
	file.open(filePath, fstream::in | fstream::out);

	if (file.is_open())
	{
		string line;
		unsigned int cursorPos = 0;
		bool foundDebug = false;
		while (getline(file, line))
		{
			// The line contains 'Debug', so let's search each word till we
			// find the position of it.
			if (line.find("Debug") != string::npos)
			{
				istringstream ss(line);
				string word;

				while (ss >> word)
				{
					// The word contains 'Debug', so make note of the cursor position.
					// We'll use the cursor position to comment it out!
					if (word.find("Debug") != string::npos)
					{
						cout << "Found Debug at cursor pos: " << cursorPos << endl;
						foundDebug = true;
					}

					// We add 1 to account for the space after the word.
					cursorPos += word.length() + 1;
				}

				// We remove 1 because we reached the end of the line, and
				// we don't want that to be treated as a space.
				cursorPos -= 1;
			}
			// If the line does not contain 'Debug', 
			// add its length to the cursorPos.
			else
				cursorPos += line.length() /*+ 1*/;
		}

		if (!foundDebug)
			cout << "No debug found..." << endl;
	}
	else
	{
		cout << "COULD NOT OPEN FILE NAME: " << filePath;
	}
	
	return 1;
}