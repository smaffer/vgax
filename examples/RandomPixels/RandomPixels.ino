#include <VGAX.h>
#include <math.h>

VGAX vga;

void setup() {
  vga.begin();
}
void loop() {
  static unsigned cnt;
  cnt++;
  vga.putpixel(rand()%VGAX_WIDTH, rand()%VGAX_HEIGHT, cnt%4);
}