#include "SFApp.h"


SFApp::SFApp(std::shared_ptr<SFWindow> window) : fire(0), is_running(true), sf_window(window), score(0){
  int canvas_w, canvas_h;
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);

  app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);

  player  = make_shared<SFAsset>(SFASSET_PLAYER, sf_window);
  auto player_pos = Point2(canvas_w/2, 22);
  player->SetPosition(player_pos);

  smoke  = make_shared<SFAsset>(SFASSET_SMOKE, sf_window);
  auto smoke_pos = Point2(canvas_w/2, 280);
  smoke->SetPosition(smoke_pos);

  barrier1  = make_shared<SFAsset>(SFASSET_BARRIER1, sf_window);
  auto barrier1_pos = Point2(canvas_w/2, 800);
  barrier1->SetPosition(barrier1_pos);


  auto coin = make_shared<SFAsset>(SFASSET_COIN, sf_window);
  auto pos  = Point2((canvas_w/4), 100);
  coin->SetPosition(pos);
  coins.push_back(coin);

  //Aliens

  const int number_of_aliens = 2;
  for(int i=0; i<number_of_aliens; i++) {
    // place an alien at width/number_of_aliens * i
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN, sf_window);
    auto pos  = Point2((canvas_w/number_of_aliens) * i, 300.0f);
    alien->SetPosition(pos);
    aliens.push_back(alien);
  }

}

SFApp::~SFApp() {
}

/**
 * Handle all events that come from SDL.
 * These are timer or keyboard events.
 */
void SFApp::OnEvent(SFEvent& event) {
  SFEVENT the_event = event.GetCode();
  switch (the_event) {
  case SFEVENT_QUIT:
    is_running = false;
    break;
  case SFEVENT_UPDATE:
    OnUpdateWorld();
    OnRender();
    break;
  case SFEVENT_PLAYER_LEFT:
    player->GoWest();
    break;
  case SFEVENT_PLAYER_RIGHT:
    player->GoEast();
    break;
  case SFEVENT_PLAYER_NORTH:
    player->GoNorth();
    break;
  case SFEVENT_PLAYER_SOUTH:
    player->GoSouth();
    break;
  case SFEVENT_FIRE:
    fire ++;
    FireProjectile();
    break;
  }
}

int SFApp::OnExecute() {
  // Execute the app
  SDL_Event event;
  while (SDL_WaitEvent(&event) && is_running) {
    // wrap an SDL_Event with our SFEvent
    SFEvent sfevent((const SDL_Event) event);
    // handle our SFEvent
    OnEvent(sfevent);
  }
}

void SFApp::OnUpdateWorld() {

 // Coin & Player Interaction // on collision, destroy coin, add one to score
  for(auto c:coins){
 	 if(player->CollidesWith(c)){
 		player->PlayerCoin();
  		 c->PlayerCoin();
 		 score++;
         std::cout <<"Score "<< score << std::endl;
 	 }
  }



  // Coin Movement

  for( auto c: coins){
	  c->CoinUp();
	  if(c->CollidesWith(barrier1)){
		  std::cout<<"check2"<<std::endl;
		  //c->CoinUp();
		  //c->setGoUp(false);
	  }
	for(auto p: projectiles){

	if(p->CollidesWith(c)){
		std::cout<<"check"<<std::endl;
	}
	  }
  }



  // remove dead coins
  list<shared_ptr<SFAsset>> tmc;
  for(auto c : coins) {
    if(c->IsAlive()) {
      tmc.push_back(c);
    }
  }
coins.clear();
coins = list<shared_ptr<SFAsset>>(tmc);

// Update projectile positions
for(auto p: projectiles) {
  p->GoNorth();
}

// Update enemy positions
  for(auto a : aliens) {
	  a->CoinUp();
  }

//Detect collisions alien vs projectiles
  for(auto p : projectiles) {
    for(auto a : aliens) {
      if(p->CollidesWith(a)) {
        p->HandleCollision();
        a->HandleCollision();
        score++;
        std::cout <<"Score "<< score << std::endl;

         }
       }
  }

//remove bullets after collision
  list<shared_ptr<SFAsset> > tmk;
  for(auto p : projectiles) {
		  if(p->IsAlive()) {
    	      tmk.push_back(p);
    }
  }
  projectiles.clear();
  projectiles = list<shared_ptr<SFAsset> >(tmk);


// remove dead aliens (the long way)
  list<shared_ptr<SFAsset>> tmp;
  for(auto a : aliens) {
    if(a->IsAlive()) {
      tmp.push_back(a);
    }
  }
  aliens.clear();
  aliens = list<shared_ptr<SFAsset>>(tmp);



// Player & Alien collision // player hits alien,player dies, players looses, display Game Over on console
   for(auto a : aliens) {
     if(player->CollidesWith(a)) {
       player->PlayerAlien();
       a->PlayerAlien();
       std::cout << "Game Over" << " | Score " << score << std::endl;

     }
   }

//Player & Barrier
   if (player ->CollidesWith(barrier1)){ //collision
	   player->GoSouth();
	   std::cout << "Congratz, you won" << " | Score " << score << std::endl;
      }


//Player & Smoke Collision
	   if (player ->CollidesWith(smoke)){ //collision
		   player->GoSouth();
		   }





	  /* // murder them coins projectiles coin
	    for(auto p: projectiles){
	  	  for(auto c: coins){
	  	 	  if(p->CollidesWith(c)) {
	      	        p->HandledCollision();
	      	        c->HandledCollision();

	  		  }
	  	  }
	    }

	   */


}
void SFApp::OnRender() {
  SDL_RenderClear(sf_window->getRenderer());

  // draw the player const SDL_Rect &rect1, const SDL_Rect &rect2
  player->OnRender();

  for(auto p: projectiles) {
	  p->ProjectileMovement();
    if(p->IsAlive()) {
    	p->OnRender();}
  }

  for(auto a: aliens) {
    if(a->IsAlive()) {a->OnRender();}
  }

  for(auto c: coins) {
    c->OnRender();
  }

 smoke->OnRender();

 barrier1->OnRender();

 //alien1->OnRender();

  // Switch the off-screen buffer to be on-screen
  SDL_RenderPresent(sf_window->getRenderer());
}

void SFApp::FireProjectile() {
  auto pb = make_shared<SFAsset>(SFASSET_PROJECTILE, sf_window);
  auto v  = player->GetPosition();
  pb->SetPosition(v);
  projectiles.push_back(pb);
}
