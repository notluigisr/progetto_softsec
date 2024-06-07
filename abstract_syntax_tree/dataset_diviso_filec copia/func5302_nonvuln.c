StrUtil_StrToDouble(double *out,      
                    const char *str)  
{
   char *ptr = NULL;

   ASSERT(out);
   ASSERT(str);

   errno = 0;

   *out = strtod(str, &ptr);

   

   return *ptr == '\0' && errno != ERANGE;
}