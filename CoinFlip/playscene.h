#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:

    PlayScene(int index);  //有参构造，参数代表当前关卡号

    int levelIndex;  //成员属性，记录当前关卡号

    //绘图事件
    void paintEvent(QPaintEvent *);

    //二维数组数据  作用初始化关卡
    int gameArray[4][4];

    //所有硬币的二维数组  方便找硬币周围的硬币
    MyCoin * coinBtn[4][4];  //金币按钮数组

    bool isWin = true;  //是否全为金币
signals:
    //点击返回按钮的自定义信号
    void ChooseSceneBack();
public slots:
};

#endif // PLAYSCENE_H
