/*************
 
 speed project by Memo Akten. http://www.memo.tv
 build against openFrameworks pre-007, stable master as of 15/07/2011 
 https://github.com/openframeworks/openFrameworks
 
 
 INSTALL ON APPLE STORES AS YOU SEE FIT. IT'S PERFECTLY LEGAL (don't quote me on that)

 context:
 http://fffff.at/people-staring-at-computers/
 http://eyeteeth.blogspot.com/2011/07/feds-visit-artist-behind-people-staring.html
 http://peoplestaringatcomputers.tumblr.com/
 http://en.wikipedia.org/wiki/People_Staring_at_Computers
 http://www.bbc.co.uk/news/technology-14080438

 ****************/

#include "testApp.h"

#include "ofxOpenCv.h"

ofVideoGrabber          vidGrabber;
ofxCvColorImage			colorImg;
ofxCvGrayscaleImage 	greyImage;
ofxCvGrayscaleImage 	greyImageSmall;
ofxCvHaarFinder         haarFinder;

ofImage                 img;


//--------------------------------------------------------------
void testApp::setup(){
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(640, 480);
    
    colorImg.allocate(vidGrabber.getWidth(), vidGrabber.getHeight());
    greyImage.allocate(vidGrabber.getWidth(), vidGrabber.getHeight());
    greyImageSmall.allocate(160, 120);

    haarFinder.setup("haarcascade_frontalface_alt2.xml");
    
    img.loadImage("stevejobs.png");
    img.setAnchorPercent(0.5, 0.5);
                    
    ofEnableAlphaBlending();
}


//--------------------------------------------------------------
void testApp::update(){

    vidGrabber.grabFrame();
    if(vidGrabber.isFrameNew()) {
        colorImg.setFromPixels(vidGrabber.getPixels(), vidGrabber.getWidth(), vidGrabber.getHeight());
        colorImg.mirror(false, true);

        greyImage = colorImg;
        
        greyImageSmall.scaleIntoMe(greyImage);
        
        haarFinder.findHaarObjects(greyImageSmall);
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255, 255, 255);
    colorImg.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    glPushMatrix();
    glScalef(ofGetWidth() / (float)greyImageSmall.getWidth(), ofGetHeight() / (float)greyImageSmall.getHeight(), 1);
//    haarTracker.draw(0, 0);
    ofNoFill();
	for(int i = 0; i < haarFinder.blobs.size(); i++) {
		ofRectangle cur = haarFinder.blobs[i].boundingRect;
//		ofRect(cur.x, cur.y, cur.width, cur.height);
        int iw = cur.width * 1.2;
        img.draw(haarFinder.blobs[i].centroid, iw, iw * img.getHeight() / img.getWidth());
	}

    glPopMatrix();
}


//--------------------------------------------------------------
void testApp::keyPressed(int key) {
    ofToggleFullscreen();
}
