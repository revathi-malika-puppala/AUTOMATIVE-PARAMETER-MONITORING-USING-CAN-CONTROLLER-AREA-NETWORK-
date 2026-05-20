#define SETBIT(WORD,BP) WORD|=1<<BP              // Set (turn ON) the bit at position BP in WORD
#define CLRBIT(WORD,BP) WORD&=~(1<<BP)           // Clear (turn OFF) the bit at position BP in WORD
#define CPLBIT(WORD,BP) WORD^=1<<BP              // Toggle (complement) the bit at position BP in WORD

#define WRITEBIT(WORD,BP,BIT) WORD=((WORD&~(1<<BP))|(BIT<<BP))  
// Write a specific BIT value (0 or 1) to the bit at position BP in WORD

#define WRITENIBBLE(WORD,SBP,NIBBLE) WORD=((WORD&~(0xf<<SBP))|(NIBBLE<<SBP))  
// Write a 4-bit value (NIBBLE) starting at bit position SBP in WORD

#define WRITEBYTE(WORD,SBP,BYTE) WORD=((WORD&~(0xff<<SBP))|(BYTE<<SBP))  
// Write an 8-bit value (BYTE) starting at bit position SBP in WORD

#define WRITEHWORD(WORD,SBP,HWORD) WORD=((WORD&~(0xffff<<SBP))|(HWORD<<SBP))  
// Write a 16-bit value (HWORD) starting at bit position SBP in WORD

#define READBIT(WORD,BP) ((WORD>>BP)&1)          // Read the bit at position BP in WORD (returns 0 or 1)

