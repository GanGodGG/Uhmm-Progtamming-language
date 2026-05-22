#include <iostream>
#include <any>
#include "../headers/parser.h"

using namespace std;

struct VariableInfo{
    void* ptr;
    string type;
};

unordered_map<string, VariableInfo> mem;
bool GetCommand(string command, void*& ret){
    if(command.find("i gonna add these things cuz i got them and they'll be") != string::npos){
        size_t val_s = command.find("they'll be ") + 11;
        size_t val_e = command.find(" n'");
        string val = command.substr(val_s, val_e - val_s);

        size_t val_s2 = command.find("n' ") + 3;
        size_t val_e2 = command.find(" so");
        string val2 = command.substr(val_s2, val_e2 - val_s2);

        if(mem[val].type == mem[val2].type && mem[val2].type == "numbr"){
            int sum = ((int)mem[val].ptr + (int)mem[val2].ptr);
            ret = (void*)sum;
            return true;
        }
    }
    return false;
}

int main(int argc, unsigned char** argv){

    vector<string> all =  Parse::ReadFile("code.uhm");

    
    bool openBuffer = false;

    for(auto& s : all){
        if(s.find("uhmm hello everyone ts me coolgamer code and now ther i got it:") != string::npos){
            openBuffer = true;
        }
        if(openBuffer){
            if(s.find("uhmm") != string::npos){
                if(s.find("i think its gonna") != string::npos){
                    
                    size_t type_s = s.find("gonna be ") + 9;
                    size_t type_e = s.find(" and ths");
                    std::string tname = s.substr(type_s, type_e - type_s);  

                    size_t val_s = s.find("is will be ") + 11;
                    size_t val_e = s.find(" with ");
                    std::string vname = s.substr(val_s, val_e - val_s);
                    
                    size_t name_s = s.find("name ") + 5;
                    size_t name_e = s.find(" and...");
                    std::string name = s.substr(name_s, name_e - name_s);
                    //HAHAHAHAHHHAH xd
                    if(tname == "numbr"){
                        void* val = nullptr;
                        if(GetCommand(vname, val)){
                            mem[name] = {val, tname};
                            //cout << "-----" << "memory name is " << name << " val is " << val << "-----" << endl;
                            continue;
                        }
                        mem[name] = {(void*)stoi(vname), tname};
                        //cout << "-----" << "memory name is " << name << " val is " << vname << "-----" << endl;
                    }
                    continue;
                }
                if(s.find("uhmm i gonna show up my obs and show that thing") != string::npos){
                    size_t name_s = s.find("thing ") + 6;
                    size_t name_e = s.find(" and...");
                    std::string name = s.substr(name_s, name_e - name_s); 

                    VariableInfo vi = mem[name];

                    if(vi.type == "numbr"){
                        cout << (int)mem[name].ptr << endl; 
                    }
                }
            }
        }

    }

    return 0;
}