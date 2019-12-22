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
    this->setWindowTitle("Simon Says");
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
    easyAction->triggered();

    connect(ui->restartButton, &QPushButton::clicked, this, &MainWindow::RestartGame);

    scorePic = new QPixmap(50, 50);
    scorePic->fill(Qt::blue);
    ui->imageLabel->setPixmap(*scorePic);
    QRegularExpression* regex = new QRegularExpression("[0-9a-z]{20}");
    QRegularExpressionValidator* valid = new QRegularExpressionValidator(*regex, ui->lineEdit);
    ui->lineEdit->setValidator(valid);
    ui->lineEdit->setDisabled(true);
    ui->lineEdit->installEventFilter(this);

    gameClock = new QTimer;
    gameClock->setInterval(1000);
    connect(gameClock, &QTimer::timeout, this, &MainWindow::Progress);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PlayerSend(QString s)
{
    if(cpuSeq.length() == seqLength && playerSeq.length() < 9)
    {
        gameClock->start();
        scene->clear();
        scene = new QGraphicsScene(0, 0, XMAX, YMAX);
        ui->graphicsView->setBackgroundBrush(Qt::black);
        ui->graphicsView->setScene(scene);
        QGraphicsTextItem* ch = new QGraphicsTextItem(s);
        ch->setScale(3);
        ch->setDefaultTextColor(Qt::blue);
        ch->setPos((XMAX/2)-1, (YMAX/2)-1);
        scene->addItem(ch);
        playerSeq.append(s);
        ui->playerLabel->setNum(playerSeq.length());
        if(playerSeq.length() == seqLength)
            CompareAnswer();
    }
}
void MainWindow::ComputerSend()
{
    int numOrLetter = qrand() % 2;
    QString ascii;
    if (numOrLetter == 1)    // Letter
    {
        ascii = QString(QChar(65 + qrand() % 25));
    } else {
        ascii = QString(QChar(48 + qrand() % 9));
    }

    if(cpuSeq.length() < seqLength)
    {
        QGraphicsTextItem* ch = new QGraphicsTextItem(ascii);
        ch->setScale(3);
        ch->setDefaultTextColor(Qt::red);
        ch->setPos((XMAX/2)-1, (YMAX/2)-1);
        scene->addItem(ch);
        cpuSeq.append(ascii);
        ui->cpuLabel->setNum(cpuSeq.length());
    }
}

void MainWindow::CompareAnswer()
{
    scene->clear();
    scene = new QGraphicsScene(0, 0, XMAX, YMAX);
    ui->graphicsView->setBackgroundBrush(Qt::black);
    ui->graphicsView->setScene(scene);
    for (int i = 0; i < seqLength; i++)
    {
        if(cpuSeq.at(i) != playerSeq.at(i))
        {
            ui->imageLabel->setPixmap(QPixmap(":/red.png"));
            gameClock->stop();
            return;
        }
    }
    ui->imageLabel->setPixmap(QPixmap(":/green.png"));
    gameClock->stop();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *e)
{
    if(!watched || !e) return QMainWindow::eventFilter(watched, e);

    if(watched == ui->lineEdit && e->type() == QEvent::KeyPress)
    {
        QKeyEvent * ke = static_cast<QKeyEvent*>(e);
        switch(ke->key())
        {
            case Qt::Key_Q:
            case Qt::Key_W:
            case Qt::Key_E:
            case Qt::Key_R:
            case Qt::Key_T:
            case Qt::Key_Y:
            case Qt::Key_U:
            case Qt::Key_I:
            case Qt::Key_O:
            case Qt::Key_P:
            case Qt::Key_A:
            case Qt::Key_S:
            case Qt::Key_D:
            case Qt::Key_F:
            case Qt::Key_G:
            case Qt::Key_H:
            case Qt::Key_J:
            case Qt::Key_K:
            case Qt::Key_L:
            case Qt::Key_Z:
            case Qt::Key_X:
            case Qt::Key_C:
            case Qt::Key_V:
            case Qt::Key_B:
            case Qt::Key_N:
            case Qt::Key_M:
            case Qt::Key_0:
            case Qt::Key_1:
            case Qt::Key_2:
            case Qt::Key_3:
            case Qt::Key_4:
            case Qt::Key_5:
            case Qt::Key_6:
            case Qt::Key_7:
            case Qt::Key_8:
            case Qt::Key_9:      this->PlayerSend(ke->text().toUpper());

            ui->lineEdit->clear();
            return true;
        }
    }
    return QMainWindow::eventFilter(watched, e);
}

void MainWindow::RestartGame()
{
    ui->restartButton->setText("Restart");
    ui->imageLabel->setPixmap(*scorePic);
    ui->cpuLabel->setNum(0);
    ui->playerLabel->setNum(0);
    cpuSeq.clear();
    playerSeq.clear();
    ui->lineEdit->setDisabled(false);
    gameClock->start();
    QGraphicsTextItem* ch = new QGraphicsTextItem("Ready?");
    ch->setScale(3);
    ch->setDefaultTextColor(Qt::red);
    ch->setPos((XMAX/2)-7, (YMAX/2)-7);
    scene->addItem(ch);
}

void MainWindow::Progress()
{
    scene->clear();
    scene = new QGraphicsScene(0, 0, XMAX, YMAX);
    ui->graphicsView->setBackgroundBrush(Qt::black);
    ui->graphicsView->setScene(scene);
    this->ComputerSend();
}

void MainWindow::SetLevelE()
{
        seqLength = 2;
        levelMenu->setDefaultAction(easyAction);
}

void MainWindow::SetLevelM()
{
        seqLength = 4;
        levelMenu->setDefaultAction(medAction);
}
void MainWindow::SetLevelH()
{
        seqLength = 6;
        levelMenu->setDefaultAction(hardAction);
}
