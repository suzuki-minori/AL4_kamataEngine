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




private:

	WorldTransform worldTransform_;
	Model* model_=nullptr;
	uint32_t textureHandle_;
	Vector3 velocity_;

};

