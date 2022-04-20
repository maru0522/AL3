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

	for (size_t y = 0; y < sizeof(worldTransform_) / sizeof(worldTransform_[0]); y++) {
		for (size_t x = 0; x < sizeof(worldTransform_[0]) / sizeof(worldTransform_[0][0]); x++) {
			// X, Y, Z 方向のスケーリングを設定
			worldTransform_[y][x].scale_ = { 1.0f, 1.0f, 1.0f };
			// X, Y, Z 軸周りの回転角を設定
			worldTransform_[y][x].rotation_ = {0.0f, 0.0f, 0.0f};
			// X, Y, Z 軸周りの平行移動を設定
			worldTransform_[y][x].translation_ = {-12.0f + x * 3, 12.0f - y * 3, 0.0f};
			// ワールドトランスフォームの初期化
			worldTransform_[y][x].Initialize();
		}
	}

#pragma endregion

	// カメラ始点座標を設定
	viewProjection_.eye = { 0,0,-60 };

#pragma region モデル部分

	// 3Dモデルの生成
	model_ = Model::Create();

	// カメラ垂直方向視野角を設定
	viewProjection_.fovAngleY = XMConvertToRadians(45.0f);

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

#pragma endregion
}

void GameScene::Update() {
	if (input_->PushKey(DIK_W)) {
		viewProjection_.target.y += 0.1f;
	}
	if (input_->PushKey(DIK_S)) {
		viewProjection_.target.y -= 0.1f;
	}
	if (input_->PushKey(DIK_A)) {
		viewProjection_.target.x -= 0.1f;
	}
	if (input_->PushKey(DIK_D)) {
		viewProjection_.target.x += 0.1f;
	}

	if (input_->PushKey(DIK_UP)) {
		viewProjection_.fovAngleY -= 0.01f;
		viewProjection_.fovAngleY = max(viewProjection_.fovAngleY, 0.01f);
	}
	else if (input_->PushKey(DIK_DOWN)) {
		viewProjection_.fovAngleY += 0.01f;
		viewProjection_.fovAngleY = min(viewProjection_.fovAngleY, XM_PI);
	}
	
	viewProjection_.UpdateMatrix();

	// デバッグテキスト
	debugText_->SetPos(50, 50);
	debugText_->Printf("eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
	debugText_->SetPos(50, 70);
	debugText_->Printf("target:(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y, viewProjection_.target.z);
	debugText_->SetPos(50, 90);
	debugText_->Printf("up:(%f,%f,%f)", viewProjection_.up.x, viewProjection_.up.y, viewProjection_.up.z);
	debugText_->SetPos(50, 110);
	debugText_->Printf("fovAngleY(Degree):(%f)", XMConvertToDegrees(viewProjection_.fovAngleY));
	debugText_->SetPos(50, 130);
	debugText_->Printf("nearZ:(%f)", viewProjection_.nearZ);
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
	for (size_t y = 0; y < sizeof(worldTransform_) / sizeof(worldTransform_[0]); y++) {
		for (size_t x = 0; x < sizeof(worldTransform_[0]) / sizeof(worldTransform_[0][0]); x++) {
				model_->Draw(worldTransform_[y][x], viewProjection_, textureHandle_);
		}
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
