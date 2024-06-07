mj_color_correct(gx_color_value *Rptr ,gx_color_value *Gptr , gx_color_value *Bptr )
                                                                
{
        short	R,G,B;				
        short	C,M,Y;				
        short	H,D,Wa;				
        long	S;					

        R = *Rptr;
        G = *Gptr;
        B = *Bptr;
        if (R==G) {
                if (G==B) {						
                        C=M=Y=1023-v_tbl[R];
                        *Rptr = C;
                        *Gptr = M;
                        *Bptr = Y;
                        return;
                } else if (G>B) {				
                        D = G-B;
                        Wa  = R;
                        H  = 256;
                } else {						
                        D = G-B;
                        Wa = R;
                        H = 1024;
                }
        }

        if (R>G) {
                if (G>=B) {			
                        Wa=R;
                        D=R-B;
                        H=(G-B)*256/D;
                } else if (R>B) {		
                        Wa=R;
                        D=R-G;
                        H=1536-(B-G)*256/D;
                } else {			
                        Wa=B;
                        D=B-G;
                        H=1024+(R-G)*256/D;
                }
        } else {
                if (R>B) {			
                        Wa=G;
                        D=G-B;
                        H=512-(R-B)*256/D;
                } else if (G>B) {		
                        Wa=G;
                        D=G-R;
                        H=512+(B-R)*256/D;
                } else {			
                        Wa=B;
                        D=B-R;
                        H=1024-(G-R)*256/D;
                }
        }

        if(Wa!=0){
                if(Wa==D){
                        Wa=v_tbl[Wa];
                        D=Wa/4;
                } else {
                        S=((long)D<<16)/Wa;
                        Wa=v_tbl[Wa];
                        D= ( ((long)S*Wa)>>18 );
                }
        }
        Wa=1023-Wa;

        C=(HtoCMY[H*3  ])*D/256+Wa;
        M=(HtoCMY[H*3+1])*D/256+Wa;
        Y=(HtoCMY[H*3+2])*D/256+Wa;
        if (C<0)
                C=0;
        if (M<0)
                M=0;
        if (Y<0)
                Y=0;

        if(H>256 && H<1024){		
                short	work;
                work=(((long)grnsep[M]*(long)grnsep2[H-256])>>16);
                C+=work;
                Y+=work+work;
                M-=work+work;
                if(C>1023) C=1023;
                if(Y>1023) Y=1023;
        }

        *Rptr = C;
        *Gptr = M;
        *Bptr = Y;
}