#include "VGAX.h"

#define PRINT_LOOP_CODE \
  if (c=='\n') { \
    dx=dx0; \
    dy0+=fntheight+vspace; \
  } else if (c==' ') { \
    dx+=3+hspace; \
  } else { \
    c-=33; \
    if (c>=0 && c<glyphscount) { \
      byte *fntg=fnt+c*(1+fntheight); \
      byte fntw=pgm_read_byte(fntg); \
      /*(inline of bitblit(fntg+1, fntw, fntheight, dx, dy, color & 3))\
        to save from stack overflow*/ \
      byte *sptr=fntg+1; \
      byte sheight=fntheight; \
      byte dy=dy0; \
      while (sheight--) { \
          byte m=pgm_read_byte(sptr++); \
          /*first nibble (higher 4 bit of src)*/ \
          if (dx+0>=VGAX_WIDTH) \
            goto next; \
          if (dx+0>-1 && m&(1<<7)) \
            putpixel(dx+0, dy, color); \
          if (fntw==0) \
            goto next; \
          if (dx+1>=VGAX_WIDTH) \
            goto next; \
          if (dx+1>-1 && m&(1<<6)) \
            putpixel(dx+1, dy, color); \
          if (fntw==1) \
            goto next; \
          if (dx+2>=VGAX_WIDTH) \
            goto next; \
          if (dx+2>-1 && m&(1<<5)) \
            putpixel(dx+2, dy, color); \
          if (fntw==2) \
            goto next; \
          if (dx+3>=VGAX_WIDTH) \
            goto next; \
          if (dx+3>-1 && m&(1<<4)) \
            putpixel(dx+3, dy, color); \
          if (fntw==3) \
            goto next; \
          /*second nibble (lower 4 bit of src)*/ \
          if (dx+4>=VGAX_WIDTH) \
            goto next; \
          if (dx+4>-1 && m&(1<<3)) \
            putpixel(dx+4, dy, color); \
          if (fntw==4) \
            goto next; \
          if (dx+5>=VGAX_WIDTH) \
            goto next; \
          if (dx+5>-1 && m&(1<<2)) \
            putpixel(dx+5, dy, color); \
          if (fntw==5) \
            goto next; \
          if (dx+6>=VGAX_WIDTH) \
            goto next; \
          if (dx+6>-1 && m&(1<<1)) \
            putpixel(dx+6, dy, color); \
          if (fntw==6) \
            goto next; \
          if (dx+7>=VGAX_WIDTH) \
            goto next; \
          if (dx+7>-1 && m&(1<<0)) \
            putpixel(dx+7, dy, color); \
      next: \
        dy++; \
      } \
      dx+=fntw+1; \
    } else { \
      dx+=hspace; \
    } \
  }

void VGAX::printPROGMEM(byte *fnt, byte glyphscount, byte fntheight, 
                        byte hspace, byte vspace, const char *str, 
                        char dx, char dy0, byte color) {
  char dx0=dx, dy;
  char *pstr=(char*)str;
  char c;
  while (c=pgm_read_byte(pstr++)) {
    PRINT_LOOP_CODE  
  }
}
void VGAX::printSRAM(byte *fnt, byte glyphscount, byte fntheight, byte hspace, 
                     byte vspace, const char *str, char dx, char dy0, 
                     byte color) {
  char dx0=dx, dy;
  char *pstr=(char*)str;
  char c;
  while (c=*pstr++) {
    PRINT_LOOP_CODE  
  }
}