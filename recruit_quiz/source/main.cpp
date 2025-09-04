
//�����@11/18[�����e�X�g�ǉ�]����


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
	//���ȃf�[�^�z��
	static const struct{
		const char* name;		//���Ȗ�
		QuestionList(*create)();//���쐬�֐��̃A�h���X
	}subjectData[] = {
		{ "���w",CreaetMathematicsExam },
		{ "����",CreateJapaneseExam },
		{ "�p��",CreateEnglish },
		{ "����",CreaetMathematicsExam },
		//{ "�n��", },
		{ "����",CreatePoliticsExam },
		{ "�o��",CreateEconomicsExam },
	};

	QuestionList questions;//���W

	
	{	//���ȑI��
		int subject = 0;
		cout << "[���N���[�g�����΍�N�C�Y]\n";

		do{	// while (subject == 0)
			cout << "���Ȃ�I��ł�������\n";
			for (int i = 0; i < size(subjectData); i++) {
				cout << i + 1 << '=' << subjectData[i].name << '\n';
			}
			cin >> subject;

			if (subject > 0 && subject <= size(subjectData)) {
				questions = subjectData[subject - 1].create();
			}
			else{
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
			else if (e.b.empty()) {
				//������1�����̏ꍇ
				cout << "�ԈႢ�I�@������" << e.a << "\n";
			}else{
				//��������������ꍇ�A�����ꂩ�ƈ�v����ΐ����Ƃ���
				bool isMatch = false;
				for (const auto& b : e.b) {
					if (answer == b) {
						isMatch = true;
						break;
					}
				}
				
				//��r���ʂ��o��
				if (isMatch) {
					cout << "�����I\n";
				}else {
					cout << "�ԈႢ�I�@������" << e.a << "(�܂���";
					for (auto& b : e.b) {
						cout << "�A" << b;
					}
					cout << ")\n";
				}
			} // if answer == e.a
		}	// for questions
	}	//����
	

	return 0;
}