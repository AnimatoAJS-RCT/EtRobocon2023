/******************************************************************************
 *  LineTracer_.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/26
 *  Implementation of the Class LineTracer_
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "LineTracer_.h"

/**
 * コンストラクタ
 * @param lineMonitor     ライン判定
 * @param walker 走行
 */
LineTracer_::LineTracer_(const LineMonitor* lineMonitor,
                       Walker* walker)
    : mLineMonitor(lineMonitor),
      mWalker(walker),
      mIsInitialized(false) {
}

/**
 * ライントレースする
 */
void LineTracer_::run() {
    if (mIsInitialized == false) {
        mWalker->init();
        mIsInitialized = true;
    }

    bool isOnLine = mLineMonitor->isOnLine();

    // 走行体の向きを計算する
    int direction = calcDirection(isOnLine);

    mWalker->setCommand(Walker::LOW, direction);

    // 走行を行う
    mWalker->run();
}

/**
 * 走行体の向きを計算する
 * @param isOnLine true:ライン上/false:ライン外
 * @retval RIGHT  ライン上にある場合(右旋回指示)
 * @retval LEFT ライン外にある場合(左旋回指示)
 */
int LineTracer_::calcDirection(bool isOnLine) {
    if (isOnLine) {
        // ライン上にある場合
        return Walker::RIGHT;
    } else {
        // ライン外にある場合
        return Walker::LEFT;
    }
}
