#include <iostream>
#include <any>
#include <stdexcept>
#include <variant>
#include "../headers/parser.h"

using namespace std;
using VarType = variant<int, float, double, bool, string>;
unordered_map<string, VarType> mem;

VarType allocTypeByValue(string vname);

VarType Operate(VarType a, VarType b, std::string operation) {
    return visit([&](auto&& valA, auto&& valB) -> VarType {
        using T_A = decay_t<decltype(valA)>;
        using T_B = decay_t<decltype(valB)>;

        if constexpr (is_same_v<T_A, string> && is_same_v<T_B, string>) {
            if (operation == "add") return valA + valB;
            
            throw std::invalid_argument("Yo, you can't multiply or divide text, are you high?!");
        }
        
        else if constexpr (is_same_v<T_A, string> || is_same_v<T_B, string>) {
            throw std::invalid_argument("Dont mix numbrs and nolanmomstrings, you're not a Minecraft letsplayer!");
        }
        else {
            if (operation == "add") return valA + valB;
            if (operation == "sub") return valA - valB;
            if (operation == "mul") return valA * valB;
            if (operation == "div") {
                if (valB == 0) throw std::runtime_error("Division by zero!");
                return valA / valB;
            }
        }
        throw std::invalid_argument("Unknown operation");
    }, a, b);
}


bool GetCommand(string command, VarType& ret){
    if(command.find("these things cuz i got them and they'll be") != string::npos){
        size_t val_s = command.find("they'll be ") + 11;
        size_t val_e = command.find(" n'");
        string val = command.substr(val_s, val_e - val_s);

        size_t val_s2 = command.find("n' ") + 3;
        size_t val_e2 = command.find(" so");
        string val2 = command.substr(val_s2, val_e2 - val_s2);

         size_t op_s = command.find("i gonna ") + 8;
            size_t op_e = command.find(" these");

            string operation = command.substr(op_s, op_e - op_s);
            VarType sum;
            try{
                sum = Operate(mem[val], mem[val2], operation);
            }
            catch(invalid_argument e){
                cout << "Yo GANGOD is here i wanna say that ur code is so SHITTY ur not micraft letsplayer get the FUCK out of my IDE!!! Error at command: " << command << e.what() << endl;
            }
            ret = sum; 
            return true;
    }

    if(command.find("getting from my viewer") != string::npos){
        string input;
        getline(cin, input);
        ret = allocTypeByValue(input);
        return true;
    }
    return false;
}

VarType allocType(string tname, string vname){
    if(tname == "numbr"){
        return {stoi(vname)};
    }
    if(tname == "swim"){
        return {stof(vname)};
    }
    if(tname == "useless"){
        return {stod(vname)};
    }
    if(tname == "trueornot"){
        if(vname == "umausume"){
            return {true};
        }
        if(vname == "ronaldo"){
            return {false};
            }
    }
    if(tname == "nolanmomstring"){
        return vname;
    }
    return NULL;
}

VarType allocType(string tname){
    if(tname == "numbr"){
        return 0;
    }
    if(tname == "swim"){
        return 1.0f;
    }
    if(tname == "useless"){
        return 0.0;
    }
    if(tname == "trueornot"){
        return {false};
    }
    if(tname == "nolanmomstring"){
        return "";
    }
}

VarType allocTypeByValue(string vname)
{
    if(vname == "umausume") return {true};
    if(vname == "ronaldo")   return {false};

    bool has_dot = false;
    bool is_numeric = true;
    
    if (vname.empty()) return {0};

    for (size_t i = 0; i < vname.length(); i++) {
        if (vname[i] == '-') {
            if (i != 0) is_numeric = false;
            continue;
        }
        if (vname[i] == '.') {
            if (has_dot) is_numeric = false;
            has_dot = true;
            continue;
        }
        if (!isdigit(vname[i])) {
            is_numeric = false;
            break;
        }
    }

    
    if (!is_numeric) {
        size_t val_s2 = vname.find("NOLSTRING ") + 10;
        size_t val_e2 = vname.find("ENDNOLSTRING");
        if(val_s2 != string::npos && val_e2 != string::npos && val_e2 > val_s2){
            return vname.substr(val_s2, val_e2 - val_s2);
        }
        return {vname + " "}; 
    }

    
    try {
        if (has_dot) {
            return {stof(vname)};
        } else {
            return {stoi(vname)};
        }
    } 
    catch (...) {
        size_t val_s2 = vname.find("NOLSTRING ") + 10;
        size_t val_e2 = vname.find("ENDNOLSTRING");
        if(val_s2 != string::npos && val_e2 != string::npos && val_e2 > val_s2){
            return vname.substr(val_s2, val_e2 - val_s2);
        }
        return {vname + " "}; 
    }
    return NULL;
}

void ReadCommands(vector<string> commands, bool bufferEnabled = false){
    bool openBuffer = bufferEnabled;
    int line = 0;
    for(size_t i = 0; i < commands.size(); i++){
        const string& s = commands.at(i);

        if(s.find("&*") != string::npos) continue;

        if(s.find("uhmm hello everyone ts me coolgamer code and now ther i got it") != string::npos){
            openBuffer = true;
        }

        if(s.find("well thats it subscribe to the chanel!") != string::npos){
            if(openBuffer){
                openBuffer = false;
            }
            else{
                cout << "YOU ENDED LETSPLAY WITHOUT START OBS!!!!!!!!!!!!!!!!!! YOU FUCKER!!!" << endl;
            }
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
                    VarType val;
                    if(GetCommand(vname, val)){
                        mem[name] = val;
                        continue;
                    }

                    if(vname.find("NOLSTRING") != string::npos){
                        size_t val_s2 = vname.find("NOLSTRING ") + 10;
                        size_t val_e2 = vname.find("ENDNOLSTRING");
                        string strVal = vname.substr(val_s2, val_e2 - val_s2);
                        mem[name] = strVal;
                        continue;
                    }

                    mem[name] = allocType(tname, vname);
                    continue;
                }
                if(s.find("i gonna show up my obs and show that thing") != string::npos){
                    size_t name_s = s.find("thing ") + 6;
                    size_t name_e = s.find(" and...");
                    std::string name = s.substr(name_s, name_e - name_s); 
                    VarType vi;
                    if(name.find("NOLSTRING") != string::npos){
                        size_t val_s2 = name.find("NOLSTRING ") + 10;
                        size_t val_e2 = name.find("ENDNOLSTRING");
                        vi = name.substr(val_s2, val_e2 - val_s2);
                        cout << get<string>(vi) << endl; 
                        continue;
                    }
                    else{
                        vi = mem[name];
                    }

                    //AHAHHAHAHAHHAH H A XD wth is this code im writing
                    if(vi.index() == 0){ // int
                        cout << get<int>(vi) << endl; 
                    }
                    else if(vi.index() == 1){ // float
                        cout << get<float>(vi) << endl; 
                    }
                    else if(vi.index() == 2){ // double
                        cout << get<double>(vi) << endl; 
                    }
                    else if(vi.index() == 3){ // bool
                        cout << (get<bool>(vi) == true ? "umausume (true)" : "ronaldo (false)") << endl; 
                    }
                    else if(vi.index() == 4){
                        cout << get<string>(vi) << endl; 
                    }
                }
                if(s.find("yanderedev") != string::npos && !(s.find("yanderedev blog end") != string::npos)){
                    size_t name_s = s.find("yanderedev ") + 11;
                    size_t name_e = s.find(" is");
                    std::string name = s.substr(name_s, name_e - name_s); 

                    size_t val_s = s.find("is ") + 3;
                    size_t val_e = s.find(" and...");
                    std::string val = s.substr(val_s, val_e - val_s); 
                    vector<string> cycleCommands;
                    for(size_t j = i + 1; j < commands.size(); j++){
                        const string& line = commands.at(j);
                        if(line.find("yanderedev blog end") != string::npos){
                            break;
                        }
                        cycleCommands.push_back(line);
                    }
                    if(mem[name] == allocTypeByValue(val)){
                        ReadCommands(cycleCommands, true);
                    }
                    i += cycleCommands.size();
                    continue;
                }
                if(s.find("im having dementia for") != string::npos)
                {
                    size_t name_s = s.find("for ") + 4;
                    size_t name_e = s.find(" until");
                    std::string name = s.substr(name_s, name_e - name_s); 
                    
                    size_t typ_s = s.find("until ") + 6;
                    size_t typ_e = s.find(" of");
                    std::string type = s.substr(typ_s, typ_e - typ_s); 

                    size_t val_s = s.find("of ") + 3;
                    size_t val_e = s.find(" and...");
                    std::string val = s.substr(val_s, val_e - val_s); 

                    string cycleLine;
                    vector<string> cycleCommands;
                    for(size_t j = i + 1; j < commands.size(); j++){
                        const string& line = commands.at(j);
                        if(line.find("im not having dementia") != string::npos){
                            break;
                        }
                        cycleCommands.push_back(line);
                    }

                    while(mem[name] == allocType(type, val)){
                        ReadCommands(cycleCommands, true);
                    }
                    i += cycleCommands.size();
                }
                
            }
            else{
                if(s.size() != string::npos){
                    cout << "uhmm you forgor 'uhmm' at line " << line << " and... " << endl;
                }
            }
        }
        line++;
    }

}

int main(int argc, unsigned char** argv){

    vector<string> all =  Parse::ReadFile("../../code.uhm");

    ReadCommands(all);
    return 0;
}