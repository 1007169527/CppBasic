/*
 * listSpecFile.h
 *
 *  Created on: 2019Äê4ÔÂ24ÈÕ
 *      Author: 10071
 */

#ifndef LISTSPECFILE_H_
#define LISTSPECFILE_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

using namespace std;
using std::ifstream;
using std::ofstream;
using std::string;

typedef vector<std::string>::iterator stringItor;

class filterFileTool {
public:
	void filterSpecFiles(vector<string> &specFiles, string flag) {
		for (stringItor fit = files.begin(); fit != files.end(); ++fit) {
			if ((*fit).find(flag, 0) != string::npos) {
				specFiles.push_back(*fit);
			}
		} //for (stringItor sfit = specFiles.begin(); sfit != specFiles.end(); ++sfit) cout << *sfit << endl;
	}

	void listFiles(string dir) {
		DIR *pDir;
		string childPath;
		struct dirent *ptr;
		if ((pDir = opendir(dir.c_str())) == NULL) {
			cout << "open " + dir + "error..." << endl;
			return;
		}
		while ((ptr = readdir(pDir)) != NULL) {
			if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
				continue;
			else if (ptr->d_type & DT_DIR) {
				childPath = dir + "\\" + ptr->d_name;
				listFiles(childPath);
			} else {
				childPath = dir + "\\" + ptr->d_name; //cout << childPath << endl;
				files.push_back(childPath);
			}
		}
		closedir(pDir);
		return;
	}
private:
	vector<string> files;
};

class filterFileTool mFilterFileTool;



#endif /* LISTSPECFILE_H_ */
