bool ExtractUnixLink30(CommandData *Cmd,ComprDataIO &DataIO,Archive &Arc,const wchar *LinkName)
{
  char Target[NM];
  if (IsLink(Arc.FileHead.FileAttr))
  {
    size_t DataSize=(size_t)Arc.FileHead.PackSize;
    if (DataSize>ASIZE(Target)-1)
      return false;
    if ((size_t)DataIO.UnpRead((byte *)Target,DataSize)!=DataSize)
      return false;
    Target[DataSize]=0;

    DataIO.UnpHash.Init(Arc.FileHead.FileHash.Type,1);
    DataIO.UnpHash.Update(Target,strlen(Target));
    DataIO.UnpHash.Result(&Arc.FileHead.FileHash);

    
    
    if (!DataIO.UnpHash.Cmp(&Arc.FileHead.FileHash,Arc.FileHead.UseHashKey ? Arc.FileHead.HashKey:NULL))
      return true;

    wchar TargetW[NM];
    CharToWide(Target,TargetW,ASIZE(TargetW));
    
    
    
    
    if (!Cmd->AbsoluteLinks && (*TargetW==0 || IsFullPath(TargetW) ||
        !IsRelativeSymlinkSafe(Cmd,Arc.FileHead.FileName,LinkName,TargetW)))
      return false;
    return UnixSymlink(Cmd,Target,LinkName,&Arc.FileHead.mtime,&Arc.FileHead.atime);
  }
  return false;
}