#define _XOPEN_SOURCE 500
#include "ntfw.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "list.h"

#define LIST(name,size,parent) struct *tree

double totalSize = 0;

static int traverse(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf)
{
 
    
    
    if (tflag == FTW_NS)
    {
        printf("-------\n");
        //return 1;
    }
    else if (tflag == FTW_F)
    {
        long int size = (intmax_t) sb->st_size;
        
            printf("%-3s %2d ",
            (tflag == FTW_D) ?   "d"   : (tflag == FTW_DNR) ? "dnr" :
            (tflag == FTW_DP) ?  "dp"  : (tflag == FTW_F) ?   "f" :
            (tflag == FTW_NS) ?  "ns"  : (tflag == FTW_SL) ?  "sl" :
            (tflag == FTW_SLN) ? "sln" : "???",
            ftwbuf->level);
            printf("%7jd", (long int) sb->st_size);
            printf("   %-40s %d %s\n", fpath, ftwbuf->base, fpath + ftwbuf->base);
        
        

    }       

    return 0;           /* To tell nftw() to continue */
}

int main(int argc, char *argv[])
{
    int flags = 0;
    
    if (argc > 2 && strchr(argv[2], 'd') != NULL)
        flags |= FTW_DEPTH;
    if (argc > 2 && strchr(argv[2], 'p') != NULL)
        flags |= FTW_PHYS;

    

    if (nftws((argc < 2) ? "/" : argv[1], traverse, 100, flags)
            == -1) {
        perror("nftw");
        //printf("Total Size = %lf \n", totalSize);
        //exit(EXIT_FAILURE);
    }
    printf("Total Size = %lf \n", totalSize);
    exit(EXIT_SUCCESS);
}
