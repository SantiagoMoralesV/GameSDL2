#include "ScoreBoard.h"



ScoreBoard::ScoreBoard()
{
	Score(0);
}


ScoreBoard::~ScoreBoard()
{
	clearBoard();
}

void ScoreBoard::Score(int score)
{
	clearBoard();

	if (score == 0)
	{
		//loop till two zeros are deisplayed
		for (int i = 0; i < 2; i++)
		{
			//to show "00" score
			mScore.push_back(new Texture("0", "ArcadeClassic.ttf", 32, { 230,230,230 }));
			mScore[i]->Parent(this);
			mScore[i]->Pos(Vector2(-32.0f*i, 0.0f));
		}
	}
	else
	{
		//convert score to string
		std::string str = std::to_string(score);
		int lastIndex = str.length() - 1;

		for (int i = 0; i <= lastIndex; i++)
		{
			//to get one character at a time
			mScore.push_back(new Texture(str.substr(i, 1), "ArcadeClassic.ttf", 32, { 230,230,230 }));
			mScore[i]->Parent(this);
			//adding numbers from left
			mScore[i]->Pos(Vector2(-32.0f*(lastIndex - i), 0.0f));

		}
	}
}

void ScoreBoard::Render()
{
	for (int i = 0; i < mScore.size(); i++)
	{
		mScore[i]->Render();
	}
}

void ScoreBoard::clearBoard()
{
	for (int i = 0; i < mScore.size(); i++)
	{
		delete mScore[i];
		mScore[i] = NULL;
	}
	mScore.clear();
}
