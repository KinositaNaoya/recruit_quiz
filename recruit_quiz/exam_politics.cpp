#include "exam_politics.h"
#include "utility.h"
#include <fstream>
#include <iostream>
#include <random>
#include <unordered_map>
using namespace std;

/*
	日本の政治の問題を作成する
*/
QuestionList CreatePoliticsExam() {
	//政治問題データ
	struct PoliticsData
	{
		string genre;			// ジャンル
		string text;			// 問題文
		vector<string> answers;	// 空欄に入る答えの配列
	};
	unordered_map<string, vector<PoliticsData>>data;

	{//政治問題データを読み込む
		constexpr char filename[] = "japanese_politics.txt";
		ifstream ifs(filename);		//txtを読み込む？
		if (!ifs) {
			cerr << "エラー" << filename << "を読み込めません\n";
			return {};
		}

		while (true){
			string s;
			getline(ifs, s);
			if (!ifs) {
				break;	//ファイル末端に到達したので終了
			}
			const vector<string> v = Split(s, ',');
			const string& genre = v[0];//ジャンルを取得
			data[genre].push_back({ genre,v[1],vector<string>(v.begin() + 2,v.end()) });
		}
	}//政治問題データを読み込む

	constexpr int genreCount = 2;	//出題するジャンル数
	constexpr int quizConut = 5;	//各ジャンルの出題数

	//ページ4/12から続き

}