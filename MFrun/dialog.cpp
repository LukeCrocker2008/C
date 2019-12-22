#include "dialog.h"
#include "ui_dialog.h"
#include <QSqlQueryModel>
#include <QTableView>
#include <QtDebug>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("highscore.db");

    if(!db.open())
    {
        qDebug() << "ERROR OPENING DB!";
    } else {
        QSqlQuery q;
        if(!q.exec("CREATE TABLE IF NOT EXISTS scores (date TEXT, score INT)"))
        {
            qDebug() << "Error executing CREATE TABLE";
        }
    }

    this->setWindowTitle("Millenium Falcon Run");
    scene->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    ui->graphicsView->setScene(scene);

    connect(ui->Quit, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->purgeButton, &QPushButton::clicked, this, &Dialog::purgeTable);
    connect(ui->restart, &QPushButton::clicked, this, &Dialog::restartGame);

    millFalcon.setPos(320, 450);
    scene->addItem(&millFalcon);
    ui->progressBar->setValue(100);
    score = 0;
    ui->restart->setDisabled(true);

    connect(gameClock, SIGNAL(timeout()), scene, SLOT(advance()));
    connect(gameClock, SIGNAL(timeout()), this, SLOT(checkHealth()));
    connect(astroClock, SIGNAL(timeout()), this, SLOT(createAstro()));
    gameClock->setInterval(1000/33);
    astroClock->setInterval(qrand() % 5000);
    gameClock->start();
    astroClock->start();

}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::event(QEvent * e)
{
    score++;
    if (!e)
    {
        return QDialog::event(e);
    }
    qreal th = millFalcon.rotation();
    if(e->type() == QEvent::KeyPress)
    {
        QKeyEvent* ke = static_cast<QKeyEvent*>(e);

        if(ke->key() == Qt::Key_A && millFalcon.EngineOn())
        {
            millFalcon.setRotation(th-5);
        } else if(ke->key() == Qt::Key_D && millFalcon.EngineOn())
        {
            millFalcon.setRotation(th+5);
        }  else if(ke->key() == Qt::Key_W) {
            millFalcon.setEngine(true);         // Ignite Engine and Advance Spaceship
            score = score + 25;
        }  else if(ke->key() == Qt::Key_S) {
            millFalcon.setEngine(false);        // Brake
        }
    }
    return QDialog::event(e);
}

void Dialog::createAstro()
{
    qreal height = 100 + qrand() % 100;
    qreal width = 100 + qrand() % 100;
    Astro* asteroid = new Astro(width, height);
    qreal x = -25 + qrand() % 675;
    qreal y = -75;
    asteroid->setPos(x, y);
    scene->addItem(asteroid);
}

void Dialog::checkHealth()
{
    int health = ui->progressBar->value();
    if(!scene->collidingItems(&millFalcon).isEmpty())
    {
       ui->progressBar->setValue(health-2);
    }
    if (health <= 0 || millFalcon.pos().x() < -380 || millFalcon.pos().x() > 1120 ||  millFalcon.pos().y() < -360 || millFalcon.pos().y() > 850)
    {
        this->EndGame();
    }
}

void Dialog::restartGame()
{
    Dialog* newGame = new Dialog;
    newGame->show();
    this->accept();
}

void Dialog::EndGame()
{
    QDateTime date(QDate::currentDate(), QTime::currentTime());
    QString dateTime = date.toString(Qt::DefaultLocaleShortDate);
    QString scoreObtained = "Score = " + QString::number(score);
    QSqlQuery q(db);
    q.prepare("SELECT MAX(score) FROM scores");
    q.exec();
    q.next();
    int highscore = q.value(0).toInt();
    if(score > highscore)
    {
        QGraphicsTextItem* t0 = new QGraphicsTextItem("New Record!");
        t0->setDefaultTextColor(Qt::red);
        t0->setScale(5);
        t0->setTextWidth(100);
        t0->setPos(100, -30);
        gameOver->addItem(t0);
        highscore = score;
        QSqlQuery i;
        i.prepare("INSERT INTO scores VALUES( :date, :score )");
        i.bindValue(":date", dateTime);
        i.bindValue(":score", highscore);
        if(!i.exec())
        {
            qDebug() << "Error executing INSERT";
        }
    } else {
        QSqlQuery d;
        d.prepare("SELECT * FROM scores WHERE score = :highscore");
        d.bindValue(":highscore", highscore);
        d.exec();
        d.next();
        dateTime = d.value(0).toString();
    }
    QString HS = "High Score = " + QString::number(highscore);

    gameOver->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    QGraphicsTextItem* t1 = new QGraphicsTextItem("Game Over");
    QGraphicsTextItem* t2 = new QGraphicsTextItem(scoreObtained);
    QGraphicsTextItem* t3 = new QGraphicsTextItem(HS);
    QGraphicsTextItem* t4 = new QGraphicsTextItem(dateTime);
    t1->setDefaultTextColor(Qt::red);
    t1->setScale(7);
    t1->setTextWidth(100);
    t1->setPos(33, 44);
    t2->setDefaultTextColor(Qt::red);
    t2->setScale(7);
    t2->setTextWidth(200);
    t2->setPos(-40, 160);
    t3->setDefaultTextColor(Qt::red);
    t3->setScale(3);
    t3->setTextWidth(200);
    t3->setPos(103, 300);
    t4->setDefaultTextColor(Qt::red);
    t4->setScale(3);
    t4->setTextWidth(200);
    t4->setPos(112, 360);
    gameOver->addItem(t1);
    gameOver->addItem(t2);
    gameOver->addItem(t3);
    gameOver->addItem(t4);
    ui->graphicsView->setScene(gameOver);
    ui->restart->setDisabled(false);
    gameClock->stop();
    astroClock->stop();
}

void Dialog::seeTable()
{
    QDialog* d = new QDialog;
    QVBoxLayout* b = new QVBoxLayout(d);
    QTableView* v = new QTableView;
    b->addWidget(v);
    QSqlQueryModel* m = new QSqlQueryModel;
    m->setQuery("SELECT * FROM scores");
    v->setModel(m);
    v->show();
    d->show();
}

void Dialog::purgeTable()
{
    QMessageBox msg;
    msg.setText("Purge data from database");
    msg.setInformativeText("Delete all data now?");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::No);
    int selection = msg.exec();

    if(selection == QMessageBox::Yes)
    {
        QSqlQuery q(db);
        q.prepare("DELETE FROM scores WHERE '1' = '1'");
        q.exec();
    }
}
