#pragma once
#include "Engine/GameObject.h"
#include<vector>

enum FoodType
{
	FOODTYPE_NORMAL,
	FOODTYPE_POWER,
	FOODTYPE_MAX
};
class Food :
	public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Food(GameObject* parent);
	~Food();
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	void SetFoodType(FoodType type);
	void OnCollision(GameObject* pTarget)override;
	int GetScore() { return score_; }
	
private:
	FoodType type_;
	int hModel_;
	int score_;

	std::vector<std::vector<int>>mapData_;
	int mapWidth_;
	int mapHeight_;
};

