void ReadReal(cmsIT8* it8, int inum)
{
    it8->dnum = (cmsFloat64Number) inum;

    while (isdigit(it8->ch)) {

        it8->dnum = it8->dnum * 10.0 + (it8->ch - '0');
        NextCh(it8);
    }

    if (it8->ch == '.') {        

        cmsFloat64Number frac = 0.0;      
        int prec = 0;                     

        NextCh(it8);               

        while (isdigit(it8->ch)) {

            frac = frac * 10.0 + (it8->ch - '0');
            prec++;
            NextCh(it8);
        }

        it8->dnum = it8->dnum + (frac / xpow10(prec));
    }

    
    if (toupper(it8->ch) == 'E') {

        int e;
        int sgn;

        NextCh(it8); sgn = 1;

        if (it8->ch == '-') {

            sgn = -1; NextCh(it8);
        }
        else
            if (it8->ch == '+') {

                sgn = +1;
                NextCh(it8);
            }

            e = 0;
            while (isdigit(it8->ch)) {

                if ((cmsFloat64Number) e * 10L < INT_MAX)
                    e = e * 10 + (it8->ch - '0');

                NextCh(it8);
            }

            e = sgn*e;
            it8 -> dnum = it8 -> dnum * xpow10(e);
    }
}