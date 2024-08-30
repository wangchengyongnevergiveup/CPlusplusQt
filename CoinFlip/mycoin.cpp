#include "mycoin.h"
#include <QDebug>
#include <QTimer>
MyCoin::MyCoin(QString img)
{
    QPixmap pix;
    bool ret = pix.load(img);
    if(!ret)
    {
        QString str = QString("金币图片加载失败，失败的路径为：%1").arg(img);
        qDebug()<<str;
        return;
    }

    this->setFixedSize(pix.width(),pix.height());
    //设置不规则样式
    this->setStyleSheet("QPushButton{border:0px;}");  //设置边框0像素
    //设置图标
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //创建定时器
    this->timer1 = new QTimer(this);
    this->timer2 = new QTimer(this);

    //监听金币翻银币的定时器
    connect(this->timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);  //从金币到银币也就是从1到8
        bool ret = pix.load(str);
        if(!ret)
        {
            QString str = QString("金币图片加载失败，失败的路径为：%1").arg(str);
            qDebug()<<str;
            return;
        }

        this->setFixedSize(pix.width(),pix.height());
        //设置不规则样式
        this->setStyleSheet("QPushButton{border:0px;}");  //设置边框0像素
        //设置图标
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->min>this->max){  //不等是等于，因为8这张图也要显示
            this->min = 1;         //重新将min置为1
            this->timer1->stop();  //关闭定时器
            isAnimation = false;
        }
    });

    //监听银币翻金币的定时器
    connect(this->timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        bool ret = pix.load(str);
        if(!ret)
        {
            QString str = QString("金币图片加载失败，失败的路径为：%1").arg(str);
            qDebug()<<str;
            return;
        }

        this->setFixedSize(pix.width(),pix.height());
        //设置不规则样式
        this->setStyleSheet("QPushButton{border:0px;}");  //设置边框0像素
        //设置图标
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->max < this->min){  //不等是等于，因为8这张图也要显示
            this->max = 8;         //重新将MAX置为8
            this->timer2->stop();  //关闭定时器2
            isAnimation = false;
        }
    });


}

//点击硬币实现翻转,改变硬币标识
void MyCoin::changeFlag()
{
    if(this->flag){
        this->timer1->start(30);
        this->flag = false;
    }else{
        this->timer2->start(30);
        this->flag = true;
    }

    isAnimation = true;  //做翻转动画的标志

}

void MyCoin::mousePressEvent(QMouseEvent *e) //用于限制快速点击硬币而导致的翻转bug
{
    if(this->isAnimation|| this->isWin)  //如果还在做动画或者游戏胜利，则鼠标无法再次点击硬币
    {
        return;
    }
    else  //否则说明，当前可以按下按钮，将鼠标事件传回给父类鼠标
    {
        QPushButton::mousePressEvent(e);
    }
}
