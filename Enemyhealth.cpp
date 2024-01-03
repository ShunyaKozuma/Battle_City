#include "Enemyhealth.h"
#include "Scene.h"

EnemyHealth::EnemyHealth(){
    setPixmap(QPixmap(":/images/Enemy_heart.png").scaled(30,30));
    setZValue(1);
}

void EnemyHealth::decrease()
{

}
