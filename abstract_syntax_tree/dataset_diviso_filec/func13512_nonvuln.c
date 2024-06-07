  bool CharLookup::insert(char key, char value) 
  {
    if (data[(unsigned char)key] != -1)
      return false;
    data[(unsigned char)key] = value;
    return true;
  }