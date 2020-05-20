#include "HuyCore.h" 
#include "HuyConfig.h"
#include "HuyCommon.h"
#include <locale>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <conio.h>
#include <windows.h> 
#include <iostream>

HuyCore::HuyCore(const unicode* title, int backgroundColor, int foregroundColor) {
	HuySize consoleSize = HuyCurrentConsole::getSize();
	_HuyWindows = HuyWindows(0, 0, consoleSize.width, consoleSize.height, 1, backgroundColor, foregroundColor);
	_HuyWindows.showConsoleCursor(false);
	_HuyWindows.clearConsole();
	_HuyWindows.drawFrame();
	_HuyWindows.write(title, (consoleSize.width - HuyUnicode::Size(title)) / 2, 0, HuyColors::RED, HuyColors::WHITE);

	HuyConfig::loadData(_Students);
}
HuyCore::~HuyCore() {

}

void HuyCore::intro() {
	int w = _HuyWindows.getWidth() - 20;
	if (w > 80) w = 80;
	int h = 17;
	int x = (_HuyWindows.getWidth() - w) / 2;
	int y = (_HuyWindows.getHeight() - h) / 2;

	_HuyWindows.saveScreenRect(x, y, w, h);

	unicode title[] = L" Giới thiệu tổng quát ";
	int background = HuyColors::LIGHTBLUE;
	int foreground = HuyColors::WHITE;

	_HuyWindows.animateFrame(x, y, w, h, background, foreground);

	HuyWindows introWin(x, y, w, h, 0, background, foreground);
	introWin.clearConsole();
	introWin.drawFrame();
	introWin.write(title, (w - HuyUnicode::Size(title)) / 2, 0, HuyColors::BROWN, foreground);

	int row = 2;
	int col = 2;
	introWin.write(L"Đây là chương trình quản lý học sinh đơn giản", col, row++, background, foreground);
	introWin.write(L"Chương trình được viết bằng ngôn ngữ C++", col, row++, background, foreground);
	row++;
	introWin.write(L"Những thư viện cần để viết là:", col, row++, background, foreground);
	introWin.write(L"+ HuySize:    tự viết đơn giản - giữ tọa độ x, y", col, row++, background, foreground);
	introWin.write(L"+ HuyWindows: tự viết đơn giản - vẽ khung, in ra màn hình tại X, Y, ...", col, row++, background, foreground);
	introWin.write(L"+ HuyUnicode: tự viết đơn giản - in chữ tiếng Việt có dấu, ...", col, row++, background, foreground);
	introWin.write(L"+ HuyStack:   tự viết đơn giản - dùng mảng array cùi bắp, ...", col, row++, background, foreground);
	introWin.write(L"+ HuyStudent: tự viết đơn giản - hồ sơ của 1 học sinh, ...", col, row++, background, foreground);
	introWin.write(L"+ HuyIO:      tự viết đơn giản - lưu vào tập tin dạng văn bản hay excel, ...", col, row++, background, foreground);
	row++;
	introWin.write(L"Tác giả: Huy Nguyễn", col, row++, background, foreground);
	introWin.write(L"Năm:     2020", col, row++, background, foreground);

	unicode close[] = L" Nhấn phím bất kỳ để đóng ";
	introWin.write(close, (w - HuyUnicode::Size(close)) / 2, h - 1, background, foreground);

	int c = _getch() - 48;
	_HuyWindows.restoreScreenRect();
} 

void HuyCore::addStudent() {
	int w = 50;
	int h = HuyStudent::HeaderCount + 3;
	int x = (_HuyWindows.getWidth() - w) / 2;
	int y = (_HuyWindows.getHeight() - h) / 2;

	_HuyWindows.saveScreenRect(x, y, w, h);

	unicode title[] = L" Thêm học sinh ";
	int background = HuyColors::LIGHTMAGENTA;
	int foreground = HuyColors::WHITE;
	_HuyWindows.animateFrame(x, y, w, h, background, foreground);
	HuyWindows console(x, y, w, h, 0, background, foreground);
	console.clearConsole();
	console.drawFrame();
	console.write(title, (w - HuyUnicode::Size(title)) / 2, 0, HuyColors::BROWN, foreground);

	int row = 2;
	int col = 2;
	wstring temp;
	vector<wstring> data;

	console.showConsoleCursor(true);

	data.push_back(L"");
	for (int i = 1; i < HuyStudent::HeaderCount; i++) {
		temp = HuyStudent::Header[i] + L": ";
		console.write(temp, col, row, background, foreground);
		console.gotoXY(temp.length() + 2, row++);
		if (HuyStudent::StudentTypes[i] == "number") {
			data.push_back(to_wstring(HuyUnicode::ReadInt()));
		}
		else {
			data.push_back(HuyUnicode::ReadString());
		}
	}
	HuyStudent student(data);
	_Students.push(student);

	console.showConsoleCursor(false);

	_HuyWindows.restoreScreenRect();
}

wstring HuyCore::printHeader() {
	wstring top = L"┌";
	wstring line = L"";
	wstring bottom = L"├";
	int w = 0;
	for (int i = 0; i < HuyStudent::HeaderCount; i++) {
		line += L"│";
		w += HuyStudent::HeaderWidth[i] + 1;
		wstring column;
		if (HuyStudent::HeaderWidth[i] > 0) {
			column = HuyCommon::headerPadding(HuyStudent::Header[i], HuyStudent::HeaderWidth[i], L" ");
		}
		else {
			column = HuyCommon::headerPadding(HuyStudent::Header[i], _HuyWindows.getWidth() - w - 3, L" ");
		}
		top += HuyCommon::headerPadding(L"", column.length(), L"─");
		if (i < HuyStudent::HeaderCount - 1) top += L"┬";
		line += column;
		bottom += HuyCommon::headerPadding(L"", column.length(), L"─");
		if (i < HuyStudent::HeaderCount - 1) bottom += L"┼";
	}
	top += L"┐";
	line += L"│";
	bottom += L"┤";
	_HuyWindows.write(top, 1, 2, HuyColors::LIGHTMAGENTA, HuyColors::WHITE);
	_HuyWindows.write(line, 1, 3, HuyColors::LIGHTMAGENTA, HuyColors::WHITE);
	_HuyWindows.write(bottom, 1, 4, HuyColors::LIGHTMAGENTA, HuyColors::WHITE);
	return top + L"\n" + line + L"\n" + bottom;
}
wstring HuyCore::getHeader() {
	wstring line = L"";
	int w = 0;
	for (int i = 0; i < HuyStudent::HeaderCount; i++) {
		line += L"\"";
		line += HuyCommon::trim(HuyStudent::Header[i]);
		line += L"\",";
	}
	return line.substr(0, line.size() - 1);
}
wstring HuyCore::printFooter(int row) {
	wstring line = L"└";
	int w = 0;
	for (int i = 0; i < HuyStudent::HeaderCount; i++) {
		w += HuyStudent::HeaderWidth[i] + 1;
		wstring column;
		if (HuyStudent::HeaderWidth[i] > 0) {
			column = HuyCommon::headerPadding(L"", HuyStudent::HeaderWidth[i], L"─");
		}
		else {
			column = HuyCommon::headerPadding(L"", _HuyWindows.getWidth() - w - 3, L"─");
		}
		line += column;
		if (i < HuyStudent::HeaderCount - 1) line += L"┴";
	}
	line += L"┘";
	if (row > 0) _HuyWindows.write(line, 1, row, HuyColors::LIGHTBLUE, HuyColors::WHITE);
	return line;
}
wstring HuyCore::printData(HuyStudent student, int row, int stt, bool display) {
	wstring line = L"";
	int w = 0;
	student.resetCurrentColumn();
	for (int i = 0; i < HuyStudent::HeaderCount; i++) {
		if (display) {
			line += L"│";
		}
		else
		{
			line += L"\"";
		}
		w += HuyStudent::HeaderWidth[i] + 1;
		wstring column;
		wstring data = student.getNextColumnData();
		if (i == 0) data = to_wstring(stt);
		if (display) {
			if (HuyStudent::HeaderWidth[i] > 0) {
				column = HuyCommon::dataPadding(data, HuyStudent::HeaderWidth[i], HuyStudent::HeaderAlign[i], display);
			}
			else {
				column = HuyCommon::dataPadding(data, _HuyWindows.getWidth() - w - 3, HuyStudent::HeaderAlign[i], display);
			}
		}
		else {
			column = HuyCommon::trim(data) + L"\",";
		}
		line += column;
	}
	if (display) {
		line += L"│";
	}
	else
	{
		line = line.substr(0, line.size() - 1);
	}
	if (display && row > 0) _HuyWindows.write(line, 1, row, HuyColors::LIGHTBLUE, HuyColors::WHITE);
	return line;
}
void HuyCore::updateStudentList() {
	_HuyWindows.write(L" Số học sinh: " + to_wstring(_Students.size()) + L" ", 1, 1, HuyColors::GREEN, HuyColors::WHITE);

	_Students.resetCurrentIndex();
	printHeader();
	int row = 4;
	int stt = 1;
	for (int i = 0; i < _Students.size(); i++) {
		row++;
		printData(_Students.getNextData(), row, stt++);
		if (row + 5 > _HuyWindows.getHeight()) break;
	}
	printFooter(++row);
	_Students.resetCurrentIndex();

}
void HuyCore::listStudents() {
	updateStudentList();
	printBottomCommands();

	unsigned int x = _getch();
	int countDown = 2;
	wstring messages[10];
	while (x != 24) { // Ctrl + x
		if (x == 19) // Ctrl + s
		{
			saveData("hocsinh", false);
			messages[0] = L"Danh sách đã lưu vào dạng văn bản !";
			alert(messages, 1, countDown);
		}
		if (x == 3) // Ctrl + c
		{
			saveData("hocsinh", true);
			messages[0] = L"Danh sách đã xuất ra dạng Excel !";
			alert(messages, 1, countDown);
		}
		if (x == 1) // Ctrl + a
		{
			addStudent();
			messages[0] = L"Đã thêm 1 học sinh !";
			messages[1] = L"Danh sách đã có " + to_wstring(_Students.size()) + L" học sinh !";
			alert(messages, 2, countDown);
			updateStudentList();
		}
		if (x == 5) // Ctrl + e
		{
			messages[0] = L"Soạn 1 học sinh !";
			alert(messages, 1, countDown);
		}
		x = _getch();
	}

	byeBye();
}

void HuyCore::byeBye() {
	int row = (_HuyWindows.getHeight() - 8) / 2;
	_HuyWindows.clearConsole();
	wstring byebye = L"";
	byebye = L"██████╗ ██╗   ██╗███████╗      ██████╗ ██╗   ██╗███████╗";
	int col = (_HuyWindows.getWidth() - byebye.size()) / 2;
	_HuyWindows.write(byebye, col, row++, HuyColors::BLUE, HuyColors::WHITE);
	byebye = L"██╔══██╗╚██╗ ██╔╝██╔════╝      ██╔══██╗╚██╗ ██╔╝██╔════╝";
	_HuyWindows.write(byebye, col, row++, HuyColors::BLUE, HuyColors::WHITE);
	byebye = L"██████╔╝ ╚████╔╝ █████╗        ██████╔╝ ╚████╔╝ █████╗";
	_HuyWindows.write(byebye, col, row++, HuyColors::BLUE, HuyColors::WHITE);
	byebye = L"██╔══██╗  ╚██╔╝  ██╔══╝        ██╔══██╗  ╚██╔╝  ██╔══╝";
	_HuyWindows.write(byebye, col, row++, HuyColors::BLUE, HuyColors::WHITE);
	byebye = L"██████╔╝   ██║   ███████╗      ██████╔╝   ██║   ███████╗";
	_HuyWindows.write(byebye, col, row++, HuyColors::BLUE, HuyColors::WHITE);
	byebye = L"╚═════╝    ╚═╝   ╚══════╝      ╚═════╝    ╚═╝   ╚══════╝";
	_HuyWindows.write(byebye, col, row++, HuyColors::BLUE, HuyColors::WHITE);
	for (int i = 0; i < 5; i++) {
		wstring temp = L" Tự động thoát trong " + to_wstring(5 - i) + L" giây ";
		_HuyWindows.write(temp, (_HuyWindows.getWidth() - temp.size()) / 2, _HuyWindows.getHeight() - 3, HuyColors::LIGHTMAGENTA, HuyColors::WHITE);
		Sleep(1000);
	}
}

void HuyCore::alert(wstring titles[], int size, int closeTime) {
	int w = 50;
	int h = size + 4;
	int x = (_HuyWindows.getWidth() - w) / 2;
	int y = (_HuyWindows.getHeight() - h) / 2;

	_HuyWindows.saveScreenRect(x, y, w, h);

	int background = HuyColors::LIGHTMAGENTA;
	int foreground = HuyColors::WHITE;

	_HuyWindows.animateFrame(x, y, w, h, background, foreground);

	HuyWindows info(x, y, w, h, 0, background, foreground);
	info.clearConsole();
	info.drawFrame();
	wstring temp = L" Thông báo ";
	info.write(temp, (w - temp.length()) / 2, 0, HuyColors::BROWN, foreground);

	for (int i = 0; i < size; i++) {
		info.write(titles[i], (w - titles[i].length()) / 2, 2 + i, background, foreground);
	}

	temp = L" Đóng trong ";
	for (int i = closeTime; i > 0; i--) {
		temp = L" Đóng trong " + to_wstring(i) + L" giây";
		info.write(temp, (w - temp.length()) / 2, h - 1, HuyColors::BROWN, foreground);
		Sleep(1000);
	}

	_HuyWindows.restoreScreenRect();
}

void HuyCore::printBottomCommands() {
	int col = 1;
	int row = _HuyWindows.getHeight() - 1;
	wstring temp = L" Ctrl + s ";
	_HuyWindows.write(temp, col, row, HuyColors::GREEN, HuyColors::WHITE);
	col += temp.size();
	temp = L" Lưu vô văn bản ";
	_HuyWindows.write(temp, col, row, HuyColors::BLUE, HuyColors::WHITE);

	col += temp.size() + 3;
	temp = L" Ctrl + c ";
	_HuyWindows.write(temp, col, row, HuyColors::GREEN, HuyColors::WHITE);
	col += temp.size();
	temp = L" Xuất ra excel ";
	_HuyWindows.write(temp, col, row, HuyColors::BLUE, HuyColors::WHITE);

	col += temp.size() + 3;
	temp = L" Ctrl + a ";
	_HuyWindows.write(temp, col, row, HuyColors::GREEN, HuyColors::WHITE);
	col += temp.size();
	temp = L" Thêm ";
	_HuyWindows.write(temp, col, row, HuyColors::BLUE, HuyColors::WHITE);

	col += temp.size() + 3;
	temp = L" Ctrl + e ";
	_HuyWindows.write(temp, col, row, HuyColors::GREEN, HuyColors::WHITE);
	col += temp.size();
	temp = L" Soạn ";
	_HuyWindows.write(temp, col, row, HuyColors::BLUE, HuyColors::WHITE);

	col += temp.size() + 3;
	temp = L" Ctrl + x ";
	_HuyWindows.write(temp, col, row, HuyColors::RED, HuyColors::WHITE);
	col += temp.size();
	temp = L" Thoát ";
	_HuyWindows.write(temp, col, row, HuyColors::BLUE, HuyColors::WHITE);
}

void HuyCore::saveData(string fileName, bool excel) {
	wstring data[MAX_LENGTH];
	int size = 0;

	_Students.resetCurrentIndex();
	wstring line;
	if (excel) line = getHeader();
	else line = printHeader();
	data[size++] = line;
	for (int i = 0; i < _Students.size(); i++) {
		line = printData(_Students.getNextData(), 0, size, !excel);
		data[size] = line;
		size++;
	}
	if (!excel) {
		line = printFooter(0);
		data[size++] = line;
	}
	_Students.resetCurrentIndex();

	if (excel) {
		HuyIO::writeToCSVFile(fileName + ".csv", data, size);
	}
	else {
		HuyIO::writeToFile(fileName + ".txt", data, size);
	}
}
