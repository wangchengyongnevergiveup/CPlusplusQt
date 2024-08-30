#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    MyCoin(QString img);  //重写了一个构造函数，参数为传入的路径

    int posX;  //x坐标
    int posY;  //y坐标
    bool flag;  //正反标志

    void changeFlag();   //改变标志，执行翻转效果（只要点了，就会执行）
    QTimer *timer1;      //正面翻反面   定时器（其实这两个用一个就行了，写两个是便于理解）
    QTimer *timer2;      //反面翻正面   定时器
    int min = 1;         //最小图片下标
    int max = 8;         //最大图片下标

    bool isAnimation = false;  //做翻转动画的标志
    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent *e);

    //游戏胜利的标志
    bool isWin = false;

signals:

public slots:
};

#endif // MYCOIN_H
