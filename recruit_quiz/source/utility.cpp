
#include "../header/utility.h"

#include <random>
using namespace std;

//�ő���񐔂����߂�
int gcd(int a, int b)
{
	//�]�肪0�ɂȂ������̏�����Ԃ�
	while (b) {
		int r = a % b;
		a = b;//���������̔폜���ɂ���
		b = r;//�]������̏����ɂ���
	}
	return a;
}

//�����_���Ȕԍ��z����쐬����
vector<int>CreateRandomIndices(int n) {
	//�ԍ���z��Ɋi�[
	vector<int> indices(n);
	for (int i = 0; i < n; i++) {
		indices[i] = i;
	}

	//�ԍ��̔z����V���b�t��
	Shuffle(indices);

	return indices;
}

/// <summary>
/// �z����V���b�t������
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
/// �Ԉ�����ԍ��̔z����쐬����
/// </summary>
/// <param name="n">�쐬����ԍ��͈̔�</param>
/// <param name="correctIndex">�����̔ԍ�</param>
/// <returns></returns>
std::vector<int> CreateWrongIndices(int n, int correctIndex){
	//�ԍ���z��Ɋi�[
	vector<int> indices(n - 1);
	for (int i = 0; i < correctIndex; i++) {
		indices[i] = i + 1;
	}

	for (int i = correctIndex; i < n - 1; i++) {
		indices[i] = i + 1;
	}

	//�ԍ��̔z����V���b�t��
	Shuffle(indices);

	return indices;
}

/*
	������𕪊�����
*/
vector<string> Split(const string& s, char c)
{
	vector<string>v;	//����������������i�[����z��(�߂�l)

	//�S�Ă̕��������[�v����
	auto begin = s.begin();	//�����͈͂̐擪�z��
	const auto end = s.end();	//������̏I�[
	for (auto p = begin; p != end; ++p) {
		//��؂蕶���̑O�܂ł̕�����Ƃ��ĕ���
		if (*p == c) {
			v.push_back(string(begin, p));
			begin = p + 1;//�擪�ʒu���u��؂蕶���̎��v�̈ʒu�ɍX�V
		}
	}
	//�c�蕔����z��ɒǉ�
	v.push_back(string(begin, end));
	return v;
}

// Shift_JIS�̐�����ASCII�̐����ɕϊ�����֐�
string ConvertSjisNumberToAscii(const string& sjis)
{
	//���l������SJIS����ASCII�ւ̕ϊ��\
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

	//�����R�[�h��ϊ�����
	string ascii;
	for(auto i = sjis.begin(); i != sjis.end(); ++i) {
		const unsigned char a = i[0];
		if (a < 0x80) {	// ASCII�����͂��̂܂܃R�s�[����
			ascii.push_back(*i);
		}
		else {			// SJIS�����̏ꍇ��ASCII�����ɕϊ�����
			const unsigned int code = a * 0x100 + (unsigned int)i[1];
			const auto itr = find_if(begin(conversionTable), end(conversionTable),
				[code](const auto& e) {return e.sjis == code; });
			if (itr == end(conversionTable)) {
				break;	//�ϊ��ł��Ȃ�����������������I��
			}
			ascii.push_back(itr->ascii);
			i++;//�Q�o�C�g�����Ȃ̂�1�o�C�g�]���ɐi�߂�
		}
	} // for i

	return string();
}
