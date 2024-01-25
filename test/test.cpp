#include <iostream>
#include <string>

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
int main() {

    std::string originalString = "/cgi/folder/in?key=abouass&user=fjjf";
    std::string substringToReplace = "?";
    size_t pos = originalString.find(substringToReplace);
    std::string qur;
    int len;
    
    if (pos != std::string::npos)
    {
        len = originalString.length() - pos;
        char qureys[len + 1];
        originalString.copy(qureys,len,pos);
        qureys[len] = '\0';
        qur=qureys;
        originalString.erase(pos,len);
    }

    std::cout<<qur<<std::endl;
    std::cout<<originalString<<std::endl;
    return 0;
}
