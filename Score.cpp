#include "score.h"
#include <QFont>

Score::Score()
{
    score = 0;

    setPlainText("Score: " + QString::number(score));
    setDefaultTextColor(Qt::green);
    setFont(QFont("times",16));
    setPos(680, 0);
}

void Score::increase(int point)
{
    score=score+point;
    setPlainText("Score: " + QString::number(score));
}

int Score::getScore()
{
    return score;
}
