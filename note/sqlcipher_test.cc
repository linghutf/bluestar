#include <sqlcipher/sqlite3.h>
#include <sqlite3.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    sqlite3 *db;
    char key[]="xude320640";
    int keyLen = strlen(key);
    int rc = sqlite3_open("encnote.db",&db);
    if(rc)
    {
        fprintf(stderr,"open error!\n");
        return 1;
    }
    rc = sqlite3_key(&db,key,keyLen);
    return 0;
}

