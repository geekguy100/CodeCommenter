#include <iostream>
#include <fstream>
#include <string>
#include "dirent.h"

using namespace std;

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
				cout << en->d_name << "\n";
			}
		}

		closedir(dr);
	}

	getchar();
	return 0;
}