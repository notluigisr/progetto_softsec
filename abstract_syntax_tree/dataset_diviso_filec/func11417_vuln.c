B44Compressor::B44Compressor
    (const Header &hdr,
     size_t maxScanLineSize,
     size_t numScanLines,
     bool optFlatFields)
:
    Compressor (hdr),
    _maxScanLineSize (maxScanLineSize),
    _optFlatFields (optFlatFields),
    _format (XDR),
    _numScanLines (numScanLines),
    _tmpBuffer (0),
    _outBuffer (0),
    _numChans (0),
    _channels (hdr.channels()),
    _channelData (0)
{
    
    (void)_maxScanLineSize;
    
    
    
    
    
    

    _tmpBuffer = new unsigned short
        [checkArraySize (uiMult (maxScanLineSize, numScanLines),
                         sizeof (unsigned short))];

    const ChannelList &channels = header().channels();
    int numHalfChans = 0;

    for (ChannelList::ConstIterator c = channels.begin();
	 c != channels.end();
	 ++c)
    {
	assert (pixelTypeSize (c.channel().type) % pixelTypeSize (HALF) == 0);
	++_numChans;

	if (c.channel().type == HALF)
	    ++numHalfChans;
    }

    
    
    

    size_t padding = 12 * numHalfChans * (numScanLines + 3) / 4;

    _outBuffer = new char
        [uiAdd (uiMult (maxScanLineSize, numScanLines), padding)];

    _channelData = new ChannelData[_numChans];

    int i = 0;

    for (ChannelList::ConstIterator c = channels.begin();
	 c != channels.end();
	 ++c, ++i)
    {
	_channelData[i].ys = c.channel().ySampling;
	_channelData[i].type = c.channel().type;
	_channelData[i].pLinear = c.channel().pLinear;
	_channelData[i].size =
	    pixelTypeSize (c.channel().type) / pixelTypeSize (HALF);
    }

    const Box2i &dataWindow = hdr.dataWindow();

    _minX = dataWindow.min.x;
    _maxX = dataWindow.max.x;
    _maxY = dataWindow.max.y;

    
    
    
    

    assert (sizeof (unsigned short) == pixelTypeSize (HALF));

    if (_numChans == numHalfChans)
	_format = NATIVE;
}