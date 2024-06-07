void XMLRPC_CleanupValue(XMLRPC_VALUE value) {
   if(value) {
      if(value->iRefCount > 0) {
         value->iRefCount --;
      }

#ifdef XMLRPC_DEBUG_REFCOUNT
      if(value->id.str) {
			printf ("STR", value->id.str,
					  value->iRefCount);
      }
      else {
			printf ("STR", value,
					  value->iRefCount);
      }
#endif

      if(value->type == xmlrpc_vector) {
         if(value->v) {
            if(value->iRefCount == 0) {
               XMLRPC_VALUE cur = (XMLRPC_VALUE)Q_Head(value->v->q);
               while( cur ) {
                  XMLRPC_CleanupValue(cur);
   
                  
                  if(value->v && value->v->q) {
                     cur = Q_Next(value->v->q);
                  }
                  else {
                     break;
                  }
               }

               Q_Destroy(value->v->q);
               my_free(value->v->q);
               my_free(value->v);
            }
         }
      }


      if(value->iRefCount == 0) {

         
         switch(value->type) {
            case xmlrpc_empty:
            case xmlrpc_base64:
            case xmlrpc_boolean:
            case xmlrpc_datetime:
            case xmlrpc_double:
            case xmlrpc_int:
            case xmlrpc_string:
            case xmlrpc_vector:
#ifdef XMLRPC_DEBUG_REFCOUNT
               if(value->id.str) {
                  printf("STR", value->id.str);
               }
               else {
                  printf("STR", value);
               }
#endif 
               simplestring_free(&value->id);
               simplestring_free(&value->str);

               memset(value, 0, sizeof(STRUCT_XMLRPC_VALUE));
               my_free(value);
               break;
            default:
				fprintf (stderr,
							"STR");
               break;
         }
      }
   }
}