#include <iostream>
#include "map.h"

using namespace std;

static const string b64Chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

void Map::Load(string mapName)
{
    // load in the xml file
    TiXmlDocument doc(mapName.c_str());
    if(!doc.LoadFile()) {
        cerr << "could not load XML map file " << mapName << endl;
    }
    TiXmlHandle hDoc(&doc);
    TiXmlElement* pElem;
    TiXmlHandle hRoot(0);
    
    pElem=hDoc.FirstChildElement().Element();
    if(!pElem) {
        cerr << "XML map file " << mapName << " has an invalid root" << endl;
    }
    mapName=pElem->Value();
    hRoot=TiXmlHandle(pElem);
    
    // read the map attributes from the root element (<map>)
    pElem->Attribute("width", &mapW);
    pElem->Attribute("height", &mapH);
    pElem->Attribute("tilewidth", &tileW);
    pElem->Attribute("tileheight", &tileH);
    
    // read the tileset attributes
    // TODO: doesn't use attributes: tilewidth/tileheight (map provides them... use constant for all tilesets is fine I guess???)
    TiXmlElement* pTileNode=hRoot.FirstChild("tileset").Element();
    pTileNode->Attribute("firstgid", &gid0);
    pTileNode->Attribute("margin", &tileMargin);
    pTileNode->Attribute("spacing", &tileSpacing);
    
    // read the image properties
    TiXmlHandle hTileset=TiXmlHandle(pTileNode);
    TiXmlElement *pImageNode=hTileset.FirstChild("image").Element();
    tilesheetTex=LoadTexture(pImageNode->Attribute("source"));

    // read all the layers in
    TiXmlElement* lElem;
    TiXmlElement* lChild;
    string dataToDecode;
    int i, layer;

    for(lElem=hRoot.FirstChild("layer").Element(), i=0; lElem; lElem=lElem->NextSiblingElement("layer"), i++) {
        // the layer to write the decoded data to
        layer=i;
        // check if the layer has any properties
        if(lElem->FirstChildElement("properties")) {
            TiXmlElement* propElem=lElem->FirstChildElement("properties")->FirstChildElement("property"); // get the first properties element
            for(propElem; propElem; propElem=propElem->NextSiblingElement("property")) {
                string propName=propElem->Attribute("name");
                // check for the "type" property
                if(propName.compare("type") == 0) {
                    string layerType=propElem->Attribute("value");
                    cout<<"value: "<<layerType;
                    if(layerType=="collision")  {
                        layer=COLLISION_LAYER;
                        cout<<"collision layer found";
                    }
                    // TODO: check for other values as necessary
                // TODO: check for other properties as necessary
                }
            }
        }
        // write the layer
        // TODO: doesn't read attributes from <layer ... >  Mostly because I don't think they're needed. assuming all layers are the same size.
        lChild=lElem->FirstChildElement("data");
        dataToDecode=lChild->GetText();
        DecodeB64(dataToDecode.c_str(), layer);
    }
    numLayers=i;
}

void Map::Render(void)
{
    int i, j, l;
    int gid;
    GLfloat tx, ty, tw, th;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tilesheetTex);


    tw=1.0/(tilesheetW/tileW);
    th=1.0/(tilesheetH/tileH);

    // draw the map
    glPushMatrix();
    for(l=0; l<numLayers; l++) {
        glTranslatef(0, 0, 1);
        for(i=0; i<mapH; i++) {
            for(j=0; j<mapW; j++) {
                gid=tileMap[l][i*mapW+j];
                if(gid == 0)
                    continue;
                gid -= gid0;

                tx=(GLfloat(tileMargin + tileSpacing + tileW) * GLfloat(gid%(tilesheetW/tileW)))/(tilesheetW);
                ty=(GLfloat(tileMargin + tileSpacing + tileH) * GLfloat(gid/(tilesheetH/tileH)))/(tilesheetH);

                glColor4f(1.0f,1.0f,1.0f,1.0f);
                glBegin(GL_QUADS);
                    glTexCoord2f(tx, ty);
                    glVertex2i(j*tileW, i*tileH);

                    glTexCoord2f(tx+tw, ty);
                    glVertex2i(j*tileW+tileW, i*tileH);
                
                    glTexCoord2f(tx+tw, ty+th);
                    glVertex2i(j*tileW+tileW, i*tileH+tileH);

                    glTexCoord2f(tx, ty+th);
                    glVertex2i(j*tileW, i*tileH+tileH);
                glEnd();
            }
        }
    }
    glPopMatrix();
}

void Map::Update()
{
}

void Map::DecodeB64(const char data[], int layer)
{
    int i, j;
    int code;
    unsigned char *result = new unsigned char[strlen(data)];        // TODO: size should be based on data's size

    for(i=0, j=0; i<strlen(data); i++) {
        if(data[i] == '=')
            break;
        code=b64Chars.find(data[i]);
        if(code == -1) {
            break;
        }
        switch(i%4) {
            case 0:
                result[j]=char(code<<2);
                break;
            case 1:
                result[j++] |= char((code>>4) & 0x03);
                result[j]=char(code << 4);
                break;
            case 2:
                result[j++] |= char((code>>2) & 0x0f);
                result[j]=char(code<<6);
                break;
            case 3:
                result[j++] |= char(code & 0x3f);
                break;
        }
    }
    for(i=0; i<j; i+=4) {
        tileMap[layer][i/4] = result[i] | (result[i+1] << 8) | (result[i+2] << 16) | (result[i+3] << 24);
    }
}

bool Map::IsMoveLegal(int x, int y, int w, int h)
{
    int i, j;
    for(i=0; i<mapW*mapH; i++) {
        if  (
            ((x+w) > (i%mapW*tileW)) && 
            (x < (i%mapW*tileW + tileW)) && 
            ((y+h) > (i/mapH*tileH)) && 
            (y < (i/mapH*tileH + tileH)) &&
            (tileMap[COLLISION_LAYER][i] != 0)
            )
            return false;
    }
    return true;
}

float Map::LeastCostEstimate(void* stateStart, void* stateEnd)
{
	// simply return the x difference + the y difference
	// TODO: maybe make more complex
	return ((int)stateStart%mapW)-((int)stateEnd%mapW) + ((int)stateStart/mapW)-((int)stateStart/mapW);
}

void Map::AdjacentCost(void* state, std::vector<StateCost> *adjacent)
{
	// TODO: should be much more advanced (account for different terrains, etc.)
	vector<StateCost> adj;
	for(int i=-1; i<2; i++) {
		for(int j=-1; j<2; j++) {
			StateCost a;
			if (tileMap[COLLISION_LAYER] != 0) {
				a.cost=1;
				adj.insert(adj.end(), a);
			}
			else {
				a.cost=0;
				adj.insert(adj.end(), a);
			}
		}
	}
}