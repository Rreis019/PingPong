#include "Ball.h"
#include "CWindow.h"
#include "ScoreManager.h"

void Ball::onStart()
{
    this->startPos = this->owner->getPos();
    timereset = SDL_GetTicks() + RESET_TIME;
    reset = true;
}

void Ball::onUpdate()
{
    if(reset)
    {
        if(SDL_GetTicks() > timereset )
        {
            reset = false;
            this->vel = this->startVel;
            printf("reset\n");
            this->owner->setPos(this->startPos);
        }
    }
    
    this->owner->move(vel);

    //if is out of bounds inverse the velocity
    Vec2 ownerpos = this->owner->getPos();
    CWindow& window = CWindow::Get();
    if(ownerpos.y < 0){ this->owner->setPos(Vec2(ownerpos.x,0)); this->vel.y *= -1;}
    if(ownerpos.y > window.height)  {this->owner->setPos(Vec2(ownerpos.x,window.height)); this->vel.y *= -1;}
    
    
    if(ownerpos.x < 0 || ownerpos.x > window.width) {
        
        if(ownerpos.x < 0)
        {
            scoreManager.p2Score++;
            scoreManager.scoreLabel.setText("%d : %d",scoreManager.p1Score,scoreManager.p2Score);
        }
        else
        {
            scoreManager.p1Score++;
            scoreManager.scoreLabel.setText("%d : %d",scoreManager.p1Score,scoreManager.p2Score);
        }

        this->owner->setPos(this->startPos);
        this->vel = Vec2(0,0);
        reset = true;
        timereset = SDL_GetTicks() + RESET_TIME;
    }
}

void Ball::onRender()
{
    CGraphics* g = CWindow::Get().getGraphics();
    g->DrawFilledCircle(this->owner->getPos().x, this->owner->getPos().y,radius,{255,255,255,255});
}

void Ball::onTriggerEnter(CGameObject* other)
{
    this->owner->move(Vec2((vel.x*1)*-1,(vel.y*1)*-1));
    this->vel = Vec2(-this->vel.x, -this->vel.y);

    //randomize the velocity y
    this->vel.y = rand() % 3 - 1;


    this->vel.x *= 1.1f;
    this->vel.y *= 1.1f;

};