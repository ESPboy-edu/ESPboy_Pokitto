#pragma once

#include "Pokitto.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"
#include "../entities/Entities.h"
#include "BaseState.h"
#include "../entities/Entities.h"
#include "../data/Formations.h"
#include "../images/Images.h"
#include "../utils/Constants.h"
#include "../utils/Utils.h"
#include "../utils/Enums.h"
#include "../utils/GameCookie.h"

class PlayGameState : public BaseState {

	private:

		void renderHUD();	
		void renderPlayer();
		void loadLevel(uint32_t level);
		void handlePlayerDead(bool suppressExplosionFX);
		void handlePlayerButtons(bool allowShoot);
		void handleStartOfPlay();
		void renderStageDetails();
		void renderChallengeStageDetails();
		void incLevel();
		void challengeRecordDeath(Enemy * enemy);
		void checkExtraLife();
		
		BulletType getEnemyBulletType();
		uint8_t getBulletsInPlay();
		void handleLevelActions();


	public:

		void activate();
		GameStateType update(GameStateType currentState, GameCookie *cookie);
		void render();

	private:

		Bullets bullets;
		EnemyBullets enemyBullets;
		Enemies enemies;
		Player player;

		const LevelData *levelData;
		const FormationData *formation;

		uint16_t levelData_Counter = 0;
		uint16_t repeatStart = 0;
		uint16_t levelData_Delay = 0;
		uint16_t levelData_Delay_All = 0;
		uint16_t levelData_Delay_AfterCompletion = 0;
		uint32_t score = 0;
		uint32_t level = 0;

		uint8_t enemyBulletCountdown = 0;
		uint8_t enemyBulletCountdown_Delay = ENEMY_BULLET_COUNTDOWN_DELAY_MAX;
		uint8_t bulletsInPlay;

		uint32_t counter = 0;
		LevelStartType levelStartType = LevelStartType::StartOfGame_Init;
		StageType stageType = StageType::Normal;

		bool startPulse = false;
		bool gamePaused = false;

		Transform transform;
		Challenge challenge;
		CaptureController captureController;

		bool extraLife1;
		bool extraLife2;
		uint8_t extraLifeCounter;
		uint8_t starFieldSpeed;

};