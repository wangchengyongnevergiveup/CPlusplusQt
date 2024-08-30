#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:

    //封装的按钮，有两种功能 参数1  正常显示图片路径  参数2  按下后切换图片路径
    MyPushButton(QString normalImg,QString pressImg=" ");  //只有当第二个参数不为空，才需要切图  //按下鼠标时显示一张图片，松开鼠标时恢复原来的效果

    QString normalPath;
    QString pressPath;

    //向下跳跃
    void zoom1();
    //向上跳跃
    void zoom2();

    //鼠标按下事件（用于返回按钮）  //按下鼠标时显示一张图片，松开鼠标时恢复原来的效果
    void mousePressEvent(QMouseEvent *e);
    //鼠标释放事件（用于返回按钮）
    void mouseReleaseEvent(QMouseEvent *e);

signals:

public slots:
};

#endif // MYPUSHBUTTON_H
