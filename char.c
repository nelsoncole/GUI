/*
 * File: char.c
 *
 * Descrição:
 *     Constrói caractere no buffer dedicado.
 *  
 * 
 * Sirius OS Versão 2.0, 2017-2018. (Nelson Cole)
 */

#include <io.h>

#define FONT_ROM_BIOS 0x000FFA6E
#define FONT_SIZE_X 8
#define FONT_SIZE_Y 8

static char charDefault = 0;

typedef struct tagCHAR {

	unsigned long xStart;
	unsigned long yStart;
	unsigned long xEnd;
	unsigned long yEnd;
	unsigned long xCursor;
	unsigned long yCursor;
	unsigned long fSizeX;
	unsigned long fSizeY;
	uint32_t *fBuffer;

}__attribute__ ((packed)) CHAR; 

extern GUI *g;
CHAR gCHAR = { 	.xStart 	=0, 
		.yStart 	=0,  
		.xEnd 		= 1, 
		.yEnd 		= 0,
		.xCursor 	= 0,
		.yCursor 	= 0,
		.fSizeX 	= FONT_SIZE_X, 
		.fSizeY 	= FONT_SIZE_X,
		.fBuffer 	= (uint32_t*) FONT_ROM_BIOS, //Font 8x8, ROM BIOS
};


// Escreve um caracter no buffer dedicado
int CHARBuilt( 	unsigned long c,
		unsigned long fgcolor,
		unsigned long bgcolor, 
		void *buffer ) 
{

	
	if(!charDefault) {

		// default
		gCHAR.xStart 	= 0;
		gCHAR.yStart 	= 0;
		gCHAR.xEnd	= g->area.xEnd;
		gCHAR.yEnd	= g->area.yEnd;
		gCHAR.xCursor 	= 0;
		gCHAR.yCursor 	= 0;
		gCHAR.fSizeX 	= FONT_SIZE_X;
		gCHAR.fSizeY 	= FONT_SIZE_Y;
		gCHAR.fBuffer  	= (uint32_t*) FONT_ROM_BIOS; //Font 8x8, ROM BIOS
	
		charDefault = 1;
	}


	if(gCHAR.yCursor >= gCHAR.yEnd ) {

		//scroll();

		gCHAR.xCursor = 0;
		gCHAR.yCursor = 0;


	}
    	if(gCHAR.xCursor >= gCHAR.xEnd) {

        	gCHAR.yCursor += gCHAR.fSizeY;
        	gCHAR.xCursor  =0;      
    	} 
	if(c == '\n') {  

        	gCHAR.yCursor += gCHAR.fSizeY;
        	gCHAR.xCursor = 0;

    	}else if(c == '\t') {

        	gCHAR.xCursor = (gCHAR.xCursor + (gCHAR.fSizeX * gCHAR.fSizeX)) &~((gCHAR.fSizeX * gCHAR.fSizeX)-1); 

    	}else if(c >= ' '){ 

        	DRAWChar(gCHAR.xCursor,gCHAR.yCursor,c,fgcolor,bgcolor,buffer,gCHAR.fBuffer);
        	gCHAR.xCursor += gCHAR.fSizeX; 
         
    	}


	return c;

}


int CHARBuiltSectCursor(	unsigned long x,
				unsigned long y) 
{


	charDefault 	= 1;

	gCHAR.xCursor 	= x;
	gCHAR.yCursor 	= y;

	return 0;	

}


int CHARBuiltSectLen(	unsigned long xStart,
			unsigned long yStart,
			unsigned long xEnd,
			unsigned long yEnd) 
{
	charDefault 	= 1;

	gCHAR.xStart 	= xStart;
	gCHAR.yStart 	= yStart;
	gCHAR.xEnd 	= xEnd;
	gCHAR.yEnd 	= yEnd;

	return 0;
}

void *CHARBuiltSectFont( void *fBuffer,
			 unsigned long x,
			 unsigned long y) 
{

	charDefault 	= 1;

	gCHAR.fSizeX 	= x;
	gCHAR.fSizeY 	= x;	
	gCHAR.fBuffer 	= (uint32_t*) fBuffer;
	return (uint32_t*) gCHAR.fBuffer;
}
