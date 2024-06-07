char *QuotedString::extractFrom(char *input, char **endPtr) {
  char firstChar = *input;

  if (!isQuote(firstChar)) {
    
    return NULL;
  }

  char stopChar = firstChar;  

  char *startPtr = input + 1;  
  char *readPtr = startPtr;
  char *writePtr = startPtr;
  char c;

  for (;;) {
    c = *readPtr++;

    if (c == '\0') {
      
      return NULL;
    }

    if (c == stopChar) {
      
      break;
    }

    if (c == '\\') {
      
      c = unescapeChar(*readPtr++);
    }

    *writePtr++ = c;
  }

  
  *writePtr = '\0';

  
  *endPtr = readPtr;

  return startPtr;
}