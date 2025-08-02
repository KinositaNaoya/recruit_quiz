#include "../header/exam_politics.h"
#include "../header/utility.h"
#include <fstream>
#include <iostream>
#include <random>
#include <unordered_map>
#include <filesystem>

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
		constexpr char filename[] = "text/japanese_politics.txt";

		ifstream ifs(filename);		//txtを読み込む？
		if (!ifs) {
			cerr << "エラー" << filename << "を読み込めません\n";
            cout << "カレントディレクトリ:" << std::filesystem::current_path() << endl;
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
	QuestionList questions;
	questions.reserve(genreCount* quizConut);	//メモリ確保
	random_device rd;	//乱数生成器
	
	//ランダムに選んだ二つのジャンルから、ジャンル内でランダムに選んだ５問を出題する
	const vector<int> genreIndices = CreateRandomIndices((int)data.size());
	for(int i = 0;i<genreCount; ++i) {
		//出題するジャンルを選択
		auto itr = data.begin();
		advance(itr, genreIndices[i]);	//参照位置を指定した値まで進める
		const auto& genre = itr->second;//値(ジャンルのデータ配列)を取り出す

		//ジャンル内でランダムに５問選ぶ
		const vector<int> questionIndices = CreateRandomIndices((int)genre.size());
		for (int j = 0; j < quizConut; j++) {
			const auto& question = genre[questionIndices[j]];	//選んだ問題データ

			//空欄の位置と数を調べる
			//空欄は「開き波括弧」と「閉じ波括弧」のペア、つまり{}で表される
			vector<int> blanks;	//空欄の位置の配列
			for(int k = 0;k< question.text.size() - 1; ++k) {
				if(question.text[k] == '{' && question.text[k + 1] == '}' ) {
					blanks.push_back(k);	//空欄の開始位置を記録
				}
			}

			//空欄のうち一つをランダムに選ぶ
			const int index = uniform_int_distribution<>(0, (int)blanks.size() - 1)(rd);

			//問題文のコピーを作成しつつ、選ばれなかった空欄を答えに置き換える
			string s = "[" + question.genre + "] 次の文章の[ ? ]に入る単語を答えよ\n";
			int from = 0;	//コピー元のの先頭位置
			for (int k = 0; k < blanks.size(); ++k) {
				const int end = blanks[k];	//空欄の位置
				s.append(question.text, from, end - from);	//空欄の手前までの範囲をコピー

				if (k != index) {
					s += question.answers[k]; // 選ばれなかった空欄の場合は答えをコピー
				}
				else {
					s.append(" ? "); // 選ばれた空欄の場合は「表示用の空欄文字列」をコピー
				}
				from = end + 2;//コピー元の位置を更新
			}
			s.append(question.text, from); // 問題文の末尾部分をコピー

			questions.push_back({ s, question.answers[index] });
		} // for j < quizConut
	} // for i < genreCount

	return questions;
}