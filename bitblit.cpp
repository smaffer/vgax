#include "VGAX.h"

void VGAX::bitblit(byte *src, byte swidth, byte sheight, char dx, char dy, byte color) {
  byte *sptr=src;
  while (sheight--) {
      byte m=pgm_read_byte(sptr++);

      //(for 0 to 8 unrolled)

      //first nibble (higher 4 bit of src)
      if (dx+0>=VGAX_WIDTH)
        goto next;
      if (dx+0>-1 && m&(1<<7))
        putpixel(dx+0, dy, color);
      if (swidth==0)
        goto next;

      if (dx+1>=VGAX_WIDTH)
        goto next;
      if (dx+1>-1 && m&(1<<6))
        putpixel(dx+1, dy, color);
      if (swidth==1)
        goto next;

      if (dx+2>=VGAX_WIDTH)
        goto next;
      if (dx+2>-1 && m&(1<<5))
        putpixel(dx+2, dy, color);
      if (swidth==2)
        goto next;

      if (dx+3>=VGAX_WIDTH)
        goto next;
      if (dx+3>-1 && m&(1<<4))
        putpixel(dx+3, dy, color);
      if (swidth==3)
        goto next;

      //second nibble (lower 4 bit of src)
      if (dx+4>=VGAX_WIDTH)
        goto next;
      if (dx+4>-1 && m&(1<<3))
        putpixel(dx+4, dy, color);
      if (swidth==4)
        goto next;

      if (dx+5>=VGAX_WIDTH)
        goto next;
      if (dx+5>-1 && m&(1<<2))
        putpixel(dx+5, dy, color);
      if (swidth==5)
        goto next;

      if (dx+6>=VGAX_WIDTH)
        goto next;
      if (dx+6>-1 && m&(1<<1))
        putpixel(dx+6, dy, color);
      if (swidth==6)
        goto next;

      if (dx+7>=VGAX_WIDTH)
        goto next;
      if (dx+7>-1 && m&(1<<0))
        putpixel(dx+7, dy, color);
  next:
    dy++;
  }
}