void APE::Properties::analyzeCurrent()
{
  
  d->file->seek(2, File::Current);
  ByteVector descriptor = d->file->readBlock(44);
  uint descriptorBytes = descriptor.mid(0,4).toUInt(false);

  if ((descriptorBytes - 52) > 0)
    d->file->seek(descriptorBytes - 52, File::Current);

  
  ByteVector header = d->file->readBlock(24);

  
  d->channels = header.mid(18, 2).toShort(false);
  d->sampleRate = header.mid(20, 4).toUInt(false);
  d->bitsPerSample = header.mid(16, 2).toShort(false);
  

  uint totalFrames = header.mid(12, 4).toUInt(false);
  uint blocksPerFrame = header.mid(4, 4).toUInt(false);
  uint finalFrameBlocks = header.mid(8, 4).toUInt(false);
  uint totalBlocks = totalFrames > 0 ? (totalFrames -  1) * blocksPerFrame + finalFrameBlocks : 0;
  d->length = totalBlocks / d->sampleRate;
  d->bitrate = d->length > 0 ? ((d->streamLength * 8L) / d->length) / 1000 : 0;
}