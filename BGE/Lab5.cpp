#include "Lab5.h"
#include "leap.h"
#include "Content.h"
#include "VectorDrawer.h"
#include "LazerBeam.h"
#include "FountainEffect.h"

using namespace BGE;
using namespace Leap;


Lab5::Lab5(void)
{
	elapsed = 10000;
}

Lab5::~Lab5(void)
{
}


bool Lab5::Initialise()
{

	riftEnabled = false;
	fullscreen = false;
	width = 800;
	height = 600;
	
	// 500 in the constructor indicates the number of particles in the effect. 
	// You may need to compile in release mode or reduce the number of particles to get an acceptable framerate
	shared_ptr<FountainEffect> centFountain = make_shared<FountainEffect>(500);
	centFountain->position.x = centFountain->position.y = 0;
	centFountain->position.y = FOUNTAIN_HEIGHT;
	centFountain->diffuse = glm::vec3(1,1,0);



	Attach(centFountain);

	// make a circle of fountains
	
	
	fountainTheta = 0.0f; 
	for (int i = 0 ; i < NUM_FOUNTAINS ; i ++)
	{
		fountainTheta = ((glm::pi<float>() * 2.0f) / NUM_FOUNTAINS) * i;
		shared_ptr<FountainEffect> fountain = make_shared<FountainEffect>(500);
		if (i % 2 == 0)
		{
			fountain->diffuse = glm::vec3(1,0,0);
		}
		else
		{
			fountain->diffuse = glm::vec3(0,1,0);
		}
		
		fountain->position.x = glm::sin(fountainTheta) * FOUNTAIN_RADIUS;
		fountain->position.z = - glm::cos(fountainTheta) * FOUNTAIN_RADIUS;
		fountain->position.y = FOUNTAIN_HEIGHT;
		fountains.push_back(fountain);
		Attach(fountain);
	}
	fountainTheta = 0.0f;

	bool circle = false;


	
	Game::Initialise();

	camera->GetController()->position = glm::vec3(-2, 45, 120);
	return true;
}

void Lab5::Update(float timeDelta)
{	
	Leap::Controller controller; 
	const Frame frame = controller.frame(); 
	const Hand hand = frame.hands()[0]; 
	const FingerList fingers = hand.fingers();

	if (!frame.hands().isEmpty()) { //your code for manipulating an object here 
		for (int i = 0 ; i < fountains.size() ; i ++)
		{/*
			if(frame.hands().count() == 1){fountains[i % 2 == 0]->position.y = FOUNTAIN_HEIGHT + (glm::sin(fountainTheta) * FOUNTAIN_HEIGHT);}
			else{fountains[i]->position.y = FOUNTAIN_HEIGHT - (glm::sin(fountainTheta) * FOUNTAIN_HEIGHT);}
			*/
			
			
				
				
				

		  if (fingers.count() > 5 || keyState[SDL_SCANCODE_UP]){
			  fountains[i]->position.y = FOUNTAIN_HEIGHT + (glm::sin(fountainTheta) * FOUNTAIN_HEIGHT);;
	  
		  }
	  
	}
	
	
	
	
	
	}
	
	for (int i = 0 ; i < fountains.size() ; i ++)
	{
		if (i % 2 == 0)
		{
			fountains[i]->position.y = FOUNTAIN_HEIGHT + (glm::sin(fountainTheta) * FOUNTAIN_HEIGHT);
		}
		else
		{
			fountains[i]->position.y = FOUNTAIN_HEIGHT - (glm::sin(fountainTheta) * FOUNTAIN_HEIGHT);
		}
		
	}
	fountainTheta += timeDelta;
	if (fountainTheta >= glm::pi<float>() * 2.0f)
	{
		fountainTheta = 0.0f;
	}

	

	
	Game::Update(timeDelta);

	float theta = 0.0f;
}



