#include "../headers/parser.h"

vector<string> Parse::ReadFile(const char *path)
{
    fstream fs(path);
    string buffer;
    string codebuffer;
    vector<string> code;
    while(fs >> buffer){
        codebuffer += buffer + " ";
        if(codebuffer.find(":") != string::npos || codebuffer.find("and...") != string::npos){
            code.push_back(codebuffer);
            codebuffer = "";
        }
        if(codebuffer.find("well thats it subscribe to the chanel!") != string::npos){
            code.push_back(codebuffer);
            codebuffer = "";
            break;
        }
    }
    fs.close();
    return code;
}
