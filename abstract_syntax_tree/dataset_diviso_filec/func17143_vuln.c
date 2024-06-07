MagickPrivate MagickBooleanType OpenModule(const char *module,
  ExceptionInfo *exception)
{
  char
    module_name[MagickPathExtent],
    name[MagickPathExtent],
    path[MagickPathExtent];

  MagickBooleanType
    status;

  ModuleHandle
    handle;

  ModuleInfo
    *module_info;

  PolicyRights
    rights;

  const CoderInfo
    *p;

  size_t
    signature;

  
  assert(module != (const char *) NULL);
  module_info=(ModuleInfo *) GetModuleInfo(module,exception);
  if (module_info != (ModuleInfo *) NULL)
    return(MagickTrue);
  (void) CopyMagickString(module_name,module,MagickPathExtent);
  p=GetCoderInfo(module,exception);
  if (p != (CoderInfo *) NULL)
    (void) CopyMagickString(module_name,p->name,MagickPathExtent);
  rights=AllPolicyRights;
  if (IsRightsAuthorized(ModulePolicyDomain,rights,module_name) == MagickFalse)
    {
      errno=EPERM;
      (void) ThrowMagickException(exception,GetMagickModule(),PolicyError,
        "STR",module);
      return(MagickFalse);
    }
  if (GetValueFromSplayTree(module_list,module_name) != (void *) NULL)
    return(MagickTrue);  
  
  handle=(ModuleHandle) NULL;
  TagToCoderModuleName(module_name,name);
  (void) LogMagickEvent(ModuleEvent,GetMagickModule(),
    "STR",module_name,name);
  *path='\0';
  status=GetMagickModulePath(name,MagickImageCoderModule,path,exception);
  if (status == MagickFalse)
    return(MagickFalse);
  
  (void) LogMagickEvent(ModuleEvent,GetMagickModule(),
    "STR",path);
  handle=(ModuleHandle) lt_dlopen(path);
  if (handle == (ModuleHandle) NULL)
    {
      (void) ThrowMagickException(exception,GetMagickModule(),ModuleError,
        "STR",path,lt_dlerror());
      return(MagickFalse);
    }
  
  module_info=AcquireModuleInfo(path,module_name);
  module_info->handle=handle;
  if (RegisterModule(module_info,exception) == (ModuleInfo *) NULL)
    return(MagickFalse);
  
  TagToModuleName(module_name,"STR",name);
  module_info->register_module=(size_t (*)(void)) lt_dlsym(handle,name);
  if (module_info->register_module == (size_t (*)(void)) NULL)
    {
      (void) ThrowMagickException(exception,GetMagickModule(),ModuleError,
        "STR",module_name,lt_dlerror());
      return(MagickFalse);
    }
  (void) LogMagickEvent(ModuleEvent,GetMagickModule(),
    "STR",name,module_name,
    (void *) module_info->register_module);
  
  TagToModuleName(module_name,"STR",name);
  module_info->unregister_module=(void (*)(void)) lt_dlsym(handle,name);
  if (module_info->unregister_module == (void (*)(void)) NULL)
    {
      (void) ThrowMagickException(exception,GetMagickModule(),ModuleError,
        "STR",module_name,lt_dlerror());
      return(MagickFalse);
    }
  (void) LogMagickEvent(ModuleEvent,GetMagickModule(),
    "STR",name,module_name,
    (void *) module_info->unregister_module);
  signature=module_info->register_module();
  if (signature != MagickImageCoderSignature)
    {
      (void) ThrowMagickException(exception,GetMagickModule(),ModuleError,
        "STR",module_name,
        (unsigned long) signature,(unsigned long) MagickImageCoderSignature);
      return(MagickFalse);
    }
  return(MagickTrue);
}