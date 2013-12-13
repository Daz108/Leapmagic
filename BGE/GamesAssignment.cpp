/* GamesAssignment 
   Darragh Mulcahy
   C09449124*/

#include "GamesAssignment.h"
#include "VectorDrawer.h"
#include "Content.h"
#include "FountainEffect.h"

using namespace BGE;

GamesAssignment::GamesAssignment(void)
{
	width = 1000;
	height = 1000;
	
	fullscreen = false;
}

GamesAssignment::~GamesAssignment(void)
{
}


bool GamesAssignment::Initialise()
{
	//settings
	riftEnabled = false;
	fullscreen = false;


	//Adttach listner to controller
	Controller.addListener(Listener);

	shared_ptr<FountainEffect> centFountain = make_shared<FountainEffect>(500);
	centFountain->position.x = centFountain->position.y = 0;
	centFountain->position.y = 50;
	centFountain->diffuse = glm::vec3(250,50,5);

	Attach(centFountain);

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
	

	//Init Game
	Game::Initialise();
	camera->GetController()->position = glm::vec3(-2, 45, 120);
	return true;
}

void GamesAssignment::Update(float timeDelta)
{	

	Leap::Controller controller; 
	const Leap::Frame frame = controller.frame();
	const Leap::Hand hand = frame.hands()[0];

	if (!frame.hands().isEmpty()) {
		// Get the first hand
		const Leap::Hand hand = frame.hands()[0];
		  }
		  
		if(frame.hands().count() == 1){
			  fountains[1]->position.x = hand.palmPosition().x / 5;
			  fountains[1]->position.y = hand.palmPosition().y / 5;
			  fountains[1]->position.z = hand.palmPosition().z / 5;

			  
		}
		if(frame.hands().count() == 2){
				for(int j = 0; j <fountains.size(); j++){
				  fountains[j]->position.x = hand.palmPosition().x / 5;
				  fountains[j]->position.y = hand.palmPosition().y / 5;
				  fountains[j]->position.z = hand.palmPosition().z / 5;
				}
		}


		const Leap::FingerList fingers = hand.fingers();
		if (!fingers.isEmpty()) {
			for(int i = 0; i < fountains.size();i++){
				if(hand.fingers().count() < 2){
					fountains[i]->diffuse = glm::vec3(1,0,0);}
				else{
					fountains[i]->diffuse = glm::vec3(0,1,0);}
			}}

		 controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);

		 // Get gestures
		const Leap::GestureList gestures = frame.gestures();
		for (int g = 0; g < gestures.count(); ++g) {
		Leap::Gesture gesture = gestures[g];

		switch (gesture.type()) {
			case Leap::Gesture::TYPE_CIRCLE:
				  {
					 Game::Instance()->PrintText("Circle gesture type.");
					Leap::CircleGesture circle = gesture;
					if (circle.pointable().direction().angleTo(circle.normal()) <= Leap::PI/4) {
						// for clockwise movements
						fountains[8]->position.x += fountains[2]->position.x * 2;}
					else {//anticlockwise movements
						fountains[8]->position.x -= fountains[2]->position.x * 2;}
					// Calculate angle swept since last frame
					float sweptAngle = 0;
					if (circle.state() != Leap::Gesture::STATE_START) {
						 Leap::CircleGesture previousUpdate = Leap::CircleGesture(controller.frame(1).gesture(circle.id()));
						sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * Leap::PI;
						}
					break;
				 }
				case Leap::Gesture::TYPE_SWIPE:
				 {
					 Game::Instance()->PrintText("Swipe gesture type.");
				 Leap::SwipeGesture swipe = gesture;
	
				 break;
				}
	
			  default:
				Game::Instance()->PrintText("Unknown/No gesture type.");
				break;
			}
		}




	
	Game::Update(timeDelta);
}
