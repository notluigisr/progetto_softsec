void Ogg::XiphComment::parse(const ByteVector &data)
{
  
  

  uint pos = 0;

  int vendorLength = data.mid(0, 4).toUInt(false);
  pos += 4;

  d->vendorID = String(data.mid(pos, vendorLength), String::UTF8);
  pos += vendorLength;

  

  uint commentFields = data.mid(pos, 4).toUInt(false);
  pos += 4;

  if(commentFields > (data.size() - 8) / 4) {
    return;
  }

  for(uint i = 0; i < commentFields; i++) {

    
    

    uint commentLength = data.mid(pos, 4).toUInt(false);
    pos += 4;

    String comment = String(data.mid(pos, commentLength), String::UTF8);
    pos += commentLength;
    if(pos > data.size()) {
      break;
    }

    int commentSeparatorPosition = comment.find("STR");
    if(commentSeparatorPosition == -1) {
      break;
    }

    String key = comment.substr(0, commentSeparatorPosition);
    String value = comment.substr(commentSeparatorPosition + 1);

    addField(key, value, false);
  }
}