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

	// X, Y, Z 方向のスケーリングを設定
	worldTransform_.scale_ = { scaleValX_,scaleValY_,scaleValZ_ };
	// X, Y, Z 軸周りの回転角を設定
	worldTransform_.rotation_ = { rotationValX_,rotationValY_,rotationValZ_ };
	// X, Y, Z 軸周りの平行移動を設定
	worldTransform_.translation_ = { 0.0f,0.0f,0.0f};

#pragma region モデル部分

	// 3Dモデルの生成
	model_ = Model::Create();
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

#pragma endregion
}

void GameScene::Update() {

	//変数の値をインクリメント
	value_++;
	// 値を含んだ文字列
	std::string strDebug = std::string("Value:") + std::to_string(value_);
	// デバッグテキストの表示
	debugText_->Print(strDebug, 50, 150, 1.0f);

	// 値を含んだ文字列
	std::string transStrDebug = std::string("translation:( ") +
		std::to_string(translationValX_); /*+
		std::string(", ") +
		std::to_string(translationValY_) +
		std::string(", ") +
		std::to_string(translationValZ_) +
		std::string(")");*/


	// デバッグテキストの表示
	debugText_->Print(transStrDebug, 50, 50, 1.0f);
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

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
