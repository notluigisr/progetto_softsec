TiledInputFile::rawTileData (int &dx, int &dy,
			     int &lx, int &ly,
                             const char *&pixelData,
			     int &pixelDataSize)
{
    try
    {
        Lock lock (*_data->_streamData);

        if (!isValidTile (dx, dy, lx, ly))
            throw IEX_NAMESPACE::ArgExc ("STR"
			       "STR");

        TileBuffer *tileBuffer = _data->getTileBuffer (0);

        
        
        
        
        int old_dx=dx;
        int old_dy=dy;
        int old_lx=lx;
        int old_ly=ly;
        if(isMultiPart(version()))
        {
            _data->_streamData->is->seekg(_data->tileOffsets(dx,dy,lx,ly));
        }
        readNextTileData (_data->_streamData, _data, dx, dy, lx, ly,
			  tileBuffer->buffer,
                          pixelDataSize);
        if(isMultiPart(version()))
        {
            if (old_dx!=dx || old_dy !=dy || old_lx!=lx || old_ly!=ly)
            {
                throw IEX_NAMESPACE::ArgExc ("STR");
            }
        }
        pixelData = tileBuffer->buffer;
    }
    catch (IEX_NAMESPACE::BaseExc &e)
    {
        REPLACE_EXC (e, "STR"
                     "STR" << e.what());
        throw;
    }
}