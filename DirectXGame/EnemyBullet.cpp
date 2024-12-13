#include "EnemyBullet.h"
#include<cassert>
#include"TextureManager.h"
#include"MathUtilityForText.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	assert(model);

	model_=model;
	velocity_ = velocity;

	textureHandle_ = TextureManager::Load("uvChecker.png");

	worldTransform_.Initialize();

	//
	worldTransform_.translation_ = position;

}

void EnemyBullet::Update()
{
	//
	worldTransform_.translation_ -= velocity_;

	worldTransform_.UpdateMatrix();

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

}

void EnemyBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}
