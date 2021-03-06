#include "SFApp.h"


SFApp::SFApp(std::shared_ptr<SFWindow> window) : fire(0), is_running(true), sf_window(window), score(0), lives(20),fire2(0){
  int canvas_w, canvas_h;
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);

  gameover = make_shared<SFAsset>(SFASSET_GAMEOVER, sf_window);
   auto go_pos = Point2(0,0);
  gameover->SetPosition(go_pos);

  background  = make_shared<SFAsset>(SFASSET_BACKGROUND, sf_window);
  auto background_pos = Point2(canvas_w/2, canvas_h/2);
  background->SetPosition(background_pos);

  app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);

  topB  = make_shared<SFAsset>(SFASSET_TOPB, sf_window);
  auto topB_pos = Point2(canvas_w/2, 1000);
  topB->SetPosition(topB_pos);

  player  = make_shared<SFAsset>(SFASSET_PLAYER, sf_window);
  auto player_pos = Point2(canvas_w/2, 22);
  player->SetPosition(player_pos);



  leftB  = make_shared<SFAsset>(SFASSET_SIDEB, sf_window);
  auto leftB_pos = Point2(canvas_w/99, 300);
  leftB->SetPosition(leftB_pos);

  rightB  = make_shared<SFAsset>(SFASSET_SIDEB, sf_window);
  auto rightB_pos = Point2(canvas_w/0.9, 300);
  rightB->SetPosition(rightB_pos);

  auto coin = make_shared<SFAsset>(SFASSET_COIN, sf_window);
  auto pos  = Point2((canvas_w/2), 360);
  coin->SetPosition(pos);
  coins.push_back(coin);


  //Cars
  const int number_of_cars = 3;
  for(int i=0; i<number_of_cars; i++) {
    // place an alien at width/number_of_cars * i
    auto car = make_shared<SFAsset>(SFASSET_CAR, sf_window);
    auto pos  = Point2((canvas_w/number_of_cars) * i + car->getAssetWidth(), 75.0f);
    car->SetPosition(pos);
    cars.push_back(car);
  }

  const int number_of_cars2 = 3;
  for(int i=0; i<number_of_cars2; i++) {
    auto car2 = make_shared<SFAsset>(SFASSET_PLAINE, sf_window);
    auto pos  = Point2((canvas_w/number_of_cars2) * i + car2->getAssetWidth(), 700.0f);
    car2->SetPosition(pos);
    cars2.push_back(car2);
  }

  //Row Wood

  const int number_of_woods1 = 3;
   for(int i=0; i<number_of_woods1; i++) {
     auto wood1 = make_shared<SFAsset>(SFASSET_WOOD, sf_window);
     auto pos1  = Point2((canvas_w/number_of_woods1) * i + wood1->getAssetWidth(), 175.0f);
     wood1->SetPosition(pos1);
     woods1.push_back(wood1);
   }
   const int number_of_woods2 = 3;
    for(int i=0; i<number_of_woods2; i++) {
     auto wood2 = make_shared<SFAsset>(SFASSET_WOOD, sf_window);
     auto pos2  = Point2((canvas_w/number_of_woods2) * i + wood2->getAssetWidth(), 375.0f);
     wood2->SetPosition(pos2);
     woods2.push_back(wood2);
   }
    const int number_of_woods3 = 3;
     for(int i=0; i<number_of_woods3; i++) {
     auto wood3 = make_shared<SFAsset>(SFASSET_WOOD, sf_window);
     auto pos3  = Point2((canvas_w/number_of_woods3) * i + wood3->getAssetWidth(), 525.0f);
     wood3->SetPosition(pos3);
     woods3.push_back(wood3);
   }

  //Trucks
   const int number_of_trucks = 3;
   for(int i=0; i<number_of_trucks; i++) {
     auto truck = make_shared<SFAsset>(SFASSET_TRUCK, sf_window);
     auto pos  = Point2((canvas_w/number_of_trucks) * i + truck->getAssetWidth(), 275.0f);
     truck->SetPosition(pos);
     trucks.push_back(truck);
   }
   const int number_of_trucks2 = 3;
      for(int i=0; i<number_of_trucks2; i++) {
        auto truck2 = make_shared<SFAsset>(SFASSET_TRUCK, sf_window);
        auto pos  = Point2((canvas_w/number_of_trucks2) * i + truck2->getAssetWidth(), 475.0f);
        truck2->SetPosition(pos);
        trucks2.push_back(truck2);
      }

   //Plaine
      const int number_of_plaines = 3;
      for(int i=0; i<number_of_plaines; i++) {
        auto plaine = make_shared<SFAsset>(SFASSET_PLAINE, sf_window);
        auto pos  = Point2((canvas_w/number_of_plaines) * i + plaine->getAssetWidth(), 850.0f);
        plaine->SetPosition(pos);
        plaines.push_back(plaine);
      }

      boss = make_shared<SFAsset>(SFASSET_PLAINE, sf_window);
      auto boss_pos = Point2(canvas_w/2, 900);
      boss->SetPosition(boss_pos);
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
  /*case SFEVENT_PLAYER_LEFT:
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
    */

  case SFEVENT_PLAYER_RIGHT:
	  fire2++;
	  FireProjectile2();
	  break;

  case SFEVENT_PLAYER_LEFT:
	  fire2++;
	  FireProjectile2();
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

	  int canvas_w, canvas_h;
	  SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);

	const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

	 if(keyboardState[SDL_SCANCODE_DOWN]) {
	 player->GoSouth();
	 for( auto w : woods1){
	 if(player->CollidesWith(w)){
	player->GoNorth();}
	 }
	 for( auto w : woods2){
	 	 if(player->CollidesWith(w)){
	 	player->GoNorth();}
	 	 }
	 for( auto w : woods3){
	 	 if(player->CollidesWith(w)){
	 	player->GoNorth();}
	 	 }
	 }

	 if(keyboardState[SDL_SCANCODE_UP]) {
	 player->GoNorth();
	  for( auto w : woods1){
	  if(player->CollidesWith(w)){
	player->GoSouth();}
	 }
	  for( auto w : woods2){
	  	  if(player->CollidesWith(w)){
	  	player->GoSouth();}
	  	 }
	  for( auto w : woods3){
	  	  if(player->CollidesWith(w)){
	  	player->GoSouth();}
	  	 }
	 }


		 if(keyboardState[SDL_SCANCODE_LEFT]) {
			 player->GoWest();
			 	 boss -> GoWest2();
				fire2++;
		 	 if(boss->CollidesWith(leftB)){
		 		 boss->SideCollision();
		 		 auto pos  = Point2(canvas_w/1 , 900.0f);
		 		 boss->SetPosition(pos);
		 }
	 }



	  for( auto w : woods1){
	  if(player->CollidesWith(w)){
	player->GoEast();}
	 }
	  for( auto w : woods2){
		  if(player->CollidesWith(w)){
		player->GoEast();}
		 }
	 for( auto w : woods3){
	 	  if(player->CollidesWith(w)){
	 	player->GoEast();}
	 	 }

	 if(keyboardState[SDL_SCANCODE_RIGHT]) {
	 player->GoEast();
	 boss->GoEast2();
	 fire2++;
	 for( auto w : woods1){
	 if(player->CollidesWith(w)){
	player->GoWest();}
	 }
	 for( auto w : woods2){
	 	 if(player->CollidesWith(w)){
	 	player->GoWest();}
	 	 }
	 for( auto w : woods3){
	 	 if(player->CollidesWith(w)){
	 	player->GoWest();}
	 	 }
	 }

//Boss


//--------------------------------------------------------------------------------
//Coins

// Coin & Player Interaction // on collision, destroy coin, add one to score
  for(auto c:coins){
 	 if(player->CollidesWith(c)){
 		player->HandleCollision();
  		 c->HandleCollision();
 		 score++;
         std::cout <<"Score "<< score << std::endl;
 	 }
  }

// Coin Movement
  for( auto c: coins){for(auto c:coins){
	 	 if(player->CollidesWith(c)){
	 		player->HandleCollision();
	  		 c->HandleCollision();
	 		 score++;
	         std::cout <<"Score "<< score << std::endl;
	 	 }
	  }
	  c->CoinUp();
	  //if(c->CollidesWith(topB)){
		  //std::cout<<"check2"<<std::endl;
		  //c->CoinUp();
		  //c->setGoUp(false);
	  //}
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

//--------------------------------------------------------------------------------
//Enemies & Barriers

// Cars
for(auto a : cars) {
	  	  if(a->CollidesWith(rightB)){
	  		  a->SideCollision();
	  		  auto pos  = Point2((canvas_w/300) , 75);
	  		  a->SetPosition(pos);
	  	  }else{
	  		  a->AlienW();
	  	  }
}



for(auto b : cars2) {
	  	  if(b->CollidesWith(rightB)){
	  		  b->SideCollision();
	  		  auto pos  = Point2((canvas_w/300) , 700);
	  		  b->SetPosition(pos);
	  	  }else{
	  		 b->AlienE();
	  	  }
  }

//Truck
for(auto c : trucks) {
	  	  if(c->CollidesWith(leftB)){
	  		  c->SideCollision();
	  		  auto pos  = Point2((canvas_w/1) , 275);
	  		  c->SetPosition(pos);
	  	  }else{
	  		 c->AlienW();
	  	  }

  }
for(auto d : trucks2) {
	  	  if(d->CollidesWith(rightB)){
	  		  d->SideCollision();
	  		  auto pos  = Point2((canvas_w/720) , 475);
	  		  d->SetPosition(pos);
	  	  }else{
	  		 d->AlienE();
	  	  }

  }

//Wood
for(auto e : woods1) {
	  	  if(e->CollidesWith(leftB)){
	  		  e->SideCollision();
	  		  auto pos  = Point2(canvas_w/1 , 175);
	  		e->SetPosition(pos);
	  	  }else{
	  		e->AlienW();
	  	  }
}

for(auto f : woods2) {
	  	  if(f->CollidesWith(rightB)){
	  		  f->SideCollision();
	  		  auto pos  = Point2(canvas_w/720 , 350);
	  		f->SetPosition(pos);
	  	  }else{
	  		f->AlienE();
	  	  }
}

for(auto g : woods3) {
	  	  if(g->CollidesWith(leftB)){
	  		  g->SideCollision();
	  		  auto pos  = Point2(canvas_w/1 , 525);
	  		g->SetPosition(pos);
	  	  }else{
	  		g->AlienW();
	  	  }
}

//plaines
for(auto a : plaines) {
	  	  if(a->CollidesWith(leftB)){
	  		  a->SideCollision();
	  		  auto pos  = Point2(canvas_w/1 , 850.0f);
	  		a->SetPosition(pos);
	  	  }else{
	  		a->AlienW();
	  	  }
}


// dead plaines
  list<shared_ptr<SFAsset>> tmy;
  for(auto a : plaines) {
    if(a->IsAlive()) {
      tmy.push_back(a);
    }
  }
 plaines.clear();
 plaines= list<shared_ptr<SFAsset>>(tmy);



// dead cars
  list<shared_ptr<SFAsset>> tmp;
  for(auto a : cars) {
    if(a->IsAlive()) {
      tmp.push_back(a);
    }
  }
 cars.clear();
 cars = list<shared_ptr<SFAsset>>(tmp);

// dead trucks
  list<shared_ptr<SFAsset>> tmn;
   for(auto a : trucks) {
     if(a->IsAlive()) {
       tmn.push_back(a);
     }
   }
  trucks.clear();
  trucks = list<shared_ptr<SFAsset>>(tmn);

//--------------------------------------------------------------------------------
//Projectile

//vs Cars
  for(auto p : projectiles) {
		  for(auto c: cars){
			  if(p->CollidesWith(c)) {
				  p->HandleCollision();
				  c->HandleCollision();
				  score++;
				  std::cout <<"Score "<< score << std::endl;
			  }
		  }
  }
 //vs Trucks
for(auto p: projectiles){
	for(auto t:trucks){
		if(p->CollidesWith(t)) {
			p->HandleCollision();
			t->HandleCollision();
			score++;
			std::cout <<"Score "<< score << std::endl;
		}
	}
	for(auto t:trucks2){
			if(p->CollidesWith(t)) {
				p->HandleCollision();
				t->HandleCollision();
				score++;
				std::cout <<"Score "<< score << std::endl;
			}
		}

		}

//vs Trucks
for(auto p: projectiles){
	for(auto b:plaines){
		if(p->CollidesWith(b)) {
			p->HandleCollision();
			b->HandleCollision();
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


  //boss bullets
    list<shared_ptr<SFAsset> > tmk2;
    for(auto p : projectiles2) {
  		  if(p->IsAlive()) {
      	      tmk2.push_back(p);
      }
    }
    projectiles2.clear();
    projectiles2 = list<shared_ptr<SFAsset> >(tmk2);



// Projectiles Speed
  for(auto p: projectiles) {
    p->GoNorth();
  }




//--------------------------------------------------------------------------------
//Player

// Player & Cars collision

   for(auto a : cars) {
     if(player->CollidesWith(a)) {
       player->HandleCollision();
       a->HandleCollision();
	   if(lives > 0){
		   auto pos  = Point2(canvas_w/2,22);
		   player->SetPosition(pos);
		   lives--;
		   std::cout << "Oh no, you lost a life, try again" << " | Lifes: " << lives << std::endl;
	   }else{
		   player->SetNotAlive();
		   std::cout << "Game Over" << " | Final Score: " << score << std::endl;
	   }
   }
}

   for(auto a : cars2) {
     if(player->CollidesWith(a)) {
       player->HandleCollision();
       a->HandleCollision();
	   if(lives > 0){
		   auto pos  = Point2(canvas_w/2,22);
		   player->SetPosition(pos);
		   lives--;
		   std::cout << "Oh no, you lost a life, try again" << " | Lifes: " << lives << std::endl;
	   }else{
		   GameOver();
		   std::cout << "Game Over" << " | Final Score: " << score << std::endl;
	   }
   }
}


   for(auto a : trucks) {
	   if(player->CollidesWith(a)) {
		   player->HandleCollision();
		   a->HandleCollision();
		   if(lives  > 0){
			   auto pos  = Point2(canvas_w/2,22);
			   player->SetPosition(pos);
			   lives--;
			   std::cout << "Oh no, you lost a life, try again" << " | Lifes: " << lives << std::endl;
		   }else{
			   GameOver();
			   std::cout << "Game Over" << " | Final Score: " << score << std::endl;
		   }
	   }
   }

   for(auto b : trucks2) {
	   if(player->CollidesWith(b)) {
		   player->HandleCollision();
		   b->HandleCollision();
		   if(lives > 0){
			   auto pos  = Point2(canvas_w/2,22);
			   player->SetPosition(pos);
			   lives--;
			   std::cout << "Oh no, you lost a life, try again" << " | Lifes: " << lives << std::endl;
		   }else{
			   GameOver();
			   std::cout << "Game Over" << " | Final Score: " << score << std::endl;
		   }
	   }
   }

   for(auto b : plaines) {
	   if(player->CollidesWith(b)) {
		   player->HandleCollision();
		   b->HandleCollision();
		   if(lives > 0){
			   auto pos  = Point2(canvas_w/2,22);
			   player->SetPosition(pos);
			   lives--;
			   std::cout << "Oh no, you lost a life, try again" << " | Lifes: " << lives << std::endl;
		   }else{
			   GameOver();
			   std::cout << "Game Over" << " | Final Score: " << score << std::endl;
		   }
	   }
   }

//Player & Barrier
   if (player ->CollidesWith(topB)){ //collision
	   player->GoSouth();
	   std::cout << "Congratz, you won" << " | Score " << score << std::endl;
      }


   if (lives == 0){
       player->HandleCollision();
 boss->HandleCollision();
 topB->HandleCollision();
 rightB->HandleCollision();
 leftB->HandleCollision();
 background->HandleCollision();
 GameOver();
     }
}



void SFApp::OnRender() {
  SDL_RenderClear(sf_window->getRenderer());






background->OnRender();
  // draw the player const SDL_Rect &rect1, const SDL_Rect &rect2

 	    	  gameover->OnRender();

  for(auto p: projectiles) {
	  p->ProjectileMovement();
    if(p->IsAlive()) {
    	p->OnRender();}
  }

  for(auto p: projectiles2) {
	  p->ProjectileMovement2();
    if(p->IsAlive()) {
    	p->OnRender();}
  }

  for(auto a: cars) {
    if(a->IsAlive()) {
    	a->OnRender();
    }
  }

  for(auto a: cars2) {
      	a->OnRender();
    }


  for(auto a: trucks) {
    if(a->IsAlive()) {
    	a->OnRender();
    }
  }

  for(auto a: trucks2) {
    if(a->IsAlive()) {
    	a->OnRender();
    }
  }

  for(auto c: woods1) {
    c->OnRender();
  }

  for(auto c: woods2) {
    c->OnRender();
  }

  for(auto c: woods3) {
    c->OnRender();
  }

  for(auto c: coins) {
    c->OnRender();
  }

  for(auto c: plaines) {
	      c->OnRender();
    }
  if(player->IsAlive()) {
   player->OnRender();
 }
  if(boss->IsAlive()) {
   boss->OnRender();
 }

  if(leftB->IsAlive()) {
   leftB->OnRender();
 }

  if(rightB->IsAlive()) {
   rightB->OnRender();
 }
 //topB->OnRender();
 //leftB->OnRender();
 //rightB->OnRender();




  // Switch the off-screen buffer to be on-screen
  SDL_RenderPresent(sf_window->getRenderer());
}
void SFApp::FireProjectile() {
  auto pb = make_shared<SFAsset>(SFASSET_PROJECTILE, sf_window);
  auto v  = player->GetPosition();
  pb->SetPosition(v);
  projectiles.push_back(pb);
}

void SFApp::FireProjectile2() {
  auto pb = make_shared<SFAsset>(SFASSET_PROJECTILE, sf_window);
  auto v  = boss->GetPosition();
  pb->SetPosition(v);
  projectiles2.push_back(pb);
}

void SFApp::GameOver(){
 auto go_pos = Point2(350,500);
 gameover->SetPosition(go_pos);
}
