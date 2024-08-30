#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>  //画家头文件
#include "mypushbutton.h"  //用于创建返回按钮
#include <QDebug>
#include <QLabel>
#include <QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //选择关卡按钮音效
    QSound * chooseSound = new QSound(":/res/TapButtonSound.wav",this);  //这段音效是在点击开始按钮之后才播放的
    //返回按钮音效
    QSound * backSound = new QSound(":/res/TapButtonSound.wav",this);  //这段音效是在点击开始按钮之后才播放的

    //设置固定尺寸
    this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle("选择关卡场景");
    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //创建菜单栏（借助代码的方式，而非ui界面）
    QMenuBar * bar = menuBar();
    this->setMenuBar(bar);
    //创建菜单
    QMenu* startMenu = bar->addMenu("开始");
    //创建菜单项
    QAction * quitAction = startMenu->addAction("退出");
    //监听退出
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //----------返回按钮  按下鼠标时显示一张图片，松开鼠标时恢复原来的效果---------
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png",
                                              ":/res/BackButtonSelected.png");

    backBtn->setParent(this);  //将按钮放在当前界面
    backBtn->move(this->width() - backBtn->width(),this->height() - backBtn->height());  //将按钮的位置置于左下角
    connect(backBtn,&MyPushButton::clicked,[=](){

        //播放返回按钮音效
        backSound->play();
        //当监听到鼠标事件后，便会发送点击返回按钮的信号
        emit this->ChooseSceneBack();  //这个信号会被主场景监听到
    });

    pScene = NULL; //游戏场景的指针一开始为空，当选择关卡之后才会出现。

    //--------创建20个具体关卡的按钮------------
    for(int i = 0 ;i <20;i++)
    {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png","");  //创建选关按钮，并设置图标
        menuBtn->setParent(this);  //让选关按钮出现在当前场景
        menuBtn->move(25+(i%4)*70,130+(i/4)*70);  //通过取模、除法运算，使得一个for循环实现4行5列的矩阵

        connect(menuBtn,&MyPushButton::clicked,[=](){  //监听每一个按钮的信号

            //播放音效
            chooseSound->play();
            //qDebug()<<"您选择的是第"<<i+1<<"关";
            this->pScene = new PlayScene(i+1);  //确认选择的关卡
            this->pScene->setGeometry(this->geometry());     //选关场景和游戏场景的位置保持一致
            this->pScene->show();               //显示游戏场景
            this->hide();                       //隐藏当前场景

            //监听第三个场景的返回按钮信号   注意这个监听信号的位置非常重要，放在for循环外面的话是空指针
            connect(this->pScene,&PlayScene::ChooseSceneBack,[=](){
                this->setGeometry(pScene->geometry());  //选关场景和游戏场景的位置保持一致
                this->show();          //返回选关场景
                this->pScene->hide();  //关闭游戏场景

                delete this->pScene;
                this->pScene = NULL;  //因为每一关的游戏场景都是不一样的，不需要复用，因此需要删除掉，场景2没有delete，是因为它可以和场景1的来回切换
            });
        });

       //显示按钮上面的数字
       QLabel * label = new QLabel;
       label->setParent(this);
       label->move(25+(i%4)*70,130+(i/4)*70);  //让QLabel移动到和按钮一样的位置
       //设置尺寸
       label->setFixedSize(menuBtn->width(),menuBtn->height());  //让QLabel的大小和按钮一样大
       //设置文本
       label->setText(QString::number(i+1));
       //设置对齐方式
       label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);  //QT中的或相当于让两个条件都成立（水平和垂直居中）
       //设置属性   鼠标穿透属性
       label->setAttribute(Qt::WA_TransparentForMouseEvents);  //不设置这一代码点击按钮时会没有反应，因为Qlabel标签位于按钮的上一层

    }


}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    //创建画家对象
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");

    //绘制背景
    painter.drawPixmap(0,0,this->width(),this->height(),pix); //起始坐标、填充大小，对象

    //加载图片左上角的标题图片
    pix.load(":/res/Title.png");  //复用一下pix对象

    //绘制标题
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix);
}
