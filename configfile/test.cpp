#include <iostream>
#include <string>

int main() {
    std::string originalString = "/cgi/folder/in";
    std::string substringToReplace = "/cgi";
    std::string replacementString = "/nfs/homes/abouassi/Desktop/root_dir/";

    size_t pos = originalString.find(substringToReplace);

    if (pos != std::string::npos) {
        originalString.replace(pos, substringToReplace.length(), replacementString);

        std::cout << "Modified string: " << originalString << std::endl;
    } else {
        std::cout << "Substring not found in the original string." << std::endl;
    }

    return 0;
}
