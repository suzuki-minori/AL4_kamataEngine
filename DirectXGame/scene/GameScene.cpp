#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include"AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

	delete model_;
	delete player_;
	delete debugCamera_;
	delete enemy_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("mario.png");
	model_ = Model::Create();
	viewProjection_.Initialize();
	debugCamera_ = new DebugCamera(1080, 720);
	player_ = new Player();
	player_->Initialize(model_,textureHandle_,&viewProjection_);
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	enemy_ = new Enemy();
	enemy_->Initialize(model_, textureHandle_, position_);
	enemy_->SetPlayer(player_);
}

void GameScene::Update() {

	player_->Update();
	enemy_->Update();
	CheckAllCollisions();

	//カメラ処理
	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView =debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		//
		viewProjection_.TransferMatrix();
	}
	else {
		//
		viewProjection_.UpdateMatrix();
	}

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_C)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
#endif // DEBUG
	

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	player_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	


	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

//衝突判定
void GameScene::CheckAllCollisions()
{
	//
	Vector3 posA, posB,posAE,posBE;

	//
	const std::list<PlayerBullet*>&playerBullets = player_->GetBullets();
	//
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

#pragma region 自キャラ敵弾

	//
	posA = player_->GetWorldPosition();

	//
	for (EnemyBullet* bullet : enemyBullets) {
		//
		posBE = bullet->GetWorldPosition();

		float l = ((posBE.x - posA.x) * (posBE.x - posA.x)) + ((posBE.y - posA.y) * (posBE.y - posA.y)) + ((posBE.z - posA.z) * (posBE.z - posA.z));
	
		if (l <= 3) {
			//
			player_->OnCollision();
			//
			bullet->OnCollision();

		}
	
	}

#pragma endregion

#pragma region 自弾敵キャラ

	//
	posAE = enemy_->GetWorldPosition();

	//
	for (PlayerBullet* bullet : playerBullets) {
		//
		posB = bullet->GetWorldPosition();

		float l = ((posB.x - posAE.x) * (posB.x - posAE.x)) + ((posB.y - posAE.y) * (posB.y - posAE.y)) + ((posB.z - posAE.z) * (posB.z - posAE.z));

		if (l <= 3) {
			//
			enemy_->OnCollision();
			//
			bullet->OnCollision();

		}

	}


#pragma endregion

#pragma region 自弾敵弾

	//
	for (EnemyBullet* bullet : enemyBullets) {
		//
		posBE = bullet->GetWorldPosition();

		for (PlayerBullet* playerBullet : playerBullets) {
			//
			posB = playerBullet->GetWorldPosition();

			float l = ((posBE.x - posB.x) * (posBE.x - posB.x)) + ((posBE.y - posB.y) * (posBE.y - posB.y)) + ((posBE.z - posB.z) * (posBE.z - posB.z));

			if (l <= 3) {
				//
				bullet->OnCollision();

			}

		}
	}

#pragma endregion
}
