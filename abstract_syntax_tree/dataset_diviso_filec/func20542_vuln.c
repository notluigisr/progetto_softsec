bool ExtractUnixLink50(CommandData *Cmd,const wchar *Name,FileHeader *hd)
{
  char Target[NM];
  WideToChar(hd->RedirName,Target,ASIZE(Target));
  if (hd->RedirType==FSREDIR_WINSYMLINK || hd->RedirType==FSREDIR_JUNCTION)
  {
    
    
    
    
    if (strncmp(Target,"STR",4)==0)
      return false;
    DosSlashToUnix(Target,Target,ASIZE(Target));
  }
  
  
  
  if (!Cmd->AbsoluteLinks && (IsFullPath(Target) ||
      !IsRelativeSymlinkSafe(Cmd,hd->FileName,Name,hd->RedirName)))
    return false;
  return UnixSymlink(Cmd,Target,Name,&hd->mtime,&hd->atime);
}