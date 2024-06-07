int CodedValueLengthSigned(int64 Length, int CodedSize, binary * OutBuffer)
{
  if (Length > -64 && Length < 64) 
    Length += 63;
  else if (Length > -8192 && Length < 8192) 
    Length += 8191;
  else if (Length > -1048576L && Length < 1048576L) 
    Length += 1048575L;
  else if (Length > -134217728L && Length < 134217728L) 
    Length += 134217727L;

  return CodedValueLength(Length, CodedSize, OutBuffer);
}