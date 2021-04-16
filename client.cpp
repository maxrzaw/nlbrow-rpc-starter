#include "client_library.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "ERROR: Usage is './client <port>'" << endl;
        return 0;
    }
    int port = atoi(argv[1]);

    list<string> memes;
    memes.push_back("ben reeBes");
    char evil[] = "evi\0l";
    std::string evil_str = std::string(evil, sizeof(evil));
    //evil_str has the embedded null char and two at the end
    memes.push_back(evil_str);
    memes.push_back("haha jk... unLESS?");

    // Before appending 'F'.
    printList(memes);
    memes = client_append(port, memes, 'F');

    // After appending 'F'.
    printList(memes);

    return 0;
}
