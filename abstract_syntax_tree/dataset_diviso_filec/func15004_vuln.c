getTiledChunkOffsetTableSize(const Header& header)
{
    
    
    

    const Box2i &dataWindow = header.dataWindow();
    
    
    
    

    int* numXTiles;
    int* numYTiles;
    int numXLevels;
    int numYLevels;
    precalculateTileInfo (header.tileDescription(),
                          dataWindow.min.x, dataWindow.max.x,
                          dataWindow.min.y, dataWindow.max.y,
                          numXTiles, numYTiles,
                          numXLevels, numYLevels);

    
    
    
    Int64 lineOffsetSize = 0;
    const TileDescription &desc = header.tileDescription();
    switch (desc.mode)
    {
        case ONE_LEVEL:
        case MIPMAP_LEVELS:
            for (int i = 0; i < numXLevels; i++)
            {
                lineOffsetSize += static_cast<Int64>(numXTiles[i]) * static_cast<Int64>(numYTiles[i]);
                if ( lineOffsetSize > static_cast<Int64>(std::numeric_limits<int>::max()) )
                {
                    throw IEX_NAMESPACE::LogicExc("STR");
                }
            }
           break;
        case RIPMAP_LEVELS:
            for (int i = 0; i < numXLevels; i++)
            {
                for (int j = 0; j < numYLevels; j++)
                {
                     lineOffsetSize += static_cast<Int64>(numXTiles[i]) * static_cast<Int64>(numYTiles[j]);
                     if ( lineOffsetSize > static_cast<Int64>(std::numeric_limits<int>::max()) )
                     {
                        throw IEX_NAMESPACE::LogicExc("STR");
                     }
                }
            }
           break;
        case NUM_LEVELMODES :
            throw IEX_NAMESPACE::LogicExc("STR");
    }

    delete[] numXTiles;
    delete[] numYTiles;

    return static_cast<int>(lineOffsetSize);
}