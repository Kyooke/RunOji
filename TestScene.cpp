#include "TestScene.h"
#include "Player.h"
#include "Ground.h"
#include "Engine/Camera.h"
#include "Engine/Text.h"
#include "Food.h"

namespace
{
	int myScore = 10;
}
//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{	
	//pWp = Instantiate<Weapon>(this);
	Player* pPlayer = Instantiate <Player>(this);
	Ground* pGround = Instantiate<Ground>(this);
	pPlayer->SetGround(pGround);

	Camera::SetPosition({ 0,10,-20 });
	Camera::SetTarget({ 0,0,0 });

	pText_ = new Text;
	pText_->Initialize();
}

//更新
void TestScene::Update()
{
	 Score =food_->GetScore();
}

//描画
void TestScene::Draw()
{
	std::string scrText;
	scrText = "SCORE:" + std::to_string(Score);
	pText_->Draw(20, 20, scrText.c_str());
}

//開放
void TestScene::Release()
{
	pText_->Release();
}
