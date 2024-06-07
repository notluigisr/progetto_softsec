    void CiffDirectory::readDirectory(const byte* pData,
                                      uint32_t    size,
                                      ByteOrder   byteOrder)
    {
        if (size < 4)
            throw Error(kerCorruptedMetadata);
        uint32_t o = getULong(pData + size - 4, byteOrder);
        if ( o+2 > size )
            throw Error(kerCorruptedMetadata);
        uint16_t count = getUShort(pData + o, byteOrder);
#ifdef DEBUG
        std::cout << "STR" << std::dec << o
                  <<"STR";
#endif
        o += 2;
        if ( (o + (count * 10)) > size )
            throw Error(kerCorruptedMetadata);

        for (uint16_t i = 0; i < count; ++i) {
            uint16_t tag = getUShort(pData + o, byteOrder);
            CiffComponent::UniquePtr m;
            switch (CiffComponent::typeId(tag)) {
            case directory: m = CiffComponent::UniquePtr(new CiffDirectory); break;
            default: m = CiffComponent::UniquePtr(new CiffEntry); break;
            }
            m->setDir(this->tag());
            m->read(pData, size, o, byteOrder);
            add(std::move(m));
            o += 10;
        }
    }  