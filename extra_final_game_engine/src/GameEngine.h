//-----------------------------------------------------------------
// Game Engine Object
// C++ Header - GameEngine.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>

#include "IGame.h"
#include "Sprite.h"

using namespace std;

namespace TYGP
{

  //-----------------------------------------------------------------
  // GameEngine Class
  //-----------------------------------------------------------------
  class GameEngine
  {
  private:
    GameEngine();
    static GameEngine *m_pGameEngine;
    SDL_Window *m_hWindow;
    SDL_Renderer *m_renderer;
    char m_szTitle[32];
    char m_szIcon[32];
    int m_iWidth, m_iHeight;
    int m_iFrameDelay;
    bool m_bSleep;
    SDL_GameController *m_gameController;
    SDL_Rect m_rcJoystickTrip;
    vector<Sprite *> m_vSprites;
    vector<Sprite *> m_vSpritesToAdd;

  public:
    IGame *m_game;

    // Destructor
    virtual ~GameEngine();

    // General Methods
    static GameEngine *GetEngine()
    {
      if (m_pGameEngine == NULL)
        m_pGameEngine = new GameEngine();
      return m_pGameEngine;
    };

    bool Initialize(const char *szTitle,
                    const char *szIcon,
                    int iWidth = 640,
                    int iHeight = 480);
    void Run();
    void HandleEvent();
    void ErrorQuit(char *szErrorMsg);
    bool InitJoystick();
    void CaptureJoystick(int id);
    void ReleaseJoystick(int id);
    void CheckJoystick();
    // Sprite managment
    void AddSprite(Sprite *pSprite);
    void DrawSprites();
    void UpdateSprites();
    void CleanupSprites();
    Sprite *IsPointInSprite(int x, int y);
    bool CheckSpriteCollision(Sprite *pTestSprite);
    void PlaySong(Mix_Music *music, bool bRestart = true);
    void PauseSong();
    void ClosePlayer();
    SDL_Texture *DrawText(SDL_Renderer *renderer,
                          const char *text,
                          TTF_Font *Font,
                          SDL_Color FontColor);
    // Accessor Methods
    SDL_Window *GetWindow() { return m_hWindow; };
    SDL_Renderer *GetRenderer() { return m_renderer; };
    void SetWindow(SDL_Window *hWindow) { m_hWindow = hWindow; };
    char *GetTitle() { return m_szTitle; };
    char *GetIcon() { return m_szIcon; };
    int GetWidth() { return m_iWidth; };
    int GetHeight() { return m_iHeight; };
    int GetFrameDelay() { return m_iFrameDelay; };
    void SetFrameRate(int iFrameRate) { m_iFrameDelay = 1000 / iFrameRate; };
    bool GetSleep() { return m_bSleep; };
    void SetSleep(bool bSleep) { m_bSleep = bSleep; };
    SDL_GameController *GetController() { return m_gameController; };
  };

}
