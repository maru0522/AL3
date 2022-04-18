#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <math.h>

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

	// カメラ視点座標を決定
	viewProjection_.eye = { 0,0,-20};

	// カメラ注視始点座標を設定
	viewProjection_.target = { targetPosX_,targetPosY_,targetPosZ_ };

	// カメラ上方向ベクトルを設定（右上45度指定）
	viewProjection_.up = { upPosX_,upPosY_,upPosZ_ };

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void GameScene::Update() {

	if (cameraAngle == 12800.0f) {
		cameraAngle = 0;
	}

	viewProjection_.eye.x = sin(cameraAngle) * 10;
	viewProjection_.eye.z = cos(cameraAngle) * 10;

	num++;
	if (num % 3 == 0) {
		cameraAngle += 0.1;
	}
	viewProjection_.UpdateMatrix();


#pragma region Camera1

	// デバッグテキストの表示
	debugText_->SetPos(50, 50);
	debugText_->Printf("Camera1");
	debugText_->SetPos(50, 70);
	debugText_->Printf("eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
	debugText_->SetPos(50, 90);
	debugText_->Printf("target:(%f,%f,%f)", targetPosX_, targetPosY_, targetPosZ_);
	debugText_->SetPos(50, 110);
	debugText_->Printf("up:(%f,%f,%f)", upPosX_, upPosY_, upPosZ_);

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
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);

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