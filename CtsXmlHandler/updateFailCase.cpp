/*
 * updateFailCase.cpp
 *
 *  Created on: 2019Äê4ÔÂ24ÈÕ
 *      Author: 10071
 */


#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <errno.h>
#include <cstring>
#include <stdlib.h>

#include "listSpecFile.h"
#include "PraseCTSCase.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;

int checkArgs(int argc, char *argv[]) {
	if (argc < 6) {
		cout << "We need four arguments for the program" << endl;
		return -1;
	}
	for (int i = 0; i < argc; i++) {
		switch (i) {
		case 0:
			cout << "argv[0] program name is " << argv[0] << endl;
			break;
		case 1:
			cout << "argv[1] base.xml is " << argv[1] << endl;
			break;
		case 2:
			cout << "argv[2] c2m.xml is " << argv[2] << endl;
			break;
		case 3:
			cout << "argv[3] results directory is " << argv[3] << endl;
			break;
		case 4:
			cout << "argv[4] org.xml is " << argv[4] << endl;
			break;
		case 5:
			cout << "argv[5] new.xml is " << argv[5] << endl;
			break;
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	//if (checkArgs(argc, argv) != 0)
	//	return -1;
	cout << "enter main" << endl;
	/*
	ifstream ctrIFS(argv[1]); //"F:\\LinkToDesktop\\base.xml"
	ifstream c2mIFS(argv[2]); //"F:\\LinkToDesktop\\c2m.xml"
	ofstream ctrOFS(argv[5]); //"F:\\LinkToDesktop\\new.xml"
	*/
	ifstream ctrIFS("F:\\LinkToDesktop\\base.xml"); //"F:\\LinkToDesktop\\base.xml"
	ifstream c2mIFS("F:\\LinkToDesktop\\c2m.xml"); //"F:\\LinkToDesktop\\c2m.xml"
	ofstream ctrOFS("F:\\LinkToDesktop\\new.xml"); //"F:\\LinkToDesktop\\new.xml"
	vector<string> specFiles;
	//mFilterFileTool.listFiles(argv[3]); //"F:\\LinkToDesktop\\0416"
	mFilterFileTool.listFiles("F:\\LinkToDesktop\\null"); //"F:\\LinkToDesktop\\0416"
	mFilterFileTool.filterSpecFiles(specFiles, ".xml");
	//STEP1
	praseC2mXml(c2mIFS);
	buildXmlHead(ctrIFS, ctrOFS);
	//praseOrgXml(argv[4]);//"F:\\LinkToDesktop\\2019.03.21_09.44.20\\test_result.xml"
	praseOrgXml("C:\\Users\\10071\\Documents\\google_report\\cts\\test_result.xml");//"F:\\LinkToDesktop\\2019.03.21_09.44.20\\test_result.xml"
	//STEP2
	for (stringItor sfit = specFiles.begin(); sfit != specFiles.end(); ++sfit) { //cout << "now prase " << *sfit << endl;
		praseSubXml(*sfit);
	}
	//STEP3
	buildXmlBody(ctrOFS);
	buildXmlTail(ctrIFS, ctrOFS);
	cout << "exit main" << endl;
	return 0;
}


