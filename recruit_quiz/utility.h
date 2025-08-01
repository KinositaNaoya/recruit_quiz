#pragma once
#include <vector>
#include <random>
#include<string>
using namespace std;

//配列をシャッフルする
void Shuffle(std::vector<int>& indices);

//シャッフルした配列番号を作成する
std::vector<int>CreateRandomIndices(int n);

//間違った番号の配列を作成する
std::vector<int> CreateWrongIndices(int n, int correctIndex);

//文字列を分割する
// s 分割する文字列
// c 区切り文字
vector<string> Split(const string& s,char c);