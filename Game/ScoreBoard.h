#ifndef _SCOREBOARD_H
#define _SCOREBOARD_H
#include "Texture.h"
#include <vector>

class Scoreboard : public GameObject
{

private:
	// stores score elements accesed by pointers or iterators
	std::vector<Texture*> mScore;

	// Delete all the textures in the board and clear textures
	void ClearBoard();
	// used for the color of the scores
	SDL_Color mColor;


public:
	Scoreboard();
	// Constructor takes the color
	Scoreboard(SDL_Color color);
	~Scoreboard();

	// takes the score and creates textures accordingly 
	void Score(int score);

	void Render();
};

#endif // !_SCOREBOARD_H
