#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{

    ofSetFrameRate(60);
    for (auto i = 0ul; i < num_boids; ++i)
    {
        boids.emplace_back(Boid({ofGetWidth() / 2.f + ofRandom(-500.f, 500.f),
                                 ofGetHeight() / 2.f + ofRandom(-500.f, 500.f)}));
    }
}

//--------------------------------------------------------------
void ofApp::update()
{

    for (auto &boid : boids)
    {
        boid.flock(boids);
    }
    for(auto& boid :boids)
    {
        boid.update();
    }
}


//--------------------------------------------------------------
void ofApp::draw()
{
    // ofSetColor(255, 130, 0);
    // ofFill();
    // ofDrawCircle(300,300,20);

    // ofDrawLine(a,b);
    for (auto &boid : boids)
    {
        boid.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

    switch (key)
    {
    case 'a':
        align_val += 0.05f;
        break;
    case 'z':
        align_val -= 0.05f;
        align_val = std::max(align_val,0.f);
        break;
    case 's':
        coh_val += 0.05f;
        break;
    case 'x':
        coh_val -= 0.05f;
        coh_val = std::max(coh_val,0.f);
        break;
    case 'd':
        sep_val += 0.05f;
        break;
    case 'c':
        sep_val -= 0.05f;
        sep_val = std::max(sep_val,0.f);
        break;
    }
    std::cout<<"Ali: " <<align_val <<" Coh: "<<coh_val <<" Sep: "<<sep_val<<'\n';
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
