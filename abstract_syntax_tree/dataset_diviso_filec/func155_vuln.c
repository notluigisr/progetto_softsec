void ScanLineInputFile::initialize(const Header& header)
{
        _data->header = header;

        _data->lineOrder = _data->header.lineOrder();

        const Box2i &dataWindow = _data->header.dataWindow();

        _data->minX = dataWindow.min.x;
        _data->maxX = dataWindow.max.x;
        _data->minY = dataWindow.min.y;
        _data->maxY = dataWindow.max.y;

        Compression comp = _data->header.compression();

        _data->linesInBuffer =
            numLinesInBuffer (comp);

        int lineOffsetSize = (dataWindow.max.y - dataWindow.min.y +
                              _data->linesInBuffer) / _data->linesInBuffer;

        
        
        
        
        
        
        
        
        if (lineOffsetSize > gLargeChunkTableSize)
        {
            Int64 pos = _streamData->is->tellg();
            _streamData->is->seekg(pos + (lineOffsetSize-1)*sizeof(Int64));
            Int64 temp;
            OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (*_streamData->is, temp);
            _streamData->is->seekg(pos);

        }


        size_t maxBytesPerLine = bytesPerLineTable (_data->header,
                                                    _data->bytesPerLine);

        if (maxBytesPerLine*numLinesInBuffer(comp) > INT_MAX)
        {
            throw IEX_NAMESPACE::InputExc("STR");
        }


        
        
        
        for (size_t i = 0; i < _data->lineBuffers.size(); i++)
        {
            _data->lineBuffers[i] = new LineBuffer (newCompressor(comp,
                                                 maxBytesPerLine,
                                                 _data->header));
        }



        _data->lineBufferSize = maxBytesPerLine * _data->linesInBuffer;

        if (!_streamData->is->isMemoryMapped())
        {
            for (size_t i = 0; i < _data->lineBuffers.size(); i++)
            {
                _data->lineBuffers[i]->buffer = (char *) EXRAllocAligned(_data->lineBufferSize*sizeof(char),16);
                if (!_data->lineBuffers[i]->buffer)
                {
                    throw IEX_NAMESPACE::LogicExc("STR");
                }
            }
        }
        _data->nextLineBufferMinY = _data->minY - 1;

        offsetInLineBufferTable (_data->bytesPerLine,
                                 _data->linesInBuffer,
                                 _data->offsetInLineBuffer);


        _data->lineOffsets.resize (lineOffsetSize);
}