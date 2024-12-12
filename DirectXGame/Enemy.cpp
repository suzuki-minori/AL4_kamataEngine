#include "Enemy.h"
#include"MathUtilityForText.h"

void Enemy::Initialize(Model*model,uint32_t textureHandle,const Vector3& position)
{
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	
}

void Enemy::Update()
{
	switch (phase_) {
	case Phase::Approach:
	default:
		ApproachUpdate();
		break;

	case Phase::Leave:
		LeaveUpdate();
		break;
	}
}

void Enemy::ApproachUpdate()
{
	//
	worldTransform_.translation_ -= approachVelocity;
	worldTransform_.UpdateMatrix();
	//
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::LeaveUpdate()
{
	//
	worldTransform_.translation_ += leaveVelocity;
	worldTransform_.UpdateMatrix();

}

void Enemy::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
