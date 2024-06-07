        DataBuf PngChunk::decodeTXTChunk(const DataBuf& data, TxtChunkType type)
        {
            DataBuf key = keyTXTChunk(data);

#ifdef DEBUG
            std::cout << "STR"
                      << std::string((const char*)key.pData_, key.size_) << std::endl;
#endif
            return parseTXTChunk(data, key.size_, type);

        }  