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
	int hGround;
	int hBrock;
	int hEsa;
	int hPesa;

	std::vector<std::vector<int>>mapData_;
	std::vector<std::vector<int>>mapObj_;

	int mapWidth_;
	int mapHeight_;
};

