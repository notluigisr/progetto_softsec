TiledInputFile::TiledInputFile (OPENEXR_IMF_INTERNAL_NAMESPACE::IStream &is, int numThreads):
    _data (new Data (numThreads))
{
    _data->_deleteStream=false;
    
    
    
    

    bool streamDataCreated = false;

    try
    {
	readMagicNumberAndVersionField(is, _data->version);

	
	
	
	if (isMultiPart(_data->version))
        {
	    compatibilityInitialize(is);
            return;
        }

	streamDataCreated = true;
	_data->_streamData = new InputStreamMutex();
	_data->_streamData->is = &is;
	_data->header.readFrom (*_data->_streamData->is, _data->version);
	initialize();
        
        _data->tileOffsets.readFrom (*(_data->_streamData->is), _data->fileIsComplete,false,false);
	_data->memoryMapped = _data->_streamData->is->isMemoryMapped();
	_data->_streamData->currentPosition = _data->_streamData->is->tellg();
    }
    catch (IEX_NAMESPACE::BaseExc &e)
    {
        if (streamDataCreated) delete _data->_streamData;
	delete _data;

	REPLACE_EXC (e, "STR"
                 "STR" << e.what());
	throw;
    }
    catch (...)
    {
        if (streamDataCreated) delete _data->_streamData;
	delete _data;
        throw;
    }
}