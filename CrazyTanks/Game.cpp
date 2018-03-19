#include "Game.h"

Game::Game()
{
	this->numberOfEnemies = 4;
	for (int i = 0; i < numberOfEnemies; i++) {
		enemies.push_back(new Enemy);
		//enemies.push_back(std::make_unique<Enemy>);
	}
}



Game::~Game()
{
}



void Game::timeInGame()
{
	int time = 0;
	for (;;)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "You are " << ++time << "sec in the game" << std::flush << std::endl;
	}
}



void Game::startTheGame() {
	// initialize our timer
	std::thread thr(timeInGame);
	thr.detach();

	world.makeWorld();

	// placing players and opponents on the map
	player->placeInTheWorld(world.heigth, world.width);
	std::for_each(enemies.begin(), enemies.end(), [this](auto _val) {
		_val->placeInTheWorld(world.heigth, world.width);
	});

	while (gameStatus()) {
		world.drawWorld();
		std::cout << "Your score: " << player->score << std::endl;

		player->input(world);

		player->logic(world);

		//std::for_each(rockets.begin(), rockets.end(), [this] (auto _val) mutable
		//{
		//	_val->logic(world);
		//});

		std::for_each(enemies.begin(), enemies.end(), [this] (auto _val) mutable
		{
			_val->logic(world);
		});
	}
}



bool Game::gameStatus() {
	return (player->isAlive() && !enemies.empty()) ? true : false;
}