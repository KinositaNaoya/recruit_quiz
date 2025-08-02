#pragma once
#include <vector>
#include <random>
#include<string>
using namespace std;

//�ő���񐔂����߂�
int gcd(int a, int b);

//�z����V���b�t������
void Shuffle(vector<int>& indices);

//�V���b�t�������z��ԍ����쐬����
vector<int>CreateRandomIndices(int n);

//�Ԉ�����ԍ��̔z����쐬����
vector<int> CreateWrongIndices(int n, int correctIndex);


/// <summary>
/// ������𕪊�����
/// </summary>
/// <param name="s"> �������镶���� </param>
/// <param name="c"> ��؂蕶�� </param>
/// <returns></returns>
vector<string> Split(const string& s,char c);


/// <summary>
/// SJIS���l�������ASCII���l������ɕϊ�����B
/// </summary>
/// <param name="sjis">�ϊ�����sjis������</param>
/// /// <returns></returns>
string ConvertSjisNumberToAscii(const string& sjis);