#ifndef _TEXT_H
#define _TEXT_H

#include <string>
#include "frame.h"
#include "texture.h"

class Text : public Entity {
private:
	int xMargin, yMargin;
	int charSpacing, lineSpacing;
	int start;      // index from text to start displaying text
	int fontW, fontH;
	int charW, charH;
	int w, h;
	GLuint font;
	std::string text;
public:
	Text();
	Text(GLuint tex, std::string font);
	void Draw();    // returns true if entire text was displayed, false if not

	void SetFont(GLuint texture) {font=texture;}
	void SetText(std::string msg) {text=msg;}
};

#endif