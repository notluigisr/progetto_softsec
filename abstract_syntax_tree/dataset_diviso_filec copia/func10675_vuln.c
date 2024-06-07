void lcdSetPixels_ArrayBuffer_flat(JsGraphics *gfx, short x, short y, short pixelCount, unsigned int col) {
  unsigned char *ptr = (unsigned char*)gfx->backendData;
  unsigned int idx = lcdGetPixelIndex_ArrayBuffer(gfx,x,y,pixelCount);
  ptr += idx>>3;

  unsigned int whiteMask = (1U<<gfx->data.bpp)-1;
  bool shortCut = (col==0 || (col&whiteMask)==whiteMask) && (!(gfx->data.flags&JSGRAPHICSFLAGS_ARRAYBUFFER_VERTICAL_BYTE)); 

  while (pixelCount--) { 
    if (gfx->data.bpp&7) {
      idx = idx & 7;
      if (shortCut && idx==0) {
        
        
        int wholeBytes = (gfx->data.bpp*(pixelCount+1)) >> 3;
        if (wholeBytes) {
          char c = (char)(col?0xFF:0);
          pixelCount = (short)(pixelCount+1 - (wholeBytes*8/gfx->data.bpp));
          while (wholeBytes--) {
            *ptr = c;
            ptr++;
          }
          continue;
        }
      }
      unsigned int mask = (unsigned int)(1<<gfx->data.bpp)-1;
      unsigned int existing = (unsigned int)*ptr;
      unsigned int bitIdx = (gfx->data.flags & JSGRAPHICSFLAGS_ARRAYBUFFER_MSB) ? 8-(idx+gfx->data.bpp) : idx;
      *ptr = (char)((existing&~(mask<<bitIdx)) | ((col&mask)<<bitIdx));
      if (gfx->data.flags & JSGRAPHICSFLAGS_ARRAYBUFFER_VERTICAL_BYTE) {
        ptr++;
      } else {
        idx += gfx->data.bpp;
        if (idx>=8) ptr++;
      }
    } else { 
      int i;
      for (i=0;i<gfx->data.bpp;i+=8) {
        *ptr = (char)(col >> i);
        ptr++;
      }
    }
  }
}