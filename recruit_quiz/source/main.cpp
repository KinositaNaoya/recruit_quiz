//#define _USE_MATH_DEFINES

#include "../header/question.h"
#include "../header/exam_math.h"
#include "../header/exam_japanese.h"
#include "../header/exam_english.h"
#include "../header/exam_science.h"
#include "../header/exam_geography.h"
#include "../header/exam_politics.h"
#include "../header/utility.h"


//#include <iostream>
//#include <string>
using namespace std;

int main()
{
	QuestionList questions;//問題集

	
	{	//教科選択
		int subject = 0;
		cout << "[リクルート試験対策クイズ]\n";

		do{	// while (subject == 0)
			cout << "教科を選んでください\n1 = 数学\n2 = 国語\n3 = 英語\n4 = 物理\n5 = 地理\n6 = 政治\n";
			cin >> subject;

			if (subject == 1) {		// 数学
				questions = CreaetMathematicsExam();
			}
			else if (subject == 2) {// 国語
				questions = CreateKanjiExam();	//問題集作成 <- 漢字の読み取り問題を追加

				QuestionList idiomExam = CreateIdiomExam();								//慣用句の問題集を追加
				questions.insert(questions.end(), idiomExam.begin(), idiomExam.end());	//問題集に慣用句の問題集を追加(以下同文)

				QuestionList homophoneExam = CreateHomophoneExam();
				questions.insert(questions.end(), homophoneExam.begin(), homophoneExam.end());

				QuestionList antonymExam = CreateAntonymExam();
				questions.insert(questions.end(), antonymExam.begin(), antonymExam.end());

				QuestionList synonymExam = CreateSynonymExam();
				questions.insert(questions.end(), synonymExam.begin(), synonymExam.end());
			}
			else if (subject == 3) {// 英語
				questions = CreateEnglishWordExam();

				QuestionList phraseExam = CreateEnglishPhraseExam();
				questions.insert(questions.end(), phraseExam.begin(), phraseExam.end());
			}
			else if (subject == 4) {//物理
				questions = CreatePhysicsExam();
			}
			else if (subject == 5) {
				questions = CreatePrefecturesExam();	// 地理
			}
			else if (subject == 6) {// 政治
				questions = CreatePoliticsExam();
			}
			else {
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
			else
			{
				cout << "間違い！正解は" << e.a << "\n";
			}
		}	// for questions
	}	//問題解答
	

	return 0;
}