/******************************************************************************
 *  RandomWalker.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/02/07
 *  Implementation of the Class RandomWalker
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include <stdlib.h>
#include "Clock.h"

#include "RandomWalker.h"

// 定数宣言
const int RandomWalker::MIN_TIME = 5000 * 1000;    // 切り替え時間の最小値
const int RandomWalker::MAX_TIME = 15000 * 1000;   // 切り替え時間の最大値

/**
 * コンストラクタ
 * @param scenarioTracer  シナリオトレーサ
 * @param starter         スタータ  
 * @param simpleTimer     タイマ
 */
RandomWalker::RandomWalker(const Starter* starter,
                           SimpleTimer* simpleTimer)
    : mStarter(starter),
      mSimpleTimer(simpleTimer),
      mState(UNDEFINED) {
    ev3api::Clock* clock = new ev3api::Clock();

    srand(clock->now());  // 乱数をリセットする

    delete clock;
}

/**
 * ランダム走行する
 */
void RandomWalker::run() {
    switch (mState) {
    case UNDEFINED:
        execUndefined();
        break;
    case WAITING_FOR_START:
        execWaitingForStart();
        break;
    case LINE_TRACING:
        execCourseRunning();
        break;
    case SCENARIO_TRACING:
        execDifficultRunning();
        break;
    default:
        break;
    }
}

/**
 * 乱数を取得する
 * @retrun 乱数
 */
int RandomWalker::getRandomTime() {
    return MIN_TIME +
        static_cast<int>(static_cast<double>(rand()) *
                         (MAX_TIME - MIN_TIME + 1.0) / (1.0 + RAND_MAX));
}

/**
 * シーン変更処理
 */
void RandomWalker::modeChangeAction() {
    mSimpleTimer->setTime(getRandomTime());
    mSimpleTimer->start();
}

/**
 * 未定義状態の処理
 */
void RandomWalker::execUndefined() {
    mState = WAITING_FOR_START;
}

/**
 * 開始待ち状態の処理
 */
void RandomWalker::execWaitingForStart() {
    if (mStarter->isPushed()) {
        mState = LINE_TRACING;

        modeChangeAction();
    }
}

/**
 * ノーマルコースの走行状態の処理
 */
void RandomWalker::execCourseRunning() {
    LineTracer lineTracer(500,20,90,true);
    ScenarioTracer scenarioTracer(500,50,90);
    lineTracer.run();
    printf("lineTracer.run()：完了\n");
    scenarioTracer.run();
    printf("scenarioTracer.run()：完了\n");
}

/**
 * 難所エリア走行状態の処理
 */
void RandomWalker::execDifficultRunning() {
    // mScenarioTracer->run();

    // if (mSimpleTimer->isTimedOut()) {
    //     mSimpleTimer->stop();

    //     mState = LINE_TRACING;

    //     modeChangeAction();
    // }
}
