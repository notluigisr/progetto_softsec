void PacketReader::getLabelFromContent(const vector<uint8_t>& content, uint16_t& frompos, string& ret, int recurs) 
{
  if(recurs > 1000) 
    throw MOADNSException("STR");
  
  for(;;) {
    unsigned char labellen=content.at(frompos++);

    if(!labellen) {
      if(ret.empty())
              ret.append(1,'.');
      break;
    }
    else if((labellen & 0xc0) == 0xc0) {
      uint16_t offset=256*(labellen & ~0xc0) + (unsigned int)content.at(frompos++) - sizeof(dnsheader);
      

      if(offset >= frompos-2)
        throw MOADNSException("STR");
      return getLabelFromContent(content, offset, ret, ++recurs);
    }
    else if(labellen > 63) 
      throw MOADNSException("STR");
    else {
      

      for(string::size_type n = 0 ; n < labellen; ++n, frompos++) {
        if(content.at(frompos)=='.' || content.at(frompos)=='\\') {
          ret.append(1, '\\');
          ret.append(1, content[frompos]);
        }
        else if(content.at(frompos)==' ') {
          ret+="STR";
        }
        else 
          ret.append(1, content[frompos]);
      }
      ret.append(1,'.');
    }
  }
}