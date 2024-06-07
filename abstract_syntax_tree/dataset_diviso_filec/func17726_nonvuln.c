TiledInputFile::initialize ()
{
    
    
    
    
    if(!isMultiPart(_data->version) &&
       !isNonImage(_data->version) && 
       isTiled(_data->version) && 
       _data->header.hasType() )
    {
        _data->header.setType(TILEDIMAGE);
    }
    
    if (_data->partNumber == -1)
    {
        if (!isTiled (_data->version))
            throw IEX_NAMESPACE::ArgExc ("STR");
        
    }
    else
    {
        if(_data->header.hasType() && _data->header.type()!=TILEDIMAGE)
        {
            throw IEX_NAMESPACE::ArgExc ("STR");
        }
    }
    
    _data->header.sanityCheck (true);

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

    _data->bytesPerPixel = calculateBytesPerPixel (_data->header);

    _data->maxBytesPerTileLine = _data->bytesPerPixel * _data->tileDesc.xSize;

    _data->tileBufferSize = _data->maxBytesPerTileLine * _data->tileDesc.ySize;

    
    
    

    for (size_t i = 0; i < _data->tileBuffers.size(); i++)
    {
        _data->tileBuffers[i] = new TileBuffer (newTileCompressor
						  (_data->header.compression(),
						   _data->maxBytesPerTileLine,
						   _data->tileDesc.ySize,
						   _data->header));

        if (!_data->_streamData->is->isMemoryMapped ())
            _data->tileBuffers[i]->buffer = new char [_data->tileBufferSize];
    }

    _data->tileOffsets = TileOffsets (_data->tileDesc.mode,
				      _data->numXLevels,
				      _data->numYLevels,
				      _data->numXTiles,
				      _data->numYTiles);
}