#ifndef RUNNER_H
#define RUNNER_H

#include "Controller.h"

class Runner {
 public:
  /**
   * コンストラクタ
   */
  Runner();

  /**
   * @brief 走行する抽象メソッド
   */
  virtual void run() = 0;

 protected:
  Controller controller;
};

#endif