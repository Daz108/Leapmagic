/* GamesAssignment 
   Darragh Mulcahy
   C09449124 */

#pragma once
#include "Game.h"
#include "GameComponent.h"
#include "Leap.h"
#include "LListener.h"
#include "Game.h"
#include "GameComponent.h"
#include "FountainEffect.h"


#define NUM_FOUNTAINS 20
#define FOUNTAIN_RADIUS 40.0f
#define FOUNTAIN_HEIGHT 10.0f

using namespace std;

namespace BGE
{
	class GamesAssignment :
		public Game
	{

	public:
		GamesAssignment(void);
		~GamesAssignment(void);
		
		bool Initialise();
		void Update(float timeDelta);
		

		float elapsed;
		vector<shared_ptr<FountainEffect>> fountains;
		float fountainTheta;
		
		Leap::Controller Controller;
		Leap::Listener Listener;
	};
}