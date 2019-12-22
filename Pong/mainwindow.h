#include "ball.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QRegularExpressionValidator>
#include <QList>
#include <QGraphicsRectItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QMenu* menu = new QMenu("File");
    QMenu* levelMenu = new QMenu("Level");
    QAction* quitAction = new QAction("Quit");
    QAction* easyAction = new QAction("Easy");
    QAction* medAction = new QAction("Medium");
    QAction* hardAction = new QAction("Hard");


protected:
    bool event(QEvent * e);

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene = new QGraphicsScene(-(XMAX/2), -(YMAX/2), XMAX, YMAX);
    QTimer* gameClock;
    qreal ballSpeed = 0;
    difficulty level;
    QGraphicsRectItem* player = new QGraphicsRectItem(0, 0, 100, 5);
    QGraphicsRectItem* cpu = new QGraphicsRectItem(0, 0, 100, 5);
    QGraphicsRectItem* leftWall = new QGraphicsRectItem(0, 0, YMAX, 5);
    QGraphicsRectItem* rightWall = new QGraphicsRectItem(0, 0, YMAX, 5);

    Ball* ball = new Ball();

public slots:
    void setCPUplayer();
    void RestartGame();
    void SeeScores();
    void SetLevelE();
    void SetLevelM();
    void SetLevelH();
};

#endif // MAINWINDOW_H
