MagickExport void GetDrawInfo(const ImageInfo *image_info,DrawInfo *draw_info)
{
  const char
    *option;

  ExceptionInfo
    *exception;

  ImageInfo
    *clone_info;

  
  (void) LogMagickEvent(TraceEvent,GetMagickModule(),"STR");
  assert(draw_info != (DrawInfo *) NULL);
  (void) ResetMagickMemory(draw_info,0,sizeof(*draw_info));
  clone_info=CloneImageInfo(image_info);
  GetAffineMatrix(&draw_info->affine);
  exception=AcquireExceptionInfo();
  (void) QueryColorCompliance("STR",AllCompliance,&draw_info->fill,
    exception);
  (void) QueryColorCompliance("STR",AllCompliance,&draw_info->stroke,
    exception);
  draw_info->stroke_width=1.0;
  draw_info->alpha=OpaqueAlpha;
  draw_info->fill_rule=EvenOddRule;
  draw_info->linecap=ButtCap;
  draw_info->linejoin=MiterJoin;
  draw_info->miterlimit=10;
  draw_info->decorate=NoDecoration;
  draw_info->pointsize=12.0;
  draw_info->undercolor.alpha=(Quantum) TransparentAlpha;
  draw_info->compose=OverCompositeOp;
  draw_info->render=MagickTrue;
  draw_info->debug=IsEventLogging();
  draw_info->stroke_antialias=clone_info->antialias;
  if (clone_info->font != (char *) NULL)
    draw_info->font=AcquireString(clone_info->font);
  if (clone_info->density != (char *) NULL)
    draw_info->density=AcquireString(clone_info->density);
  draw_info->text_antialias=clone_info->antialias;
  if (clone_info->pointsize != 0.0)
    draw_info->pointsize=clone_info->pointsize;
  draw_info->border_color=clone_info->border_color;
  if (clone_info->server_name != (char *) NULL)
    draw_info->server_name=AcquireString(clone_info->server_name);
  option=GetImageOption(clone_info,"STR");
  if (option != (const char *) NULL)
    draw_info->direction=(DirectionType) ParseCommandOption(
      MagickDirectionOptions,MagickFalse,option);
  else
    draw_info->direction=UndefinedDirection;
  option=GetImageOption(clone_info,"STR");
  if (option != (const char *) NULL)
    (void) CloneString(&draw_info->encoding,option);
  option=GetImageOption(clone_info,"STR");
  if (option != (const char *) NULL)
    (void) CloneString(&draw_info->family,option);
  option=GetImageOption(clone_info,"STR");
  if (option != (const char *) NULL)
    (void) QueryColorCompliance(option,AllCompliance,&draw_info->fill,
      exception);
  option=GetImageOption(clone_info,"STR");
  if (option != (const char *) NULL)
    draw_info->gravity=(GravityType) ParseCommandOption(MagickGravityOptions,
      MagickFalse,option);
  option=GetImageOption(clone_info,"STR");
  if (option != (const char *) NULL)
    draw_info->interline_spacing=StringToDouble(option,(char **) NULL);
  option=GetImageOption(clone_info,"STR");
  if (option != (const char *) NULL)
    draw_info->interword_spacing=StringToDouble(option,(char **) NULL);
  option=GetImageOption(clone_info,"STR");
  if (option != (const char *) NULL)
    draw_info->kerning=StringToDouble(option,(char **) NULL);
  option=GetImageOption(clone_info,"STR");
  if (option != (const char *) NULL)
    (void) QueryColorCompliance(option,AllCompliance,&draw_info->stroke,
      exception);
  option=GetImageOption(clone_info,"STR");
  if (option != (const char *) NULL)
    draw_info->stroke_width=StringToDouble(option,(char **) NULL);
  option=GetImageOption(clone_info,"STR");
  if (option != (const char *) NULL)
    draw_info->style=(StyleType) ParseCommandOption(MagickStyleOptions,
      MagickFalse,option);
  option=GetImageOption(clone_info,"STR");
  if (option != (const char *) NULL)
    (void) QueryColorCompliance(option,AllCompliance,&draw_info->undercolor,
      exception);
  option=GetImageOption(clone_info,"STR");
  if (option != (const char *) NULL)
    {
      ssize_t
        weight;

      weight=ParseCommandOption(MagickWeightOptions,MagickFalse,option);
      if (weight == -1)
        weight=StringToUnsignedLong(option);
      draw_info->weight=(size_t) weight;
    }
  exception=DestroyExceptionInfo(exception);
  draw_info->signature=MagickCoreSignature;
  clone_info=DestroyImageInfo(clone_info);
}