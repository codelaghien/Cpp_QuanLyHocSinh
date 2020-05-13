#include "HuyConfig.h"
#include "HuyStudent.h"
#include "HuyCommon.h"
#include "HuyIO.h"
#include "HuyStack.h"

HuyConfig::HuyConfig() {
}

HuyConfig::~HuyConfig() {
}

bool HuyConfig::loadConfig() {
	vector<wstring> config = HuyIO::loadConfig("config.txt");
	if (config.size() < 5) return false;

	int headerCount = 0;
	wstring temp = L"";
	HuyStudent::Header = {};
	wstring line = config[1] + L",";
	// "STT", "Lớp", "SBD", "Tên", "Chữ lót", "Họ", "Tuổi", "Giới tính", "Địa chỉ"
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == L',') {
			HuyStudent::Header.push_back(HuyCommon::trim(temp));
			temp = L"";
			headerCount++;
		}
		else if (line[i] != L'\"') temp += line[i];
	}
	HuyStudent::HeaderCount = headerCount;

	headerCount = 0;
	temp = L"";
	HuyStudent::HeaderWidth = {};
	line = config[2] + L",";
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == L',') {
			HuyStudent::HeaderWidth.push_back(stoi(temp)); 
			temp = L"";
			headerCount++;
		}
		else {
			temp += line[i];
		}
	}
	if (HuyStudent::HeaderCount != headerCount) return false;

	headerCount = 0;
	temp = L"";
	HuyStudent::HeaderAlign = {};
	line = config[3] + L",";
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == L',') {
			string str(temp.begin(), temp.end());
			HuyStudent::HeaderAlign.push_back(HuyCommon::trim(str));
			temp = L"";
			headerCount++;
		}
		else if (line[i] != L'\"') temp += line[i];
	}
	if (HuyStudent::HeaderCount != headerCount) return false;

	headerCount = 0;
	temp = L"";
	HuyStudent::StudentTypes = {};
	line = config[4] + L",";
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == L',') {
			string str(temp.begin(), temp.end());
			HuyStudent::StudentTypes.push_back(HuyCommon::trim(str));
			temp = L"";
			headerCount++;
		}
		else if (line[i] != L'\"') temp += line[i];
	}
	if (HuyStudent::HeaderCount != headerCount) return false;

	return true;
}

void HuyConfig::loadData(HuyStack& students) {
	vector<wstring> data = HuyIO::readDataFromFile("hocsinh.csv");

	for (int i = 1; i < data.size(); i++) {
		if (data[i] != L"") {
			vector<wstring> dataLine;
			wstring temp = L"";
			wstring line = data[i] + L",";
			for (int i = 0; i < line.size(); i++) {
				if (line[i] == L',') {
					dataLine.push_back(temp);
					temp = L"";
				}
				else if (line[i] != L'\"') temp += line[i];
			}
			students.push(HuyStudent(dataLine));
		}
	}
}
