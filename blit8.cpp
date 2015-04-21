#include "VGAX.h"

void VGAX::blit8aligned(byte *src, byte sheight, byte dbx, byte dy) {
  byte *sptr=src;
  byte *dptr=(byte*)vgaxfb+VGAX_BWIDTH*dy+dbx;
  while (sheight--) {
    dptr[0]=pgm_read_byte(sptr++);
    dptr[1]=pgm_read_byte(sptr++);
    dptr+=VGAX_BWIDTH;
  }
}
void VGAX::blit8(byte *src, byte sheight, char dx, char dy) {
  byte *sptr=src;
  if (dy<0) {
    if (dy<-8)
      return;
    sheight+=dy;
    sptr+=(-dy)*2;
    dy=0;
  }
  if (dy>=VGAX_HEIGHT)
    return;
  char yout=dy+sheight-VGAX_HEIGHT;
  if (yout>0)
    sheight-=yout;
  byte *dptr=(byte*)vgaxfb+VGAX_BWIDTH*dy+(dx>>2);
  if (dx<0) {
    if (dx<-7)
      return;
    //left clip
    switch (dx & 7) {
    case 0:
      break;
    case 1:
      //7 pixels unaligned
      while (sheight--) {
        sptr++;
        byte b1=pgm_read_byte(sptr++);
        dptr[2]&=0x3f;
        dptr[2]|=b1<<6;
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 2:
      //6 pixels unaligned
      while (sheight--) {
        sptr++;
        byte b1=pgm_read_byte(sptr++);
        dptr[2]&=0x0f;
        dptr[2]|=b1<<4;
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 3:
      //5 pixel unaligned
      while (sheight--) {
        sptr++;
        byte b1=pgm_read_byte(sptr++);
        dptr[2]&=0x03;
        dptr[2]|=b1<<2;
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 4:
      //4 pixel unaligned. blit is byte aligned!
      while (sheight--) {
        sptr++;
        dptr[1]=pgm_read_byte(sptr++);
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 5:
      //3 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte b1=pgm_read_byte(sptr++);
        dptr[1]=(b0<<6) | (b1>>2);
        dptr[2]&=0x3f;
        dptr[2]|=b1<<6;
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 6:
      //2 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte b1=pgm_read_byte(sptr++);
        dptr[1]=(b0<<4) | (b1>>4);
        dptr[2]&=0x0f;
        dptr[2]|=b1<<4;
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 7:
      //1 pixel unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte b1=pgm_read_byte(sptr++);
        dptr[1]=(b0<<2) | (b1>>6);
        dptr[2]&=0x03;
        dptr[2]|=b1<<2;
        dptr+=VGAX_BWIDTH;
      }
      break;
    }
  } else if (dx>VGAX_WIDTH-8) {
    if (dx>=VGAX_WIDTH)
      return;
    //right clip
    switch (dx & 7) {
    case 0:
      break;
    case 1:
      //7 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte b1=pgm_read_byte(sptr++);
        dptr[0]&=0xc0;
        dptr[0]|=b0>>2;
        dptr[1]=(b0<<6) | (b1>>2);
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 5:
      //3 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        sptr++;
        dptr[0]&=0xc0;
        dptr[0]|=b0>>2;
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 6:
      //2 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        sptr++;
        dptr[0]&=0xf0;
        dptr[0]|=b0>>4;
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 2:
      //6 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte b1=pgm_read_byte(sptr++);
        dptr[0]&=0xf0;
        dptr[0]|=b0>>4;
        dptr[1]=(b0<<4) | (b1>>4);
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 3:
      //5 pixel unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte b1=pgm_read_byte(sptr++);
        dptr[0]&=0xfc;
        dptr[0]|=b0>>6;
        dptr[1]=(b0<<2) | (b1>>6);
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 4:
      //4 pixel unaligned. blit is byte aligned!
      while (sheight--) {
        dptr[0]=pgm_read_byte(sptr++);
        sptr++;
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 7:
      //1 pixel unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        sptr++;
        dptr[0]&=0xfc;
        dptr[0]|=b0>>6;
        dptr+=VGAX_BWIDTH;
      }
      break;
    }
  } else {
    byte dx3=dx & 3;
    if (dx3==0) {
      //0 pixel unaligned. blit is byte aligned!
      while (sheight--) {
        dptr[0]=pgm_read_byte(sptr++);
        dptr[1]=pgm_read_byte(sptr++);
        dptr+=VGAX_BWIDTH;
      }
    } else if (dx3==1) {
      //3 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte b1=pgm_read_byte(sptr++);
        dptr[0]&=0xc0;
        dptr[0]|=b0>>2;
        dptr[1]=(b0<<6) | (b1>>2);
        dptr[2]&=0x3f;
        dptr[2]|=b1<<6;
        dptr+=VGAX_BWIDTH;
      }
    } else if (dx3==2) {
      //2 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte b1=pgm_read_byte(sptr++);
        dptr[0]&=0xf0;
        dptr[0]|=b0>>4;
        dptr[1]=(b0<<4) | (b1>>4);
        dptr[2]&=0x0f;
        dptr[2]|=b1<<4;
        dptr+=VGAX_BWIDTH;
      }
    } else { //dx3=3
      //1 pixel unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte b1=pgm_read_byte(sptr++);
        dptr[0]&=0xfc;
        dptr[0]|=b0>>6;
        dptr[1]=(b0<<2) | (b1>>6);
        dptr[2]&=0x03;
        dptr[2]|=b1<<2;
        dptr+=VGAX_BWIDTH;
      }
    }
  }
}
void VGAX::blit8wmask(byte *src, byte *mask, byte sheight, char dx, char dy) {
  byte *sptr=src;
  byte *mptr=mask;
  if (dy<0) {
    if (dy<-8)
      return;
    sheight+=dy;
    sptr+=(-dy)*2;
    mptr+=(-dy)*2;
    dy=0;
  }
  if (dy>=VGAX_HEIGHT)
    return;
  char yout=dy+sheight-VGAX_HEIGHT;
  if (yout>0)
    sheight-=yout;
  byte *dptr=(byte*)vgaxfb+VGAX_BWIDTH*dy+(dx>>2);
  if (dx<0) {
    if (dx<-7)
      return;
    //left clip
    switch (dx & 7) {
    case 0:
      break;
    case 1:
      //7 pixels unaligned
      while (sheight--) {
        sptr++;
        mptr++;
        byte m1=pgm_read_byte(mptr++);
        byte b1=pgm_read_byte(sptr++);
        dptr[2]&=m1<<6 | 0x3f;
        dptr[2]|=b1<<6;
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 5:
      //3 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte b1=pgm_read_byte(sptr++);
        byte m0=pgm_read_byte(mptr++);
        byte m1=pgm_read_byte(mptr++);
        dptr[1]&=(m0<<6) | (m1>>2);
        dptr[1]|=(b0<<6) | (b1>>2);
        dptr[2]&=m1<<6 | 0x3f;
        dptr[2]|=b1<<6;
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 6:
      //2 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte b1=pgm_read_byte(sptr++);
        byte m0=pgm_read_byte(mptr++);
        byte m1=pgm_read_byte(mptr++);
        dptr[1]&=(m0<<4) | (m1>>4);
        dptr[1]|=(b0<<4) | (b1>>4);
        dptr[2]&=m1<<4 | 0xf;
        dptr[2]|=b1<<4;
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 2:
      //6 pixels unaligned
      while (sheight--) {
        sptr++;
        mptr++;
        byte b1=pgm_read_byte(sptr++);
        byte m1=pgm_read_byte(mptr++);
        dptr[2]&=m1<<4 | 0xf;
        dptr[2]|=b1<<4;
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 3:
      //5 pixel unaligned
      while (sheight--) {
        sptr++;
        mptr++;
        byte b1=pgm_read_byte(sptr++);
        byte m1=pgm_read_byte(mptr++);
        dptr[2]&=m1<<2 | 0x3;
        dptr[2]|=b1<<2;
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 4:
      //4 pixel unaligned. blit is byte aligned!
      while (sheight--) {
        sptr++;
        mptr++;
        dptr[1]&=pgm_read_byte(mptr++);
        dptr[1]|=pgm_read_byte(sptr++);
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 7:
      //1 pixel unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte b1=pgm_read_byte(sptr++);
        byte m0=pgm_read_byte(mptr++);
        byte m1=pgm_read_byte(mptr++);
        dptr[1]&=(m0<<2) | (m1>>6);
        dptr[1]|=(b0<<2) | (b1>>6);
        dptr[2]&=m1<<2 | 0x3;
        dptr[2]|=b1<<2;
        dptr+=VGAX_BWIDTH;
      }
      break;
    }
  } else if (dx>VGAX_WIDTH-8) {
    if (dx>=VGAX_WIDTH)
      return;
    //right clip
    switch (dx & 7) {
    case 0:
      break;
    case 1:
      //7 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte b1=pgm_read_byte(sptr++);
        byte m0=pgm_read_byte(mptr++);
        byte m1=pgm_read_byte(mptr++);
        dptr[0]&=m0>>2 | 0xc0;
        dptr[0]|=b0>>2;
        dptr[1]&=(m0<<6) | (m1>>2);
        dptr[1]|=(b0<<6) | (b1>>2);
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 5:
      //3 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte m0=pgm_read_byte(mptr++);
        sptr++;
        mptr++;
        dptr[0]&=m0>>2 | 0xc0;
        dptr[0]|=b0>>2;
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 6:
      //2 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte m0=pgm_read_byte(mptr++);
        sptr++;
        mptr++;
        dptr[0]&=m0>>4 | 0xf0;
        dptr[0]|=b0>>4;
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 2:
      //6 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte b1=pgm_read_byte(sptr++);
        byte m0=pgm_read_byte(mptr++);
        byte m1=pgm_read_byte(mptr++);
        dptr[0]&=m0>>4 | 0xf0;
        dptr[0]|=b0>>4;
        dptr[1]&=(m0<<4) | (m1>>4);
        dptr[1]|=(b0<<4) | (b1>>4);
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 3:
      //5 pixel unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte b1=pgm_read_byte(sptr++);
        byte m0=pgm_read_byte(mptr++);
        byte m1=pgm_read_byte(mptr++);
        dptr[0]&=m0>>6 | 0xfc;
        dptr[0]|=b0>>6;
        dptr[1]&=(m0<<2) | (m1>>6);
        dptr[1]|=(b0<<2) | (b1>>6);
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 4:
      //4 pixel unaligned. blit is byte aligned!
      while (sheight--) {
        dptr[0]&=pgm_read_byte(mptr++);
        dptr[0]|=pgm_read_byte(sptr++);
        sptr++;
        mptr++;
        dptr+=VGAX_BWIDTH;
      }
      break;
    case 7:
      //1 pixel unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte m0=pgm_read_byte(mptr++);
        sptr++;
        mptr++;
        dptr[0]&=m0>>6 | 0xfc;
        dptr[0]|=b0>>6;
        dptr+=VGAX_BWIDTH;
      }
      break;
    }
  } else {
    byte dx3=dx & 3;
    if (dx3==0) {
      //0 pixel unaligned. blit is byte aligned!
      while (sheight--) {
        dptr[0]&=pgm_read_byte(mptr++);
        dptr[0]|=pgm_read_byte(sptr++);
        dptr[1]&=pgm_read_byte(mptr++);
        dptr[1]|=pgm_read_byte(sptr++);
        dptr+=VGAX_BWIDTH;
      }
    } else if (dx3==1) {
      //3 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte b1=pgm_read_byte(sptr++);
        byte m0=pgm_read_byte(mptr++);
        byte m1=pgm_read_byte(mptr++);
        dptr[0]&=m0>>2 | 0xc0;
        dptr[0]|=b0>>2;
        dptr[1]&=(m0<<6) | (m1>>2);
        dptr[1]|=(b0<<6) | (b1>>2);
        dptr[2]&=m1<<6 | 0x3f;
        dptr[2]|=b1<<6;
        dptr+=VGAX_BWIDTH;
      }
    } else if (dx3==2) {
      //2 pixels unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte b1=pgm_read_byte(sptr++);
        byte m0=pgm_read_byte(mptr++);
        byte m1=pgm_read_byte(mptr++);
        dptr[0]&=m0>>4 | 0xf0;
        dptr[0]|=b0>>4;
        dptr[1]&=(m0<<4) | (m1>>4);
        dptr[1]|=(b0<<4) | (b1>>4);
        dptr[2]&=m1<<4 | 0xf;
        dptr[2]|=b1<<4;
        dptr+=VGAX_BWIDTH;
      }
    } else { //dx3=3
      //1 pixel unaligned
      while (sheight--) {
        byte b0=pgm_read_byte(sptr++);
        byte b1=pgm_read_byte(sptr++);
        byte m0=pgm_read_byte(mptr++);
        byte m1=pgm_read_byte(mptr++);
        dptr[0]&=m0>>6 | 0xfc;
        dptr[0]|=b0>>6;
        dptr[1]&=(m0<<2) | (m1>>6);
        dptr[1]|=(b0<<2) | (b1>>6);
        dptr[2]&=m1<<2 | 0x3;
        dptr[2]|=b1<<2;
        dptr+=VGAX_BWIDTH;
      }
    }
  }
}
