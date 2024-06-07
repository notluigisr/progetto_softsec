int ReplaceThumbnail(const char * ThumbFileName)
{
    FILE * ThumbnailFile;
    int ThumbLen, NewExifSize;
    Section_t * ExifSection;
    uchar * ThumbnailPointer;

    if (ImageInfo.ThumbnailOffset == 0 || ImageInfo.ThumbnailAtEnd == FALSE){
        if (ThumbFileName == NULL){
            
            
            return FALSE;
        }

        
        
        fprintf(stderr,"STR");
        return FALSE;
    }

    if (ThumbFileName){
        ThumbnailFile = fopen(ThumbFileName,"STR");

        if (ThumbnailFile == NULL){
            noread:
            ErrFatal("STR");
            return FALSE;
        }

        
        fseek(ThumbnailFile, 0, SEEK_END);

        ThumbLen = ftell(ThumbnailFile);
        fseek(ThumbnailFile, 0, SEEK_SET);

        if (ThumbLen + ImageInfo.ThumbnailOffset > 0x10000-20){
            ErrFatal("STR");
        }
    }else{
        if (ImageInfo.ThumbnailSize == 0){
             return FALSE;
        }

        ThumbLen = 0;
        ThumbnailFile = NULL;
    }

    ExifSection = FindSection(M_EXIF);

    NewExifSize = ImageInfo.ThumbnailOffset+8+ThumbLen;
    ExifSection->Data = (uchar *)realloc(ExifSection->Data, NewExifSize);

    ThumbnailPointer = ExifSection->Data+ImageInfo.ThumbnailOffset+8;

    if (ThumbnailFile){
        if (fread(ThumbnailPointer, 1, ThumbLen, ThumbnailFile) != ThumbLen){
            goto noread;
        }
        fclose(ThumbnailFile);
    }

    ImageInfo.ThumbnailSize = ThumbLen;

    Put32u(ExifSection->Data+ImageInfo.ThumbnailSizeOffset+8, ThumbLen);

    ExifSection->Data[0] = (uchar)(NewExifSize >> 8);
    ExifSection->Data[1] = (uchar)NewExifSize;
    ExifSection->Size = NewExifSize;

    return TRUE;
}