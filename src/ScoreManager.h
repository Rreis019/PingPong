#include "CLabel.h"
class ScoreManager
{
    public:
        ScoreManager(){}
        void setPos(int x, int y){
            this->x = x;
            this->y = y;
            scoreLabel.setPos(x,y);
        }
        inline void draw();
        inline void init();

        int getWidth(){return scoreLabel.getWidth();}
        CLabel scoreLabel = CLabel(0,0,"res/fonts/manaspc.ttf",{255,255,255,255},32, "%d : %d",p1Score,p2Score);
        int p1Score = 0;
        int p2Score = 0;
    private:
        //Label(int x,int y,std::string fontName,SDL_Color color,int fontSize,char* str,...)
        int x,y;
};

void ScoreManager::init()
{
    scoreLabel.init();
}

void ScoreManager::draw()
{
    scoreLabel.draw();
}

inline ScoreManager scoreManager;