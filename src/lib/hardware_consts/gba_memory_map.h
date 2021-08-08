#ifndef GBA_MEMORY_MAP
#define GBA_MEMORY_MAP


/* Address Bus Width and CPU Read/Write Access Widths

   Region         Bus  Read     Write    Cycles       
   BIOS           32   8/16/32  -        1/1/1        
   IWRAM 32K      32   8/16/32  8/16/32  1/1/1        
   I/O            32   8/16/32  8/16/32  1/1/1        
   OAM            32   8/16/32    16/32  1/1/1 *      
   EWRAM 256K     16   8/16/32  8/16/32  3/3/6 **     
   Palette RAM    16   8/16/32    16/32  1/1/2 *      
   VRAM           16   8/16/32    16/32  1/1/2 *      
   GamePak ROM    16   8/16/32  -        5/5/8 ** / *** 
   GamePak Flash  16   8/16/32    16/32  5/5/8 ** / *** 
   GamePak SRAM   8    8        8        5     **     
   
   Timing Notes:
   *     Plus 1 cycle if GBA accesses video memory at the same time.
   **    Default waitstate settings, see System Control chapter in GBA tek specs.
   ***   Separate timings for sequential, and non-sequential accesses.
   One cycle equals approx. 59.59ns (ie. 16.78MHz clock).

 */

#define BIOS_ADDR               0x00000000
#define BIOS_END_ADDR           0x00003FFF
//Internal Working RAM (32KB)
#define IWRAM_ADDR              0x02000000
#define IWRAM_END_ADDR          0x0203FFFF
//External Working RAM (256KB)
#define EWRAM_ADDR              0x03000000
#define EWRAM_END_ADDR          0x03007FFF

#define IO_REGISTERS_ADDR       0x04000000
#define IO_REGISTERS_END_ADDR   0x040003FE

#define OBJ_PALETTE_ADDR        0x05000000
#define OBJ_PALETTE_END_ADDR    0x050003FF
// Video
#define MODE3_SCREENWIDTH       240
#define MODE3_SCREENHEIGHT      160
#define MODE4_SCREENWIDTH       240
#define MODE4_SCREENHEIGHT      160

#define VRAM_ADDR               0x06000000
#define VRAM_MODE4_PAGE1        0x06000000
#define VRAM_MODE4_PAGE2        0x0600A000
#define VRAM_END_ADDR           0x06017FFF
//Object Attribute Memory
#define OAM_ADDR                0x07000000
#define OAM_END_ADDR            0x070003FF

#define GAME_PAK_ROM_ADDR       0x08000000
#define GAME_PAK_ROM_END_ADDR   0x09FFFFFF

#define GAME_PAK_SRAM_ADDR      0x0E000000
#define GAME_PAK_SRAM_END_ADDR  0x0E00FFFF

typedef volatile unsigned short * Mem_ptr;
 
#endif