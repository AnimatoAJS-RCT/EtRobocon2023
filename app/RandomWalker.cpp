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
    generateCourseList(); // courseListを生成する。
    
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
    case COURSE_RUNNING:
        execCourseRunning();
        break;
    case DIFFICULT_RUNNING:
        execDifficultRunning();
        break;
    case FINISHED:
        execFinished();
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

void RandomWalker::generateCourseList()
{
  constexpr int BRIGHTNESS_TH = 20;   // 輝度の閾値
  constexpr bool LEFT_EDGE = true;    // 左エッジ
  constexpr bool RIGHT_EDGE = false;  // 右エッジ
  // ノーマルコースに必要なTracerインスタンスをcourseListに追加する
  // courseList.push_back(new ScenarioTracer(200,40,40));
  // courseList.push_back(new ScenarioTracer(150,80,78));
  // courseList.push_back(new ScenarioTracer(2500,100,100));
  // courseList.push_back(new ScenarioTracer(500,100,50));
  // courseList.push_back(new LineTracer(500,20,90,true));

//   courseList.push_back(new LineTracer2(2000, BRIGHTNESS_TH, 70, LEFT_EDGE, PidGain(0.20, 0.04, 0.04)));
//   courseList.push_back(new LineTracer2(2000, BRIGHTNESS_TH, 70, LEFT_EDGE, PidGain(0.20, 0.04, 0.04)));

    Controller controller;
    while(true) {
      printf("Brightness:%d\n", controller.getBrightness());
      controller.sleep(1000);
    }
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
        mState = COURSE_RUNNING;

        modeChangeAction();
    }
}

/**
 * ノーマルコースの走行状態の処理
 */
void RandomWalker::execCourseRunning() {
    int i = 1;
    for(const auto& tracer : courseList) {
        tracer->run();
        printf("No.%d インスタンス終了\n", i++);
    }

    mState = DIFFICULT_RUNNING;
}

/**
 * 難所エリア走行状態の処理
 */
void RandomWalker::execDifficultRunning() {
    /* TODO: 
     * 難所エリア攻略に必要な走行インスタンスのリストを作ってそれのrun()を実行する。
     * やり方はノーマルコースと同様。
     */

    mState = FINISHED;
}

void RandomWalker::execFinished() {
    // シミュレータに終了を通知する
    Controller controller;
    controller.notifyCompleted();
}