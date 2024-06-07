    void CrwMap::decodeBasic(const CiffComponent& ciffComponent,
                             const CrwMapping*    pCrwMapping,
                                   Image&         image,
                                   ByteOrder      byteOrder)
    {
        assert(pCrwMapping != 0);
        
        ExifKey key(pCrwMapping->tag_, Internal::groupName(pCrwMapping->ifdId_));
        Value::AutoPtr value;
        if (ciffComponent.typeId() != directory) {
            value = Value::create(ciffComponent.typeId());
            uint32_t size = 0;
            if (pCrwMapping->size_ != 0) {
                
                size = pCrwMapping->size_;
            }
            else if (ciffComponent.typeId() == asciiString) {
                
                uint32_t i = 0;
                for (;    i < ciffComponent.size()
                       && ciffComponent.pData()[i] != '\0'; ++i) {
                    
                }
                size = ++i;
            }
            else {
                
                size = ciffComponent.size();
            }
            value->read(ciffComponent.pData(), size, byteOrder);
        }
        
        image.exifData().add(key, value.get());
    } 