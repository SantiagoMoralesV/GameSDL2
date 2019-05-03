#include <iostream>
#include"GameManager.h"

int main(int argc, char* argv[]) {

	GameManager* game = GameManager::Instance();
	// Runs the game
	game->Run();

	GameManager::Release();
	game = NULL;

	//system("pause");
	return 0;
	
}