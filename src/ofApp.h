#pragma once

#include "ofMain.h"
#include <iostream>
static float align_val=1, coh_val=1, sep_val=1;

struct Boid
{
	ofVec2f pos;
	ofVec2f vel = {ofRandomf(), ofRandomf()};

	ofVec2f acc;

	float max_force = 0.8f;
	float max_speed = 5.f;

	bool drawn = false;
	Boid(ofVec2f _pos)
	{
		this->pos = _pos;
		this->vel.normalize();
		// this->vel /= ofRandom(16.f, 32.f);
	}
	void draw()
	{
		ofSetColor(255, 130, 0);
		ofFill();
		ofDrawCircle(pos.x, pos.y, 4);
	}
	void draw(std::vector<Boid>& boids)
	{
		
		for (auto &b : boids)
		{
			if (*this != b and this->pos.distance(b.pos) < 50.f
			    and not drawn)
			{
				ofSetColor(255, 130, 0);
				ofFill();
				ofDrawCircle(b.pos.x, b.pos.y, 4);
			}
		}
	}
	void update()
	{

		pos += vel;
		vel += acc;
		this->vel.limit(this->max_speed);
		auto width = static_cast<float>(ofGetWidth());
		auto height = static_cast<float>(ofGetHeight());
		this->acc *= 0;

		if (this->pos.x < 0)
		{
			this->pos.x = width;
		}
		if(this->pos.x > width)
		{
			this->pos.x = 0;
		}
		if(this->pos.y < 0 )
		{
			this->pos.y = height;
		}
		if(this->pos.y > height)
		{
			this->pos.y = 0;
		}
	}
	bool operator==(const Boid &other)
	{
		return std::fabs(this->pos.x - other.pos.x) <=
				   std::numeric_limits<float>::epsilon() &&
			   std::fabs(this->pos.y - other.pos.y) <=
				   std::numeric_limits<float>::epsilon();
	}
	bool operator!=(const Boid &other)
	{
		return not((*this) == other);
	}
	auto cohesion(std::vector<Boid> &boids)
	{	auto perc_rad = 100.f;
		ofVec2f steering(0, 0);
		float total = 0.f;
		for (auto &b : boids)
		{
			if (*this != b and this->pos.distance(b.pos) < perc_rad)
			{
				steering += b.pos;
				++total;
			}
		}
		if (total> 0)
		{
			steering /= total;;
			steering -= this->pos;
			steering = steering.getNormalized() * this->max_speed;
			steering -= this->vel;
			steering.limit(this->max_force);
		}
		return steering;
	}
	auto align(std::vector<Boid> &boids)
	{
		auto perc_rad = 100.f;
		ofVec2f steering(0, 0);
		float total = 0.f;
		for (auto &b : boids)
		{
			if (*this != b and this->pos.distance(b.pos) < perc_rad)
			{
				steering += b.vel;
				++total;
			}
		}
		if (total)
		{
			steering /= total;
			steering = steering.getNormalized() * this->max_speed;
			steering -= this->vel;
			steering.limit(this->max_force);
		}
		return steering;
	}
	auto separation(std::vector<Boid> &boids)
	{	auto perc_rad = 50.f;
		ofVec2f steering(0, 0);
		float total = 0.f;
		for (auto &b : boids)
		{
			auto d = this->pos.distance(b.pos);
			if (*this != b and d < perc_rad)
			{
				auto diff = this->pos - b.pos;
				diff /= d;
				steering += diff;
				++total;
			}
		}
		if (total> 0)
		{
			steering /= total;;
			steering = steering.getNormalized() * this->max_speed;
			steering -= this->vel;
			steering.limit(this->max_force);
		}
		return steering;
	}
	auto flock(std::vector<Boid> &boids)
	{
		auto ali = this->align(boids);
		auto coh = this->cohesion(boids);
		auto sep = this->separation(boids);
		ali *= align_val;
		coh *= coh_val;
		sep *= sep_val;
		this->acc += ali;
		this->acc += coh;
		this->acc += sep;
	}
};

class ofApp : public ofBaseApp
{

  public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	std::vector<Boid> boids;
	size_t num_boids = 800;
};
