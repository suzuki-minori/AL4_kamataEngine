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

Player::~Player()
{
	//
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}

}


void Player::Update()
{
	//
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});


	//
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

	////アフィン変換行列の作成
	//worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	//player移動制限
	const float kMoveLimitX = 33.0;
	const float kMoveLimitY = 18.0;

	//↑の処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);



	//
	Attack();

	//
	Rotate();


	//
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}

	
	//
	//worldTransformBlock->TransferMatrix();

	worldTransform_.UpdateMatrix();



#pragma region デバッグ表示
	
	ImGui::Begin("playerData");
	ImGui::DragFloat3("playerTranslate", &worldTransform_.translation_.x);
	ImGui::End();


#pragma endregion


}

void Player::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}

}

void Player::Rotate()
{
	const float kRotSpeed = 0.02f;

	//
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	}
	else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}
}

void Player::Attack()
{
	if (input_->TriggerKey(DIK_SPACE)) {

		//
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		//
		velocity = TransformNormal(velocity, worldTransform_.matWorld_);

		//
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_,velocity);

		//
		bullets_.push_back(newBullet);

	}


}


