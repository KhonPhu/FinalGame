#include "Game.h"
#include <iostream>

// default constructor
Game::Game() {
	// set the window SDL to null
	sdlWindow = nullptr;
	// set the renderer SDL to null
	sdlRenderer = nullptr;

	// Player Attribute
	m_playerHP = 100;
	m_playerDmg = 100;
	m_playerLevel = 1;
	m_playerCurrentHealth;

	//Enemy Attribute
	m_enemyHP = 110;
	m_enemyDmg = 10;
	m_enemyLevel = 1;
	m_enemyCurrentHealth;

	//// initialize SDL
	// if the initialization was unsuccessful
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init() == -1) {
		// disable game loop
		isGameOver = true;

		// print faled to the console
		std::cout << "Initialize SDL - failed" << std::endl;
	}
	// if the initialization was successful
	else {
		// enable game loop
		isGameOver = false;

		if (Mix_OpenAudio(192000, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
			std::cout << "Audio Init - failed" << std::endl;
		}

		// print faled to the console
		std::cout << "Initialize SDL - success" << std::endl;
	}
}

bool Game::Start() {
	sdlRenderer = SDL_CreateRenderer(sdlWindow, 0, -1);

	if (sdlRenderer != nullptr) {
		std::cout << "Create Renderer - success" << std::endl;

		// TODO: Initialize Objects Here
		m_input = new Input();
		m_inputS = new Input();

		audio = new Audio();

		m_Wall_Up = new Wall();
		m_Wall_Left = new Wall_2();
		m_Wall_Down = new Wall_3();
		m_Wall_Right = new Wall_4();

		m_player = new Player(sdlRenderer, Vector2(50, 50), 64, 64);

		m_enemy = new Enemy(sdlRenderer, Vector2(900, 600), 64, 64);

		m_Portal = new Portal(sdlRenderer, Vector2(900, 700), 52, 52);

		m_Wall_Up = new Wall(sdlRenderer, Vector2(0, 0), 1817, 31);

		m_Wall_Left = new Wall_2(sdlRenderer, Vector2(0, 0), 34, 822);

		m_Wall_Down = new Wall_3(sdlRenderer, Vector2(0, 769), 1817, 31);

		m_Wall_Right = new Wall_4(sdlRenderer, Vector2(969, 0), 34, 822);

		audio->PlayBGMusic("../assets/MainAudio.mp3");

		// initialize texture
		m_textTexture = new Texture();
		// load the font with size
		m_font = TTF_OpenFont("../assets/BAUHS93.TTF", 20);

		

		// Initialize second screen texture & object
		m_idlePlayer = new IdlePlayer(sdlRenderer, Vector2(50, 50), 64, 64);
		m_healthBar = new HealthBar(sdlRenderer, Vector2(30, 150), 146, 146);

		m_idleEnemy = new IdleEnemy(sdlRenderer, Vector2(300, 50), 64, 64);
		m_enemyHealthBar = new HealthBarEnemy(sdlRenderer, Vector2(280, 150), 146, 146);
		m_enemyHealthBarLow = new HBEnemyLow(sdlRenderer, Vector2(280, 150), 146, 146);

		return true;
	}
	std::cout << "Create Renderer - failed" << std::endl;
	return false;
}

void Game::Run(char* title, int width, int height, bool fullscreen) {
	int creationFlag = 0;

	if (!fullscreen) {
		creationFlag = SDL_WINDOW_SHOWN;
	}
	else {
		creationFlag = SDL_WINDOW_FULLSCREEN;
	}

	sdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, creationFlag);

	if (sdlWindow != nullptr && Start()) {
		std::cout << "Create Window - success" << std::endl;
		while (!m_input->GetGameOver()) {
			// current time since the last tick
			unsigned int ticks = SDL_GetTicks() - m_lastUpdateTimer;
			// change that time from milliseconds to seconds
			float deltaTime = ticks / 1000.0f;
			m_lastUpdateTimer = SDL_GetTicks();

			ProcessInput();
			Update(deltaTime);
			Draw();
		}
	}

	std::cout << "Create Window - closed" << std::endl;

	ShutDown();
	Destroy();
}

void Game::FightingScreen(char* title, int width, int height) {
	int creationFlag = 0;

	creationFlag = SDL_WINDOW_SHOWN;
	
	sdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, creationFlag);

	if (sdlWindow != nullptr && Start()) {
		std::cout << "Fight Window - success" << std::endl;
		while (!m_inputS->GetGameOver()) {
			// current time since the last tick
			unsigned int ticks = SDL_GetTicks() - m_lastUpdateTimer;
			// change that time from milliseconds to seconds
			float deltaTime = ticks / 1000.0f;
			m_lastUpdateTimer = SDL_GetTicks();

			ProcessInput();
			Update(deltaTime);
			DrawSecondScreen();
		}
	}

	std::cout << "Create Window - closed" << std::endl;

	ShutDown();
	Destroy();
}

void Game::PE_CollisionCheck()
{
	m_player->ToggleGround(true);
	m_idlePlayer->ToggleGround(true);
	if (m_player->GetCollider()) {

		//if the player hit the portal
		if (m_player->GetCollider()->RectCollision(*m_Portal->GetCollider())) {

			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, " ", "YOU WIN", NULL);

			m_input->ToggleGameOver();

		}
		//If Player hit the Enemy
		if (m_player->GetCollider()->RectCollision(*m_enemy->GetCollider())) {

			FightingScreen((char*)"FIGHTING", 400, 200);

		}

		//If the player hit the wall
		if (m_player->GetCollider()->RectCollision(*m_Wall_Up->GetCollider())) {

			m_player->Deccelerate(Vector2(0, -2) * 1000.0f);

		}
		if (m_player->GetCollider()->RectCollision(*m_Wall_Left->GetCollider())) {

			m_player->Deccelerate(Vector2(-2, 0) * 1000.0f);

		}
		if (m_player->GetCollider()->RectCollision(*m_Wall_Down->GetCollider())) {

			m_player->Deccelerate(Vector2(0, 2) * 1000.0f);

		}
		if (m_player->GetCollider()->RectCollision(*m_Wall_Right->GetCollider())) {

			m_player->Deccelerate(Vector2(2, 0) * 1000.0f);

		}

		// Second sdlWindow Enemy and Player Fighting
		if (m_idlePlayer->GetCollider()->RectCollision(*m_idleEnemy->GetCollider())) {

			m_enemyCurrentHealth = m_enemyHP - m_playerDmg;

			if (m_enemyCurrentHealth > 0) {
				m_idlePlayer->Deccelerate(Vector2(2, 0) * 100.0f);
				if (m_enemyCurrentHealth <= 10)
				{
					delete m_enemyHealthBar;
					m_enemyHealthBar = nullptr;
				}
			}
			else 
			{ 
				ShutDown();
			}
		}
	}
}

void Game::Draw() {
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);

	SDL_RenderClear(sdlRenderer);

	if (m_font != nullptr) {
		std::string pPosX;
		std::string pPosY;

		if (m_player) {
			// get the player position and convert it to a string
			pPosX = std::to_string((int)m_player->GetPlayerPosition().x);
			pPosY = std::to_string((int)m_player->GetPlayerPosition().y);
		}
		else {
			pPosX = "0";
			pPosY = "0";
		}
		
	}


	if (m_player) {
		m_player->Draw(sdlRenderer);
	}
	if (m_enemy) {
		m_enemy->Draw(sdlRenderer);
	}

	if (m_Portal) {
		m_Portal->Draw(sdlRenderer);
	}

	if (m_Wall_Up && m_Wall_Left && m_Wall_Down && m_Wall_Right) {
		m_Wall_Up->Draw(sdlRenderer);
		m_Wall_Left->Draw(sdlRenderer);
		m_Wall_Down->Draw(sdlRenderer);
		m_Wall_Right->Draw(sdlRenderer);
	}


	SDL_RenderPresent(sdlRenderer);
}

void Game::DrawSecondScreen() {
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);

	SDL_RenderClear(sdlRenderer);

	if (m_font != nullptr) {
		std::string pPosX;
		std::string pPosY;

		if (m_idlePlayer) {
			// get the player position and convert it to a string
			pPosX = std::to_string((int)m_idlePlayer->GetIdlePlayerPosition().x);
			pPosY = std::to_string((int)m_idlePlayer->GetIdlePlayerPosition().y);
		}
		else {
			pPosX = "0";
			pPosY = "0";
		}

		if (m_idlePlayer) {
			m_idlePlayer->Draw(sdlRenderer);
		}
		if (m_idleEnemy) {
			m_idleEnemy->Draw(sdlRenderer);
		}
		if (m_healthBar) {
			m_healthBar->Draw(sdlRenderer);
		}
		if (m_enemyHealthBar) {
			m_enemyHealthBar->Draw(sdlRenderer);
		}
		if (m_enemyHealthBar == nullptr && m_enemyHealthBarLow) {
			m_enemyHealthBarLow->Draw(sdlRenderer);
		}
		if (m_enemyCurrentHealth < 0)
		{
			m_textTexture->Draw(sdlRenderer, 200, 100);
		}
	}
	

	SDL_RenderPresent(sdlRenderer);
}

SDL_Texture* Game::LoadFont(const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color) {
	TTF_Font* font = TTF_OpenFont(font_path.c_str(), font_size);
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, message_text.c_str(), color);
	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(sdlRenderer, text_surface);

	SDL_FreeSurface(text_surface);

	return text_texture;
}

void Game::Destroy() {

	SDL_DestroyWindow(sdlWindow);

	SDL_DestroyRenderer(sdlRenderer);

	SDL_Quit();
}

void Game::ProcessInput() {
	// Player Input
	m_input->UpdateInput();
	m_inputS->UpdateInput();
	if (m_player) {
		m_player->HandleInput(m_input);
	}

	if (m_idlePlayer) {
		m_idlePlayer->HandleInputS(m_inputS);
	}
}

void Game::Update(float deltaTime) {
	// Update on deltaTime
	if (m_player) {
		PE_CollisionCheck();
		m_player->Update(deltaTime);
	}
	if (m_Portal) {
		PE_CollisionCheck();
		m_Portal->Update(deltaTime);
	}
	if (m_enemy) {
		PE_CollisionCheck();
		m_enemy->Update(deltaTime);
	}
	if (m_idlePlayer) {
		PE_CollisionCheck();
		m_idlePlayer->Update(deltaTime);
	}
	if (m_idleEnemy) {
		PE_CollisionCheck();
		m_idleEnemy->Update(deltaTime);
	}
	if (m_healthBar) {
		PE_CollisionCheck();
		m_healthBar->Update(deltaTime);
	}
	if (m_enemyHealthBar) {
		PE_CollisionCheck();
		m_enemyHealthBar->Update(deltaTime);
	}
}


void Game::ShutDown() {
	// deallocate stuff
}

Game::~Game() {

}