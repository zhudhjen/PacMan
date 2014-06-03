#include "draw.h"


char *numToString(int num) {
  char *result = "0000000";
  int k, n;
  int i = 0;
  while (num > 0) {
  	result[i++] = num % 10 + 48;
  	num /= 10;
  }
  result[i] = '\0';
  i--;
  for (n = i; i > n / 2; i--)
  {
  	k = result[i];
  	result[i] = result[n - i];
  	result[n - i] = k;
  }
  return result;
}

main() {
  int i , j;
  int driver=0, mode=VESA_1024x768x8bit;
  initgraph(&driver, &mode, "");
  load_8bit_bmp(0, 0, "pacman.bmp");
  setcolor(118);
  outtextxy(220,20, numToString(410));
  settextstyle(TRIPLEX_FONT,HORIZ_DIR, 2);
  settextjustify(LEFT_TEXT,0);
  outtextxy(220,50,"Triplex font");
  settextstyle(SMALL_FONT,HORIZ_DIR, 2);
  settextjustify(LEFT_TEXT,0);
  outtextxy(220,80,"Smallfont");
  settextstyle(SANS_SERIF_FONT,HORIZ_DIR,2);
  settextjustify(LEFT_TEXT,0);
  outtextxy(220,110,"Sans serif font");
  settextstyle(GOTHIC_FONT,HORIZ_DIR, 2);
  settextjustify(LEFT_TEXT,0);
  outtextxy(220,140,"gothic font");
  getch();
  closegraph();
}
