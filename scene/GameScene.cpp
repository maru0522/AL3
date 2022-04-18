#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <Calc.h>

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

#pragma region 初期位置

	for (size_t i = 0; i < sizeof(worldTransform_) / sizeof(worldTransform_[0]); i++) {
		// X, Y, Z 方向のスケーリングを設定
		worldTransform_[i].scale_ = { 1.0f, 1.0f, 1.0f };
		// X, Y, Z 軸周りの回転角を設定
		worldTransform_[i].rotation_ = { 0.0f, 0.0f, 0.0f };
		// X, Y, Z 軸周りの平行移動を設定
		worldTransform_[i].translation_ = { (float)cos(i * (2 * PI_ / 10)) * 10, (float)sin(i * (2 * PI_ / 10)) * 10, 0.0f };
		// ワールドトランスフォームの初期化
		worldTransform_[i].Initialize();
	}

#pragma endregion

	// カメラ始点座標を設定
	viewProjection_.eye = { 0,0,-60 };

#pragma region モデル部分

	// 3Dモデルの生成
	model_ = Model::Create();

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

#pragma endregion
}

void GameScene::Update() {
	for (size_t i = 0; i < sizeof(worldTransform_) / sizeof(worldTransform_[0]); i++) {
		// X, Y, Z 軸周りの平行移動を設定
		worldTransform_[i].translation_ = { Calc::RotateX((float)cos(i * (2 * PI_ / 10)) * 10,(float)sin(i * (2 * PI_ / 10)) * 10,RADIANS(angle_)),
											Calc::RotateY((float)cos(i * (2 * PI_ / 10)) * 10,(float)sin(i * (2 * PI_ / 10)) * 10,RADIANS(angle_)),
														  0.0f };
		worldTransform_[i].UpdateMatrix();
	}

	angle_ += 2;
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
	for (size_t i = 0; i < sizeof(worldTransform_) / sizeof(worldTransform_[0]); i++) {
		model_->Draw(worldTransform_[i], viewProjection_, textureHandle_);
	}

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
