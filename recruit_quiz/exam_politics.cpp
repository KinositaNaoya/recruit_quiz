#include "exam_politics.h"
#include "utility.h"
#include <fstream>
#include <iostream>
#include <random>
#include <unordered_map>
using namespace std;

/*
	���{�̐����̖����쐬����
*/
QuestionList CreatePoliticsExam() {
	//�������f�[�^
	struct PoliticsData
	{
		string genre;			// �W������
		string text;			// ��蕶
		vector<string> answers;	// �󗓂ɓ��铚���̔z��
	};
	unordered_map<string, vector<PoliticsData>>data;

	{//�������f�[�^��ǂݍ���
		constexpr char filename[] = "japanese_politics.txt";
		ifstream ifs(filename);		//txt��ǂݍ��ށH
		if (!ifs) {
			cerr << "�G���[" << filename << "��ǂݍ��߂܂���\n";
			return {};
		}

		while (true){
			string s;
			getline(ifs, s);
			if (!ifs) {
				break;	//�t�@�C�����[�ɓ��B�����̂ŏI��
			}
			const vector<string> v = Split(s, ',');
			const string& genre = v[0];//�W���������擾
			data[genre].push_back({ genre,v[1],vector<string>(v.begin() + 2,v.end()) });
		}
	}//�������f�[�^��ǂݍ���

	constexpr int genreCount = 2;	//�o�肷��W��������
	constexpr int quizConut = 5;	//�e�W�������̏o�萔

	//�y�[�W4/12���瑱��

}