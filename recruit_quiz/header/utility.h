#pragma once
#include <vector>
#include <random>
#include <string>
#include <iostream>

using namespace std;

/// <summary>
/// 最大公約数を求める
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
int gcd(int a, int b);

/// <summary>
/// 配列をシャッフルする
/// </summary>
/// <param name="indices"></param>
void Shuffle(vector<int>& indices);

/// <summary>
/// シャッフルした配列番号を作成する
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
vector<int>CreateRandomIndices(int n);

/// <summary>
/// 間違った番号の配列を作成する
/// </summary>
/// <param name="n"></param>
/// <param name="correctIndex"></param>
/// <returns></returns>
vector<int> CreateWrongIndices(int n, int correctIndex);


/// <summary>
/// 文字列を分割する
/// </summary>
/// <param name="s"> 分割する文字列 </param>
/// <param name="c"> 区切り文字 </param>
/// <returns></returns>
vector<string> Split(const string& s,char c);


/// <summary>
/// SJIS数値文字列をASCII数値文字列に変換する。
/// </summary>
/// <param name="sjis">変換元のsjis文字列</param>
/// /// <returns></returns>
string ConvertSjisNumberToAscii(const string& sjis);