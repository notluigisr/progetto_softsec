void WavOutFile::write(const short *buffer, int numElems)
{
    int res;

    
    if (numElems < 1) return;   

    switch (header.format.bits_per_sample)
    {
        case 8:
        {
            int i;
            unsigned char *temp = (unsigned char *)getConvBuffer(numElems);
            
            for (i = 0; i < numElems; i ++)
            {
                temp[i] = (unsigned char)(buffer[i] / 256 + 128);
            }
            
            write(temp, numElems);
            break;
        }

        case 16:
        {
            

            
            short *pTemp = (short *)getConvBuffer(numElems * sizeof(short));
            memcpy(pTemp, buffer, numElems * 2);
            _swap16Buffer(pTemp, numElems);

            res = (int)fwrite(pTemp, 2, numElems, fptr);

            if (res != numElems) 
            {
                ST_THROW_RT_ERROR("STR");
            }
            bytesWritten += 2 * numElems;
            break;
        }

        default:
        {
            stringstream ss;
            ss << "STR";
            ss << (int)header.format.bits_per_sample;
            ss << "STR";
            ST_THROW_RT_ERROR(ss.str().c_str());
        }
    }
}