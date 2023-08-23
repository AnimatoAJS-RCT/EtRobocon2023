#include "LineTracer_.h"
using namespace std;

LineTracer_::LineTracer_(double _targetDistance, int _targetBrightness, int _pwm, bool _isLeftEdge)
  : targetDistance(_targetDistance),
    targetBrightness(_targetBrightness),
    pwm(_pwm),
    isLeftEdge(_isLeftEdge)
{
}

void LineTracer_::run()
{
  double initialDistance = 0;  // 実行前の走行距離
  double currentDistance = 0;  // 現在の走行距離

  // pwm値が0の場合は終了する
  if(pwm == 0) {
    return;
  }
  // 目標距離が0以下の場合は終了する
  if(targetDistance <= 0) {
    return;
  }

  // 初期値を格納
  initialDistance = Mileage::calculateMileage(controller.getRightCount(), controller.getLeftCount());
  currentDistance = initialDistance;

  // 走行距離が目標距離に到達するまで繰り返す
  while(abs(currentDistance - initialDistance) < targetDistance) {
    currentDistance = Mileage::calculateMileage(controller.getRightCount(), controller.getLeftCount());

    int rightPwm, leftPwm;
    if(controller.getBrightness() >= targetBrightness) { // カラーセンサが白を取得した場合
      rightPwm = isLeftEdge ? pwm - 10 : pwm;
      leftPwm = isLeftEdge ? pwm : pwm - 10;
    } else {
      rightPwm = isLeftEdge ? pwm : pwm - 10;
      leftPwm = isLeftEdge ? pwm - 10 : pwm;
    }

    controller.setRightPwm(rightPwm);
    controller.setLeftPwm(leftPwm);
    // 10ミリ秒待機
    controller.sleep();
  }
  // 両輪を停止する
  controller.stopMotor();
}