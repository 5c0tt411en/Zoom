#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowPosition(0, 30);
	ofSetWindowTitle("Zoom v 0.1.1");
	ofEnableAlphaBlending();
	ofSetFrameRate(60);

	_font.load("./GUI/SourceCodePro-Regular.ttf", 10);

	grbl.setup(realW, realH);
	ofAddListener(grbl.UpDownEvent, this, &ofApp::UpDownHandler);
    
    //relay sync
    serialRelay.getDeviceList();
    serialRelay.listDevices();
    serialRelay.setup(portRelay, baudRateRelay);
}

//--------------------------------------------------------------
void ofApp::update(){
    time = ofGetElapsedTimef() - timeStamp;

	grbl.update();

    // homing when app opened
    if (time >= threOpenApp && openApp) {
        grbl.killAlarmLock();
        grbl.homing();
        openApp = false;
    }
    
    // homing when over limits
    if (grbl.homingFlag && grbl.status == "Alarm") {
        grbl.homing();
        grbl.homingFlag = false;
    }
    
    switch (grbl.opm) {
        case ofxGrbl::ONCE:
           
            break;
        case ofxGrbl::LOOP:
            switch (st) {
                case IDLE:
                    //Run data when open app
                    if (grbl.status == "Idle") {
						//light off 
                        sendMessage(ofToString(int(4)));
						//ON relay switch
                        sendMessage(ofToString(int(1)));
                        grbl.loadFromFile("gcode/scopitone2019.gcode");
                        st = RUN;
                        timeStamp = ofGetElapsedTimef();
						time = ofGetElapsedTimef() - timeStamp;
                    }
                    if (grbl.status == "Run") {
                        st = RUN;
                        timeStamp = ofGetElapsedTimef();
						time = ofGetElapsedTimef() - timeStamp;
                    }
                    break;
                case RUN:
                    if (time >= lightON) {
						//light on
                        sendMessage(ofToString(int(3)));
                    }
                    if (time >= thre && grbl.status == "Idle") {
						//OFF relay switch
                        sendMessage(ofToString(int(2)));
                        st = FINISHED;
                        timeStamp = ofGetElapsedTimef();
						time = ofGetElapsedTimef() - timeStamp;
                    }
                    break;
                case FINISHED:
                    if (ofGetHours() < exitHour && time >= loopThre) {
						//light off 
                        sendMessage(ofToString(int(4)));
						//ON relay switch
                        sendMessage(ofToString(int(1)));
                        grbl.repeatFile(grbl.loadedPath);
                        st = RUN;
                        timeStamp = ofGetElapsedTimef();
						time = ofGetElapsedTimef() - timeStamp;
                    }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(255);
	ofBackground(0);
	int px = 300, py = ofGetHeight() - 10, h = ofGetHeight() - 20, w = h * realW / realH;
	grbl.draw(px, py, w, -h);
    
    _font.drawString(grbl.info(), 810, 25);
    string s = "[time(sec.)] " + ofToString(time) + '\n';
    s += "[status(0:IDLE, 1:RUN, 2:FINISHED)] " +  ofToString(st) + '\n';
    s += "[loop thre seconds(sec.)] " +  ofToString(thre) + '\n';
    s += "[loop interval(sec.)] " +  ofToString(loopThre) + '\n';
    s += "[exit hour] " +  ofToString(exitHour) + '\n';
    _font.drawString(s, 860, 100);
}

//--------------------------------------------------------------
void ofApp::exit() {
	grbl.close();
    sendMessage(ofToString(int(2)));
    serialRelay.close();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	string _message = "";
	switch (key) {
	case OF_KEY_RIGHT:
		grbl.moveRight(10);
		break;
	case OF_KEY_LEFT:
		grbl.moveLeft(10);
		break;
	case OF_KEY_UP:
		grbl.moveUp(10);
		break;
	case OF_KEY_DOWN:
		grbl.moveDown(10);
		break;
	case OF_KEY_RETURN:
		grbl.toggleVisible();
		break;
	case OF_KEY_DEL:
	case OF_KEY_BACKSPACE:
		if (!grbl.gui->isVisible()) grbl.resetStrokes();
		break;
	case OF_KEY_HOME:
		grbl.home();
		break;
	case ' ':
		grbl.isDrawMode = !grbl.isDrawMode;
		break;
	case 'f':
	case 'F':
		ofToggleFullscreen();
		break;
	}
}

void ofApp::sendMessage(string _msg) {
//    if (direct) {
//        if (isConnect) {
            if (_msg != "") {
//                string _message = _msg + "\n";
//                unsigned char* writeByte = (unsigned char*)_message.c_str();
                serialRelay.writeByte(char(ofToInt(_msg)));
                //sentCount++;
                cout << "sendMessage( " << _msg << " )" << endl;
            }
            else {
                cout << "sendMessage() : Message is empty." << endl;
            }
//        }
//        else {
//            cout << "[ ofxGrbl ] sendMessage() : Serial is not connected." << endl;
//        }
//    }
//    else {
//        if (_msg != "") {
//            string _message = _msg;
//            sendQueList.push_back(_message);
//        }
//    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	grbl.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	grbl.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	grbl.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	grbl.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	grbl.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	grbl.dragEvent(dragInfo);
}

//--------------------------------------------------------------
void ofApp::UpDownHandler(bool &_isDown) {
	if (_isDown) {
		cout << "[ GrblManager ] DOWN" << endl;
	}
	else {
		cout << "[ GrblManager ] UP" << endl;
	}
	
}
