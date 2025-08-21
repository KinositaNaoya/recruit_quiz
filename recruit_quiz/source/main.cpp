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
	QuestionList questions;//���W

	
	{	//���ȑI��
		int subject = 0;
		cout << "[���N���[�g�����΍�N�C�Y]\n";

		do{	// while (subject == 0)
			cout << "���Ȃ�I��ł�������\n1 = ���w\n2 = ����\n3 = �p��\n4 = ����\n5 = �n��\n6 = ����\n";
			cin >> subject;

			if (subject == 1) {		// ���w
				questions = CreaetMathematicsExam();
			}
			else if (subject == 2) {// ����
				questions = CreateKanjiExam();	//���W�쐬 <- �����̓ǂݎ�����ǉ�

				QuestionList idiomExam = CreateIdiomExam();								//���p��̖��W��ǉ�
				questions.insert(questions.end(), idiomExam.begin(), idiomExam.end());	//���W�Ɋ��p��̖��W��ǉ�(�ȉ�����)

				QuestionList homophoneExam = CreateHomophoneExam();
				questions.insert(questions.end(), homophoneExam.begin(), homophoneExam.end());

				QuestionList antonymExam = CreateAntonymExam();
				questions.insert(questions.end(), antonymExam.begin(), antonymExam.end());

				QuestionList synonymExam = CreateSynonymExam();
				questions.insert(questions.end(), synonymExam.begin(), synonymExam.end());
			}
			else if (subject == 3) {// �p��
				questions = CreateEnglishWordExam();

				QuestionList phraseExam = CreateEnglishPhraseExam();
				questions.insert(questions.end(), phraseExam.begin(), phraseExam.end());
			}
			else if (subject == 4) {//����
				questions = CreatePhysicsExam();
			}
			else if (subject == 5) {
				questions = CreatePrefecturesExam();	// �n��
			}
			else if (subject == 6) {// ����
				questions = CreatePoliticsExam();
			}
			else {
				cout << "�I�����ꂽ���ڂ͂���܂���A������x�I��ł��������B\n";
				subject = 0;
			}

		} while (subject == 0);
	}	//���ȑI��
	
	{	//����
		for (const auto& e : questions) {
			cout << e.q << "\n";
			string answer;
			cin >> answer;

			//���͂��ꂽ������SJIS����ASCII�ɕϊ�����
			const string ascii = ConvertSjisNumberToAscii(answer);
			//�ϊ������������ꍇ��ASCII������ɒu��������
			if (!ascii.empty()) {
				answer = ascii;
			}

			if (answer == e.a) {
				cout << "�����I\n";
			}
			else
			{
				cout << "�ԈႢ�I������" << e.a << "\n";
			}
		}	// for questions
	}	//����
	

	return 0;
}