#ifndef PPLWINDOW_H
#define PPLWINDOW_H

#include <QWidget>
#include <QString>

#include "pplracket.h"
#include "pplball.h"

class PPLWindow : public QWidget
{
    Q_OBJECT
    
public:
    PPLWindow(QWidget *parent = 0);
    ~PPLWindow();

    int getWidth(){return _width;}
    int getHeight(){return _height;}
    int getMarginWidth(){return _marginW;}
    int getMarginHeightUp(){return _marginH;}
    int getMarginHeightBottom(){return _marginHBottom;}

    int getScore(){return _score;}
    void addScore(){_score++;}
    bool isMaxScoreReached(){return _score == 75;}
    QString getLevelTag(){return _level[_score/10];}

    bool finishGame(){_gameOver = true;}
    bool victoryGame(){_victory = true;}
    bool isGameOver(){return _gameOver;}
    bool isVictory(){return _victory;}

    PPLRacket racket;
    PPLBall ball;


protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    int _width;
    int _height;
    int _marginW;
    int _marginH;
    int _marginHBottom;

    int _score;
    int _scoreMax;
    QString _level[8] = {
        "Slowpoke",
        "Private Ryan",
        "Sgt Pepper",
        "Major Pain",
        "Agent 007",
        "John Rambo",
        "Terminator",
        "Hello, Chuck!"
    };

    bool _gameOver;
    bool _victory;

};

#endif // PPLWINDOW_H
