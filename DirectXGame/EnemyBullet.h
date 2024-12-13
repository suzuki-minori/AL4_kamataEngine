#pragma once
#include"Model.h"
#include"Vector3.h"
#include"ViewProjection.h"
#include"WorldTransform.h"

class EnemyBullet
{
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	int32_t deathTimer_ = kLifeTime;

	//
	bool IsDead() const { return isDead_; }


private:
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Vector3 velocity_ = {0.0f,0.0f,0.1f};

	static const int32_t kLifeTime = 60 * 5;

	//
	bool isDead_ = false;

};

