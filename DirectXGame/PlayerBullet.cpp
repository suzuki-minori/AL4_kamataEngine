#include "PlayerBullet.h"
#include"assert.h"
#include"TextureManager.h"
#include"Player.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position)
{
	assert(model);

	model_=model;

	//
	textureHandle_ = TextureManager::Load("uvChecker.png");

	worldTransform_.Initialize();

	//
	worldTransform_.translation_ = position;


}

void PlayerBullet::Update()
{
	worldTransform_.UpdateMatrix();

}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}
