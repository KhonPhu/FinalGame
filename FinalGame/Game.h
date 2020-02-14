#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Texture.h"
#include "Input.h"
#include "Player.h"
#include "Portal.h"
#include "Wall.h"
#include "Wall_2.h"
#include "Wall_3.h"
#include "Wall_4.h"
#include "Enemy.h"
#include "IdlePlayer.h"
#include "IdleEnemy.h"
#include "HealthBar.h"
#include "HealthBarEnemy.h"
#include "HBEnemyLow.h"

class Game
{
public:
	Game();

	bool Start();

	void ProcessInput();

	void Update(float deltaTime);

	void Draw();

	void DrawSecondScreen();

	void ShutDown();

	void Run(char* title, int width, int height, bool fullscreen);

	void FightingScreen(char* title, int width, int height);

	void PE_CollisionCheck();

	void Destroy();

	SDL_Texture* LoadFont(const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color);

	~Game();
private:

	SDL_Window* sdlWindow;

	SDL_Renderer* sdlRenderer;

	bool isGameOver;

	Texture* m_textTexture;
	TTF_Font* m_font;

	IdlePlayer* m_idlePlayer;
	IdleEnemy* m_idleEnemy;

	HealthBar* m_healthBar;
	HealthBarEnemy* m_enemyHealthBar;
	HBEnemyLow* m_enemyHealthBarLow;

	Input* m_input;
	Input* m_inputS;

	Player* m_player;

	Enemy* m_enemy;

	Portal* m_Portal;

	Wall* m_Wall_Up;
	Wall_2* m_Wall_Left;
	Wall_3* m_Wall_Down;
	Wall_4* m_Wall_Right;

	unsigned int m_lastUpdateTimer;

	Audio* audio;

	//attribute
	int m_playerHP;
	int m_playerDmg;
	int m_playerLevel;
	int m_playerCurrentHealth;

	//Attribute
	int m_enemyHP;
	int m_enemyDmg;
	int m_enemyLevel;
	int m_enemyCurrentHealth;

};

