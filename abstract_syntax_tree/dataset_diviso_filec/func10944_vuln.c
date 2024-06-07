DeepTiledInputFile::initialize ()
{
    if (_data->partNumber == -1)
        if (_data->header.type() != DEEPTILE)
            throw IEX_NAMESPACE::ArgExc ("STR");
   if(_data->header.version()!=1)
   {
       THROW(IEX_NAMESPACE::ArgExc, "STR");
   }
        
    _data->header.sanityCheck (true);

    
    
    
    
    
    if (!isMultiPart(_data->version))
    {
        _data->validateStreamSize();
    }


    _data->tileDesc = _data->header.tileDescription();
    _data->lineOrder = _data->header.lineOrder();

    
    
    

    const Box2i &dataWindow = _data->header.dataWindow();
    _data->minX = dataWindow.min.x;
    _data->maxX = dataWindow.max.x;
    _data->minY = dataWindow.min.y;
    _data->maxY = dataWindow.max.y;

    
    
    

    precalculateTileInfo (_data->tileDesc,
                          _data->minX, _data->maxX,
                          _data->minY, _data->maxY,
                          _data->numXTiles, _data->numYTiles,
                          _data->numXLevels, _data->numYLevels);

    
    
    

    _data->tileOffsets = TileOffsets (_data->tileDesc.mode,
                                      _data->numXLevels,
                                      _data->numYLevels,
                                      _data->numXTiles,
                                      _data->numYTiles);

    for (size_t i = 0; i < _data->tileBuffers.size(); i++)
        _data->tileBuffers[i] = new TileBuffer ();

    _data->maxSampleCountTableSize = _data->tileDesc.ySize *
                                     _data->tileDesc.xSize *
                                     sizeof(int);

    _data->sampleCountTableBuffer.resizeErase(_data->maxSampleCountTableSize);

    _data->sampleCountTableComp = newCompressor(_data->header.compression(),
                                                _data->maxSampleCountTableSize,
                                                _data->header);
                                                
                                                
    const ChannelList & c=_data->header.channels();
    _data->combinedSampleSize=0;
    for(ChannelList::ConstIterator i=c.begin();i!=c.end();i++)
    {
        switch( i.channel().type )
        {
            case OPENEXR_IMF_INTERNAL_NAMESPACE::HALF  :
                _data->combinedSampleSize+=Xdr::size<half>();
                break;
            case OPENEXR_IMF_INTERNAL_NAMESPACE::FLOAT :
                _data->combinedSampleSize+=Xdr::size<float>();
                break;
            case OPENEXR_IMF_INTERNAL_NAMESPACE::UINT  :
                _data->combinedSampleSize+=Xdr::size<unsigned int>();
                break;
            default :
                THROW(IEX_NAMESPACE::ArgExc, "STR");
        }
    }
                                                  
}