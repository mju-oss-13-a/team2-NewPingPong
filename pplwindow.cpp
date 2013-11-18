#include <QtGui>
#include <QFrame>

#include "pplwindow.h"

PPLWindow::PPLWindow(QWidget *parent)
    : QWidget(parent)
{
    _width = 500;
    _height = 500;
    _marginW = 20;
    _marginH = 20;
    _marginHBottom = 100;

    _score = 0;
    _scoreMax = 75;

    _gameOver = false;
    _victory = false;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);

    setWindowTitle(tr("Ping-Pong Lives v.0.3git"));
    resize(getWidth(), getHeight());

    setMouseTracking(true);

    racket.setCenter(getWidth()/2);
    ball.setX(getWidth()/2);
    ball.setY(getMarginHeightUp()+
              (getHeight()-getMarginHeightUp()-getMarginHeightBottom())/2);
}

PPLWindow::~PPLWindow()
{
    
}

void PPLWindow::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QColor mainColor(127, 0, 127);
    QPainter painter(this);
    painter.setPen(mainColor);
    painter.setBrush(Qt::NoBrush);

    // Draw screen
    painter.drawRect(getMarginWidth(), getMarginHeightUp(),
                     getWidth()-2*getMarginWidth(),
                     getHeight()-getMarginHeightUp()-getMarginHeightBottom());
    painter.drawText(getMarginWidth(),
                     getHeight()-getMarginHeightBottom()+20,
                     200, 20, 0, "Your score: " + QString::number(getScore()));
    painter.drawText(getMarginWidth(),
                     getHeight()-getMarginHeightBottom()+40,
                     200, 20, 0, "Your level:  " + getLevelTag());

    // Draw rackets
    painter.setBrush(mainColor);
    painter.drawRect(racket.getCenter()-racket.getWidth()/2,
                     getMarginHeightUp(), racket.getWidth(), racket.getHeight());
    painter.drawRect(racket.getCenter()-racket.getWidth()/2,
                     getHeight()-getMarginHeightBottom()-racket.getHeight(),
                     racket.getWidth(), racket.getHeight());


    // Move ball
    ball.setX(ball.getX() + ball.getXStep());
    ball.setY(ball.getY() + ball.getYStep()
              + 0.5*(getScore()/10)*(ball.isDown ? 1 : (-1)));


    // Draw ball
    painter.drawEllipse(ball.getX(), ball.getY(),
                        ball.getRadius(), ball.getRadius());


    // Check conditions
    if (isMaxScoreReached())
    {
        victoryGame();
        finishGame();
    }

    if (isGameOver())
    {
        painter.drawText(getMarginWidth(),
                         getHeight()-getMarginHeightBottom()+60,
                         200, 20, 0, (isVictory() ? "WELL DONE" : "GAME OVER"));
        if (!isVictory())
            painter.drawText(getMarginWidth(),
                             getHeight()-getMarginHeightBottom()+80,
                             400, 20, 0, "You can do better. Try again, champion!");
        return;
    }


    if (ball.getY()>getWidth() || ball.getY() <0)
    {
        finishGame();
        return;
    }


    // Check coordinates
    if (!ball.isDown && ball.getY() <=
            getMarginHeightUp() + racket.getHeight())
    {
        if (ball.getY() <= getMarginHeightUp())
        {
            finishGame();
            return;
        }

        if ((ball.getX() <= racket.getCenter() + racket.getWidth()/2) &&
                (ball.getX() >= racket.getCenter() - racket.getWidth()/2))
        {
            ball.setXStep((ball.getX() - racket.getCenter())*2/
                          (racket.getWidth()/2));
            ball.setYStep(ball.getBaseStep() + ball.getBaseStep()*getScore()/10);
            ball.isDown = true;
            addScore();
            ball.isRight = (ball.getXStep()>0) ? true : false;
        }
    }
    else if (ball.isDown &&
             ball.getY() >= getHeight()-getMarginHeightBottom()-racket.getHeight()-ball.getRadius())
    {
        if (ball.getY() >= getHeight()-getMarginHeightBottom())
        {
            finishGame();
            return;
        }

        if ((ball.getX() <= racket.getCenter() + racket.getWidth()/2) &&
                (ball.getX() >= racket.getCenter() - racket.getWidth()/2))
        {
            ball.setXStep((ball.getX() - racket.getCenter())*2/
                          (racket.getWidth()/2));
            ball.setYStep((-1)*(ball.getBaseStep() + ball.getBaseStep()*getScore()/10));        }
            ball.isDown = false;
            addScore();
            ball.isRight = (ball.getXStep()>0) ? true : false;
    }


    if (ball.getX() <= getMarginWidth() && !ball.isRight)
    {
        ball.setXStep((-1)*ball.getXStep());
        ball.isRight = true;
    }
    else if ((ball.getX() >= getWidth()-getMarginWidth()-ball.getRadius()) && ball.isRight)
    {
        ball.setXStep((-1)*ball.getXStep());
        ball.isRight = false;
    }


}

void PPLWindow::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);

    switch(event->key())
    {
    case Qt::Key_Left:
    {
        int newCenter = racket.getCenter() - racket.getBaseStep();
        if (newCenter<=(getMarginWidth()+racket.getWidth()/2))
            newCenter = getMarginWidth()+racket.getWidth()/2;
        racket.setCenter(newCenter);
    }
        break;
    case Qt::Key_Right:
    {
        int newCenter = racket.getCenter() + racket.getBaseStep();
        if (newCenter>=(getWidth()-getMarginWidth()-racket.getWidth()/2))
            newCenter=(getWidth()-getMarginWidth()-racket.getWidth()/2);
        racket.setCenter(newCenter);
    }
        break;
    }
}

void PPLWindow::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);

    int newCenter = event->x();
    if (newCenter<=(getMarginWidth()+racket.getWidth()/2))
        newCenter = getMarginWidth()+racket.getWidth()/2;
    else if (newCenter>=(getWidth()-getMarginWidth()-racket.getWidth()/2))
        newCenter=(getWidth()-getMarginWidth()-racket.getWidth()/2);
    racket.setCenter(newCenter);

}
