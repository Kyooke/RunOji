#include "TitleScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
    : GameObject(parent, "TitleScene")
{
}

//初期化
void TitleScene::Initialize()
{
    hImage = Image::Load("Title.png");
}

//更新
void TitleScene::Update()
{
    if (Input::IsKey(DIK_T))
    {
        SceneManager* mgr = (SceneManager*)GetParent();
        mgr->ChangeScene(SCENE_ID_TEST);
    }
}

//描画
void TitleScene::Draw()
{
    Image::Draw(hImage);
}

//開放
void TitleScene::Release()
{

}
