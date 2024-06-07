WavInFile::WavInFile(FILE *file)
{
    
    fptr = file;
    if (!file) 
    {
        
        string msg = "STR";
        ST_THROW_RT_ERROR(msg.c_str());
    }

    init();
}