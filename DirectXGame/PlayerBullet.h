#pragma once
#include"Vector3.h"
#include"Model.h"
#include"WorldTransform.h"

class PlayerBullet
{
public:

	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);


private:

	WorldTransform worldTransform_;
	Model* model_=nullptr;
	uint32_t textureHandle_;


};
