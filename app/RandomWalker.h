/******************************************************************************
 *  RandomWalker.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/02/07
 *  Implementation of the Class RandomWalker
 *  Author: Kenya Yabe
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef EV3_APP_RANDOMWALKER_H_
#define EV3_APP_RANDOMWALKER_H_

#include <vector>
#include "Starter.h"
#include "SimpleTimer.h"
#include "LineTracer.h"
#include "ScenarioTracer.h"
#include "LineMonitor.h"

/**
 * Lコース/Rコース向けの設定を定義
 * デフォルトはLコース
 */
#if defined(MAKE_RIGHT)
static constexpr bool IS_LEFT_COURSE = false; // Rコース
#else
static constexpr bool IS_LEFT_COURSE = true; // Lコース
#endif

class RandomWalker
{
public:
    RandomWalker(const Starter *starter,
                 SimpleTimer *simpleTimer);

    void run();

private:
    enum State
    {
        UNDEFINED,
        WAITING_FOR_START,
        COURSE_RUNNING,
        DIFFICULT_RUNNING,
        FINISHED
    };

    static const int MIN_TIME;
    static const int MAX_TIME;
    static constexpr int BRIGHTNESS_TH = 32;  // 輝度の閾値(白：61、黒：3)
    static constexpr bool LEFT_EDGE = true;   // 左エッジ
    static constexpr bool RIGHT_EDGE = false; // 右エッジ

    const Starter *mStarter;
    SimpleTimer *mSimpleTimer;
    State mState;
    std::vector<Tracer *> courseList; // ノーマルコースの走行インスタンスのリスト

    int getRandomTime();
    void modeChangeAction();
    void generateCourseList();
    void execUndefined();
    void execWaitingForStart();
    void execCourseRunning();
    void execDifficultRunning();
    void execFinished();
};

#endif // EV3_APP_RANDOMWALKER_H_
