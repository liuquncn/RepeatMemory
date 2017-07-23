#ifndef SCORE_H
#define SCORE_H

#include <math.h>

// ����: ��һ��С�ڻ����0�ĸ�������������Ϊ���Ŷȣ�ȡֵ��Χ(0,1]���Ķ���
class Score
{
	float TheScore;
public:
	Score() { TheScore=0; }
	// ȡ�ý�������
	float getScore() const { return TheScore; }
	// ���øý�������
	void setScore(float s) { TheScore=(s>0 ? 0 : (s<LowestScore ? LowestScore : s)); }
	// ������Ŷȼ����һ���ȼ�����һ�������ͳ�������
	static const float ScaledRuleScore[10];
	// ������Ŷȼ������Сֵ����һ�������ͳ�������
	static const float LowestRuleScore;
	// ��С����ֵ���κ����ֶ�Ӧ�������ֵ
	static const float LowestScore;
};

#endif//SCORE_H