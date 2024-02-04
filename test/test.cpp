#include <iostream>
#include <string>
#include <stdio.h>
#include <dirent.h>
#include <iostream>
#include<cstring>
// int main() {
//     std::string originalString = "/cgi/folder/in";
//     std::string substringToReplace = "/cgi";
//     std::string replacementString = "/nfs/homes/abouassi/Desktop/root_dir/";

//     size_t pos = originalString.find(substringToReplace);

//     if (pos != std::string::npos) {
//         originalString.replace(pos, substringToReplace.length(), replacementString);

//         std::cout << "Modified string: " << originalString << std::endl;
//     } else {
//         std::cout << "Substring not found in the original string." << std::endl;
//     }

//     return 0;
// }
// int main() {

//     std::string originalString = "/cgi/folder/in?key=abouass&user=fjjf";
//     std::string substringToReplace = "?";
//     size_t pos = originalString.find(substringToReplace);
//     std::string qur;
//     int len;
    
//     if (pos != std::string::npos)
//     {
//         len = originalString.length() - pos;
//         char qureys[len + 1];
//         originalString.copy(qureys,len,pos);
//         qureys[len] = '\0';
//         qur=qureys;
//         originalString.erase(pos,len);
//     }

//     std::cout<<qur<<std::endl;
//     std::cout<<originalString<<std::endl;
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <limits.h>

int checkDirectoryPermissions(const char *absolutePath) {
    // Resolve the absolute path
    char resolvedPath[PATH_MAX];
    char *result = realpath(absolutePath, resolvedPath);

    if (result == NULL) {
        perror("Error resolving path");
        return -1;
    }

    // Use stat to get information about the file/directory
    struct stat stat_info;
    if (stat(resolvedPath, &stat_info) == 0) {
        // Check if it's a directory
        if (S_ISDIR(stat_info.st_mode)) {
            // Print the permissions
            printf("Directory Permissions for %s: ", resolvedPath);
            printf((stat_info.st_mode & S_IRUSR) ? "r" : "-");
            printf((stat_info.st_mode & S_IWUSR) ? "w" : "-");
            printf((stat_info.st_mode & S_IXUSR) ? "x" : "-");
            printf((stat_info.st_mode & S_IRGRP) ? "r" : "-");
            printf((stat_info.st_mode & S_IWGRP) ? "w" : "-");
            printf((stat_info.st_mode & S_IXGRP) ? "x" : "-");
            printf((stat_info.st_mode & S_IROTH) ? "r" : "-");
            printf((stat_info.st_mode & S_IWOTH) ? "w" : "-");
            printf((stat_info.st_mode & S_IXOTH) ? "x" : "-");
            printf("\n");
            return 0;
        } else {
            printf("%s is not a directory.\n", resolvedPath);
            return -1;
        }
    } else {
        perror("Error while getting file/directory information");
        return -1;
    }
}
void 

int main() {
    const char *absolutePath = "/nfs/homes/abouassi/Desktop/wepserv/delete/root_dir";

    if (checkDirectoryPermissions(absolutePath) == 0) {
        // Successfully checked permissions
    } else {
        // Handle error
    }

    return 0;
}
