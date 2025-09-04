
//メモ　11/18[総合テスト追加]から


#include "../header/question.h"
#include "../header/exam_math.h"
#include "../header/exam_japanese.h"
#include "../header/exam_english.h"
#include "../header/exam_science.h"
#include "../header/exam_politics.h"
#include "../header//exam_economics.h"
#include "../header/utility.h"

using namespace std;

int main()
{
	//教科データ配列
	static const struct{
		const char* name;		//教科名
		QuestionList(*create)();//問題作成関数のアドレス
	}subjectData[] = {
		{ "数学",CreaetMathematicsExam },
		{ "国語",CreateJapaneseExam },
		{ "英語",CreateEnglish },
		{ "物理",CreaetMathematicsExam },
		//{ "地理", },
		{ "政治",CreatePoliticsExam },
		{ "経済",CreateEconomicsExam },
	};

	QuestionList questions;//問題集

	
	{	//教科選択
		int subject = 0;
		cout << "[リクルート試験対策クイズ]\n";

		do{	// while (subject == 0)
			cout << "教科を選んでください\n";
			for (int i = 0; i < size(subjectData); i++) {
				cout << i + 1 << '=' << subjectData[i].name << '\n';
			}
			cin >> subject;

			if (subject > 0 && subject <= size(subjectData)) {
				questions = subjectData[subject - 1].create();
			}
			else{
				cout << "選択された項目はありません、もう一度選んでください。\n";
				subject = 0;
			}

		} while (subject == 0);
	}	//教科選択
	
	{	//問題解答
		for (const auto& e : questions) {
			cout << e.q << "\n";
			string answer;
			cin >> answer;

			//入力された答えをSJISからASCIIに変換する
			const string ascii = ConvertSjisNumberToAscii(answer);
			//変換が成功した場合はASCII文字列に置き換える
			if (!ascii.empty()) {
				answer = ascii;
			}

			if (answer == e.a) {
				cout << "正解！\n";
			}
			else if (e.b.empty()) {
				//答えが1つだけの場合
				cout << "間違い！　正解は" << e.a << "\n";
			}else{
				//答えが複数ある場合、いずれかと一致すれば正解とする
				bool isMatch = false;
				for (const auto& b : e.b) {
					if (answer == b) {
						isMatch = true;
						break;
					}
				}
				
				//比較結果を出力
				if (isMatch) {
					cout << "正解！\n";
				}else {
					cout << "間違い！　正解は" << e.a << "(または";
					for (auto& b : e.b) {
						cout << "、" << b;
					}
					cout << ")\n";
				}
			} // if answer == e.a
		}	// for questions
	}	//問題解答
	

	return 0;
}