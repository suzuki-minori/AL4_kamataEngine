#include "Enemy.h"
#include"MathUtilityForText.h"
#include<cassert>
#include"Player.h"

void Enemy::Initialize(Model*model,uint32_t textureHandle,const Vector3& position)
{
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	ApproachInitialize();
}

Enemy::~Enemy()
{
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Enemy::Update()
{
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
		});

	switch (phase_) {
	case Phase::Approach:
	default:
		ApproachUpdate();
		break;

	case Phase::Leave:
		LeaveUpdate();
		break;
	}

	//
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
}

void Enemy::ApproachUpdate()
{
	//
	kAttackTimer_--;
	//
	if (kAttackTimer_ == 0) {
		//
		Attack();
		//
		kAttackTimer_ = kAttackInterval;
	}
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
	//
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}

}

void Enemy::ApproachInitialize()
{
	kAttackTimer_ = kAttackInterval;
}

Vector3 Enemy::GetWorldPosition()
{
	Vector3 worldPos;
	//
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void Enemy::OnCollision()
{
}

void Enemy::Attack()
{
	assert(player_);
	//
	const float kBulletSpeed = 1.0f;
	//Vector3 velocity(0, 0, kBulletSpeed);
	
	//
	Vector3 playerWorldTranslation = player_->GetWorldPosition();
	Vector3 enemyWorldTranslation = worldTransform_.translation_;
	Vector3 d = enemyWorldTranslation - playerWorldTranslation;
	//
	d = Normalize(d);
	//
	d *= kBulletSpeed;


	//
	//velocity = TransformNormal(velocity, worldTransform_.matWorld_);

	//
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, d);

	//
	bullets_.push_back(newBullet);
}
