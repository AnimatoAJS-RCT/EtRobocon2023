#ifndef LINE_TRACER_H
#define LINE_TRACER_H

#include "Runner.h"
#include "Mileage.h"

class LineTracer : public Runner {
 public:
  /**
   * コンストラクタ
   * @param _targetDistance 目標距離 0~
   * @param _targetBrightness 目標輝度 0~100
   * @param _pwm PWM値 -100~100
   * @param _isLeftEdge エッジの左右判定(true:左エッジ, false:右エッジ)
   */
  LineTracer(double _targetDistance, int _targetBrightness, int _pwm, bool _isLeftEdge);

  /**
   * @brief ライントレースする
   */
  void run();

 private:
  double targetDistance;  // 目標距離 0~
  int targetBrightness;   // 目標輝度 0~
  int pwm;                // PWM値 -100~100
  bool& isLeftEdge;       // エッジの左右判定(true:左エッジ, false:右エッジ)
};

#endif