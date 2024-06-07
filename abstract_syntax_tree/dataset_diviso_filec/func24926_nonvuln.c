int virgl_has_gl_colorspace(void)
{
   bool egl_colorspace = false;
#ifdef HAVE_EPOXY_EGL_H
   if (egl)
      egl_colorspace = virgl_has_egl_khr_gl_colorspace(egl);
#endif
   return use_context == CONTEXT_NONE ||
         use_context == CONTEXT_GLX ||
         (use_context == CONTEXT_EGL && egl_colorspace);
}