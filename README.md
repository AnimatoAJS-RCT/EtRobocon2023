# EtRobocon2023
AJSによるETロボコン2023エントリークラスのプログラムです．

## セットアップ
セットアップを行う際の前提条件は以下の通りです．
- Ubuntu(WSL)が入っている
- UbuntuにGitコマンドが利用可能
- ETロボコンシミュレータ環境をセットアップ済み
  
以下の手順でセットアップを行います．
1. Ubuntu(WSL)で`etrobo/workspace/`に移動する
2. `git clone https://github.com/AnimatoAJS-RCT/EtRobocon2023.git`を実行する
3. `cd $ETROBO_ROOT`でETロボコン環境のルートディレクトリに移動する
4. `make app=EtRobocon2023 sim up`でコンパイルが成功してシミュレータが立ち上がることを確認する
