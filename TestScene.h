#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"

class Text;

class Food;

class Player;
//テストシーンを管理するクラス
class TestScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TestScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	
private:

	int Score = 0;
	Text* pText_;
	Food* food_;
	Player* pPlayer;
};