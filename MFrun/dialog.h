#include "astro.h"

#ifndef DIALOG_H
#define DIALOG_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDialog>
#include <QEvent>
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>
#include "mfalcon.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QGraphicsScene* scene = new QGraphicsScene(QRect(0, 0, 640, 480));
    QGraphicsScene* gameOver = new QGraphicsScene(QRect(0, 0, 640, 480));
    void EndGame();
    void seeTable();

protected:
    bool event(QEvent * e);

private:
    Ui::Dialog *ui;
    QSqlDatabase db;
    MFalcon millFalcon;
    int score;
    QTimer* gameClock = new QTimer;
    QTimer* astroClock = new QTimer;

public slots:
    void createAstro();
    void checkHealth();
    void restartGame();
    void purgeTable();
};

#endif // DIALOG_H
