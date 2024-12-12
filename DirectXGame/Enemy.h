#pragma once

#include "WorldTransform.h"
#include"Model.h"
#include"TextureHandle.h"
#include"ViewProjection.h"

enum class Phase {
	Approach,
	Leave,
};


class Enemy
{
public:

	void Initialize(Model*model,uint32_t textureHandle,const Vector3&position);

	void Update();

	void ApproachUpdate();
	void LeaveUpdate();

	void Draw(ViewProjection& viewProjection);



private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	ViewProjection* viewProjection_ = nullptr;
	Vector3 approachVelocity = { 0.0f,0.0f,0.1f };
	Vector3 leaveVelocity = { 0.2f,0.2f,0.2f };
	Phase phase_ = Phase::Approach;

};

