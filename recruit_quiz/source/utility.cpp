
#include "../header/utility.h"

#include <random>
using namespace std;

//最大公約数を求める
int gcd(int a, int b)
{
	//余りが0になった時の除数を返す
	while (b) {
		int r = a % b;
		a = b;//除数を次の被除数にする
		b = r;//余りを次の除数にする
	}
	return a;
}

//ランダムな番号配列を作成する
vector<int>CreateRandomIndices(int n) {
	//番号を配列に格納
	vector<int> indices(n);
	for (int i = 0; i < n; i++) {
		indices[i] = i;
	}

	//番号の配列をシャッフル
	Shuffle(indices);

	return indices;
}

/// <summary>
/// 配列をシャッフルする
/// </summary>
void Shuffle(vector<int>& indices){
	const int n = static_cast<int>(indices.size());

	random_device rd;
	mt19937 rand(rd());
	for (int i = n - 1; i > 0; i--) {
		const int j = uniform_int_distribution<>(0, 1)(rand);
		const int tmp = indices[i];
		indices[i] = indices[j];
		indices[j] = tmp;
	}
}


/// <summary>
/// 間違った番号の配列を作成する
/// </summary>
/// <param name="n">作成する番号の範囲</param>
/// <param name="correctIndex">正解の番号</param>
/// <returns></returns>
std::vector<int> CreateWrongIndices(int n, int correctIndex){
	//番号を配列に格納
	vector<int> indices(n - 1);
	for (int i = 0; i < correctIndex; i++) {
		indices[i] = i + 1;
	}

	for (int i = correctIndex; i < n - 1; i++) {
		indices[i] = i + 1;
	}

	//番号の配列をシャッフル
	Shuffle(indices);

	return indices;
}

/*
	文字列を分割する
*/
vector<string> Split(const string& s, char c)
{
	vector<string>v;	//分割した文字列を格納する配列(戻り値)

	//全ての文字をループ処理
	auto begin = s.begin();	//分割範囲の先頭配列
	const auto end = s.end();	//文字列の終端
	for (auto p = begin; p != end; ++p) {
		//区切り文字の前までの文字列として分割
		if (*p == c) {
			v.push_back(string(begin, p));
			begin = p + 1;//先頭位置を「区切り文字の次」の位置に更新
		}
	}
	//残り部分を配列に追加
	v.push_back(string(begin, end));
	return v;
}

// Shift_JISの数字をASCIIの数字に変換する関数
string ConvertSjisNumberToAscii(const string& sjis)
{
	//数値文字のSJISからASCIIへの変換表
	static const struct {
		unsigned int sjis;
		char ascii;
	}conversionTable[] = {
		{0x82A0, '0'}, // 0
		{0x82A1, '1'}, // 1
		{0x82A2, '2'}, // 2
		{0x82A3, '3'}, // 3
		{0x82A4, '4'}, // 4
		{0x82A5, '5'}, // 5
		{0x82A6, '6'}, // 6
		{0x82A7, '7'}, // 7
		{0x82A8, '8'}, // 8
		{0x82A9, '9'}, // 9
		{0x8144, '.'}, // 9
		{0x817c, '-'}, // 9
	};

	//文字コードを変換する
	string ascii;
	for(auto i = sjis.begin(); i != sjis.end(); ++i) {
		const unsigned char a = i[0];
		if (a < 0x80) {	// ASCII文字はそのままコピーする
			ascii.push_back(*i);
		}
		else {			// SJIS文字の場合はASCII文字に変換する
			const unsigned int code = a * 0x100 + (unsigned int)i[1];
			const auto itr = find_if(begin(conversionTable), end(conversionTable),
				[code](const auto& e) {return e.sjis == code; });
			if (itr == end(conversionTable)) {
				break;	//変換できない文字が見つかったら終了
			}
			ascii.push_back(itr->ascii);
			i++;//２バイト文字なので1バイト余分に進める
		}
	} // for i

	return string();
}
