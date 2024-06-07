DeepScanLineInputFile::compatibilityInitialize(OPENEXR_IMF_INTERNAL_NAMESPACE::IStream& is)
{
    is.seekg(0);
    
    
    
    
    
    _data->multiPartBackwardSupport = true;
    _data->multiPartFile = new MultiPartInputFile(is, _data->numThreads);
    InputPartData* part = _data->multiPartFile->getPart(0);
    
    multiPartInitialize(part);
}