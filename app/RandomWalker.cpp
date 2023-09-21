/******************************************************************************
 *  RandomWalker.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/02/07
 *  Implementation of the Class RandomWalker
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include <stdlib.h>
#include "Clock.h"

// T.Takahashi added start
#include "ev3api.h"
// T.Takahashi added end

#include "RandomWalker.h"

// 定数宣言
const int RandomWalker::MIN_TIME = 5000 * 1000;   // 切り替え時間の最小値
const int RandomWalker::MAX_TIME = 15000 * 1000;  // 切り替え時間の最大値

/**
 * コンストラクタ
 * @param starter         スタータ
 * @param simpleTimer     タイマ
 */
<<<<<<< HEAD

// T.Takahashi added start
/* センサーの設定 */
static const sensor_port_t
    ultrasonic_sensor = EV3_PORT_2;
// T.Takahashi added end

RandomWalker::RandomWalker(const Starter* starter,
                           SimpleTimer* simpleTimer)
    : mStarter(starter),
      mSimpleTimer(simpleTimer),
      mState(UNDEFINED) {
    ev3api::Clock* clock = new ev3api::Clock();

    srand(clock->now());  // 乱数をリセットする
    generateCourseList(); // courseListを生成する。

    delete clock;
=======
RandomWalker::RandomWalker(const Starter* starter, SimpleTimer* simpleTimer)
  : mStarter(starter), mSimpleTimer(simpleTimer), mState(UNDEFINED)
{
  ev3api::Clock* clock = new ev3api::Clock();

  srand(clock->now());   // 乱数をリセットする
  generateCourseList();  // courseListを生成する。

  delete clock;
>>>>>>> 77cd6f9e2395aafe61fa93eff4ff9a0c71bfe722
}

/**
 * ランダム走行する
 */
void RandomWalker::run()
{
  switch(mState) {
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
int RandomWalker::getRandomTime()
{
  return MIN_TIME
         + static_cast<int>(static_cast<double>(rand()) * (MAX_TIME - MIN_TIME + 1.0)
                            / (1.0 + RAND_MAX));
}

/**
 * シーン変更処理
 */
void RandomWalker::modeChangeAction()
{
  mSimpleTimer->setTime(getRandomTime());
  mSimpleTimer->start();
}

void RandomWalker::generateCourseList()
{
  // ノーマルコースに必要なTracerインスタンスをcourseListに追加する
  if(IS_LEFT_COURSE) {  // Lコースの場合
    courseList.push_back(
        new ScenarioTracer(100, 40, 40));  // 初速が早いとブレるため少しだけ低速で走る
    courseList.push_back(
        new LineTracer(1300, BRIGHTNESS_TH, 90, LEFT_EDGE, PidGain(0.30, 0.12, 0.12)));
    courseList.push_back(new ScenarioTracer(1350, 100, 100));
    courseList.push_back(new ScenarioTracer(550, 100, 60));  // 第一カーブ
    courseList.push_back(
        new LineTracer(800, BRIGHTNESS_TH, 80, RIGHT_EDGE, PidGain(0.25, 0.04, 0.04)));
    courseList.push_back(new ScenarioTracer(690, 100, 100));
    courseList.push_back(new ScenarioTracer(590, 100, 60));  // 第二カーブ
    courseList.push_back(new ScenarioTracer(
        300, 100, 100));  // 青線でライントレースが狂うため少しシナリオトレースする
    courseList.push_back(
        new LineTracer(800, BRIGHTNESS_TH, 80, LEFT_EDGE, PidGain(0.24, 0.04, 0.04)));
    courseList.push_back(
        new LineTracer(300, BRIGHTNESS_TH, 60, LEFT_EDGE, PidGain(0.21, 0.04, 0.04)));
  } else {  // Rコースの場合
    courseList.push_back(
        new ScenarioTracer(100, 40, 40));  // 初速が早いとブレるため少しだけ低速で走る
    courseList.push_back(
        new LineTracer(1300, BRIGHTNESS_TH, 90, RIGHT_EDGE, PidGain(0.30, 0.12, 0.12)));
    courseList.push_back(new ScenarioTracer(1350, 100, 100));
    courseList.push_back(new ScenarioTracer(550, 60, 100));  // 第一カーブ
    courseList.push_back(
        new LineTracer(800, BRIGHTNESS_TH, 80, LEFT_EDGE, PidGain(0.25, 0.04, 0.04)));
    courseList.push_back(new ScenarioTracer(680, 100, 100));
    courseList.push_back(new ScenarioTracer(590, 60, 100));  // 第二カーブ
    courseList.push_back(new ScenarioTracer(
        300, 100, 100));  // 青線でライントレースが狂うため少しシナリオトレースする
    courseList.push_back(
        new LineTracer(800, BRIGHTNESS_TH, 80, RIGHT_EDGE, PidGain(0.24, 0.04, 0.04)));
    courseList.push_back(
        new LineTracer(300, BRIGHTNESS_TH, 60, RIGHT_EDGE, PidGain(0.21, 0.04, 0.04)));
  }
}

/**
 * 未定義状態の処理
 */
void RandomWalker::execUndefined()
{
  mState = WAITING_FOR_START;
}

/**
 * 開始待ち状態の処理
 */
void RandomWalker::execWaitingForStart()
{
  if(mStarter->isPushed()) {
    mState = COURSE_RUNNING;

    modeChangeAction();
  }
}

/**
 * ノーマルコースの走行状態の処理
 */
void RandomWalker::execCourseRunning()
{
  int i = 1;
  for(const auto& tracer : courseList) {
    // courseListのインスタンスを順に実行していく
    tracer->run();
    // デバッグ用
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
/* シナリオフラグ */
    static int sflag = 0;

    if(sflag == 0){
        printf("execDifficultRunning センサー接続\n");
/* ループに入る前にセンサーとセンサーポートを接続する */
        ev3_sensor_config (ultrasonic_sensor, ULTRASONIC_SENSOR);
        sflag = 1;
    }

/* 反射光値格納用の変数 */
    static int distance = 255;
// 進行方向（1:前進　-1:後進）
    int p_moveon = 1;
// 速度 LOW 右９０度旋回カウント
// int p_count = 170; 
    int p_count = 175; 
// 壁への最接近距離
    static int wall_distance = 16;
// バック終了する壁までの距離
    static int back_distance = 16;

//    while(distance > wall_distance){
/* 距離を測定して表示し続ける */
/* 反射値を測って変数に格納 */
        distance = ev3_ultrasonic_sensor_get_distance(ultrasonic_sensor);
/* 文字配列に読み取った値を格納する */
        printf("DISTANCE:%d  sflag:%d \n",distance,sflag);

// 前進
        ScenarioTracer(13500, 100, 100);
//    }

//    mState = FINISHED;
}

void RandomWalker::execFinished()
{
  // シミュレータに終了を通知する
  Controller controller;
  controller.notifyCompleted();
}