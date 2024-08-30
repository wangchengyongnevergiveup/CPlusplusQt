#include "mypushbutton.h"
#include <QDebug>
#include<QPropertyAnimation>  //动画对象的头文件

//参数1  正常显示图片路径  参数2  按下后切换图片路径
MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    this->normalPath = normalImg;
    this->pressPath = pressImg;

    //创建QPixmap对象
    QPixmap pix;
    bool ret = pix.load(this->normalPath);  //ret用于报错加载成功与否的结果
    if(!ret)
    {
        QString str = QString("图片加载失败，失败的路径是： %1").arg(this->normalPath);
        qDebug()<<str;
    }
    //如果成功
    //设置按钮固定尺寸
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则样式
    this->setStyleSheet("QPushButton{border:0px;}");  //有点类似于网页设计中的CSS语法
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}

//让按钮向下跳跃
void MyPushButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");  //参数1：让谁去做这个动画，参数2：动画的方式

    //设置动画间隔
    animation->setDuration(200);

    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置结束位置（接口和起始位置不一样）
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));  //因为是向下跳跃，所以只有y坐标会增加

    //设置动画曲线（加速、减速、变速）
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);  //DeleteWhenStopped表示动画执行完毕后就释放对象，KeepWhenStopped则表示保存对象


}

void MyPushButton::zoom2()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");  //参数1：让谁去做这个动画，参数2：动画的方式

    //设置动画间隔
    animation->setDuration(200);

    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height())); //这里和向下跳跃不同的是，他的起始位置是变化之后的位置

    //设置结束位置（接口和起始位置不一样）
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置动画曲线（加速、减速、变速）
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start(QAbstractAnimation::DeleteWhenStopped);  //DeleteWhenStopped表示动画执行完毕后就释放对象，KeepWhenStopped则表示保存对象
}

void MyPushButton::mousePressEvent(QMouseEvent *e)  //按下鼠标时显示一张图片，松开鼠标时恢复原来的效果
{
    //pressPath不为空，说明参数2传入了，那么需要切换界面
    if(this->pressPath != "")
    {
        //创建QPixmap对象
        QPixmap pix;
        bool ret = pix.load(this->pressPath);  //ret用于报错加载成功与否的结果
        if(!ret)
        {
            QString str = QString("图片加载失败，失败的路径是： %1").arg(this->pressPath);
            qDebug()<<str;
        }
        //如果成功
        //设置按钮固定尺寸
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则样式
        this->setStyleSheet("QPushButton{border:0px;}");  //有点类似于网页设计中的CSS语法
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //其他的事情交给父类处理
    QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    //如果按下的路径不为空，说明需要还原正常显示的图片
    if(this->pressPath != "")
    {
        //创建QPixmap对象
        QPixmap pix;
        bool ret = pix.load(this->normalPath);  //ret用于报错加载成功与否的结果
        if(!ret)
        {
            QString str = QString("图片加载失败，失败的路径是： %1").arg(this->normalPath);
            qDebug()<<str;
        }
        //如果成功
        //设置按钮固定尺寸
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则样式
        this->setStyleSheet("QPushButton{border:0px;}");  //有点类似于网页设计中的CSS语法
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //其他的事情交给press处理
    QPushButton::mouseReleaseEvent(e);
}
