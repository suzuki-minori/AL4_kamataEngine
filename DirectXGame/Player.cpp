#include "Player.h"
#include"cassert"
#include"ImGuiManager.h"
#include"Vector3.h"
#include"MathUtilityForText.h"

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection)
{
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	viewProjection_ = viewProjection;
	input_ = Input::GetInstance();
}


void Player::Update()
{
	Vector3 move = { 0,0,0 };

	const float kCharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_UP)) {
		move.y+= kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}
	//座標移動
	worldTransform_.translation_ += move;
	//アフィン変換行列の作成
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_,worldTransform_.rotation_,worldTransform_.translation_);
	//
	//worldTransformBlock->TransferMatrix();

	worldTransform_.TransferMatrix();

}

void Player::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}


