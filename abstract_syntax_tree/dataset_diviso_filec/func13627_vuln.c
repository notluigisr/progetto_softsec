DeepTiledInputFile::Data::Data (int numThreads):
    numXTiles (0),
    numYTiles (0),
    partNumber (-1),
    multiPartBackwardSupport(false),
    numThreads(numThreads),
    memoryMapped(false),
    _streamData(NULL),
    _deleteStream(false)
{
    
    
    
    

    tileBuffers.resize (max (1, 2 * numThreads));
}