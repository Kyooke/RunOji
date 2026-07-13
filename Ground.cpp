#include "Ground.h"
#include "Engine/Model.h"


namespace
{
	using std::vector;
	int model_t = -1;
	vector<vector<int>>mapData =
	{
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,1,0,0,0,0,1},
		{1,0,1,0,1,0,1,1,0,1},
		{1,0,1,0,0,0,1,0,0,1},
		{1,0,1,1,1,0,1,0,1,1},
		{1,0,0,0,1,0,0,0,0,1},
		{1,1,1,0,1,1,1,1,0,1},
		{1,0,0,0,0,0,0,1,0,1},
		{1,0,1,1,1,1,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1},
	};
}

Ground::Ground(GameObject* parent)
{
	mapData_ = mapData;
}

void Ground::Initialize()
{
	//transform_.scale_ = { 40, 1, 40 };
	hSilly = Model::Load("Ground2.fbx");
	hBrock = Model::Load("Block.fbx");
}

void Ground::Update()
{
}

void Ground::Draw()
{
	Model::SetTransform(hSilly, transform_);
	Model::Draw(hSilly);
	for (int j = 0;j < 10;j++)
	{
		for (int i = 0;i < 10;i++)
		{
			if (mapData_[j][i] == 1)
			{
				Transform tr;
				tr.position_ = { 10.0f - i * 2 - 2,.0f,j * 2 - 10.0f };

				Model::SetTransform(hBrock, tr);
				Model::Draw(hBrock);
			}
		}
	}
}

void Ground::Release()
{
}
