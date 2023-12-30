#include <algorithm> 
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <map>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>


#include <stdio.h>
#include <sys/stat.h>

#include <stdio.h>
#include <sys/stat.h>

int pathExists(const char *path) {
    struct stat fileStat;
    return stat(path, &fileStat) == 0;
}

int main() {
    const char *path = "/nfs/homes/abouassi/Desktop/wepserv/configfile/Makefidle";

    if (pathExists(path)) {
        printf("Path %s exists.\n", path);
    } else {
        printf("Path %s does not exist.\n", path);
    }

    return 0;
}