#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"
#include <QPainter>  //画家头文件
#include <QDebug>
#include <QTimer>
#include <QSound>  //包含这个头文件需要在.pro中添加multimedia模块
mainscene::mainscene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainscene)
{
    ui->setupUi(this);

    //准备音效
    QSound * startSound = new QSound(":/res/TapButtonSound.wav",this);  //这段音效是在点击开始按钮之后才播放的

    //点击退出菜单项 实现退出
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
    //设置固定尺寸
    this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle("翻金币主场景");
    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //创建第二个选关场景
    this->chooseScene = new ChooseLevelScene;

    //创建开始按钮
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png","");  //
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);  //按钮的位置

    connect(startBtn,&MyPushButton::clicked,[=](){

        //播放音效
        startSound->play();

        startBtn->zoom1();  //向下跳跃的动画
        startBtn->zoom2();  //向上跳跃的动画

        //延时500ms，再执行lamda表达式中的内容
        QTimer::singleShot(500,this,[=](){
            this->chooseScene->setGeometry(this->geometry());  //将第二个场景移动到第一个场景当前所在的位置
            this->chooseScene->show();  //显示第二个场景
            this->hide();  //隐藏第一个场景
        });

    });

    //监听选关场景中的返回按钮信号
    connect(this->chooseScene,&ChooseLevelScene::ChooseSceneBack,[=](){
        this->setGeometry(this->chooseScene->geometry());  //返回的场景要和选关场景的位置一致
        QTimer::singleShot(500,this,[=](){  //延时0.5s后，切换场景
            this->show();
            this->chooseScene->hide();
        });
    });
}

//绘图事件
void mainscene::paintEvent(QPaintEvent *)
{
    //创建画家对象
    QPainter painter(this);

    //创建QPixmap对象
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");  //加载第一个场景的背景图

    //绘制背景
    painter.drawPixmap(0,0,this->width(),this->height(),pix);  //参数3和4表示将图片与屏幕进行适配

    //加载图片左上角的标题图片
    pix.load(":/res/Title.png");  //复用一下pix对象

    //缩放图片
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);

    //绘制标题
    painter.drawPixmap(10,30,pix);
}
mainscene::~mainscene()
{
    delete ui;
}

