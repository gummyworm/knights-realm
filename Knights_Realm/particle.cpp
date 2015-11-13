#include "particle.h"

Emitter::Emitter(Node *par) : Entity() 
{
	parent=par;
	group=new ParticleGroup(LoadTexture("testplayer.png"));
	vel=1.0;
	dir=10.0 * PI / 180.0;

	min = 3;
	max = 7;

	rate=5;
	frameCount=0;	// initialize frame count

	lifespan = 200;
}

void Emitter::Emit(int density) 
{
	// TODO: seed rng, but really... who care's?
	for(int i=0; i < (rand() % density); i++) {
		// TODO: add randomness to x, y, dX, and dY
		Particle* p = new Particle(parent->GetX(), parent->GetY(), vel*cos(dir), vel*sin(dir), 10.0, 10.0, lifespan);
		group->Add(p);
	}
}

void Emitter::Emit() 
{
	// TODO: seed rng, but really... who care's?
		for(int i=0; i<(min + (rand()%(max-min))); i++) {
		// TODO: add randomness to x, y, dX, and dY
		Particle* p = new Particle(parent->GetX(), parent->GetY(), vel*cos(dir), vel*sin(dir), 100.0, 100.0, lifespan);
		group->Add(p);
	}
}

void Emitter::Update()
{
	if(frameCount % rate == 0) {
		this->Emit();
	}	
	frameCount++;
}

ParticleGroup::ParticleGroup(GLuint tex)
{
	// TODO: again... idk
	particles.clear();
	
	texture=tex;
}

void ParticleGroup::Update()
{
	int i=0;
	for(std::vector<Particle*>::iterator it=particles.begin(); it != particles.end(); it++) {
		(*it)->life--;
		if((*it)->life > 0) {
			(*it)->x += (*it)->dX;
			(*it)->y += (*it)->dY;
		}
		else {
			particles.erase(it);
		}
		i++;
	}
}

void ParticleGroup::Draw()
{
	int i=0;
	for(std::vector<Particle*>::iterator it=particles.begin(); it != particles.end(); it++, i++) {
		glPushMatrix();
		glTranslatef((*it)->x, (*it)->y, 0.0);
		RectTextured* r = new RectTextured((*it)->w, (*it)->h, texture);
		DrawRectTextured(r);	// TODO: lighter rendering... this is gross
		glPopMatrix();
	}
}