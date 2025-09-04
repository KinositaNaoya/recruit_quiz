#include "../header/exam_economics.h"
#include "../header/utility.h"
#include <fstream>
#include <iostream>
#include <random>
#include <unordered_map>
using namespace std;

/// <summary>
/// �o�ς̖����쐬����
/// </summary>
/// <returns></returns>
QuestionList CreateEconomicsExam()
{
	//�o�ϖ��f�[�^
	struct EconomicsData
	{
		string genre;
		string text;
		vector<vector<string>> answers;
	};
	unordered_map<string, vector<EconomicsData>> data;

	{	//�o�ϖ��f�[�^��ǂݍ���
		constexpr char filename[] = "text/japanese_economics.txt";
		ifstream ifs(filename);
		if (!ifs) {
			cerr << "�G���[:" << filename << "��ǂݍ��߂܂���\n";
			return {};
		}

		while (true)
		{
			string s;
			getline(ifs, s);
			if (!ifs) {
				break;
			}
			const vector<string> v = Split(s, ',');
			const string& genre = v[0];

			//���������
			vector<vector<string>> answers;
			for (auto i = v.begin() + 2; i != v.end(); i++) {
				answers.push_back(Split(*i, '|'));
			}

			//���f�[�^��ǉ�
			data[genre].push_back({ genre, v[1], answers });
		}
	}	//�o�ϖ��f�[�^��ǂݍ���

	constexpr int genreCount = 2;
	constexpr int QuizCount = 5;
	QuestionList questions;
	questions.reserve(genreCount* QuizCount);
	random_device rd;

	//�����_���ɑI�񂾓�̃W����������A�W���������Ń����_���ɑI�񂾂T����o�肷��
	const vector<int> genreIndices = CreateRandomIndices((int)data.size());
	for (int i = 0; i < genreCount; i++) {
		//�o�肷��W��������I��
		auto itr = data.begin();
		advance(itr, genreIndices[i]);
		const auto& genre = itr->second;

		// �W���������Ń����_���ɂT��I��
		const vector<int> questionIndices = CreateRandomIndices((int)genre.size());
		for (int j = 0; j < QuizCount; j++){
			const auto& question = genre[questionIndices[j]];	//�I�񂾖��f�[�^

			//�󗓂̈ʒu�Ɛ��𒲂ׂ�
			//�󗓂́u�J���g���ʁv�Ɓu���g���ʁv�̃y�A�A�܂�{}�ŕ\�����
			vector<int> blanks;
			for (int k = 0; k < question.text.size() - 1; k++) {
				if (question.text[k] == '{' && question.text[k + 1] == '}') {
					blanks.push_back(k);
				}
			}

			//�󗓂̂���1�������_���ɑI��
			const int index = uniform_int_distribution<>(0, (int)blanks.size() - 1)(rd);

			//��蕶�̃R�s�[���쐬���A�I�΂�Ȃ������󗓂��u�����v�ɒu��������
			string s = "[" + question.genre + "]���̕��͂�[ ? ]�ɓ���P��𓚂���\n";
			int from = 0;
			for (int k = 0; k < blanks.size(); k++){
				const int end = blanks[k];
				s.append(question.text, end - from);
				
				if (k != index) {
					s += question.answers[k][0];
				}else {
					s.append("[ ? ]");
				}
				from = end + 2;
			}
			s.append(question.text, from);

			questions.push_back({ s,question.answers[index][0] });

			//�������������肤��ꍇ�A�������u����b�v�̔z��ɑ��
			const auto& answer = question.answers[index];
			if (answer.size() > 1) {
				questions.back().b.assign(answer.begin() + 1, answer.end());
			}
		} // for i < quizCount
	} // for i < genreCount

	return questions;
}
