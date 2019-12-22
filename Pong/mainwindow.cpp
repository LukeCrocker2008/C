#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsSimpleTextItem>
#include <QtDebug>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Pong");
    ui->graphicsView->setBackgroundBrush(Qt::black);
    ui->graphicsView->setScene(scene);

    menu->addAction(quitAction);
    levelMenu->addAction(easyAction);
    levelMenu->addAction(medAction);
    levelMenu->addAction(hardAction);

    ui->menuBar->addMenu(menu);
    connect(quitAction, &QAction::triggered, this, &MainWindow::close);
    connect(easyAction, &QAction::triggered, this, &MainWindow::SetLevelE);
    connect(medAction, &QAction::triggered, this, &MainWindow::SetLevelM);
    connect(hardAction, &QAction::triggered, this, &MainWindow::SetLevelH);
    ui->menuBar->addMenu(levelMenu);
    levelMenu->setDefaultAction(easyAction);
    hardAction->triggered();

    connect(ui->restartButton, &QPushButton::clicked, this, &MainWindow::RestartGame);
    connect(ui->quitButton, &QPushButton::clicked, this, &MainWindow::close);

    player->setBrush(Qt::blue);
    cpu->setBrush(Qt::green);
    leftWall->setBrush(Qt::white);
    rightWall->setBrush(Qt::white);

    ball->setPos(0, 0);
    player->setPos(-50, 250);
    cpu->setPos(-50, -250);
    leftWall->setRotation(90);
    rightWall->setRotation(90);
    leftWall->setPos(-XMAX/2, -YMAX/2);
    rightWall->setPos(XMAX/2, -YMAX/2);

    scene->addItem(ball);
    scene->addItem(player);
    scene->addItem(cpu);
    scene->addItem(leftWall);
    scene->addItem(rightWall);

    gameClock = new QTimer;
    gameClock->setInterval(1000/33);

    connect(gameClock, &QTimer::timeout, scene, &QGraphicsScene::advance);
    connect(gameClock, &QTimer::timeout, this, &MainWindow::setCPUplayer);
//    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    gameClock->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::event(QEvent * e)
{
    if (!e)
    {
        return QMainWindow::event(e);
    }
    qreal x = player->pos().x();
    qreal y = player->pos().y();
    if(e->type() == QEvent::KeyPress)
    {
        QKeyEvent* ke = static_cast<QKeyEvent*>(e);

        if(ke->key() == Qt::Key_A)
        {
            player->setPos(x-15, y);
        } else if(ke->key() == Qt::Key_D)
        {
            player->setPos(x+15, y);
        }
    }
    return QMainWindow::event(e);
}

void MainWindow::setCPUplayer()
{
    if(level == easy)
    {
        static int velocity = 10;
        qreal x = cpu->pos().x();
        qreal y = cpu->pos().y();
        if(x >= qreal(XMAX/3) || x <= qreal(-XMAX/2))
        {
            velocity = -velocity;
        }
        cpu->setPos(x+velocity, y);
    } else if (level == medium) {
        static int velocity = 10;
        static int xupboun = XMAX/3;
        static int xloboun = -XMAX/2;
        qreal x = cpu->pos().x();
        qreal y = cpu->pos().y();
        if(ball->pos().x() < 0 && x < 0)
        {
            xupboun = 0;
            xloboun = -XMAX/2;
        } else if((ball->pos().x() < 0 && x >= 0) || (ball->pos().x() >= 0 && x < 0)) {
            xupboun = XMAX/3;
            xloboun = -XMAX/2;
        }
        else {
            xupboun = XMAX/3;
            xloboun = 0;
        }
        if(x >= qreal(xupboun) || x <= qreal(xloboun))
        {
            velocity = -velocity;
        }
        cpu->setPos(x+velocity, y);
    } else {
        static int resistance = 2;
        qreal x = cpu->pos().x();
        qreal y = cpu->pos().y();
        cpu->setPos(ball->pos().x()-resistance, y);
    }
}

void MainWindow::RestartGame()
{
    MainWindow* newGame = new MainWindow;
    newGame->show();
    this->close();
}

void MainWindow::SeeScores()
{

}

void MainWindow::SetLevelE()
{
        level = easy;
        ball->setSpeed(3);
        levelMenu->setDefaultAction(easyAction);
}

void MainWindow::SetLevelM()
{
        level = medium;
        ball->setSpeed(5);
        levelMenu->setDefaultAction(medAction);
}
void MainWindow::SetLevelH()
{
        level = hard;
        ball->setSpeed(7);
        levelMenu->setDefaultAction(hardAction);
}

