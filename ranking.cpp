//********************************************************************************
//
// ranking.cpp[ƒ‰ƒ“ƒLƒ“ƒOŠÖŒW]
//
//															Author :Riugo Honda
//															Date   :2025/10/28
//********************************************************************************
#include <string>
#include <iostream>
#include <fstream>

#include "ranking.h"

Ranking::Ranking()
{
	for (int i = 0; i < RANK_NUM; i++)
	{
		m_Score[i] = 0;
	}

	LoadRanking();
}

Ranking::~Ranking()
{
	SaveRanking();
}

void Ranking::SaveRanking()
{
	std::ofstream myfile;

	myfile.open("Savefile.txt");

	for (int i = 0 ;i < RANK_NUM; i++)
	{
		myfile << m_Score[i] << std::endl;
	}

	myfile.close();
}

void Ranking::LoadRanking()
{
	std::ifstream myfile("Savefile.txt");

	std::string line;

	int line_count = 0;

	while (std::getline(myfile, line))
	{
		int score = std::stoi(line);
		m_Score[line_count] = score;

		line_count++;
	}

}

void Ranking::SetRanking(int score)
{
	for (int i = 0; i < RANK_NUM; i++)
	{
		if (m_Score[i] < score)
		{
			switch (i)
			{
			case 0:
				m_Score[4] = m_Score[3];
				m_Score[3] = m_Score[2];
				m_Score[2] = m_Score[1];
				m_Score[1] = m_Score[0];
				m_Score[0] = score;
				break;
			case 1:
				m_Score[4] = m_Score[3];
				m_Score[3] = m_Score[2];
				m_Score[2] = m_Score[1];
				m_Score[1] = score;
				break;
			case 2:
				m_Score[4] = m_Score[3];
				m_Score[3] = m_Score[2];
				m_Score[2] = score;
				break;
			case 3:
				m_Score[4] = m_Score[3];
				m_Score[3] = score;
				break;
			case 4:
				m_Score[4] = score;
				break;
			}

			return;
		}
	}
}

int Ranking::GetRank(int num)
{
	return m_Score[num];
}

void Ranking::RankOrganize()
{


	/*for (int i = 0; i < RANK_NUM; i++)
	{


		for (int j = 0; j < RANK_NUM; j++)
		{

		}
	}*/
}

void Ranking::ResetRanking()
{
	for (int i = 1; i < RANK_NUM; i++)
	{
		m_Score[i] = 0;
	}
}
