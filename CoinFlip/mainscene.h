#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include "chooselevelscene.h"
QT_BEGIN_NAMESPACE
namespace Ui { class mainscene; }
QT_END_NAMESPACE

class mainscene : public QMainWindow
{
    Q_OBJECT

public:
    mainscene(QWidget *parent = nullptr);
    ~mainscene();

    //绘图事件
    void paintEvent(QPaintEvent *);

    //维护第二个场景的指针
    ChooseLevelScene * chooseScene;

private:
    Ui::mainscene *ui;
};
#endif // MAINSCENE_H
