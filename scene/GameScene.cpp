#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <random>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete sprite_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("Task1_2Resources/mario.jpg");
	reticle_ = TextureManager::Load("Task1_2Resources/reticle.png");


	// 乱数シード生成器
	std::random_device seed_gen;
	// メルセンヌ・ツイスター
	std::mt19937_64 engin(seed_gen());
	// 乱数範囲(回転角用)
	std::uniform_real_distribution<float> rotDist(0.0f, XM_2PI);
	// 乱数範囲(座標用)
	std::uniform_real_distribution<float> posDist(-10.0f, 10.0f);


	for (size_t i = 0; i < _countof(worldTransform_); i++) {
		// X, Y, Z 方向のスケーリングを設定
		worldTransform_[i].scale_ = { 1.0f,1.0f,1.0f };
		// X, Y, Z 軸周りの回転角を設定
		worldTransform_[i].rotation_ = { rotDist(engin),rotDist(engin),rotDist(engin) };
		// X, Y, Z 軸周りの平行移動を設定
		worldTransform_[i].translation_ = { posDist(engin),posDist(engin),posDist(engin) };


		// ワールドトランスフォームの初期化
		worldTransform_[i].Initialize();
	}


	// カメラ始点座標を設定
	viewProjection_.eye = { 0,0,-60 };

#pragma region モデル部分

	// 3Dモデルの生成
	model_ = Model::Create();
	// レティクルスプライトの生成
	sprite_ = Sprite::Create(reticle_, { 550,270 });


	// カメラ垂直方向視野角を設定
	viewProjection_.fovAngleY = XMConvertToRadians(45.0f);

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

#pragma endregion
}

void GameScene::Update() {
	if (input_->PushKey(DIK_UP)) {
		viewProjection_.target.y += 0.1f;
	}
	if (input_->PushKey(DIK_DOWN)) {
		viewProjection_.target.y -= 0.1f;
	}
	if (input_->PushKey(DIK_LEFT)) {
		viewProjection_.target.x -= 0.1f;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		viewProjection_.target.x += 0.1f;
	}

	if (input_->PushKey(DIK_SPACE)) {
		scope = Near_;
	}
	else {
		scope = Far_;
	}


	if (scope == Near_) {
		if (viewProjection_.fovAngleY > XMConvertToRadians(20.0f)) {
			viewProjection_.fovAngleY -= 0.01f;
		}
	}
	if (scope == Far_) {
		if (viewProjection_.fovAngleY < XMConvertToRadians(40.0f)) {
			viewProjection_.fovAngleY += 0.01f;
		}
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
	// 3Dモデル描画
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
	if (scope == Near_) {
		sprite_->Draw();
	}

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
