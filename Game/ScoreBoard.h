#ifndef  _SCOREBOARD_H_
#define _SCOREBOARD_H_
#include "Texture.h"
#include <vector>

class ScoreBoard : public GameObject
{
public:
	ScoreBoard();
	~ScoreBoard();

	//to pass score
	void Score(int score);
	void Render();

private:
	//vector that will track all texture
	std::vector<Texture*> mScore;

	//delete all textures and score and clear vector
	void clearBoard();
};

#endif // ! _SCOREBOARD_H_
