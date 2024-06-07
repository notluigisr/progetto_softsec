UnicodeString::doAppend(const UChar *srcChars, int32_t srcStart, int32_t srcLength) {
  if(!isWritable() || srcLength == 0 || srcChars == NULL) {
    return *this;
  }

  
  
  srcChars += srcStart;

  if(srcLength < 0) {
    
    if((srcLength = u_strlen(srcChars)) == 0) {
      return *this;
    }
  }

  int32_t oldLength = length();
  int32_t newLength = oldLength + srcLength;

  
  const UChar* oldArray = getArrayStart();
  if (isBufferWritable() &&
      oldArray < srcChars + srcLength &&
      srcChars < oldArray + oldLength) {
    
    UnicodeString copy(srcChars, srcLength);
    if (copy.isBogus()) {
      setToBogus();
      return *this;
    }
    return doAppend(copy.getArrayStart(), 0, srcLength);
  }

  
  if((newLength <= getCapacity() && isBufferWritable()) ||
      cloneArrayIfNeeded(newLength, getGrowCapacity(newLength))) {
    UChar *newArray = getArrayStart();
    
    
    
    
    
    
    
    if(srcChars != newArray + oldLength) {
      us_arrayCopy(srcChars, 0, newArray, oldLength, srcLength);
    }
    setLength(newLength);
  }
  return *this;
}