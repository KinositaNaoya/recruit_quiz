#pragma once
#include <vector>

//配列をシャッフルする
void Shuffle(std::vector<int>& indices);

//シャッフルした配列番号を作成する
std::vector<int>CreateRandomIndices(int n);

//間違った番号の配列を作成する
std::vector<int> CreateWrongIndices(int n, int correctIndex);