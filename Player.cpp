#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "TestScene.h"
#include "Engine/Input.h"
#include"Engine/SphereCollider.h"

namespace
{
	enum PLAYER_STATE
	{
		PLAYER_IDLE,
		PLAYER_WALK,
		PLAYER_TURN,
		PLAYER_STATE_MAX
	};
	PLAYER_STATE pstate = PLAYER_STATE::PLAYER_IDLE;

	enum PLAYER_DIRECTION
	{
		PLAYER_UP,
		PLAYER_DOWN,
		PLAYER_LEFT,
		PLAYER_RIGHT,
		PLAYER_DIRECTION_MAX
	};

	float P_ANGLE[4] = { 180.0f,0.0f,270.0f,90.0f };
	PLAYER_DIRECTION pdirection=PLAYER_DOWN;
	XMVECTOR P_MOVE[4] = {XMVectorSet(0,0,1,0),XMVectorSet(0,0,-1,0) ,XMVectorSet(1,0,0,0) ,XMVectorSet(-1,0,0,0) };

	float TURN_FRAME = 30.0f;
	float turnStartAngle = 0.0f;
	float turnEndAngle = 0.0f;
	PLAYER_DIRECTION turnEndDirection = PLAYER_DOWN;
	float AdjustAngle(float angle)
	{
		if (angle > 180.0f)
			angle -= 360.0f;

		if(angle < -180.0f)
			angle += 360.0f;

		return angle;
	}
	std::vector<std::vector<int>>gmap;
}
Player::Player(GameObject* parent)
	:GameObject(parent,"Player"), hIdleModel_(-1), hWalkModel_(-1) {
	//swordDirには、初期方向として、ローカルモデルの剣の根っこから
	//先端までのベクトルとして（0,1,0)を代入しておく
	//初期位置は原点
}

void Player::Initialize()
{
	hIdleModel_ = Model::Load("Idle.fbx");
	hWalkModel_ = Model::Load("Walk.fbx");
	Model::SetAnimFrame(hIdleModel_, 0, 59, 1.0);
	Model::SetAnimFrame(hWalkModel_, 0, 119, 1.0);
	if (ground_ != nullptr)
	{
		gmap = ground_->GetMapData();
	}
	else
	{
		Debug::Log("Ground is not set for Player.");
	}
	Collider* collider = new SphereCollider({ 0,0,0 }, 0.25f);
	AddCollider(collider);
}

void Player::Update()
{
	//transform_.rotate_.y +=1;
	//static float angle = 0.0;
	//angle = angle + 0.3f;
	//XMMATRIX scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	//XMMATRIX rotateX = XMMatrixRotationX(XMConvertToRadians(angle));
	//XMMATRIX rotate = XMMatrixRotationY(XMConvertToRadians(angle));
	//XMMATRIX translate = XMMatrixTranslation(1.0f, 0.0f, 0.0f);
	//SetWorldMatrix(scale *  rotate * translate);

	XMVECTOR pos = XMLoadFloat3(&transform_.position_);
	XMVECTOR move = XMVectorSet(0, 0, 0, 0);
	PLAYER_DIRECTION oldDir = pdirection;


	float Angle = 0.0f;
	const float SPEED = 0.05f;
	static float turnFrame = 0.0f;
	static PLAYER_STATE oldState = PLAYER_STATE::PLAYER_IDLE;
	if (oldState != PLAYER_STATE::PLAYER_WALK &&
		pstate == PLAYER_STATE::PLAYER_WALK)
	{
		Model::SetAnimFrame(hWalkModel_, 0, 117, 1.0f);
	}

	oldState = pstate;

	if (pstate != PLAYER_STATE::PLAYER_TURN)
	{
		pstate = PLAYER_STATE::PLAYER_IDLE;
	}
	PLAYER_DIRECTION old = pdirection;
	if (pstate != PLAYER_STATE::PLAYER_TURN)
	{
		if (Input::IsKey(DIK_D))
		{
			pdirection = PLAYER_DIRECTION::PLAYER_LEFT;
			pstate = PLAYER_STATE::PLAYER_WALK;
		}
		if (Input::IsKey(DIK_A))
		{
			pdirection = PLAYER_DIRECTION::PLAYER_RIGHT;
			pstate = PLAYER_STATE::PLAYER_WALK;
		}
	}
	if (oldDir != pdirection)
	{
		pstate = PLAYER_STATE::PLAYER_TURN;
		turnFrame = 0.0f;
		turnStartAngle = P_ANGLE[oldDir];
		turnEndDirection = pdirection;
		turnEndAngle = P_ANGLE[turnEndDirection];
	}
	if (pstate == PLAYER_STATE::PLAYER_TURN)
	{
		turnFrame += 1.0f;
		float t = turnFrame / TURN_FRAME;
		if (t > 1.0f)
		{
			t = 1.0f;
		}
		 float nAngle=AdjustAngle(turnEndAngle - turnStartAngle);
		Angle = turnStartAngle + nAngle * t;
		transform_.rotate_.y = Angle;
		if (turnFrame>=TURN_FRAME)
		{
			transform_.rotate_.y = P_ANGLE[pdirection];
			pdirection = turnEndDirection;
			pstate = PLAYER_STATE::PLAYER_WALK;
		}
	}
	if(pstate != PLAYER_STATE::PLAYER_IDLE)
	{

		Angle = P_ANGLE[pdirection];
		
	}
	if (pstate == PLAYER_STATE::PLAYER_WALK)
	{
		move = P_MOVE[pdirection];
	}

	pos = pos + SPEED * move;
	XMStoreFloat3(&transform_.position_, pos);
	XMFLOAT3 wpos = transform_.position_;
	
	gmap = ground_->GetMapData();
	int mapX = (int)((10 - wpos.x) / 2);
	int mapZ = (int)((wpos.z + 10) / 2);
	if (gmap[mapZ][mapX] == 1)
	{
		pos = pos - SPEED * move;
		XMStoreFloat3(&transform_.position_, pos);
	}
}

void Player::Draw()
{
	//transform_.scale_ = { 0.01,0.01,0.01 };
	//transform_.position_ = { 0, 0.0, 0 };
	if (pstate == PLAYER_STATE::PLAYER_IDLE)
	{
		Model::SetTransform(hIdleModel_, transform_);
		Model::Draw(hIdleModel_);
	}
	else if (pstate == PLAYER_STATE::PLAYER_WALK|| pstate == PLAYER_STATE::PLAYER_TURN)
	{
		Model::SetTransform(hWalkModel_ ,transform_);
		Model::Draw(hWalkModel_);
	}
}


void Player::Release()
{
}
