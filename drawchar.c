/*
 * File: drawchar.c
 *
 * Descrição:
 *     Constrói caractere em modo gráfico.
 *     Desenha o caractere pixel por pixel.
 * 
 * Sirius OS Versão 2.0, 2017-2018. (Nelson Cole)
 */
#include <io.h>


void DRAWChar( 	unsigned long x,
		unsigned long y,	
		unsigned long c,
		unsigned long fgcolor,
		unsigned long bgcolor, 
		void *buffer,
		void *fbuffer )
{
   	static  int font;
	const char *font_data = (const char*) fbuffer;
   	int cx, cy;
   	char mask[]={128,64,32,16,8,4,2,1};

    
   	for(cy=0;cy < 8;cy++){
        
		font = font_data[(c *8) + cy];
                	for(cx = 0;cx < 8;cx++) {
 
                		if(font &mask[cx])PutPixelX(x + cx,y + cy,buffer,fgcolor);
                        	else PutPixelX(x + cx,y + cy,buffer,bgcolor);
          }
        
    }
        
    

}
