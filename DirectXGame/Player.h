#pragma once
#include"Model.h"
#include"WorldTransform.h"



class Player
{
public:

	void Initialize(Model*model,uint32_t textureHandle,ViewProjection*viewProjection);


	void Update();


	void Draw(ViewProjection& viewProjection);


private:

	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0u;

	ViewProjection* viewProjection_=nullptr;

};

