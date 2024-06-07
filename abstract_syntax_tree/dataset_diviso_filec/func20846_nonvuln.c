    BSONElement(const char* d, int fieldNameSize, int totalSize, CachedSizeTag) : data(d) {
        if (eoo()) {
            fieldNameSize_ = 0;
            this->totalSize = 1;
        } else {
            if (fieldNameSize == -1) {
                fieldNameSize_ = strlen(d + 1 ) + 1 ;
            } else {
                fieldNameSize_ = fieldNameSize;
            }
            if (totalSize == -1) {
                this->totalSize = computeSize();
            } else {
                this->totalSize = totalSize;
            }
        }
    }