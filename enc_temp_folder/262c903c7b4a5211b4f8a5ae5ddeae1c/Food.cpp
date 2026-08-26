#include "Food.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

Food::Food(GameObject*parent)
	:GameObject(parent,"Food"),type_(FOODTYPE_NORMAL),hModel_(-1),score_(0)
{
}

Food::~Food()
{
}

void Food::Initialize()
{
	Collider* collider = new SphereCollider({ 0,0,0 }, 0.5f);
	AddCollider(collider);
}

void Food::Update()
{
}

void Food::Draw()
{
		Model::SetTransform(hModel_, transform_);
		Model::Draw(hModel_);
	
}

void Food::Release()
{
}

void Food::SetFoodType(FoodType type)
{
	 type_ = type;

	 if (type_ == FoodType::FOODTYPE_NORMAL)
	 {
		 hModel_ = Model::Load("esa.fbx");
	 }
	 else if (type_ == FoodType::FOODTYPE_POWER)
	 {
		 hModel_ = Model::Load("Pesa.fbx");
	 }

}

void Food::OnCollision(GameObject* pTarget)
{
	if (type_ == FoodType::FOODTYPE_NORMAL)
		score_ += 1;
	if (type_ = FOODTYPE_NORMAL)
		score_ += 5;

	KillMe();
	return;
}
