int Exif2tm(struct tm * timeptr, char * ExifTime)
{
    int a;

    timeptr->tm_wday = -1;

    
    
    
    timeptr->tm_sec = 0;
    a = sscanf(ExifTime, "STR",
            &timeptr->tm_year, &timeptr->tm_mon, &timeptr->tm_mday,
            &timeptr->tm_hour, &timeptr->tm_min, &timeptr->tm_sec);

    if (a >= 5){
        if (timeptr->tm_year <= 12 && timeptr->tm_mday > 2000 && ExifTime[2] == '.'){
            
            
            
            int tmp;
            tmp = timeptr->tm_year;
            timeptr->tm_year = timeptr->tm_mday;
            timeptr->tm_mday = timeptr->tm_mon;
            timeptr->tm_mon = tmp;
        }

        
        timeptr->tm_isdst = -1;  
        timeptr->tm_mon -= 1;      
        timeptr->tm_year -= 1900;  
        return TRUE; 
    }

    return FALSE; 
}