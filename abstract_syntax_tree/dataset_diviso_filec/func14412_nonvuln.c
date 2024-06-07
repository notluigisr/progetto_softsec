copyFromFrameBuffer (char *& writePtr,
		     const char *& readPtr,
                     const char * endPtr,
		     size_t xStride,
                     Compressor::Format format,
		     PixelType type)
{
    
    
    
    

    if (format == Compressor::XDR)
    {
        
        
        

        switch (type)
        {
          case OPENEXR_IMF_INTERNAL_NAMESPACE::UINT:

            while (readPtr <= endPtr)
            {
                Xdr::write <CharPtrIO> (writePtr,
                                        *(const unsigned int *) readPtr);
                readPtr += xStride;
            }
            break;

          case OPENEXR_IMF_INTERNAL_NAMESPACE::HALF:

            while (readPtr <= endPtr)
            {
                Xdr::write <CharPtrIO> (writePtr, *(const half *) readPtr);
                readPtr += xStride;
            }
            break;

          case OPENEXR_IMF_INTERNAL_NAMESPACE::FLOAT:

            while (readPtr <= endPtr)
            {
                Xdr::write <CharPtrIO> (writePtr, *(const float *) readPtr);
                readPtr += xStride;
            }
            break;

          default:

            throw IEX_NAMESPACE::ArgExc ("STR");
        }
    }
    else
    {
        
        
        

        switch (type)
        {
          case OPENEXR_IMF_INTERNAL_NAMESPACE::UINT:

            while (readPtr <= endPtr)
            {
                for (size_t i = 0; i < sizeof (unsigned int); ++i)
                    *writePtr++ = readPtr[i];

                readPtr += xStride;
            }
            break;

          case OPENEXR_IMF_INTERNAL_NAMESPACE::HALF:

            while (readPtr <= endPtr)
            {
                *(half *) writePtr = *(const half *) readPtr;
                writePtr += sizeof (half);
                readPtr += xStride;
            }
            break;

          case OPENEXR_IMF_INTERNAL_NAMESPACE::FLOAT:

            while (readPtr <= endPtr)
            {
                for (size_t i = 0; i < sizeof (float); ++i)
                    *writePtr++ = readPtr[i];

                readPtr += xStride;
            }
            break;
            
          default:

            throw IEX_NAMESPACE::ArgExc ("STR");
        }
    }
}