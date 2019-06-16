#ifndef _SCOREBOARD_H
#define _SCOREBOARD_H
#include "Texture.h"
#include <vector>

class Scoreboard : public GameObject
{

private:

	std::vector<Texture*> mScore;

	// Delete all the textures in the board and clear textures
	void ClearBoard();

	SDL_Color mColor;


public:
	Scoreboard();
	Scoreboard(SDL_Color color);
	~Scoreboard();

	void Score(int score);

	void Render();
};

#endif // !_SCOREBOARD_H
