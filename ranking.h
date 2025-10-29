//********************************************************************************
//
// ranking.h[ƒ‰ƒ“ƒLƒ“ƒOŠÖŒW]
//
//															Author :Riugo Honda
//															Date   :2025/10/28
//********************************************************************************

#ifndef _RANKING_H_
#define _RANKING_H_

#define RANK_NUM (5)

class Ranking
{
private:
	int m_Score[RANK_NUM] = {};

public:
	Ranking();
	~Ranking();

	void SetRanking(int score);
	int GetRank(int num);

	void RankOrganize();
	void ResetRanking();
private:
	void SaveRanking();
	void LoadRanking();
};

#endif // !_RANKING_H_
