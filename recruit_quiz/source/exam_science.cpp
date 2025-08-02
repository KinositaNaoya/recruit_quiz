#include "../header/exam_science.h"
#include "../header/utility.h"
#include <random>

using namespace std;

/// <summary>
/// 物理の問題を作成する
/// </summary>
/// <returns></returns>
QuestionList CreatePhysicsExam()
{
	QuestionList questions;
	questions.reserve(10);	//10個の問題と答えを用意する
	random_device rd;
	
	{	// 等速直線運動
		constexpr int divisors[] = { 1,2,3,4,5,6,10,12,15,20,30,60 };		//(ﾃﾞｨﾊﾞｲｻﾞｰｽﾞ)60を割り切れる数の集まり
		int i = uniform_int_distribution<>(0, size(divisors) - 1)(rd);		//divisors配列の0～11をランダムに選ぶ
		int v = uniform_int_distribution<>(1, 10)(rd) * 60 / divisors[i];	//時速
		int t = uniform_int_distribution<>(1, 10)(rd) * divisors[i];		//時間
		questions.push_back({
			"時速" + to_string(v) +
			"kmで移動する車がある。\nこの車が" +
			to_string(v * t / 60) +
			"km移動するのにかかる時間を分単位で求めよ。",to_string(t)
			});
	}	//等速直線運動

	return QuestionList();
}
