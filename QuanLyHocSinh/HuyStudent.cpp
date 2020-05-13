#include "HuyStudent.h" 

HuyStudent::HuyStudent() {
}

HuyStudent::HuyStudent(vector<wstring> data) {
    _Data = data;
}

HuyStudent::~HuyStudent() {
}

wstring HuyStudent::getNextColumnData() {
    return _Data[_CurrentColumn++];
}

int HuyStudent::HeaderCount = 9;
vector<wstring> HuyStudent::Header = { L"STT", L"Lớp", L"SBD", L"Tên", L"Chữ lót", L"Họ", L"Tuổi", L"Giới tính", L"Địa chỉ" };
vector<int> HuyStudent::HeaderWidth = { 5, 10, 10, 15, 15, 15, 12, 13, 0 };
vector<string> HuyStudent::HeaderAlign = { "center", "center", "center", "left", "left", "right", "center", "center", "left" };
vector<string> HuyStudent::StudentTypes = { "number", "string", "string", "string", "string", "string", "number", "string", "string" };
