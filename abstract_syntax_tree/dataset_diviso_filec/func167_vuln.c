cmsBool  CMSEXPORT cmsPipelineCat(cmsPipeline* l1, const cmsPipeline* l2)
{
    cmsStage* mpe, *NewMPE;

    
    
    if (l1 ->Elements == NULL && l2 ->Elements == NULL) {
        l1 ->InputChannels  = l2 ->InputChannels;
        l1 ->OutputChannels = l2 ->OutputChannels;
    }

    
    for (mpe = l2 ->Elements;
         mpe != NULL;
         mpe = mpe ->Next) {

            
             NewMPE = cmsStageDup(mpe);

             if (NewMPE == NULL) {
                 return FALSE;
             }

             cmsPipelineInsertStage(l1, cmsAT_END, NewMPE);
    }

  BlessLUT(l1);
  return TRUE;
}