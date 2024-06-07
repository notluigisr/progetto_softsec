  Statement_Ptr Expand::operator()(Debug_Ptr d)
  {
    
    d->perform(&eval);
    return 0;
  }