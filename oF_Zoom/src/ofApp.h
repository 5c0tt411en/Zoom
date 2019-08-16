#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxGrbl.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void sendMessage(string _msg);

		// grbl
		ofxGrbl grbl;
		void UpDownHandler(bool &_isDown); // Event Handler

		ofTrueTypeFont _font;
		int realW = 2700, realH = 3400;
    
    float time = 0;
    float timeStamp = 0;
    enum State {
        IDLE,
        RUN,
        FINISHED
    };
    State st = IDLE;
    
    //setting
	const float lightON = 445; // light on time
    const float thre = 40; // end seconds 
    const float loopThre = 10; // loop interval
    const int exitHour = 19; // exit hour
	const int killAppMinute = 15; // kill app minute
    const float threOpenApp = 4; // offset seconds since open app
    bool openApp = true;
    bool homingComp = false;
    
    //relay settings
    ofSerial serialRelay;
    string portRelay = "COM12";
    int baudRateRelay = 9600;
    int relayState = true;
    
    private:
};
