#include "../header/exam_science.h"
#include "../header/utility.h"
#include <random>

using namespace std;

/// <summary>
/// �����̖����쐬����
/// </summary>
/// <returns></returns>
QuestionList CreatePhysicsExam()
{
	QuestionList questions;
	questions.reserve(10);	//10�̖��Ɠ�����p�ӂ���
	random_device rd;
	
	{	// ���������^��
		constexpr int divisors[] = { 1,2,3,4,5,6,10,12,15,20,30,60 };		//(�ި�޲�ް��)60������؂�鐔�̏W�܂�
		int i = uniform_int_distribution<>(0, size(divisors) - 1)(rd);		//divisors�z���0�`11�������_���ɑI��
		int v = uniform_int_distribution<>(1, 10)(rd) * 60 / divisors[i];	//����
		int t = uniform_int_distribution<>(1, 10)(rd) * divisors[i];		//����
		questions.push_back({
			"����" + to_string(v) +
			"km�ňړ�����Ԃ�����B\n���̎Ԃ�" +
			to_string(v * t / 60) +
			"km�ړ�����̂ɂ����鎞�Ԃ𕪒P�ʂŋ��߂�B",to_string(t)
			});
	}	//���������^��

	return QuestionList();
}
