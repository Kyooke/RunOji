#include "Food.h"
#include "Player.h"	
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

Food::Food(GameObject* parent)
	: GameObject(parent, "Food")
	, type_(FOODTYPE_NORMAL)
	, hModel_(-1)
	, score_(0)
{
}

Food::~Food()
{
}

void Food::Initialize()
{
	Collider* collider = new SphereCollider({ 0, 0, 0 }, 0.5f);
	AddCollider(collider);

	if (hModel_ == -1)
	{
		hModel_ = Model::Load("esa.fbx");
		score_ = 1;
	}
}

void Food::Update()
{
}

void Food::Draw()
{
	if (hModel_ != -1)
	{
		Model::SetTransform(hModel_, transform_);
		Model::Draw(hModel_);
	}
}

void Food::Release()
{
}

void Food::SetFoodType(FoodType type)
{
	type_ = type;

	if (type_ == FOODTYPE_NORMAL)
	{
		hModel_ = Model::Load("esa.fbx");
		score_ = 1;
	}
	else if (type_ == FOODTYPE_POWER)
	{
		hModel_ = Model::Load("Pesa.fbx");
		score_ = 5;
	}
}

void Food::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Player")
	{
		Player* player = dynamic_cast<Player*>(pTarget);
		if (player != nullptr)
		{
			player->AddScore(score_);

			if (type_ == FOODTYPE_POWER)
			{
				player->PowerUp(5.0f); 
			}
		}

		KillMe();
	}
}