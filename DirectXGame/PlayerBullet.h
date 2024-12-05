#pragma once
#include"Vector3.h"
#include"Model.h"
#include"WorldTransform.h"

class PlayerBullet
{
public:

	void Initialize(Model* model, const Vector3& position,const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	//
	int32_t deathTimer_ = kLifeTime;

	//
	bool IsDead() const { return isDead_; }


private:

	WorldTransform worldTransform_;
	Model* model_=nullptr;
	uint32_t textureHandle_;
	Vector3 velocity_;

	static const int32_t kLifeTime = 60 * 5;

	//
	bool isDead_ = false;
};

