#ifndef SFAPP_H
#define SFAPP_H

#include <memory>   // Pull in std::shared_ptr
#include <iostream> // Pull in std::cerr, std::endl
#include <list>     // Pull in list
#include <sstream>

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFAsset.h"
// #include <SDL2/SDL_ttf.h> // Pull in the SDL definitions

/**
 * Represents the StarshipFontana application.  It has responsibilities for
 * * Creating and destroying the app window
 * * Processing game events
 */
class SFApp {
public:
  SFApp(std::shared_ptr<SFWindow>);
  virtual ~SFApp();
  void    OnEvent(SFEvent &);
  int     OnExecute();
  void    OnUpdateWorld();
  void    OnRender();

  void    FireProjectile();
  void    FireProjectile2();
  void    GameOver();
private:
  bool                    is_running;

  shared_ptr<SFWindow>       sf_window;
  shared_ptr<SFAsset>  gameover;

  shared_ptr<SFAsset>        player;
  shared_ptr<SFBoundingBox>  app_box;
  list<shared_ptr<SFAsset> > projectiles;
  list<shared_ptr<SFAsset> > projectiles2;

  list<shared_ptr<SFAsset> > cars;
  list<shared_ptr<SFAsset> > cars2;

  list<shared_ptr<SFAsset> > trucks;
  list<shared_ptr<SFAsset> > trucks2;

  list<shared_ptr<SFAsset> > coins;

  list<shared_ptr<SFAsset> > woods1;
  list<shared_ptr<SFAsset> > woods2;
  list<shared_ptr<SFAsset> > woods3;

  list<shared_ptr<SFAsset> > plaines;
  shared_ptr<SFAsset>  boss;

  shared_ptr<SFAsset>  topB;
  shared_ptr<SFAsset>  rightB;
  shared_ptr<SFAsset>  leftB;
  shared_ptr<SFAsset>  background;



  int fire;
  int lives;
  int score;
  int fire2;

};
#endif
