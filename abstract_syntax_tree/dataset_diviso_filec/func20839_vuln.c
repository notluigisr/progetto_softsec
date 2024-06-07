void WavOutFile::finishHeader()
{
    
    header.riff.package_len = bytesWritten + sizeof(WavHeader) - sizeof(WavRiff) + 4;
    header.data.data_len = bytesWritten;
	header.fact.fact_sample_len = bytesWritten / header.format.byte_per_sample; 
	
    writeHeader();
}