#include "defs.h"

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
#include <stdlib.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject *watched, QEvent *e);
    void PlayerSend(QString);
    void ComputerSend();
    void CompareAnswer();
    QMenu* menu = new QMenu("File");
    QMenu* levelMenu = new QMenu("Level");
    QAction* quitAction = new QAction("Quit");
    QAction* easyAction = new QAction("Easy");
    QAction* medAction = new QAction("Medium");
    QAction* hardAction = new QAction("Hard");

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene = new QGraphicsScene(0, 0, XMAX, YMAX);
    QTimer* gameClock;
    QPixmap* scorePic;
    QList<QString> cpuSeq;
    QList<QString> playerSeq;
    int seqLength = 0;

public slots:
    void RestartGame();
    void Progress();
    void SetLevelE();
    void SetLevelM();
    void SetLevelH();
};

#endif // MAINWINDOW_H
