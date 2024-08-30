#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include "mycoin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSound>

PlayScene::PlayScene(int index)
{
    //音效准备
    //以下三种音效分别是  返回按钮音效  翻金币音效  胜利按钮音效
    QSound * backSound = new QSound(":/res/TapButtonSound.wav",this);  //这段音效是在点击开始按钮之后才播放的
    QSound * flipSound = new QSound(":/res/ConFlipSound.wav",this);  //这段音效是在点击开始按钮之后才播放的
    QSound * winSound = new QSound(":/res/TapButtonSound.wav",this);  //这段音效是在点击开始按钮之后才播放的


    this->levelIndex = index;  //外面传进来的参数用于赋值给成员变量
    qDebug()<<"您进入的是第"<<this->levelIndex<<"关";

    //设置固定尺寸
    this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle("游戏场景");
    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //创建菜单项
    QMenuBar * bar = menuBar();
    QMenu * startMenu = bar->addMenu("开始");
    QAction * quitAction = startMenu->addAction("退出");  //创建菜单项
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //----------返回按钮  按下鼠标时显示一张图片，松开鼠标时恢复原来的效果---------
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png",
                                              ":/res/BackButtonSelected.png");

    backBtn->setParent(this);  //将按钮放在当前界面
    backBtn->move(this->width() - backBtn->width(),this->height() - backBtn->height());  //将按钮的位置置于左下角
    connect(backBtn,&MyPushButton::clicked,[=](){
        //当监听到鼠标事件后，便会发送点击返回按钮的信号
        //qDebug()<<"返回到选择关卡的场景";

        //播放音效
        backSound->play();
        QTimer::singleShot(500,this,[=](){
            emit this->ChooseSceneBack();
        });
    });


    //---------显示当前的关卡号-----------
    QLabel * label = new QLabel;  //创建一个QLable标签用于显示当前关卡号
    label->setParent(this);
    QString str = QString("Level:%1").arg(this->levelIndex);  //arg的作用是拼接
    label->setText(str);
    QFont font("华文新魏",20);  //设置标签的字体属性
    label->setFont(font);
    //设置标签的大小和位置
    label->setGeometry(QRect(30,this->height()-50,this->width(),50));
    //设置属性  鼠标穿透
    label->setAttribute(Qt::WA_TransparentForMouseEvents);

    //胜利图片的准备
    QLabel * winLabel = new QLabel;
    winLabel->setParent(this);
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setPixmap(pix);
    winLabel->setGeometry(0,0,pix.width(),pix.height());
    winLabel->move(this->width()*0.5-pix.width()*0.5,-pix.height());

    //初始化关卡的二维数组数据
    dataConfig config;  //创建一个对象，可以调用其成员函数
    for(int i = 0;i < 4;i++){
        for(int j = 0;j < 4;j++){
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];  //因为mData是一个<key,value>型的容器，[关卡][行][列]
        }
    }
    //创建金币的背景图片
    for(int i = 0;i < 4;i++){
        for(int j = 0;j < 4;j++){
            //绘制背景图片
            QLabel * label = new QLabel;
            QPixmap pix;
            pix.load(":/res/BoardNode.png");
            //设置背景图片的大小
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            //设置背景图片的位置
            label->move(57+i*pix.width(),200+j*pix.height());

            //创建金币
            QString str;
            if(this->gameArray[i][j] == 1){
                str = ":/res/Coin0001.png";  //此时显示的是金币
            }else{
                str = ":/res/Coin0008.png"; //此时显示的是银币
            }
            MyCoin * coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*pix.width(),204+j*pix.height());
            coin->posX = i;  //记录下硬币的坐标
            coin->posY = j;
            coin->flag = gameArray[i][j]; //记录下硬币的金银情况

            this->coinBtn[i][j] = coin;  //翻转周围硬币数组初始化

            //点击硬币 调用 changeFlag
            connect(coin,&MyCoin::clicked,[=](){

                //播放点击硬币的音效
                flipSound->play();
                coin->changeFlag();
                gameArray[i][j] = gameArray[i][j] == 0? 1 : 0;  //这段代码用于同步二维数组，利于后期拓展，例如存档、读档

                //防止在延时翻转的0.3s内出现点击的bug----假设当前赢了，用于禁用所有金币点击
                for(int i =0;i < 4;i++){
                    for(int j = 0;j <4;j++){
                        this->coinBtn[i][j]->isWin = true;
                    }
                }


                //延时翻转周围硬币
                QTimer::singleShot(300,this,[=](){
                    //检测右侧硬币翻转（上下左不动）
                    if(coin->posX + 1 <=3)
                    {
                        this->coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        gameArray[coin->posX+1][coin->posY] = gameArray[coin->posX+1][coin->posY] == 0? 1 : 0;
                    }

                    //检测左侧硬币翻转（上下左不动）
                    if(coin->posX - 1 >= 0)
                    {
                        this->coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        gameArray[coin->posX-1][coin->posY] = gameArray[coin->posX-1][coin->posY] == 0? 1 : 0;
                    }

                    //检测右侧硬币翻转（上下左不动）
                    if(coin->posY + 1 <=3)
                    {
                        this->coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        gameArray[coin->posX][coin->posY+1] = gameArray[coin->posX][coin->posY+1] == 0? 1 : 0;
                    }

                    //检测右侧硬币翻转（上下左不动）
                    if(coin->posY - 1 >= 0)
                    {
                        this->coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        gameArray[coin->posX][coin->posY-1] = gameArray[coin->posX][coin->posY-1] == 0? 1 : 0;
                    }

                    //通过检测所有硬币是否都为金币来检测游戏是否胜利
                    this->isWin = true;
                    for(int i =0;i < 4;i++){
                        for(int j = 0;j <4;j++){
                            if(this->coinBtn[i][j]->flag == false){  //只要有一个标志位为0，就说明还有银币，游戏未胜利
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin)  //如果检测后，isWin为真，说明真的胜利了
                    {
                        //播放游戏胜利音效
                        winSound->play();
                        for(int i =0;i < 4;i++){
                            for(int j = 0;j <4;j++){
                                this->coinBtn[i][j]->isWin = true;
                            }
                        }

                        //将胜利的图片显示出来
                        QPropertyAnimation * animation = new QPropertyAnimation(winLabel,"geometry");  //创建动画对象
                        animation->setDuration(1000);  //设置时间间隔
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->width()));  //动画的起始位置保持不变
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->width()));  //动画的最终位置;
                        animation->setEasingCurve(QEasingCurve::OutBounce);  //动画的弹起效果
                        animation->start(QAbstractAnimation::DeleteWhenStopped);
                    }
                    else   //将之前为了防止bug而设置
                    {
                        for(int i =0;i < 4;i++){
                            for(int j = 0;j <4;j++){
                                this->coinBtn[i][j]->isWin = false;
                            }
                        }
                    }
                });

            });

        }
    }
}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //绘制背景
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //绘制标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}
