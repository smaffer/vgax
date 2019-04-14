/*
Utils for VGAX Library 

COPYRIGHT (C) 2014 Sandro Maffiodo
smaffer@gmail.com
http://www.sandromaffiodo.com

Some of these methods are from TVOut library created by Myles Metzer (thank you!)
https://code.google.com/p/arduino-tvout/
*/
#ifndef __VGAX_utils__
#define __VGAX_utils__

#include <VGAX.h>

class VGAXUtils {
public:
  //porting of TVOut::draw_line method, writen by Myles Metzer
  static inline void draw_line(uint8_t x0, uint8_t y0, 
                               uint8_t x1, uint8_t y1, uint8_t c) {
    if (x0>VGAX_WIDTH || y0>VGAX_HEIGHT || x1>VGAX_WIDTH || y1>VGAX_HEIGHT)
      return;
    if (x0==x1)
      VGAXUtils::draw_column(x0, y0, y1, c);
    else if (y0==y1)
      VGAXUtils::draw_row(y0, x0, x1, c);
    else {
      int e;
      signed int dx, dy, j, temp;
      signed char s1, s2, xchange;
      signed int x, y;
      x=x0;
      y=y0;
      //take absolute value
      if (x1<x0) {
        dx=x0-x1;
        s1=-1;
      } else if (x1==x0) {
        dx=0;
        s1=0;
      } else {
        dx=x1-x0;
        s1=1;
      }
      if (y1<y0) {
        dy=y0-y1;
        s2=-1;
      } else if (y1==y0) {
        dy=0;
        s2=0;
      } else {
        dy=y1-y0;
        s2=1;
      }
      xchange=0;   
      if (dy>dx) {
        temp=dx;
        dx=dy;
        dy=temp;
        xchange=1;
      } 
      e=((int)dy<<1)-dx;  
      for (j=0; j<=dx; j++) {
        VGAX::putpixel(x, y, c);
        if (e>=0) {
          if (xchange==1) 
            x=x+s1;
          else 
            y=y+s2;
          e=e-((int)dx<<1);
        }
        if (xchange==1)
          y=y+s2;
        else
          x=x+s1;
        e=e+((int)dy<<1);
      }
    }
  }
  //porting of TVOut::draw_circle method, writen by Myles Metzer
  static inline void draw_circle(uint8_t x0, uint8_t y0, 
                                 uint8_t radius, uint8_t c, char fc) {
    int f=1-radius;
    int ddF_x=1;
    int ddF_y=-2 * radius;
    int x=0;
    int y=radius;
    uint8_t pyy=y, pyx=x;
    //there is a fill color
    if (fc!=-1)
      VGAXUtils::draw_row(y0, x0-radius, x0+radius, fc);
    VGAX::putpixel(x0, y0+radius, c);
    VGAX::putpixel(x0, y0-radius, c);
    VGAX::putpixel(x0+radius, y0, c);
    VGAX::putpixel(x0-radius, y0, c);
    
    while (x < y) {
      if (f >= 0) {
        y--;
        ddF_y += 2;
        f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x;
      //there is a fill color
      if (fc != -1) {
        //prevent double draws on the same rows
        if (pyy != y) {
          VGAXUtils::draw_row(y0+y, x0-x, x0+x, fc);
          VGAXUtils::draw_row(y0-y, x0-x, x0+x, fc);
        }
        if (pyx != x && x != y) {
          VGAXUtils::draw_row(y0+x, x0-y, x0+y, fc);
          VGAXUtils::draw_row(y0-x, x0-y, x0+y, fc);
        }
        pyy=y;
        pyx=x;
      }
      VGAX::putpixel(x0+x, y0+y, c);
      VGAX::putpixel(x0-x, y0+y, c);
      VGAX::putpixel(x0+x, y0-y, c);
      VGAX::putpixel(x0-x, y0-y, c);
      VGAX::putpixel(x0+y, y0+x, c);
      VGAX::putpixel(x0-y, y0+x, c);
      VGAX::putpixel(x0+y, y0-x, c);
      VGAX::putpixel(x0-y, y0-x, c);
    }
  }
  //porting of TVOut::draw_rect method, writen by Myles Metzer
  static inline void draw_rect(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, 
                               uint8_t c, char fc) {
    if (fc != -1) {
      for (unsigned char i=y0; i < y0+h; i++) {
        VGAXUtils::draw_row(i, x0, x0+w, fc);
      }
    }
    VGAXUtils::draw_line(x0,   y0,   x0+w, y0,   c);
    VGAXUtils::draw_line(x0,   y0,   x0,   y0+h, c);
    VGAXUtils::draw_line(x0+w, y0,   x0+w, y0+h, c);
    VGAXUtils::draw_line(x0,   y0+h, x0+w, y0+h, c);
  }
  //porting of TVOut::draw_row method, writen by Myles Metzer
  static inline void draw_row(uint8_t line, uint8_t x0, uint8_t x1, uint8_t c) {
    if (x0 == x1) {
      VGAX::putpixel(x0, line, c);
    } else {
      if (x0 > x1) {
        uint8_t tmp=x0;
        x0=x1;
        x1=tmp;
      }
      while (x0 < x1) {
        VGAX::putpixel(x0++, line, c);
      }
    }
  }
  //porting of TVOut::draw_column method, writen by Myles Metzer
  static inline void draw_column(uint8_t row, uint8_t y0, uint8_t y1, uint8_t c) {
    if (y0 == y1) {
      VGAX::putpixel(row, y0, c);
    } else {
      if (y1 < y0) {
        uint8_t tmp=y0;
        y0=y1;
        y1=tmp;
      }
      while (y0 < y1) {
        VGAX::putpixel(row, y0++, c);
      }
    }
  }
  //porting of TVOut::draw_line method, writen by Myles Metzer
  //Safe version with screen clipping
  static inline void draw_line_safe(uint8_t x0, uint8_t y0, 
                                    uint8_t x1, uint8_t y1, uint8_t c) {
    if (x0>VGAX_WIDTH || y0>VGAX_HEIGHT || x1>VGAX_WIDTH || y1>VGAX_HEIGHT)
      return;
    if (x0==x1)
      VGAXUtils::draw_column_safe(x0, y0, y1, c);
    else if (y0==y1)
      VGAXUtils::draw_row_safe(y0, x0, x1, c);
    else {
      int e;
      signed int dx, dy, j, temp;
      signed char s1, s2, xchange;
      signed int x, y;
      x=x0;
      y=y0;
      //take absolute value
      if (x1<x0) {
        dx=x0-x1;
        s1=-1;
      } else if (x1==x0) {
        dx=0;
        s1=0;
      } else {
        dx=x1-x0;
        s1=1;
      }
      if (y1<y0) {
        dy=y0-y1;
        s2=-1;
      } else if (y1==y0) {
        dy=0;
        s2=0;
      } else {
        dy=y1-y0;
        s2=1;
      }
      xchange=0;   
      if (dy>dx) {
        temp=dx;
        dx=dy;
        dy=temp;
        xchange=1;
      } 
      e=((int)dy<<1)-dx;  
      for (j=0; j<=dx; j++) {
        putpixel_safe(x, y, c);
        if (e>=0) {
          if (xchange==1) 
            x=x+s1;
          else 
            y=y+s2;
          e=e-((int)dx<<1);
        }
        if (xchange==1)
          y=y+s2;
        else
          x=x+s1;
        e=e+((int)dy<<1);
      }
    }
  }
  //porting of TVOut::draw_circle method, writen by Myles Metzer
  //Safe version with screen clipping
  static inline void draw_circle_safe(uint8_t x0, uint8_t y0, 
                                      uint8_t radius, uint8_t c, char fc) {
    int f=1-radius;
    int ddF_x=1;
    int ddF_y=-2 * radius;
    int x=0;
    int y=radius;
    uint8_t pyy=y, pyx=x;
    //there is a fill color
    if (fc!=-1)
      VGAXUtils::draw_row_safe(y0, x0-radius, x0+radius, fc);
    VGAX::putpixel(x0, y0+radius, c);
    VGAX::putpixel(x0, y0-radius, c);
    VGAX::putpixel(x0+radius, y0, c);
    VGAX::putpixel(x0-radius, y0, c);
    
    while (x < y) {
      if (f >= 0) {
        y--;
        ddF_y += 2;
        f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x;
      //there is a fill color
      if (fc != -1) {
        //prevent double draws on the same rows
        if (pyy != y) {
          VGAXUtils::draw_row_safe(y0+y, x0-x, x0+x, fc);
          VGAXUtils::draw_row_safe(y0-y, x0-x, x0+x, fc);
        }
        if (pyx != x && x != y) {
          VGAXUtils::draw_row_safe(y0+x, x0-y, x0+y, fc);
          VGAXUtils::draw_row_safe(y0-x, x0-y, x0+y, fc);
        }
        pyy=y;
        pyx=x;
      }
      putpixel_safe(x0+x, y0+y, c);
      putpixel_safe(x0-x, y0+y, c);
      putpixel_safe(x0+x, y0-y, c);
      putpixel_safe(x0-x, y0-y, c);
      putpixel_safe(x0+y, y0+x, c);
      putpixel_safe(x0-y, y0+x, c);
      putpixel_safe(x0+y, y0-x, c);
      putpixel_safe(x0-y, y0-x, c);
    }
  }
  //porting of TVOut::draw_rect method, writen by Myles Metzer
  //Safe version with screen clipping
  static inline void draw_rect_safe(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, 
                                    uint8_t c, char fc) {
    if (fc != -1) {
      for (unsigned char i=y0; i < y0+h; i++) {
        VGAXUtils::draw_row_safe(i, x0, x0+w, fc);
      }
    }
    VGAXUtils::draw_line_safe(x0,   y0,   x0+w, y0,   c);
    VGAXUtils::draw_line_safe(x0,   y0,   x0,   y0+h, c);
    VGAXUtils::draw_line_safe(x0+w, y0,   x0+w, y0+h, c);
    VGAXUtils::draw_line_safe(x0,   y0+h, x0+w, y0+h, c);
  }
  //porting of TVOut::draw_row method, writen by Myles Metzer
  //Safe version with screen clipping
  static inline void draw_row_safe(uint8_t line, uint8_t x0, uint8_t x1, uint8_t c) {
    if (x0 == x1) {
      putpixel_safe(x0, line, c);
    } else {
      if (x0 > x1) {
        uint8_t tmp=x0;
        x0=x1;
        x1=tmp;
      }
      while (x0 < x1) {
        putpixel_safe(x0++, line, c);
      }
    }
  }
  //porting of TVOut::draw_column method, writen by Myles Metzer
  //Safe version with screen clipping
  static inline void draw_column_safe(uint8_t row, uint8_t y0, uint8_t y1, uint8_t c) {
    if (y0 == y1) {
      putpixel_safe(row, y0, c);
    } else {
      if (y1 < y0) {
        uint8_t tmp=y0;
        y0=y1;
        y1=tmp;
      }
      while (y0 < y1) {
        putpixel_safe(row, y0++, c);
      }
    }
  }
  static inline void putpixel_safe(char x, char y, uint8_t color) {
    if (x>=VGAX_WIDTH || y>=VGAX_HEIGHT || x<0 || y<0)
      return;
    VGAX::putpixel(x, y, color);
  }
};

#endif