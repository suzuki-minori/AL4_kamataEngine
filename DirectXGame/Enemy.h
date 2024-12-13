#pragma once

#include "WorldTransform.h"
#include"Model.h"
#include"TextureHandle.h"
#include"ViewProjection.h"
#include"EnemyBullet.h"

enum class Phase {
	Approach,
	Leave,
};


class Enemy
{
public:

	void Initialize(Model*model,uint32_t textureHandle,const Vector3&position);

	~Enemy();

	void Update();

	void ApproachUpdate();
	void LeaveUpdate();

	void Draw(ViewProjection& viewProjection);

	void ApproachInitialize();

public:

	EnemyBullet* bullet_ = nullptr;

	//発射間隔
	static const int kAttackInterval = 60;

private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	ViewProjection* viewProjection_ = nullptr;
	Vector3 approachVelocity = { 0.0f,0.0f,0.1f };
	Vector3 leaveVelocity = { 0.1f,0.1f,0.1f };
	Phase phase_ = Phase::Approach;

	std::list<EnemyBullet*>bullets_;

	int32_t kAttackTimer_ = 0;

	void Attack();
};

