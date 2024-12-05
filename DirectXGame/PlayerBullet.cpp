#include "PlayerBullet.h"
#include"assert.h"
#include"TextureManager.h"
#include"Player.h"
#include"MathUtilityForText.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position,const Vector3& velocity)
{
	assert(model);

	model_=model;
	velocity_ = velocity;

	//
	textureHandle_ = TextureManager::Load("uvChecker.png");

	worldTransform_.Initialize();

	//
	worldTransform_.translation_ = position;

}

void PlayerBullet::Update()
{
	//
	worldTransform_.translation_ += velocity_;

	worldTransform_.UpdateMatrix();

	//
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}
