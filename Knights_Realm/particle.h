#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <vector>
#include "SDL_opengl.h"
#include "entity.h"
#include "node.h"
#include "texture.h"
#include "rect.h"
#include "draw.h"

class Particle {
public:
	float x, y;
	float dX, dY;
	float w, h;
	int life;
	Particle(float X=0.0, float Y=0.0, float DX=0.0, float DY=0.0, float W=10.0, float H=10.0, int L=60) {x=X; y=Y; dX=DX; dY=DY; w=W; h=H; life=L;}
};

class ParticleGroup : public Entity {
private:
	std::vector<Particle*> particles;
	GLuint texture;
public:
	ParticleGroup(GLuint tex=0);
	void Add(Particle* p) {particles.push_back(p);}
	void Update();

	/** draws the particles in this group.
	* although particle groups are (almost) always created and added to by an emitter, they are not drawn by the emitter.
	* instead they are put in the top level set of entities.  the reason for this is that particles must position themselves independent
	* of the emitter's node's position.
	*/
	void Draw();

	void GetParticles();
};

class Emitter : public Entity {
private:
	/** the parent entity to attach the emitter to.
	* the emitter's parent is used to position the emitter and determine the direction that it will emit particles.
	* the parent entity must therefore have x,y,z coordinates and a rotation value.
	*/
	Node* parent;

	/** the currently alive particles.
	* a reference to the group of particles that are emitted to by the emitter.
	*/
	ParticleGroup* group;

	/** the greatest possible lifespan of particles (in frames)
	*
	*/
	int lifespan;

	/** the greatest possible velocity of particles
	*
	*/
	float vel;

	/** the direction to emit the particles in. 
	* the angle (+ or -) from the rotation of the parent node to emit the particles.
	*/
	float dir;

	/** the rate at which new particles are emitted.
	* particles are emitted at the rate frameCount mod this number. if this value is 0, no particles are emitted.
	*/
	int rate;

	/** a frame counter kept to determine when it's time to emit more particles.
	*
	*/
	int frameCount;

	/** the minimum number of particles emitted each time particles are emitted.
	* 
	*/
	int min;

	/** the maximum number of particles emitted each time particles are emitted.
	*
	*/
	int max;

public:
	Emitter(Node *par);

	/** emit particles at the passed density.
	* emits particles from the emitter.  the density determines how many particles are produced.  a higher density results in more particles
	* being emitted than a lower density.
	*/
	void Emit(int density);

	/** emits particles using the internal min and max variables.
	* this is the function called by the Update function to emit particles as opposed to Emit(int density), which is for manually emitting
	* particles.
	*/
	void Emit();

	/** updates the associated particle group and emits particles as necessary.
	* moves all particles in the referenced particle group.  in addition, new particles are emitted at rate.
	*/
	void Update();

	/** select the std::set that the particle group will be put in.
	* this is generally going to be the top level set because the particles need to be independent of any other entity (in most cases).
	*/
	void SetParticleDest(GameEntity* dest) {dest->insert(group);}
};

#endif