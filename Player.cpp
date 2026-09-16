#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "TestScene.h"
#include "Engine/Input.h"
#include "Engine/SphereCollider.h"
#include "Food.h"

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

	float P_ANGLE[4] = { 180.0f, 0.0f, 270.0f, 90.0f };
	PLAYER_DIRECTION pdirection = PLAYER_DOWN;
	XMVECTOR P_MOVE[4] = { XMVectorSet(0, 0, 1, 0), XMVectorSet(0, 0, -1, 0), XMVectorSet(1, 0, 0, 0), XMVectorSet(-1, 0, 0, 0) };

	float TURN_FRAME = 30.0f;
	float turnStartAngle = 0.0f;
	float turnEndAngle = 0.0f;
	PLAYER_DIRECTION turnEndDirection = PLAYER_DOWN;

	float AdjustAngle(float angle)
	{
		if (angle > 180.0f)
			angle -= 360.0f;

		if (angle < -180.0f)
			angle += 360.0f;

		return angle;
	}
	std::vector<std::vector<int>> gmap;
}

Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), hIdleModel_(-1), hWalkModel_(-1)
{
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
	Collider* collider = new SphereCollider({ 0, 0, 0 }, 0.25f);
	AddCollider(collider);
}

void Player::Update()
{
	XMVECTOR pos = XMLoadFloat3(&transform_.position_);
	XMVECTOR move = XMVectorSet(0, 0, 0, 0);

	float currentSpeed = 0.05f; 
	if (speedUpTimer_ > 0.0f)
	{
		currentSpeed = 0.1f; 
		speedUpTimer_ -= 1.0f; 
	}

	static float turnFrame = 0.0f;

	bool isKeyInput = false;
	PLAYER_DIRECTION nextDir = pdirection;

	if (pstate != PLAYER_STATE::PLAYER_TURN)
	{
		if (Input::IsKey(DIK_W)) { nextDir = PLAYER_DIRECTION::PLAYER_UP; isKeyInput = true; }
		else if (Input::IsKey(DIK_S)) { nextDir = PLAYER_DIRECTION::PLAYER_DOWN; isKeyInput = true; }
		else if (Input::IsKey(DIK_D)) { nextDir = PLAYER_DIRECTION::PLAYER_LEFT; isKeyInput = true; }
		else if (Input::IsKey(DIK_A)) { nextDir = PLAYER_DIRECTION::PLAYER_RIGHT; isKeyInput = true; }

		if (isKeyInput)
		{
			if (pdirection != nextDir)
			{
				pstate = PLAYER_STATE::PLAYER_TURN;
				turnFrame = 0.0f;
				turnStartAngle = P_ANGLE[pdirection];
				turnEndDirection = nextDir;
				turnEndAngle = P_ANGLE[turnEndDirection];
			}
			else
			{
				pstate = PLAYER_STATE::PLAYER_WALK;
			}
		}
		else
		{
			pstate = PLAYER_STATE::PLAYER_IDLE;
		}
	}

	if (pstate == PLAYER_STATE::PLAYER_TURN)
	{
		turnFrame += 1.0f;
		float t = turnFrame / TURN_FRAME;
		if (t > 1.0f)
		{
			t = 1.0f;
		}
		float nAngle = AdjustAngle(turnEndAngle - turnStartAngle);
		transform_.rotate_.y = turnStartAngle + nAngle * t;

		if (turnFrame >= TURN_FRAME)
		{
			transform_.rotate_.y = P_ANGLE[turnEndDirection];
			pdirection = turnEndDirection;
			pstate = PLAYER_STATE::PLAYER_WALK;
		}
	}

	if (pstate == PLAYER_STATE::PLAYER_WALK)
	{
		move = P_MOVE[pdirection];
		transform_.rotate_.y = P_ANGLE[pdirection];
	}

	pos = pos + currentSpeed * move;
	XMStoreFloat3(&transform_.position_, pos);
	XMFLOAT3 wpos = transform_.position_;

	if (ground_ != nullptr)
	{
		gmap = ground_->GetMapData();
		int mapX = (int)((10 - wpos.x) / 2);
		int mapZ = (int)((wpos.z + 10) / 2);

		if (mapZ >= 0 && mapZ < gmap.size() && mapX >= 0 && mapX < gmap[0].size())
		{
			if (gmap[mapZ][mapX] == 1)
			{
				pos = pos - currentSpeed * move;
				XMStoreFloat3(&transform_.position_, pos);
			}
		}
	}
}

void Player::Draw()
{
	if (pstate == PLAYER_STATE::PLAYER_IDLE)
	{
		Model::SetTransform(hIdleModel_, transform_);
		Model::Draw(hIdleModel_);
	}
	else if (pstate == PLAYER_STATE::PLAYER_WALK || pstate == PLAYER_STATE::PLAYER_TURN)
	{
		Model::SetTransform(hWalkModel_, transform_);
		Model::Draw(hWalkModel_);
	}
}

void Player::Release()
{
}

void Player::OnCollision(GameObject* pTarget)
{
	if (pTarget == nullptr)
	{
		return;
	}

	
	if (pTarget->GetObjectName() == "PowerFood")
	{
		PowerUp(5.0f); 
	}
}