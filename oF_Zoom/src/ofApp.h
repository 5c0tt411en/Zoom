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
		int realW = 3750, realH = 23500;
    
    float time = 0;
    float timeStamp = 0;
    enum State {
        IDLE,
        RUN,
        FINISHED
    };
    State st = IDLE;
    
    //setting
    const float thre = 840;
    const float loopThre = 5;
    const int exitHour = 18;
    const float threOpenApp = 4;
    bool openApp = true;
    bool homingComp = false;
    
    //relay settings
    ofSerial serialRelay;
    string portRelay = "/dev/tty.usbserial-AI02RJCG";
    int baudRateRelay = 9600;
    int relayState = true;
    
    private:
};
