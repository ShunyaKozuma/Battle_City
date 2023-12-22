#include "score.h"
#include <QFont>

Score::Score()
{
    score = 0;

    setPlainText("Score: " + QString::number(score));
    setDefaultTextColor(Qt::green);
    setFont(QFont("times",16));
}

void Score::increase()
{
    score=score+100;
    setPlainText("Score: " + QString::number(score));
}

int Score::getScore()
{
    return score;
}
