        std::string PngChunk::makeUtf8TxtChunk(const std::string& keyword, const std::string& text, bool compress)
        {
            
            
            

            
            
            

            
            std::string chunkData = keyword;
            if (compress) {
                static const char flags[] = {0x00, 0x01, 0x00, 0x00, 0x00};
                chunkData += std::string(flags, 5) + zlibCompress(text);
            } else {
                static const char flags[] = {0x00, 0x00, 0x00, 0x00, 0x00};
                chunkData += std::string(flags, 5) + text;
            }
            
            byte length[4];
            ul2Data(length, static_cast<uint32_t>(chunkData.size()), bigEndian);
            
            std::string chunkType = "STR";
            std::string crcData = chunkType + chunkData;
            uLong tmp = crc32(0L, Z_NULL, 0);
            tmp = crc32(tmp, (const Bytef*)crcData.data(), static_cast<uInt>(crcData.size()));
            byte crc[4];
            ul2Data(crc, tmp, bigEndian);
            
            return std::string((const char*)length, 4) + chunkType + chunkData + std::string((const char*)crc, 4);

        }  