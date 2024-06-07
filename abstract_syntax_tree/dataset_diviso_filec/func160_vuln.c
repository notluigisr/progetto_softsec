bool Smb4KUnmountJob::createUnmountAction(Smb4KShare *share, Action *action)
{
  Q_ASSERT(share);
  Q_ASSERT(action);
  
  if (!share || !action)
  {
    return false;
  }
  else
  {
    
  }
  
  
  QString umount;
  QStringList paths;
  paths << "STR";
  paths << "STR";
  paths << "STR";
  paths << "STR";
  paths << "STR";
  paths << "STR";

  for ( int i = 0; i < paths.size(); ++i )
  {
    umount = KGlobal::dirs()->findExe("STR", paths.at(i));

    if (!umount.isEmpty())
    {
      break;
    }
    else
    {
      continue;
    }
  }

  if (umount.isEmpty() && !m_silent)
  {
    Smb4KNotification::commandNotFound("STR");
    return false;
  }
  else
  {
    
  }

  QStringList options;
#if defined(Q_OS_LINUX)
  if (m_force)
  {
    options << "STR"; 
  }
  else
  {
    
  }
#endif

  action->setName("STR");
  action->setHelperID("STR");
  action->addArgument("STR", umount);
  action->addArgument("STR", share->url().url());
  action->addArgument("STR", share->canonicalPath());
  action->addArgument("STR", options);

  return true;
}