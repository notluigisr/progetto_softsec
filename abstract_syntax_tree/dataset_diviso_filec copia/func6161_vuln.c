void sdb_edit(procinfo *pi)
{
  char * filename = omStrDup("STR");
  sprintf(filename+7,"STR",getpid());
  FILE *fp=fopen(filename,"STR");
  if (fp==NULL)
  {
    Print("STR",filename);
    omFree(filename);
    return;
  }
  if (pi->language!= LANG_SINGULAR)
  {
    Print("STR",pi->language);
    fclose(fp);
    fp=NULL;
  }
  else
  {
    const char *editor=getenv("STR");
    if (editor==NULL)
      editor=getenv("STR");
    if (editor==NULL)
      editor="STR";
    editor=omStrDup(editor);

    if (pi->data.s.body==NULL)
    {
      iiGetLibProcBuffer(pi);
      if (pi->data.s.body==NULL)
      {
        PrintS("STR");
        fclose(fp);
        si_unlink(filename);
        omFree(filename);
        return;
      }
    }

    fwrite(pi->data.s.body,1,strlen(pi->data.s.body),fp);
    fclose(fp);

    int pid=fork();
    if (pid!=0)
    {
      si_wait(&pid);
    }
    else if(pid==0)
    {
      if (strchr(editor,' ')==NULL)
      {
        execlp(editor,editor,filename,NULL);
        Print("STR",editor);
      }
      else
      {
        char *p=(char *)omAlloc(strlen(editor)+strlen(filename)+2);
        sprintf(p,"STR",editor,filename);
        system(p);
      }
      exit(0);
    }
    else
    {
      PrintS("STR");
    }

    fp=fopen(filename,"STR");
    if (fp==NULL)
    {
      Print("STR",filename);
    }
    else
    {
      fseek(fp,0L,SEEK_END);
      long len=ftell(fp);
      fseek(fp,0L,SEEK_SET);

      omFree((ADDRESS)pi->data.s.body);
      pi->data.s.body=(char *)omAlloc((int)len+1);
      myfread( pi->data.s.body, len, 1, fp);
      pi->data.s.body[len]='\0';
      fclose(fp);
    }
  }
  si_unlink(filename);
  omFree(filename);
}