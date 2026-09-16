#pragma once
#include "Engine/GameObject.h"
#include "Ground.h"

class Ground;

class Player :
	public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Player(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	void SetGround(Ground* ground) { ground_ = ground; }

	void AddScore(int s) { score_ += s; }
	int GetScore() const { return score_; }
	void OnCollision(GameObject* pTarget) override;
private:
	int hIdleModel_;
	int hWalkModel_;
	Ground* ground_;
	int score_ = 0;
	int oldState_ = -1;
};

