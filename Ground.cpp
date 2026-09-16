#include "Ground.h"
#include "Engine/Model.h"
#include"Engine/CsvReader.h"
#include"Food.h"

namespace
{
	using std::vector;
	int model_t = -1;
	/*vector<vector<int>>mapData =
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
	};*/
}

Ground::Ground(GameObject* parent)
	:hGround(-1), hBrock(-1), hEsa(-1), hPesa(-1), mapWidth_(-1), mapHeight_(-1)
{
	CsvReader csvData;
	csvData.Load("map.csv");
	mapWidth_ = csvData.GetWidth();
	mapHeight_ = csvData.GetHeight();

	mapData_ = vector<vector<int>>(mapHeight_, vector<int>(mapWidth_, 0));
	mapObj_ = vector<vector<int>>(mapHeight_, vector<int>(mapWidth_, 0));

	for (int y = 0; y < mapHeight_; y++)
	{
		for (int x = 0; x < mapWidth_; x++)
		{
			mapData_[y][x] = csvData.GetValue(x, y);
		}
	}

	for (int y = 0; y < mapHeight_; y++)
	{
		for (int x = 0; x < mapWidth_; x++)
		{
			if (mapData_[y][x] == 1)
			{
				continue;
			}

			Food* food = (Food*)Instantiate<Food>(this);
			food->SetPosition({ 10.0f - x * 2 - 1, 0.0f, y * 2 - 9.0f });

			if (mapData_[y][x] == 2)
			{
				food->SetFoodType(FoodType::FOODTYPE_POWER);
			}
			else
			{
				food->SetFoodType(FoodType::FOODTYPE_NORMAL);
			}
		}
	}
}

void Ground::Initialize()
{
	//transform_.scale_ = { 40, 1, 40 };
	hGround = Model::Load("Ground2.fbx");
	hBrock = Model::Load("Block.fbx");
}

void Ground::Update()
{
}

void Ground::Draw()
{
	Model::SetTransform(hGround, transform_);
	Model::Draw(hGround);
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
