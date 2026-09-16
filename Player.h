#pragma once
#include "Engine/GameObject.h"
#include "Ground.h"

class Ground;

class Player : public GameObject
{
public:
	Player(GameObject* parent);

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void SetGround(Ground* ground) { ground_ = ground; }
	void AddScore(int s) { score_ += s; }
	int GetScore() const { return score_; }

	void PowerUp(float durationSeconds = 5.0f)
	{
		speedUpTimer_ = durationSeconds * 60.0f; 
	}

	void OnCollision(GameObject* pTarget) override;

private:
	int hIdleModel_;
	int hWalkModel_;
	Ground* ground_;
	int score_ = 0;

	float speedUpTimer_ = 0.0f;
};