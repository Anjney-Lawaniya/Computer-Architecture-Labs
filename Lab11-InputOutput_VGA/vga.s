.equ ADDR_VGA, 0x08000000
.equ ADDR_CHAR, 0x09000000

  movia r2,ADDR_VGA
  movia r3, ADDR_CHAR
  movui r4,0xffff  /* White pixel */
  movi  r5, 0x41   /* ASCII for 'A' */
  sthio r4,1032(r2) /* pixel (4,1) is x*2 + y*1024 so (8 + 1024 = 1032) */
  stbio r5,132(r3) /* character (4,1) is x + y*128 so (4 + 128 = 132) */
