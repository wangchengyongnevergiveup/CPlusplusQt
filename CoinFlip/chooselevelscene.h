#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"  //第三个场景
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //绘图事件
    void paintEvent(QPaintEvent *);

    //维护第三个场景的指针 (游戏场景）
    PlayScene * pScene;

signals:
    //点击返回按钮的自定义信号
    void ChooseSceneBack();
public slots:
};

#endif // CHOOSELEVELSCENE_H
