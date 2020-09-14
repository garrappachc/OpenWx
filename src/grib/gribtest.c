#include "grib2.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned char *cgrib;
    g2int  listsec0[3],listsec1[13],numlocal,numfields;
    long   lskip,n,lgrib,iseek;
    int    unpack,ret,ierr,expand;
    gribfield  *gfld;
    FILE   *fptr;
    size_t  lengrib;
 
    iseek=0;
    unpack=1;
    expand=1;
    fptr=fopen("/home/garapich/gfs.t06z.pgrb2full.0p50.f000","r");
    for (;;) {
         seekgb(fptr,iseek,32000,&lskip,&lgrib);
         if (lgrib == 0) break;    // end loop at EOF or problem
         cgrib=(unsigned char *)malloc(lgrib);
         ret=fseek(fptr,lskip,SEEK_SET);
         lengrib=fread(cgrib,sizeof(unsigned char),lgrib,fptr);
         iseek=lskip+lgrib;
         ierr=g2_info(cgrib,listsec0,listsec1,&numfields,&numlocal);
         for (n=0;n<numfields;n++) {
            ierr=g2_getfld(cgrib,n+1,unpack,expand,&gfld);

            if (gfld->fld) {
                for (int i = 0; i < gfld->ndpts; ++i) {
                    printf("%f", gfld->fld[i]);
                }
            }

            printf("\n");

            g2_free(gfld);
         }
         free(cgrib);
    }
}
