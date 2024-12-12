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
	worldTransform_.translation_ -= velocity;

	worldTransform_.UpdateMatrix();

}

void Enemy::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
