#pragma once

#include "WorldTransform.h"
#include"Model.h"
#include"TextureHandle.h"
#include"ViewProjection.h"


class Enemy
{
public:

	void Initialize(Model*model,uint32_t textureHandle,const Vector3&position);

	void Update();

	void Draw(ViewProjection& viewProjection);



private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	ViewProjection* viewProjection_ = nullptr;
	Vector3 velocity = { 0.0f,0.0f,0.1f };


};

