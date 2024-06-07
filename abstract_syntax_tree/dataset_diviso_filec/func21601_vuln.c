MagickExport MemoryInfo *AcquireVirtualMemory(const size_t count,
  const size_t quantum)
{
  MemoryInfo
    *memory_info;

  size_t
    length;

  length=count*quantum;
  if ((count == 0) || (quantum != (length/count)))
    {
      errno=ENOMEM;
      return((MemoryInfo *) NULL);
    }
  memory_info=(MemoryInfo *) MagickAssumeAligned(AcquireAlignedMemory(1,
    sizeof(*memory_info)));
  if (memory_info == (MemoryInfo *) NULL)
    ThrowFatalException(ResourceLimitFatalError,"STR");
  (void) ResetMagickMemory(memory_info,0,sizeof(*memory_info));
  memory_info->length=length;
  memory_info->signature=MagickCoreSignature;
  if (AcquireMagickResource(MemoryResource,length) != MagickFalse)
    {
      memory_info->blob=AcquireAlignedMemory(1,length);
      if (memory_info->blob != NULL)
        {
          memory_info->type=AlignedVirtualMemory;
          return(memory_info);
        }
    }
  RelinquishMagickResource(MemoryResource,length);
  if (AcquireMagickResource(MapResource,length) != MagickFalse)
    {
      
      memory_info->blob=MapBlob(-1,IOMode,0,length);
      if (memory_info->blob != NULL)
        {
          memory_info->type=MapVirtualMemory;
          return(memory_info);
        }
      if (AcquireMagickResource(DiskResource,length) != MagickFalse)
        {
          int
            file;

          
          file=AcquireUniqueFileResource(memory_info->filename);
          if (file != -1)
            {
              if ((lseek(file,length-1,SEEK_SET) == (length-1)) &&
                  (write(file,"",1) == 1))
                {
                  memory_info->blob=MapBlob(file,IOMode,0,length);
                  if (memory_info->blob != NULL)
                    {
                      (void) close(file);
                      memory_info->type=MapVirtualMemory;
                      return(memory_info);
                    }
                }
              
              (void) close(file);
              (void) RelinquishUniqueFileResource(memory_info->filename);
              *memory_info->filename = '\0';
            }
        }
      RelinquishMagickResource(DiskResource,length);
    }
  RelinquishMagickResource(MapResource,length);
  if (memory_info->blob == NULL)
    {
      memory_info->blob=AcquireMagickMemory(length);
      if (memory_info->blob != NULL)
        memory_info->type=UnalignedVirtualMemory;
    }
  if (memory_info->blob == NULL)
    memory_info=RelinquishVirtualMemory(memory_info);
  return(memory_info);
}