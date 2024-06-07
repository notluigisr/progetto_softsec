static unsigned int XBMInteger(Image *image,short int *hex_digits)
{ 
  int
    c;
  
  unsigned int
    value;
  
  
  do
  { 
    c=ReadBlobByte(image);
    if (c == EOF)
      return(0);
  } while ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r'));
  
  value=0;
  do
  { 
    if (value > (unsigned int) (INT_MAX/10))
      break;
    value*=16;
    c&=0xff;
    if (value > (unsigned int) (INT_MAX-hex_digits[c]))
      break;
    value+=hex_digits[c];
    c=ReadBlobByte(image);
    if (c == EOF)
      return(0);
  } while (hex_digits[c] >= 0);
  return(value);
}