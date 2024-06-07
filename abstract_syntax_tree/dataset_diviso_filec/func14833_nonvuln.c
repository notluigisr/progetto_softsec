    virtual uint receiveSamples(SAMPLETYPE *outBuffer, 
                                uint maxSamples                    
                                )
    {
        return output->receiveSamples(outBuffer, maxSamples);
    }