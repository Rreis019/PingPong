#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "CEntityManager.h"
#include "CWindow.h"
#include "CInput.h"
#include <time.h>
#include "Vec2.h"
#include "ScoreManager.h"

//COMPONENTS
#include "CColider.h"
#include "Pallet.h"
#include "Ball.h"
#include "Hax.h"

void CWindow::Events()
{
    CInput::Get().Reset();
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        CInput::Get().onUpdate(event);
        switch (event.type)
        {
            case SDL_QUIT:
                isRunning = false;
                break;
            //video resize
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    SDL_GetWindowSize(window, &width, &height);
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        isRunning = false;
                        break;
                    default:
                        break;
                }
                break;
        }
    }
}





void CWindow::Render()
{
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    CEntityManager::Get().onUpdate();
    CEntityManager::Get().onRender();
    scoreManager.draw();
    SDL_RenderPresent(renderer);
}



int main(int argc, char* argv[])
{
    CEntityManager & entmanager = CEntityManager::Get();
    CWindow& window = CWindow::Get();
    window.Init();
    scoreManager.init();
    scoreManager.setPos((window.width/2) - scoreManager.getWidth()/2, 10);

  

    CGameObject* player1 = entmanager.addEntity((char*)"player1",Vec2(10,10));
    auto p = player1->addComponent<Pallet>((int)SDL_SCANCODE_W,(int)SDL_SCANCODE_S);
    player1->addComponent<CColider>(Vec2(0,0),Vec2(p.width,p.height));

    CGameObject* player2 = entmanager.addEntity((char*)"player2",Vec2(window.width-30,window.height));
    auto p2 =  player2->addComponent<Pallet>((int)SDL_SCANCODE_UP,(int)SDL_SCANCODE_DOWN);
    player2->addComponent<CColider>(Vec2(0,0),Vec2(p2.width,p2.height));

    CGameObject* ball = entmanager.addEntity((char*)"ball",Vec2(window.width/2,window.height/2));
    auto b = ball->addComponent<Ball>();
    auto c = ball->addComponent<CColider>(Vec2(-10,-10),Vec2(20,20));

    CGameObject* huum = entmanager.addEntity("hum",Vec2(0,0));
    huum->addComponent<Hax>();
    
    window.GameLoop();    
    window.Free(); 
    CEntityManager::Get().clear();
    return 0;
}