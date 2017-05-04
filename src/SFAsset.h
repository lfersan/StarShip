#ifndef SFASSET_H
#define SFASSET_H

#include <string>
#include <memory>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFWindow.h"
#include "SFBoundingBox.h"

/**
 * We could create SFPlayer, SFProjectile and SFAsset which are subclasses
 * of SFAsset.  However, I've made an implementation decision to use this
 * enum to mark the type of the SFAsset.  If we add more asset types then
 * the subclassing strategy becomes a better option.
 */
enum SFASSETTYPE {SFASSET_DEAD,SFASSET_GAMEOVER,SFASSET_BACKGROUND, SFASSET_PLAYER, SFASSET_PROJECTILE, SFASSET_CAR, SFASSET_COIN, SFASSET_WOOD,SFASSET_TOPB,SFASSET_SIDEB,SFASSET_TRUCK, SFASSET_PLAINE};

class SFAsset {
public:
  SFAsset(const SFASSETTYPE, const std::shared_ptr<SFWindow>);
  SFAsset(const SFAsset&);
  virtual ~SFAsset();

  virtual void      SetPosition(Point2 &);
  virtual Point2    GetPosition();
  virtual SFAssetId GetId();
  virtual void      OnRender();
  //movement
  virtual void      GoEast();
  virtual void      GoEast2();
  virtual void      GoWest();
  virtual void      GoWest2();
  virtual void      GoSouth();
  virtual void      GoNorth();
  virtual void 		CoinUp();

  virtual void 		ProjectileMovement();
  virtual void 		ProjectileMovement2();

  virtual void		AlienW();
  virtual void		AlienE();

  //status
  virtual void      SetNotAlive();
  virtual bool      IsAlive();
  //collision
  virtual void      SideCollision();
  virtual void      HandleCollision();
 // virtual void      HandleCollisionT();
  //virtual void  	PlayerCoin();
  //virtual void 		PlayerAlien();
  virtual void 		WoodCollision();


  virtual int		getAssetWidth();
  virtual int		getAssetHeight();


  virtual bool                      CollidesWith(shared_ptr<SFAsset>);
  virtual shared_ptr<SFBoundingBox> GetBoundingBox();
private:
  // it would be nice if we could make this into a smart pointer,
  // but, because we need to call SDL_FreeSurface on it, we can't.
  // (or we could use a std::shared_ptr with a custom Deleter, but
  // that's a little too much right now)
  SDL_Texture               * sprite;
  shared_ptr<SFBoundingBox>   bbox;
  SFASSETTYPE                 type;
  SFAssetId                   id;
  std::shared_ptr<SFWindow>   sf_window;

  static int SFASSETID;
};

#endif
