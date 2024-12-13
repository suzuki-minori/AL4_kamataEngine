#include "Enemy.h"
#include"MathUtilityForText.h"

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

void Enemy::Attack()
{
	//
	const float kBulletSpeed = 1.0f;
	Vector3 velocity(0, 0, kBulletSpeed);

	//
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);

	//
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	//
	bullets_.push_back(newBullet);
}
