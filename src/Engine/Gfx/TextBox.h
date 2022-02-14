/* Copyright (C) Dante Treglia II, 2000. 
 */
#ifndef __TEXTBOX_H__
#define __TEXTBOX_H__


typedef struct {unsigned char r, g, b, a;} COLOR;;

#define SET_COLOR(c, rIn, gIn, bIn, aIn) \
	c.r = rIn; \
	c.g = gIn; \
	c.b = bIn; \
	c.a = aIn


#define MAX_STR 16384

#define TEXT_NONE 0x00
#define TEXT_DRAW_BOX 0x04
#define TEXT_DRAW_SPACES 0x02
#define TEXT_WRAP_SPACES 0x08
#define TEXT_DRAW_BACKGROUND 0x01


class TextBox 
{
public:
	TextBox(int boxL, int boxR, int boxT, int boxB);
	//~TextBox() {free(buffer);}

private:
	// Bounding Box
	int boxL;
	int boxR;
	int boxT;
	int boxB;

	// Text Buffers
	char * buffer;
	char * drawBufferPtr;

	// Info
	int pageLineCnt;
	int scrollCnt;
	int currX;
	int currY;
	COLOR color;

public:
	unsigned int mode;

public:
	void Begin();
	void End();
	void DrawStr(int x, int y, char* string);
	void Draw();
	void Printf(char* fmt, ...);
	void Clear() {buffer[0] = '\0';};
	void SetColor(COLOR colorIn) {color = colorIn;};
	void SetMode(unsigned int modeIn) {mode = modeIn;};
	void PageUp() {scrollCnt += pageLineCnt;};
	void PageDown() {scrollCnt -= pageLineCnt; if (scrollCnt < 0) scrollCnt = 0;};
	void PageReset() {scrollCnt = 0;};

private:
	void Paginate();	
	void DrawStr(int x, int y, int maxFlag, int maxY, char* string);
	void DrawBoundingBox();
	void FormatStrCat(char * str);


public:
    //---------------------------------------------------------------------------
    //---------------------------------------------------------------------------
    // The text texture only needs to be initialized once
    static unsigned int fontID;
    // Forward definition
    static const unsigned char fontData[];

    static const COLOR  BLACK;
    static const COLOR  GREY;
    static const COLOR  GREEN;
    static const COLOR  WHITE;
	static const COLOR  YELLOW;
    static const COLOR  BLUE;
    static const COLOR  RED;
    static const COLOR  MAGENTA;
    static const COLOR  CYAN;
};

#endif 
