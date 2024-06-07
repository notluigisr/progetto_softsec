void SSL::verifyState(const RecordLayerHeader& rlHeader)
{
    if (GetError()) return;

    if (rlHeader.version_.major_ != 3 || rlHeader.version_.minor_ > 2) {
        SetError(badVersion_error);
        return;
    }

    if (states_.getRecord() == recordNotReady || 
            (rlHeader.type_ == application_data &&        
             states_.getHandShake() != handShakeReady) )  
              SetError(record_layer);
}