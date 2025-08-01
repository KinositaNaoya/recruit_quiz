#pragma once
#include <vector>
#include <random>
#include<string>
using namespace std;

//�z����V���b�t������
void Shuffle(std::vector<int>& indices);

//�V���b�t�������z��ԍ����쐬����
std::vector<int>CreateRandomIndices(int n);

//�Ԉ�����ԍ��̔z����쐬����
std::vector<int> CreateWrongIndices(int n, int correctIndex);

//������𕪊�����
// s �������镶����
// c ��؂蕶��
vector<string> Split(const string& s,char c);