#include "Scoreboard.h"



Scoreboard::Scoreboard()
	: Scoreboard({ 230, 230, 230 })
{}

Scoreboard::Scoreboard(SDL_Color color) {

	mColor = color;
	Score(0);
}


Scoreboard::~Scoreboard()
{
	ClearBoard();
}

void Scoreboard::ClearBoard()
{
	// clears the score size
	for (int i = 0; i < mScore.size(); i++) {

		delete mScore[i];
		mScore[i] = NULL;
	}

	mScore.clear();
}

void Scoreboard::Score(int score) 
{
	//clears previous score 
	ClearBoard();

	if (score == 0) {

		for (int i = 0; i < 2; i++) {
			// creates new score texture when score equals 0
			mScore.push_back(new Texture("0", "kenvector_future.ttf", 32, mColor ));
			mScore[i]->Parent(this);
			// position of the score 
			mScore[i]->Pos(Vector2(-32.0f*i, 0.0f));
		}
	}
	else {
		// replaces the a number in the last index 
		std::string str = std::to_string(score);
		int lastIndex = str.length() - 1;

		for (int i = 0; i <= lastIndex; i++) {
			// creates a texture of depending of the position
			mScore.push_back(new Texture(str.substr(i, 1), "kenvector_future.ttf", 32, mColor));
			//relative to its parent
			mScore[i]->Parent(this);
			// position  of the new texture
			mScore[i]->Pos(Vector2(-32.0f*(lastIndex - i), 0.0f));
		}
	}

}

void Scoreboard::Render()
{
	for (int i = 0; i < mScore.size(); i++) {
		// render textures depending on the score
		mScore[i]->Render();
	}
}

