CharString *Formattable::internalGetCharString(UErrorCode &status) {
    if(fDecimalStr == NULL) {
      if (fDecimalQuantity == NULL) {
        
        
        
        
        
        LocalPointer<DecimalQuantity> dq(new DecimalQuantity(), status);
        if (U_FAILURE(status)) { return nullptr; }
        populateDecimalQuantity(*dq, status);
        if (U_FAILURE(status)) { return nullptr; }
        fDecimalQuantity = dq.orphan();
      }

      fDecimalStr = new CharString();
      if (fDecimalStr == NULL) {
        status = U_MEMORY_ALLOCATION_ERROR;
        return NULL;
      }
      
      
      
      if (fDecimalQuantity->isZero()) {
        fDecimalStr->append("STR", -1, status);
      } else if (std::abs(fDecimalQuantity->getMagnitude()) < 5) {
        fDecimalStr->appendInvariantChars(fDecimalQuantity->toPlainString(), status);
      } else {
        fDecimalStr->appendInvariantChars(fDecimalQuantity->toScientificString(), status);
      }
    }
    return fDecimalStr;
}