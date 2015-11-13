#include "sprite.h"

//Sprite::Sprite(int W, int H, GLuint tex, int cX, int cY, int cW, int cH) : Entity()
//{
//    rect=new RectTextured(W, H, tex);
//	restoreRect=new RectTextured(W, H, tex);
//
//    sSheetW=512;
//    sSheetH=512;
//
//    colX=cX;
//    colY=cY;
//    colW=cW;
//    colH=cH;
//}
Sprite::Sprite(std::string filename)
{
	animMgr=new Animation();
	Load(filename);
    sSheetW=512;
    sSheetH=512;	
}

void Sprite::Draw()
{
    rect->FindClip(animMgr->GetFrame(), sSheetW, sSheetH, rect->GetW(), rect->GetH());
    rect->Draw();
}

void Sprite::Update() {
	animMgr->Update();
    rect->FindClip(animMgr->GetFrame(), sSheetW, sSheetH, rect->GetW(), rect->GetH());
}

// TODO: node's should revert!!! sprites, rects, etc don't 
//void Sprite::Revert() {
//    rect->SetX(restoreRect->GetX());
//    rect->SetY(restoreRect->GetY());
//}

void Sprite::Load(std::string filename)
{
	// check that we have a filename
	if(filename.empty()) {
		return;	// if not, nothing can be done.
	}

	// load in the xml file
    TiXmlDocument doc(filename.c_str());
    if(!doc.LoadFile()) {
        std::cerr << "could not load XML sprite file " << filename << std::endl;
		return;
    }
    TiXmlHandle hDoc(&doc);
    TiXmlElement* pElem;
    TiXmlHandle hRoot(0);
    
    pElem=hDoc.FirstChildElement().Element();
    if(!pElem) {
        std::cerr << "XML sprite file " << filename << " has an invalid root" << std::endl;
    }

	int w, h;
	GLuint tex;
	// set root attributes
	tex = LoadTexture(pElem->Attribute("spritesheet"));
	pElem->Attribute("w", &w);
	pElem->Attribute("h", &h);
	rect = new RectTextured(w, h, tex);
	restoreRect=new RectTextured(w, h, tex);

	hRoot=TiXmlHandle(pElem);

    TiXmlElement* lElem;
    TiXmlElement* lChild;
	int i;
	// load the animations
    for(lElem=hRoot.FirstChild("animation").Element(), i=0; lElem; lElem=lElem->NextSiblingElement("animation"), i++) {
		int start, stop, speed;
		std::string name = lElem->Attribute("name");
		lElem->Attribute("start", &start);
		lElem->Attribute("stop", &stop);
		lElem->Attribute("speed", &speed);
		std::cout << "added animation:  " << name << " framestart: " << start << " framestop: " << stop << " framespeed: " << speed << std::endl;
		animMgr->AddAnimation(name, start, stop, speed);
	}
	// load the script (if any) TODO: might fail epicly if there's no script file
	cout << "trying to make script " << endl;
	script=new Script(hRoot.FirstChild("script").Element()->Attribute("name"));
}