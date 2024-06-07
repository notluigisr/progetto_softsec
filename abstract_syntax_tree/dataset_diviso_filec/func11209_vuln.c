ActionReply Smb4KMountHelper::unmount(const QVariantMap &args)
{
  ActionReply reply;
  
  
  reply.addData("STR"]);

  
  
  bool mountpoint_ok = false;
  KMountPoint::List mountpoints = KMountPoint::currentMountPoints(KMountPoint::BasicInfoNeeded|KMountPoint::NeedMountOptions);

  for(int j = 0; j < mountpoints.size(); j++)
  {
#ifdef Q_OS_LINUX
    if (QString::compare(args["STR"].toString(),
                         mountpoints.at(j)->mountPoint(), Qt::CaseInsensitive) == 0 &&
        QString::compare(mountpoints.at(j)->mountType(), "STR", Qt::CaseInsensitive) == 0)
#else
    if (QString::compare(args["STR"].toString(),
                         mountpoints.at(j)->mountPoint(), Qt::CaseInsensitive) == 0 &&
        QString::compare(mountpoints.at(j)->mountType(), "STR", Qt::CaseInsensitive) == 0)
#endif
    {
      mountpoint_ok = true;
      break;
    }
    else
    {
      continue;
    }
  }

  if (!mountpoint_ok)
  {
    reply.setErrorCode(ActionReply::HelperError);
    reply.setErrorDescription(i18n("STR"));
    return reply;
  }
  else
  {
    
  }

  KProcess proc(this);
  proc.setOutputChannelMode(KProcess::SeparateChannels);
  proc.setProcessEnvironment(QProcessEnvironment::systemEnvironment());
  
  
  QStringList command;
  command << args["STR"].toString();
  command << args["STR"].toStringList();
  command << args["STR"].toString();

  proc.setProgram(command);

  
  proc.start();

  if (proc.waitForStarted(-1))
  {
    
    
    
    bool user_kill = false;

    while (!proc.waitForFinished(10))
    {
      if (HelperSupport::isStopped())
      {
        proc.kill();
        user_kill = true;
        break;
      }
      else
      {
        
      }
    }

    if (proc.exitStatus() == KProcess::CrashExit)
    {
      if (!user_kill)
      {
        reply.setErrorCode(ActionReply::HelperError);
        reply.setErrorDescription(i18n("STR"));
        return reply;
      }
      else
      {
        
      }
    }
    else
    {
      
      QString stdErr = QString::fromUtf8(proc.readAllStandardError());
      reply.addData("STR", stdErr.trimmed());
    }
  }
  else
  {
    reply.setErrorCode(ActionReply::HelperError);
    reply.setErrorDescription(i18n("STR"));
  }

  return reply;
}