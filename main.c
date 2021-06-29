#define pos(x, y) ((x) + (y)*240)

#define MEM_IO 0x04000000
#define REG_DISPLAY        (*((volatile unsigned int *)(MEM_IO)))
#define REG_DISPLAY_VCOUNT (*((volatile unsigned int *)(MEM_IO + 0x0006)))
#define REG_KEY_INPUT      (*((volatile unsigned int *)(MEM_IO + 0x0130)))

#define BUTTON_A 0x0001
#define BUTTON_B 0x0002
#define SELECT   0x0004
#define START    0x0008
#define RIGHT    0x0010
#define LEFT     0x0020
#define UP       0x0040
#define DOWN     0x0080
#define BUTTON_R 0x0100
#define BUTTON_L 0x0200

#define ALL_BUTTONS 0x03FF

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
  // Write into the I/O registers, setting video display parameters.
  volatile unsigned char* ioram= (unsigned char*)0x04000000;
  ioram[0] =0x03; // Use video mode 3 (in BG2, a 16bpp bitmap in VRAM)
  ioram[1] =0x04; // Enable BG2 (BG0 = 1, BG1 = 2, BG2 = 4, ...)

  // Write pixel colours into VRAM
  volatile unsigned short* vram= (unsigned short*)0x06000000;

  // Init radio buttons
  struct RadioButton rbs[10];

  for (int i; i < 10; i++) {
    rbs[i].x = 90 + i*6;
    rbs[i].y = 80;
    rbs[i].on = 0;
    paint_RadioButton(vram, rbs[i]);
  }

  // Wait forever
  while(1) {
    unsigned int key_states = 0;
    // Skip past the rest of any current V-Blank, then skip past
    // the V-Draw
    while(REG_DISPLAY_VCOUNT >= 160);
    while(REG_DISPLAY_VCOUNT < 160);

    key_states = ~REG_KEY_INPUT & ALL_BUTTONS;

    for (unsigned int i = 0, j = 1; i < 10; i++, j = j*2) {
      rbs[i].on = key_states & j;
      paint_RadioButton_state(vram, rbs[i]);
    }
  }

  return 0;
}
