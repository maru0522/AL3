#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <DirectXMath.h>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
  /// <summary>
  /// コンストクラタ
  /// </summary>
    GameScene();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GameScene();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 毎フレーム処理
    /// </summary>
    void Update();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

private: // メンバ変数
    DirectXCommon* dxCommon_ = nullptr;
    Input* input_ = nullptr;
    Audio* audio_ = nullptr;
    DebugText* debugText_ = nullptr;

    // テクスチャハンドル
    uint32_t textureHandle_ = 0;

#pragma region モデル部分

    // 3Dモデル
    Model* model_ = nullptr;
    // ワールドトランスフォーム
    WorldTransform worldTransform_;
    // ビュープロジェクション
    ViewProjection viewProjection_;

#pragma endregion

#pragma region デバッグテキスト部分

    float targetPosX_ = 0.0f;
    float targetPosY_ = 0.0f;
    float targetPosZ_ = 0.0f;

    float upPosX_ = 0.0f;
    float upPosY_ = 1.0f;
    float upPosZ_ = 0.0f;

    float cameraAngle = 0.0f;
    uint32_t num = 0;

#pragma endregion

    /// <summary>
    /// ゲームシーン用
    /// </summary>
};