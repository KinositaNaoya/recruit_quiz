#include "../header/exam_geography.h"
#include "../header/utility.h"
#include <iostream>
#include <fstream>
#include <random>


using namespace std;

/*
	都道府県の問題を作成する関数
*/
QuestionList CreatePrefecturesExam()
{
	//都道府県のデータ
	struct PrefectureData
	{
		string name; // 都道府県名
		string capital; // 県庁所在地
		vector<string> features; // 特徴
	};
	vector<PrefectureData> data;

	{ // 都道府県データを読み込む
		constexpr char filename[] = "text/japanese_prefectures.txt";
		ifstream ifs(filename);
		if(!ifs) {
			cerr << "エラー: " << filename << "をよみこめていません\n" << endl;
			return {};
		}

		string s;
		while (true){
			getline(ifs, s);	//1行読み取る
			if (!ifs) {
				break; // EOFに到達したら終了
			}
			const vector<string> v = Split(s, ',');
			data.push_back({ v[0], v[1], vector<string>(v.begin() + 2, v.end()) });
		}
	} // 都道府県データを読み込む

	constexpr int question_count = 5; // 問題数
	QuestionList questions;
	questions.reserve(question_count);
	vector<int> indices = CreateRandomIndices((int)data.size());
	random_device rd;

	const int type = uniform_int_distribution<>(0, 2)(rd);

	if(false)const int type = 0;//デバッグ用

	switch (type)
	{
	case 0: // 特徴から都道府県名を答える問題
		for (int i = 0; i < question_count; i++) {
			//正解以外の答えをランダムに選ぶ
			const int correctIndex = indices[i];
			vector<int> answer = CreateWrongIndices((int)data.size(), correctIndex);

			//ランダムな位置を正しい番号で上書き
			const int correctNo = uniform_int_distribution<>(1, 3)(rd);
			answer[correctNo - 1] = correctIndex;

			//問題文を作成
			string s = "以下の特徴をもつ都道府県はどれですか？\n";

			// 都道府県の特徴をランダムな順番で連結し、問題文に追加
			const auto& features = data[correctIndex].features;
			vector<int> featureIndices = CreateRandomIndices((int)features.size());
			s += features[featureIndices[0]]; // 最初の特徴を追加
			for (int j = 1; j < features.size(); j++) {
				s += ",";
				s += features[featureIndices[j]]; // 残りの特徴を追加
			}

			//答えとなる都道府県を問題文に追加
			for (int j = 0; j < 3; j++) {
				s += "\n  " + to_string(j + 1) + " : " + data[answer[j]].name;
			}

			//問題文と答えのペアを問題配列に追加
			questions.push_back({ s, to_string(correctNo)});
		}
		break;

	case 1: // 都道府県をあらわす特徴を答える問題
		for (int i = 0; i < question_count; i++) {
			//正解以外の答えをランダムに選ぶ
			const int correctIndex = indices[i];
			vector<int>answers = CreateWrongIndices((int)data.size(),correctIndex);

			//ランダムな位置を正しい番号で上書き
			const int correctNo = uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			//問題文を作成
			string s = "「" + data[correctIndex].name + "」の特徴をあらわす番号を選べ";
			for (int j = 0; j < 3; j++){
				const auto& feature = data[answers[j]].features;
				const int n = uniform_int_distribution<>(0,(int)feature.size() - 1)(rd);
				s += "\n  " + to_string(j + 1) + " : " + feature[n]; // 特徴をランダムに選ぶ
			}

			// 問題文と答えのペアを問題配列に追加
			questions.push_back({ s, to_string(correctNo) });
		}
		break;

	case 2: // 都道府県から県庁所在地を答える問題
			// 都道府県と県庁所在地が異なる都道府県のリストを作る
		vector<pair<string, string>> differentNames;
		for (const auto& e : data) {
			//都道府県名と県庁所在地名の長さが異なるか、末尾の1文字を除く部分文字列が異なる場合、
			//「都道府県名と県庁所在地が異なるリスト」に追加する
			if (e.name.size() != e.capital.size() ||
				memcmp(e.name.data(), e.capital.data(), e.name.size() - 2) != 0) {
				differentNames.push_back({ e.name, e.capital });
			}
		}

		// 作成したリストからランダムに出題する
		vector<int> indices = CreateRandomIndices((int)differentNames.size());
		for (int i = 0; i < question_count; i++) {
			const int correctIndex = indices[i];
			questions.push_back({
				"「" + differentNames[correctIndex].first + "」の県庁所在地を答えよ",
				differentNames[correctIndex].second });
		}
		break;
		
	}	// switch (type)

	return questions;
}