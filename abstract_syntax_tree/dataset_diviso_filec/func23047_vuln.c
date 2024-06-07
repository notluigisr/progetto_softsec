ScanLineInputFile::ScanLineInputFile
    (const Header &header,
     OPENEXR_IMF_INTERNAL_NAMESPACE::IStream *is,
     int numThreads)
:
    _data (new Data (numThreads)),
    _streamData (new InputStreamMutex())
{
    _streamData->is = is;
    _data->memoryMapped = is->isMemoryMapped();

    initialize(header);
    
    
    
    
    
    
    
    _data->version=0;
    readLineOffsets (*_streamData->is,
                     _data->lineOrder,
                     _data->lineOffsets,
                     _data->fileIsComplete);
}