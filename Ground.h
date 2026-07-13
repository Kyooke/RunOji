#pragma once
#include "Engine/GameObject.h"
#include<vector>


class Ground :
	public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Ground(GameObject* parent);

	std::vector<std::vector<int>>GetMapData() { return mapData_; }
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
private:
	int hSilly;
	int hBrock;
	std::vector<std::vector<int>>mapData_;
};

