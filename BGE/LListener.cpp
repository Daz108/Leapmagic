/* GamesAssignment 
   Darragh Mulcahy
   C09449124*/

#include "LListener.h"


void LListener::onInit(const Leap::Controller& controller) {
  std::cout << "Leap Initialized" << std::endl;
}

void LListener::onConnect(const Leap::Controller& controller) {
  std::cout << "Connected" << std::endl;
  controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
  controller.enableGesture(Leap::Gesture::TYPE_SWIPE);
}

void LListener::onDisconnect(const Leap::Controller& controller) {
  //Note: not dispatched when running in a debugger.
  std::cout << "Disconnected" << std::endl;
}

void LListener::onExit(const Leap::Controller& controller) {
  std::cout << "Leap Exited" << std::endl;
}

void LListener::onFrame(const Leap::Controller& controller) {
  // Get the most recent frame and report some basic information
	// Get the first hand
  const Leap::Frame frame = controller.frame();

	  if (!frame.hands().isEmpty()) {
		// Get the first hand
		const Leap::Hand hand = frame.hands()[0];

		// Check if the hand has any fingers
		const Leap::FingerList fingers = hand.fingers();
		if (!fingers.isEmpty()) {
		  // Calculate the hand's average finger tip position
		  Leap::Vector avgPos;
		  for (int i = 0; i < fingers.count(); ++i) {
			avgPos += fingers[i].tipPosition();
		  }
		  avgPos /= (float)fingers.count();
		
    }

    
    const Leap::Vector normal = hand.palmNormal();
    const Leap::Vector direction = hand.direction();

  }

  // Get gestures
  const Leap::GestureList gestures = frame.gestures();
  for (int g = 0; g < gestures.count(); ++g) {
    Leap::Gesture gesture = gestures[g];

    switch (gesture.type()) {
	//Circle gesture case
	case Leap::Gesture::TYPE_CIRCLE:
      {
        Leap::CircleGesture circle = gesture;
     
        if (circle.pointable().direction().angleTo(circle.normal()) <= Leap::PI/4) {
          
        } else {
          
        }

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
        Leap::SwipeGesture swipe = gesture;
	
        break;
      }
	
      default:
        std::cout << "Unknown/No gesture type." << std::endl;
        break;
    }
  }

  if (!frame.hands().isEmpty() || !gestures.isEmpty()) {
    //std::cout << std::endl;
  }
}

void LListener::onFocusGained(const Leap::Controller& controller) {
  std::cout << "Focus Gained" << std::endl;
}

void LListener::onFocusLost(const Leap::Controller& controller) {
  std::cout << "Focus Lost" << std::endl;
}