#pragma once
#include <vector>
#include <random>
#include <string>
#include <iostream>

using namespace std;

/// <summary>
/// �ő���񐔂����߂�
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
int gcd(int a, int b);

/// <summary>
/// �z����V���b�t������
/// </summary>
/// <param name="indices"></param>
void Shuffle(vector<int>& indices);

/// <summary>
/// �V���b�t�������z��ԍ����쐬����
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
vector<int>CreateRandomIndices(int n);

/// <summary>
/// �Ԉ�����ԍ��̔z����쐬����
/// </summary>
/// <param name="n"></param>
/// <param name="correctIndex"></param>
/// <returns></returns>
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