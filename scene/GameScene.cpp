#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

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

#pragma region 上部分 [0] ~ [8]

	for (size_t i = 0; i < _countof(worldTransform_); i++) {
		if (i <= 8) {
			// X, Y, Z 方向のスケーリングを設定
			worldTransform_[i].scale_ = { scaleValX_,scaleValY_,scaleValZ_ };
			// X, Y, Z 軸周りの回転角を設定
			worldTransform_[i].rotation_ = { 0.0f,0.0f,0.0f };
			// X, Y, Z 軸周りの平行移動を設定
			worldTransform_[i].translation_ = { -40.0f + i*10,20.0f,0.0f };
			// ワールドトランスフォームの初期化
			worldTransform_[i].Initialize();
		}
	}

#pragma endregion


#pragma region 下方向 [9] ~ [17]

	// X, Y, Z 方向のスケーリングを設定
	worldTransform_[9].scale_ = { scaleValX_,scaleValY_,scaleValZ_ };
	// X, Y, Z 軸周りの回転角を設定
	worldTransform_[9].rotation_ = { 0.0f,0.0f,0.0f };
	// X, Y, Z 軸周りの平行移動を設定
	worldTransform_[9].translation_ = { -40.0f,-20.0f,0.0f };
	// ワールドトランスフォームの初期化
	worldTransform_[9].Initialize();

	// X, Y, Z 方向のスケーリングを設定
	worldTransform_[10].scale_ = { scaleValX_,scaleValY_,scaleValZ_ };
	// X, Y, Z 軸周りの回転角を設定
	worldTransform_[10].rotation_ = { 0.0f,0.0f,0.0f };
	// X, Y, Z 軸周りの平行移動を設定
	worldTransform_[10].translation_ = { -40.0f + 10,-20.0f,0.0f };
	// ワールドトランスフォームの初期化
	worldTransform_[10].Initialize();

	// X, Y, Z 方向のスケーリングを設定
	worldTransform_[11].scale_ = { scaleValX_,scaleValY_,scaleValZ_ };
	// X, Y, Z 軸周りの回転角を設定
	worldTransform_[11].rotation_ = { 0.0f,0.0f,0.0f };
	// X, Y, Z 軸周りの平行移動を設定
	worldTransform_[11].translation_ = { -40.0f + 20,-20.0f,0.0f };
	// ワールドトランスフォームの初期化
	worldTransform_[11].Initialize();

	// X, Y, Z 方向のスケーリングを設定
	worldTransform_[12].scale_ = { scaleValX_,scaleValY_,scaleValZ_ };
	// X, Y, Z 軸周りの回転角を設定
	worldTransform_[12].rotation_ = { 0.0f,0.0f,0.0f };
	// X, Y, Z 軸周りの平行移動を設定
	worldTransform_[12].translation_ = { -40.0f + 30,-20.0f,0.0f };
	// ワールドトランスフォームの初期化
	worldTransform_[12].Initialize();

	// X, Y, Z 方向のスケーリングを設定
	worldTransform_[13].scale_ = { scaleValX_,scaleValY_,scaleValZ_ };
	// X, Y, Z 軸周りの回転角を設定
	worldTransform_[13].rotation_ = { 0.0f,0.0f,0.0f };
	// X, Y, Z 軸周りの平行移動を設定
	worldTransform_[13].translation_ = { -40.0f + 40,-20.0f,0.0f };
	// ワールドトランスフォームの初期化
	worldTransform_[13].Initialize();

	// X, Y, Z 方向のスケーリングを設定
	worldTransform_[14].scale_ = { scaleValX_,scaleValY_,scaleValZ_ };
	// X, Y, Z 軸周りの回転角を設定
	worldTransform_[14].rotation_ = { 0.0f,0.0f,0.0f };
	// X, Y, Z 軸周りの平行移動を設定
	worldTransform_[14].translation_ = { -40.0f + 50,-20.0f,0.0f };
	// ワールドトランスフォームの初期化
	worldTransform_[14].Initialize();

	// X, Y, Z 方向のスケーリングを設定
	worldTransform_[15].scale_ = { scaleValX_,scaleValY_,scaleValZ_ };
	// X, Y, Z 軸周りの回転角を設定
	worldTransform_[15].rotation_ = { 0.0f,0.0f,0.0f };
	// X, Y, Z 軸周りの平行移動を設定
	worldTransform_[15].translation_ = { -40.0f + 60,-20.0f,0.0f };
	// ワールドトランスフォームの初期化
	worldTransform_[15].Initialize();

	// X, Y, Z 方向のスケーリングを設定
	worldTransform_[16].scale_ = { scaleValX_,scaleValY_,scaleValZ_ };
	// X, Y, Z 軸周りの回転角を設定
	worldTransform_[16].rotation_ = { 0.0f,0.0f,0.0f };
	// X, Y, Z 軸周りの平行移動を設定
	worldTransform_[16].translation_ = { -40.0f + 70,-20.0f,0.0f };
	// ワールドトランスフォームの初期化
	worldTransform_[16].Initialize();

	// X, Y, Z 方向のスケーリングを設定
	worldTransform_[17].scale_ = { scaleValX_,scaleValY_,scaleValZ_ };
	// X, Y, Z 軸周りの回転角を設定
	worldTransform_[17].rotation_ = { 0.0f,0.0f,0.0f };
	// X, Y, Z 軸周りの平行移動を設定
	worldTransform_[17].translation_ = { -40.0f + 80,-20.0f,0.0f };
	// ワールドトランスフォームの初期化
	worldTransform_[17].Initialize();

#pragma endregion

#pragma region モデル部分

	// 3Dモデルの生成
	model_ = Model::Create();

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

#pragma endregion
}

void GameScene::Update() {

	//#pragma region translation debug string
	//
	//	// 値を含んだ文字列
	//	std::string transStrDebug = std::string("translation:(") +
	//		std::to_string(translationValX_) +
	//		std::string(", ") +
	//		std::to_string(translationValY_) +
	//		std::string(", ") +
	//		std::to_string(translationValZ_) +
	//		std::string(")");
	//
	//	// デバッグテキストの表示
	//	debugText_->Print(transStrDebug, 50, 50, 1.0f);
	//
	//#pragma endregion

	//#pragma region rotation debug string
	//
	//	// 値を含んだ文字列
	//	std::string rotStrDebug = std::string("rotation:(") +
	//		std::to_string(rotationValX_) +
	//		std::string(", ") +
	//		std::to_string(rotationValY_) +
	//		std::string(", ") +
	//		std::to_string(rotationValZ_) +
	//		std::string(")");
	//
	//	// デバッグテキストの表示
	//	debugText_->Print(rotStrDebug, 50, 80, 1.0f);
	//
	//#pragma endregion

	//#pragma region scale debug string
	//
	//	// 値を含んだ文字列
	//	std::string scaleStrDebug = std::string("scale:(") +
	//		std::to_string(scaleValX_) +
	//		std::string(", ") +
	//		std::to_string(scaleValY_) +
	//		std::string(", ") +
	//		std::to_string(scaleValZ_) +
	//		std::string(")");
	//
	//	// デバッグテキストの表示
	//	debugText_->Print(scaleStrDebug, 50, 110, 1.0f);
	//
	//#pragma endregion
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
	for (size_t i = 0; i < _countof(worldTransform_); i++) {
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
