#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <random>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();


	// 乱数シード生成器
	std::random_device seed_gen;
	// メルセンヌ・ツイスター
	std::mt19937_64 engin(seed_gen());
	// 乱数範囲(座標用)
	std::uniform_real_distribution<float> posDist(-10.0f, 10.0f);


	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("Task1_2Resources/mario.jpg");

	// X, Y, Z 方向のスケーリングを設定
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };
	// X, Y, Z 軸周りの回転角を設定
	worldTransform_.rotation_ = { 0.0f,0.0f,0.0f };
	// X, Y, Z 軸周りの平行移動を設定
	worldTransform_.translation_ = { 0.0f,0.0f,0.0f };

#pragma region モデル部分

	// 3Dモデルの生成
	model_ = Model::Create();
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

#pragma endregion
	for (size_t i = 0; i < _countof(viewProjection_); i++) {
		// eye座標をランダム生成
		eyePosX_[i] = posDist(engin);
		eyePosY_[i] = posDist(engin);
		eyePosZ_[i] = posDist(engin);


		// カメラ視点座標を決定
		viewProjection_[i].eye = { eyePosX_[i],eyePosY_[i],eyePosZ_[i]};

		// カメラ注視始点座標を設定
		viewProjection_[i].target = {0,0,0};

		// カメラ上方向ベクトルを設定（右上45度指定）
		viewProjection_[i].up = {0.0f,1.0f,0.0f};

		// ビュープロジェクションの初期化
		viewProjection_[i].Initialize();
	}
}

void GameScene::Update() {

	if (input_->TriggerKey(DIK_SPACE)) {
		if (cameraNum < 2) {
			cameraNum++;
		}
		else {
			cameraNum = 0;
		}
	}

#pragma region Camera1

	// デバッグテキストの表示
	debugText_->SetPos(50, 50);
	debugText_->Printf("Camera1");
	debugText_->SetPos(50, 70);
	debugText_->Printf("eye:(%f,%f,%f)",eyePosX_[0], eyePosY_[0], eyePosZ_[0]);
	debugText_->SetPos(50, 90);
	debugText_->Printf("target:(%f,%f,%f)", targetPosX_[0], targetPosY_[0], targetPosZ_[0]);
	debugText_->SetPos(50, 110);
	debugText_->Printf("up:(%f,%f,%f)", upPosX_[0], upPosY_[0], upPosZ_[0]);

#pragma endregion

#pragma region Camera2

	// デバッグテキストの表示
	debugText_->SetPos(50, 150);
	debugText_->Printf("Camera2");
	debugText_->SetPos(50, 170);
	debugText_->Printf("eye:(%f,%f,%f)", eyePosX_[1], eyePosY_[1], eyePosZ_[1]);
	debugText_->SetPos(50, 190);
	debugText_->Printf("target:(%f,%f,%f)", targetPosX_[1], targetPosY_[1], targetPosZ_[1]);
	debugText_->SetPos(50, 210);
	debugText_->Printf("up:(%f,%f,%f)", upPosX_[1], upPosY_[1], upPosZ_[1]);

#pragma endregion

#pragma region Camera3

	// デバッグテキストの表示
	debugText_->SetPos(50, 250);
	debugText_->Printf("Camera3");
	debugText_->SetPos(50, 270);
	debugText_->Printf("eye:(%f,%f,%f)", eyePosX_[2], eyePosY_[2], eyePosZ_[2]);
	debugText_->SetPos(50, 290);
	debugText_->Printf("target:(%f,%f,%f)", targetPosX_[2], targetPosY_[2], targetPosZ_[2]);
	debugText_->SetPos(50, 310);
	debugText_->Printf("up:(%f,%f,%f)", upPosX_[2], upPosY_[2], upPosZ_[2]);

#pragma endregion
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
	model_->Draw(worldTransform_, viewProjection_[cameraNum], textureHandle_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
