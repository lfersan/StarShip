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
private:
  bool                    is_running;

  shared_ptr<SFWindow>       sf_window;

  shared_ptr<SFAsset>        player;
  shared_ptr<SFBoundingBox>  app_box;
  list<shared_ptr<SFAsset> > projectiles;
  list<shared_ptr<SFAsset> > aliens;
  list<shared_ptr<SFAsset> > coins;
  shared_ptr<SFAsset>  smoke;
  shared_ptr<SFAsset>  barrier1;
  //shared_ptr<SFAsset>  alien1;


  int fire;
  int score;

};
#endif
