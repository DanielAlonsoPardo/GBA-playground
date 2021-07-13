#include "lib/hardware_consts/gba_memory_map.h"
#include "lib/hardware_consts/gba_io_registers.h"

#define pos(x, y) ((x) + (y)*240)

void circle(volatile unsigned short* vram, int x, int y) {
  // .xxx.
  // x...x
  // x.O.x
  // x...x
  // .xxx.

  vram[pos(x-1, y-2)] = 0xFFFF;
  vram[pos(x, y-2)] = 0xFFFF;
  vram[pos(x+1, y-2)] = 0xFFFF;
  
  vram[pos(x-2, y-1)] = 0xFFFF;
  vram[pos(x+2, y-1)] = 0xFFFF;

  vram[pos(x-2, y)] = 0xFFFF;
  vram[pos(x+2, y)] = 0xFFFF;

  vram[pos(x-2, y+1)] = 0xFFFF;
  vram[pos(x+2, y+1)] = 0xFFFF;

  vram[pos(x-1, y+2)] = 0xFFFF;
  vram[pos(x, y+2)] = 0xFFFF;
  vram[pos(x+1, y+2)] = 0xFFFF;

}

struct RadioButton {
  int short x;
  int short y;
  int short on;
};

void paint_RadioButton(volatile unsigned short* vram, struct RadioButton rb) {
  circle(vram, rb.x, rb.y);
  if (rb.on)
    vram[pos(rb.x, rb.y)] = 0xFFFF;
}

void paint_RadioButton_state(volatile unsigned short* vram, struct RadioButton rb) {
  if (rb.on)
    vram[pos(rb.x, rb.y)] = 0xFFFF;
  else
    vram[pos(rb.x, rb.y)] = 0x0000;
}

void toggle_RadioButton(volatile unsigned short* vram, struct RadioButton rb) {
  if (rb.on) {
    rb.on = 0;
    vram[pos(rb.x, rb.y)] = 0x0000;
  } else {
    rb.on = 1;
    vram[pos(rb.x, rb.y)] = 0xFFFF;
  }
}

int main(void) {
  //Set video mode
  SET_VIDEO_MODE_3();

  volatile unsigned short* const VRAM = (unsigned short*)VRAM_ADDR;
  volatile unsigned short* const KEYINPUT = (unsigned short*)(IO_REGISTERS_KEYINPUT_ADDR);
  volatile unsigned char*  const VCOUNT = (unsigned char*)(IO_REGISTERS_VCOUNT_ADDR);


  // Init radio buttons
  struct RadioButton rbs[10];

  for (int i; i < 10; i++) {
    rbs[i].x = 90 + i*6;
    rbs[i].y = 80;
    rbs[i].on = 0;
    paint_RadioButton(VRAM, rbs[i]);
  }

  //Enter game loop
  while(1) {
    unsigned int key_states;
    // Skip past the rest of any current V-Blank, then skip past
    // the V-Draw
    while(*VCOUNT >= 160);
    while(*VCOUNT < 160);

    key_states = ~(*KEYINPUT) & KEYINPUT_ANY;

    for (unsigned int i = 0, j = 1; i < 10; i++, j = j*2) {
      rbs[i].on = key_states & j;
      paint_RadioButton_state(VRAM, rbs[i]);
    }
  }

  return 0;
}
