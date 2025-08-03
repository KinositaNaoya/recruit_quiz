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

	{	//等加速度直線運動

		// 公式: v = v0 + at を使って解く問題
		int v0 = uniform_int_distribution<>(1, 10)(rd);	//初速
		int a = uniform_int_distribution<>(1, 5)(rd);	//加速度
		int t = uniform_int_distribution<>(1, 20)(rd);	//移動時間
		questions.push_back({
			"秒速" + to_string(v0) +
			"mで移動していた車が、進行方向に大きさ" + to_string(a) +
			"m/sで等加速度直線運動をはじめた。\n" + to_string(t) +
			"秒後の速度をm/s単位で求めよ。",to_string(v0 + a * t)
			});


		//公式: x = v0t + 1/2*at^2を使って解く問題
		v0 = uniform_int_distribution<>(5, 20)(rd);	//初速
		a = uniform_int_distribution<>(1, 5)(rd);	//加速度
		t = uniform_int_distribution<>(1, 10)(rd);	//移動時間
		questions.push_back({
			"秒速" + to_string(v0) +
			"mで移動していた車が、進行方向に大きさ" + to_string(a) +
			"m/sで等加速度直線運動をはじめた。\n加速を始めてから" + to_string(t) +
			"秒後までに移動した距離をm単位で求めよ。",to_string(v0 * t + a * t * t / 2)
			});


		//公式: v^2 - v0^2 = 2ax を使って解く問題
		a = -uniform_int_distribution<>(1, 5)(rd) * 2;	//加速度
		t = uniform_int_distribution<>(1, 10)(rd);		//移動時間
		v0 = -a * t;									//初速
		questions.push_back({
			"秒速" + to_string(v0) +
			"mで移動していた車がブレーキをかけたところ" +
			to_string(v0 * t + a * t * t / 2) +
			"m進んで停止した。\n" +
			"ブレーキの加速度をm/s^2単位で求めよ。",to_string(a)
			});

	}	//等加速度直線運動

	{	//重力加速度
		int t = uniform_int_distribution<>(1, 10)(rd);	//移動時間
		int x = 98 * t * t / 2;	//10倍することで、小数点以下第１位までを整数として表す
		string answer = to_string(x / 10);
		if (x % 10) {
			//小数部がある場合は小数部を文字列化
			answer += '.';
			answer += '0' + x % 10;
		}
		questions.push_back({
			"重力加速度を9.8m/s^2とする。\n十分に高い位置から物体を静かに落とすと、物体は"+
			to_string(t) + "秒間でXm落下する。\n"+
			"xの値を小数点以下第1位まで求めよ(ただし空気抵抗はないものとする)。",answer
			});

		int v0 = uniform_int_distribution<>(1, 10)(rd);	//初速
		t = uniform_int_distribution<>(1, 10)(rd);	//移動時間
		int v = v0 * 10 - 98 * t;//速度
		answer.clear();
		if (v < 0) {
			v = -v;
			answer = '-';
			answer += '0' + v % 10;
		}
		questions.push_back({
			"重力加速度を9.8m/s^2とする。\n初速"+ to_string(v0)+
			"m/sで物体を鉛直に投げたとき、"+to_string(t)+
			"秒後の物体の速度はXm/sである。\n" +
			"Xの値を少数点以下第1位まで求めよ(ただし空気抵抗はないものとする)。",
			answer
			});

	}	//重力加速度

	return questions;
}
