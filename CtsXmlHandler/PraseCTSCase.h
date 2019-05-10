/*
 * PraseCTSCase.h
 *
 *  Created on: 2019年4月24日
 *      Author: 10071
 */

#ifndef PRASECTSCASE_H_
#define PRASECTSCASE_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
typedef vector<std::string>::iterator stringItor;
#define STEP1 1
#define STEP2 2
#define STEP3 3
#define OWNER 1
#define ADDON 2

class ctsTool {
public:
	size_t findString(string orgString, string flag, int count, int offset) {
		int cnt = 0;
		size_t index = 0;
		size_t indexLast = string::npos;
		while (cnt <= count) {
			index = orgString.find(flag, index); //cout << "index is " << index << endl;
			if (index != string::npos) {
				indexLast = index;
				++cnt;
				++index; //cout << "indexLast is " << indexLast << endl;//cout << "cnt is " << cnt << endl;
			} else { //++indexLast;
				break;
			}
		}
		return indexLast + offset;
	}

	int countString(string orgString, string flag) {
		int cnt = 0;
		size_t index = 0;
		while (true) {
			index = orgString.find(flag, index); //cout << "index is " << index << endl;
			if (index != string::npos) {
				++cnt;
				++index; //cout << "indexLast is " << indexLast << endl;//cout << "cnt is " << cnt << endl;
			} else { //++indexLast;
				break;
			}
		}
		return cnt;
	}

	string cutOutString(string orgString, string beginFlag, int countBegin,
			int offsetBegin, string endFlag, int countEnd, int offsetEnd,
			int addon) {
		size_t beginIndex = findString(orgString, beginFlag, countBegin,
				offsetBegin); //cout << "beginIndex is " << beginIndex << endl;
		size_t endIndex = findString(orgString, endFlag, countEnd, offsetEnd); //cout << "endIndex is " << endIndex << endl;
		return orgString.substr(beginIndex, endIndex - beginIndex + addon);
	}

	void replace(string &orgString, string from, string to) {
		size_t index = 0;
		while (true) {
			index = orgString.find(from, index); //cout << "index is " << index << endl;
			if (index != string::npos) {
				++index;
				//orgString.replace(index, to);
			} else { //++indexLast;
				break;
			}
		}
	}
};
class ctsTool mCtsTool;

class ctrData {
public:
	string mTestCase;
	string mPath;
	string mErrMsg;
	string mOwner;
	string mAddon;
	ctrData(string testCase, string path, string errMsg, string owner,
			string addon) {
		mTestCase = testCase;
		mPath = path;
		mErrMsg = errMsg;
		mOwner = owner;
		mAddon = addon;
	}
};
typedef vector<ctrData>::iterator vcdItor;

class c2mData {
public:
	string mTestCase;
	string mOwner;
	string mAddon;
	c2mData(string testCase, string owner, string addon) {
		mTestCase = testCase;
		mOwner = owner;
		mAddon = addon;
	}
};
typedef vector<c2mData>::iterator vc2mItor;

struct ctsBox {
	vector<string> ctsPassCase;
	vector<string> ctsFailCase;
	vector<ctrData> vectCfrData;
	vector<ctrData> vectCprData;
	vector<ctrData> vectCtrData;
	vector<c2mData> vectC2mData;
};
ctsBox mCtsBox;

void feedXml(ctrData tmpCtrData, ofstream &ctsOFS) {
	ctsOFS << "<Row> ";
	ctsOFS << "<Cell> <Data ss:Type=\"String\">" << tmpCtrData.mTestCase
			<< "</Data> </Cell>";
	ctsOFS << "<Cell> <Data ss:Type=\"String\">" << tmpCtrData.mPath
			<< "</Data> </Cell>";
	ctsOFS << "<Cell> <Data ss:Type=\"String\">" << tmpCtrData.mErrMsg
			<< "</Data> </Cell>";
	ctsOFS << "<Cell> <Data ss:Type=\"String\">" << tmpCtrData.mOwner
			<< "</Data> </Cell>";
	ctsOFS << "<Cell> <Data ss:Type=\"String\">" << tmpCtrData.mAddon
			<< "</Data> </Cell>";
	ctsOFS << "</Row>";
}

string praseMessage(string testCase, int messageType) {
	for (vc2mItor vc2mit = mCtsBox.vectC2mData.begin(); vc2mit != mCtsBox.vectC2mData.end(); ++vc2mit) {
		if ((*vc2mit).mTestCase.compare(testCase) == 0) {
			if (messageType == OWNER) {
				if ((*vc2mit).mOwner.length() != 0)
				return (*vc2mit).mOwner;
				else
				return "暂未分配";
			}
			if (messageType == ADDON) {
				if ((*vc2mit).mAddon.length() != 0)
				return (*vc2mit).mAddon;
				else
				return "";
			}
		}
	}
	return "";
}

string praseOwner(string testCase) {
	return praseMessage(testCase, OWNER);
}

string praseAddon(string testCase) {
	return praseMessage(testCase, ADDON);
}

bool isNewTestCase(vector<ctrData> &vectCtrData, string testCase) {
	for (vcdItor vctrit = vectCtrData.begin(); vctrit != vectCtrData.end();
			++vctrit) {
		if ((*vctrit).mTestCase.compare(testCase) == 0) {
			return false;
		}
	}
	return true;
}

void praseXml(string ctsTestResultFile, bool isOrgXml) {
	ifstream ctrIFS(ctsTestResultFile);
	string orgline, moudleName, TestCase, Test, testMsg, path, errMsg, owner,
			addon, tmpbuf, testCase;
	bool keep = false;
	int cnt = 0;
	while (getline(ctrIFS, orgline)) {
		if (orgline.find("Module name", 0) != string::npos) {
			moudleName = mCtsTool.cutOutString(orgline, "\"", 0, 1, "\"", 1, 0,
					0); //cout << "orgline: " << orgline << endl; //cout << "moudleName:" << moudleName << endl;
		}
		if (orgline.find("TestCase name", 0) != string::npos) {
			TestCase = mCtsTool.cutOutString(orgline, "\"", 0, 1, "\"", 1, 0,
					0); //cout << "orgline: " << orgline << endl;//cout << "TestCase:" << TestCase << endl;
		}
		if (orgline.find("Test result=\"fail\"", 0) != string::npos) {
			Test = mCtsTool.cutOutString(orgline, "\"", 2, 1, "\"", 3, 0, 0); //cout << "orgline: " << orgline << endl;
			cnt = mCtsTool.countString(ctsTestResultFile, "\\");
			path = mCtsTool.cutOutString(ctsTestResultFile, "\\", cnt - 2, 1,
					"\\", cnt - 1, 0, 0);
			//cout << "ctsTestResultFile is " + ctsTestResultFile << " cnt = " << cnt << " path is " << path << endl;
		}
		if (orgline.find("<Failure", 0) != string::npos) {
			errMsg = "";
			keep = true;
		}
		if (keep == true) {
			orgline.erase(0, orgline.find_first_not_of(" ")); //cout << "orgline is " << orgline << endl;
			size_t indexLeft = 0;
			size_t indexRight = 0;
			do {
				indexLeft = orgline.find("<", indexLeft);
				if (indexLeft != string::npos) { //cout << "indexLeft " << indexLeft << endl;
					orgline.erase(indexLeft, 1);
					orgline.insert(indexLeft, "&lt;");
					continue;
				}
				indexRight = orgline.find(">", indexRight);
				if (indexRight != string::npos) { //cout << "indexRight " << indexRight << endl;
					orgline.erase(indexRight, 1);
					orgline.insert(indexRight, "&gt;");
					continue;
				}
			} while (indexLeft != string::npos || indexRight != string::npos);
			if (orgline.find("\r", 0) != string::npos) {
				orgline.erase(orgline.find("\r", 0), 1);
			}   //cout << "orgline is " << orgline << endl;
			errMsg = errMsg + orgline + "&#10;";   //
		}
		if (orgline.find("/Failure", 0) != string::npos) {
			keep = false;
			testCase = moudleName + " " + TestCase + "#" + Test;
			owner = praseOwner(testCase);
			addon = praseAddon(testCase);
			//cout << testCase << addon << endl;
			if(addon != "waived")
			  addon = "run cts -m " + moudleName + " -t " + TestCase + "#" + Test + " --skip-preconditions";
			//cout << Test << endl;
			ctrData tmpCtrData(testCase, path, errMsg, owner, addon);
			if (isOrgXml == false) {
				if (isNewTestCase(mCtsBox.vectCfrData, testCase)) {
					mCtsBox.vectCfrData.push_back(tmpCtrData);
					//cout << testCase << endl;
				}
			} else {
				if (isNewTestCase(mCtsBox.vectCtrData, testCase)) {
					mCtsBox.vectCtrData.push_back(tmpCtrData);
					//cout << testCase << endl;
				}
			}
		}
		if (isOrgXml == false) {
			if (orgline.find("Test result=\"pass\"", 0) != string::npos) {
				Test = mCtsTool.cutOutString(orgline, "\"", 2, 1, "\"", 3, 0, 0); //cout << "orgline: " << orgline << endl;
				testCase = moudleName + " " + TestCase + "#" + Test;
				//cout << testCase << endl;
				ctrData tmpCtrData(testCase, "", "", "", "");
				if (isNewTestCase(mCtsBox.vectCprData, testCase))
					mCtsBox.vectCprData.push_back(tmpCtrData);
			}
		}
	}
}

void praseOrgXml(string ctsTestResultFile) {
	praseXml(ctsTestResultFile, true);
}

void praseSubXml(string ctsTestResultFile) {
	praseXml(ctsTestResultFile, false);
}

bool testCaseSort(ctrData c1, ctrData c2) {
	return c1.mTestCase < c2.mTestCase;
}

void praseC2mXml(ifstream &c2mIFS) {
	static string orgLineLast;
	string orgLine, testCase, owner, addon;
	int loopMax = 2, cnt = 0;
	while (getline(c2mIFS, orgLine)) {
		if (orgLine.find("<Row", 0) != string::npos)
			cnt = 0;
		if (orgLine.find("<Data", 0) != string::npos) {
			if (cnt == 0)
				testCase = mCtsTool.cutOutString(orgLine, ">", 0, 1, "<", 1, 0, 0);
			if (cnt == 1)
				owner = mCtsTool.cutOutString(orgLine, ">", 0, 1, "<", 1, 0, 0);
			if (cnt == 2)
				addon = mCtsTool.cutOutString(orgLine, ">", 0, 1, "<", 1, 0, 0);
			++cnt;
			if (cnt > loopMax) {
				c2mData tmpC2mData(testCase, owner, addon);
				mCtsBox.vectC2mData.push_back(tmpC2mData);
				//cout << "testCase is " << testCase << " owner is " << owner << " addon is " << addon << endl;
			}
		}
	}
}

void buildXmlHead(ifstream &ctrIFS, ofstream &ctrOFS) {
	string orgLine;
	while (getline(ctrIFS, orgLine)) {
		if (orgLine.find("</Table>", 0) != string::npos) {
			break;
		}
		ctrOFS << orgLine;
	}
}

void buildXmlBody(ofstream &ctrOFS) {
	bool passNow;
	bool failNow;
	sort(mCtsBox.vectCtrData.begin(), mCtsBox.vectCtrData.end(), testCaseSort);
	sort(mCtsBox.vectCprData.begin(), mCtsBox.vectCprData.end(), testCaseSort);
	sort(mCtsBox.vectCfrData.begin(), mCtsBox.vectCfrData.end(), testCaseSort);
	for (vcdItor vtcdit = mCtsBox.vectCtrData.begin();
			vtcdit != mCtsBox.vectCtrData.end(); ++vtcdit) {
		passNow = false;
		failNow = false;
		//cout << (*vtcdit).mTestCase << endl;
		for (vcdItor vpcdit = mCtsBox.vectCprData.begin();
				vpcdit != mCtsBox.vectCprData.end(); ++vpcdit) {
			if ((*vtcdit).mTestCase == (*vpcdit).mTestCase) {
				//cout << "one more pass: " << (*vpcdit).mTestCase << endl;
				passNow = true;
				break;
			}
		}
		if (passNow == true)
			continue;
		for (vcdItor vfcdit = mCtsBox.vectCfrData.begin();
				vfcdit != mCtsBox.vectCfrData.end(); ++vfcdit) {
			if ((*vtcdit).mTestCase == (*vfcdit).mTestCase) {
				failNow = true;
				feedXml(*vfcdit, ctrOFS);
				break;
			}
		}
		if (failNow == true)
			continue;
		feedXml(*vtcdit, ctrOFS);
	}
	ctrOFS << "</Table>";
}

void buildXmlTail(ifstream &ctrIFS, ofstream &ctrOFS) {
	string orgLine;
	while (getline(ctrIFS, orgLine)) {
		ctrOFS << orgLine;
	}
}

#endif /* PRASECTSCASE_H_ */
