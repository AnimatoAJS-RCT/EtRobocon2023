/******************************************************************************
 *  ScenarioTracer_.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/02/07
 *  Implementation of the Class ScenarioTracer_
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "ScenarioTracer_.h"

/**
 * コンストラクタ
 * @param walker          走行
 * @param scenario        シナリオ
 * @param timer           タイマ
 */
ScenarioTracer_::ScenarioTracer_(Walker* walker,
                               Scenario* scenario,
                               SimpleTimer* timer)
    : mWalker(walker),
      mScenario(scenario),
      mSimpleTimer(timer),
      mState(UNDEFINED) {
}

/**
 * シナリオトレースする
 */
void ScenarioTracer_::run() {
    switch (mState) {
    case UNDEFINED:
        execUndefined();
        break;
    case INITIAL:
        execInitial();
        break;
    case WALKING:
        execWalking();
        break;
    default:
        break;
    }
}

/**
 * シナリオトレース初期化処理
 */
void ScenarioTracer_::initAction() {
    mWalker->init();
}

/**
 * トレースコマンド設定
 * @param command 走行向き
 */
void ScenarioTracer_::setCommand(SceneCommands command) {
    int turn = -1;
    if (command == TURN_LEFT) {
      turn = Walker::LEFT;
    } else if (command == TURN_RIGHT) {
      turn = Walker::RIGHT;
    }

    mWalker->setCommand(Walker::LOW, turn);
}

/**
 * シーン変更処理
 */
void ScenarioTracer_::modeChangeAction() {
    mScenario->next();

    SceneCommands command = mScenario->currentSceneCommand();
    setCommand(command);

    mSimpleTimer->setTime(mScenario->currentSceneTime());
    mSimpleTimer->start();
}

/**
 * 未定義状態の処理
 */
void ScenarioTracer_::execUndefined() {
    mState = INITIAL;
}

/**
 * 初期状態の処理
 */
void ScenarioTracer_::execInitial() {
    initAction();   // entry アクション(INITIAL)

    mState = WALKING;   // 状態遷移

    modeChangeAction();    // entry アクション(WALKING)
}

/**
 * 走行中状態の処理
 */
void ScenarioTracer_::execWalking() {
    mWalker->run();             // do アクティビティ

    if (mSimpleTimer->isTimedOut()) {   // イベントチェック
        mSimpleTimer->stop();   // exit アクション

        modeChangeAction();    // entry アクション(WALKING)
    }
}
