#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <sstream>

using namespace::std;

struct Node{
    vector<Node*> children;
    string value;
    Node(string s) : value(s){}
};

int getIntegerLength(string s, int start);
string convertToString(int num);
bool checkStmt(Node* parent);
bool checkWhile(Node* parent);
bool checkCond(Node* parent);
bool cCond(Node* parent);
bool checkAnd(Node* parent);
bool cAnd(Node* parent);
bool checkEq(Node* parent);
bool cEq(Node* parent);
bool checkCmp(Node* parent);
bool cCmp(Node* parent);
bool checkExpr(Node* parent);
bool cExpr(Node* parent);
bool checkMult(Node* parent);
bool cMult(Node* parent);
bool checkUnary(Node* parent);
bool checkParen(Node* parent);
bool checkBasic(Node* parent);

bool checkFor(Node* parent);
bool checkOptAssign(Node* parent);
bool checkOptCond(Node* parent);
bool checkAssign(Node* parent);

bool checkIf(Node* parent);
bool checkOptElse(Node* parent);

bool checkOutput(Node* parent);

void printTree(Node* node, int space);

struct token{
    string id;
    string num;
    string name;
    string position;
    string length;
    string value;
    token(string init_id, string init_num, string init_name, string init_position, string init_length, string init_value){
        id = init_id;
        num = init_num;
        name = init_name;
        position = init_position;
        length = init_length;
        value = init_value;
    }
};
vector<string> tokens;
vector<bool> record;
vector<token> toks;
int x = 0;
int n = 0;
Node* root = new Node("<node><nt>stmt</nt><children>");

int main(int argc, const char * argv[]) {
    set<string> unimplemented;
    map<string,int> map;
    set<string> set;
    map["!"] = 12;
    map["%"] = 13;
    map["&"] = 14;
    map["|"] = 15;
    map["+"] = 16;
    map["-"] = 17;
    map["*"] = 18;
    map["/"] = 19;
    map["{"] = 20;
    map["}"] = 21;
    map["["] = 22;
    map["]"] = 23;
    map[";"] = 24;
    map[","] = 25;
    map["<"] = 26;
    map[">"] = 27;
    map["="] = 28;
    map["<="] = 29;
    map[">="] = 30;
    map["!="] = 31;
    map[":="] = 32;
    map["("] = 33;
    map[")"] = 34;
    set.insert("#");
    set.insert("$");
    set.insert("'");
    set.insert(":");
    set.insert("?");
    set.insert("@");
    set.insert("\\");
    set.insert("^");
    set.insert("`");
    set.insert("~");
    set.insert(".");
    unimplemented.insert("%");
    unimplemented.insert("/");
    unimplemented.insert(",");
    int position = 0;
    int tokenNumber = 1;
    while (true) {
        string input;
        getline(cin, input);
        int i = 0;
        while (i<input.length()){
            if((input[i] - '0' >= 0) && (input[i] - '0'<= 9)){
                int len = getIntegerLength(input, i);
                int j = i + len;
                string substring = input.substr(i, len);
                if(j < input.length() && input[j] == '.'){
                    int len2 = getIntegerLength(input, j + 1);
                    string substring2 = input.substr(j + 1, len2);
                    int totalLen = len + len2 + 1;
                    tokens.push_back("TID: " + convertToString(tokenNumber) + ", TYPE: 4(FLOAT), POS: " + convertToString(position) + ", LEN: " + convertToString(totalLen) + ", VALUE: " + substring + "." + substring2);
                    record.push_back(true);
                    token *t = new token(convertToString(tokenNumber), convertToString(4), "FLOAT", convertToString(position), convertToString(totalLen), substring + "." + substring2);
                    toks.push_back(*t);
                    i += totalLen;
                    position += totalLen;
                    
                }else{
                    tokens.push_back("TID: " + convertToString(tokenNumber) + ", TYPE: 3(INT), POS: " + convertToString(position) + ", LEN: " + convertToString(len) + ", VALUE: " + substring);
                    record.push_back(true);
                    token *t = new token(convertToString(tokenNumber), convertToString(3), "INT", convertToString(position), convertToString(len), substring);
                    toks.push_back(*t);
                    i += len;
                    position += len;
                }
            }else if(input[i] == '.' && (input.length() - i >= 2) && ((input[i + 1] - '0' >= 0) && (input[i + 1] - '0' <= 9))){
                int len = getIntegerLength(input, i + 1);
                int totalLen = len + 1;
                tokens.push_back("TID: " + convertToString(tokenNumber) + ", TYPE: 4(FLOAT), POS: " + convertToString(position) + ", LEN: " + convertToString(totalLen) + ", VALUE: ." + input.substr(i + 1, len));
                record.push_back(true);
                token *t = new token(convertToString(tokenNumber), convertToString(4), "FLOAT", convertToString(position), convertToString(totalLen), input.substr(i + 1, len));
                toks.push_back(*t);
                i += totalLen;
                position += totalLen;
                
            }else if(input[i] == ' ' || input[i] == 0X09){
                int start = i + 1;
                while(start < input.length() && (input[start] == ' ' || input[start] == 0X09)){
                    start ++;
                }
                int len = start - i;
                i += len;
                position += len;
            }else if(input[i] == '#'){
                int start = i + 1;
                int len = 1;
                while(start < input.length() && (input[start] == 0X09 || (input[start] >= 0X20 && input[start] <= 0X7E))){
                    start++;
                    len++;
                }
                string substring = input.substr(i, len);
                i += len;
                position += len;
            }else if(input[i] == 'f' && input.length() - i >= 3 && input.substr(i, 3) == "for"){
                if(input.length() - i >=4 && (input[i+3] == '_' || (input[i+3] >= 0X30 && input[i+3] <= 0X39) || (input[i+3] >= 0x41 && input[i+3] <= 0x5A) || (input[i+3] >= 0X61 && input[i+3] <= 0x7A))){
                    int start = i+3;
                    int len = 3;
                    while(start < input.length() && (input[start] == '_' || ((input[start] - '0' >= 0) && (input[start] - '0' <= 9)) || ((input[start] - 'a' >= 0) && (input[start] - 'a' <= 25)) || ((input[start] - 'A' >= 0) && (input[start] - 'A' <= 25)))){
                        start ++;
                        len ++;
                    }
                    tokens.push_back("TID: " + convertToString(tokenNumber) + ", TYPE: 1(ID), POS: " + convertToString(position) + ", LEN: " + convertToString(len) + ", VALUE: " + input.substr(i, len));
                    token *t = new token(convertToString(tokenNumber), convertToString(1), "ID", convertToString(position), convertToString(len), input.substr(i, len));
                    toks.push_back(*t);
                    i += len;
                    position += len;
                }else{
                    tokens.push_back("TID: " + convertToString(tokenNumber) + ", TYPE: 8(FOR), POS: " + convertToString(position) + ", LEN: " + convertToString(3) + ", VALUE: for");
                    token *t = new token(convertToString(tokenNumber), convertToString(8), "FOR", convertToString(position), convertToString(3), "for");
                    toks.push_back(*t);
                    i += 3;
                    position += 3;
                }
                record.push_back(true);
            }else if(input[i] == 'w' && input.length() - i >= 5 && input.substr(i, 5) == "while"){
                if(input.length() - i >=6 && (input[i+5] == '_' || (input[i+5] >= 0X30 && input[i+5] <= 0X39) || (input[i+5] >= 0x41 && input[i+5] <= 0x5A) || (input[i+5] >= 0X61 && input[i+5] <= 0x7A))){
                    int start = i+5;
                    int len = 5;
                    while(start < input.length() && (input[start] == '_' || ((input[start] - '0' >= 0) && (input[start] - '0' <= 9)) || ((input[start] - 'a' >= 0) && (input[start] - 'a' <= 25)) || ((input[start] - 'A' >= 0) && (input[start] - 'A' <= 25)))){
                        start ++;
                        len ++;
                    }
                    tokens.push_back("TID: " + convertToString(tokenNumber) + ", TYPE: 1(ID), POS: " + convertToString(position) + ", LEN: " + convertToString(len) + ", VALUE: " + input.substr(i, len));
                    token *t = new token(convertToString(tokenNumber), convertToString(1), "ID", convertToString(position), convertToString(len), input.substr(i, len));
                    toks.push_back(*t);
                    i += len;
                    position += len;
                }else{
                    tokens.push_back("TID: " + convertToString(tokenNumber) + ", TYPE: 9(WHILE), POS: " + convertToString(position) + ", LEN: " + convertToString(5) + ", VALUE: while");
                    token *t = new token(convertToString(tokenNumber), convertToString(9), "WHILE", convertToString(position), convertToString(5), "while");
                    toks.push_back(*t);
                    i += 5;
                    position += 5;
                }
                record.push_back(true);
            }else if(input[i] == 'i' && input.length() - i >= 2 && input.substr(i, 2) == "if"){
                if(input.length() - i >= 3 && (input[i+2] == '_' || (input[i+2] >= 0X30 && input[i+2] <= 0X39) || (input[i+2] >= 0x41 && input[i+2] <= 0x5A) || (input[i+2] >= 0X61 && input[i+2] <= 0x7A))){
                    int start = i+2;
                    int len = 2;
                    while(start < input.length() && (input[start] == '_' || ((input[start] - '0' >= 0) && (input[start] - '0' <= 9)) || ((input[start] - 'a' >= 0) && (input[start] - 'a' <= 25)) || ((input[start] - 'A' >= 0) && (input[start] - 'A' <= 25)))){
                        start ++;
                        len ++;
                    }
                    tokens.push_back("TID: " + convertToString(tokenNumber) + ", TYPE: 1(ID), POS: " + convertToString(position) + ", LEN: " + convertToString(len) + ", VALUE: " + input.substr(i, len));
                    token *t = new token(convertToString(tokenNumber), convertToString(1), "ID", convertToString(position), convertToString(len), input.substr(i, len));
                    toks.push_back(*t);
                    i += len;
                    position += len;
                }else{
                    tokens.push_back("TID: " + convertToString(tokenNumber) + ", TYPE: 10(IF), POS: " + convertToString(position) + ", LEN: " + convertToString(2) + ", VALUE: if");
                    token *t = new token(convertToString(tokenNumber), convertToString(10), "IF", convertToString(position), convertToString(2), "if");
                    toks.push_back(*t);
                    i += 2;
                    position += 2;
                }
                record.push_back(true);
            }else if(input[i] == 'e' && input.length() - i >= 4 && input.substr(i, 4) == "else"){
                if(input.length() - i >= 5 && (input[i+4] == '_' || (input[i+4] >= 0X30 && input[i+4] <= 0X39) || (input[i+4] >= 0x41 && input[i+4] <= 0x5A) || (input[i+4] >= 0X61 && input[i+4] <= 0x7A))){
                    int start = i+4;
                    int len = 4;
                    while(start < input.length() && (input[start] == '_' || ((input[start] - '0' >= 0) && (input[start] - '0' <= 9)) || ((input[start] - 'a' >= 0) && (input[start] - 'a' <= 25)) || ((input[start] - 'A' >= 0) && (input[start] - 'A' <= 25)))){
                        start ++;
                        len ++;
                    }
                    tokens.push_back("TID: " + convertToString(tokenNumber) + ", TYPE: 1(ID), POS: " + convertToString(position) + ", LEN: " + convertToString(len) + ", VALUE: " + input.substr(i, len));
                    token *t = new token(convertToString(tokenNumber), convertToString(1), "ID", convertToString(position), convertToString(len), input.substr(i, len));
                    toks.push_back(*t);
                    i += len;
                    position += len;
                }else{
                    tokens.push_back("TID: " + convertToString(tokenNumber) + ", TYPE: 11(ELSE), POS: " + convertToString(position) + ", LEN: " + convertToString(4) + ", VALUE: else");
                    token *t = new token(convertToString(tokenNumber), convertToString(11), "ELSE", convertToString(position), convertToString(4), "else");
                    toks.push_back(*t);
                    i += 4;
                    position += 4;
                }
                record.push_back(true);
            }else if(input[i] == '"'){
                int start = i + 1;
                while(start < input.length() && input[start] != '"'){
                    if(input[start] == 0X09 || (input[start] >= 0X20 && input[start] <= 0X7E)){
                        start ++;
                    }else{
                        break;
                    }
                }
                if(start < input.length() && input[start] == '"'){
                    int len = start - i + 1;
                    string substring = input.substr(i + 1, len - 2);
                    tokens.push_back("TID: " + convertToString(tokenNumber) + ", TYPE: 2(STR), POS: " + convertToString(position) + ", LEN: " + convertToString(len) + ", VALUE: " + substring);
                    record.push_back(true);
                    token *t = new token(convertToString(tokenNumber), convertToString(2), "STR", convertToString(position), convertToString(len), substring);
                    toks.push_back(*t);
                    i += len;
                    position += len;
                }else if(start == input.length()){
                    int len = start - i;
                    tokens.push_back("TID: " + convertToString(tokenNumber) + ", TYPE: 98(ERR2), POS: " + convertToString(position) + ", LEN: " + convertToString(len) );
                    record.push_back(false);
                    i += len;
                    position += len;
                    cout << "Lex error" << endl;
                    return 0;
                }else{
                    int len = start - i;
                    tokens.push_back("TID: " + convertToString(tokenNumber) + ", TYPE: 98(ERR2), POS: " + convertToString(position) + ", LEN: " + convertToString(len) );
                    record.push_back(false);
                    i += len;
                    position += len;
                    cout << "Lex error" << endl;
                    return 0;
                }
            }else if((input[i] <= 0X20 || input[i] >= 0X7E) && (input[i] != 0X09) && (input[i] != 0X0a)){
                int start = i + 1;
                while(start < input.length() && (input[start] <= 0X20 || input[start] >= 0X7E) && (input[i] != 0X09) && (input[i] != 0X0a)){
                    start ++;
                }
                int len = start - i;
                tokens.push_back("TID: " + convertToString(tokenNumber) + ", TYPE: 99(ERR3), POS: " + convertToString(position) + ", LEN: " + convertToString(len));
                record.push_back(false);
                i += len;
                position += len;
                cout << "Lex error" << endl;
                return 0;
            }else if(input.length() - i >= 2 && map.count(input.substr(i, 2)) == 1){
                tokens.push_back("TID: " + convertToString(tokenNumber) + ", TYPE: " + convertToString(map.find(input.substr(i,2))->second) + "(" + input.substr(i, 2) + "), POS: " + convertToString(position) + ", LEN: " + convertToString(2));
                record.push_back(true);
                token *t = new token(convertToString(tokenNumber), convertToString(map.find(input.substr(i,2))->second), input.substr(i, 2), convertToString(position), convertToString(2), "");
                toks.push_back(*t);
                i += 2;
                position += 2;
            }else if(map.count(input.substr(i, 1)) == 1){
                if(unimplemented.count(input.substr(i, 1)) == 1){
                    cout << "Unimplemented error" << endl;
                    return 0;
                }
                tokens.push_back("TID: " + convertToString(tokenNumber) + ", TYPE: " + convertToString(map.find(input.substr(i,1))->second) + "(" + input.substr(i, 1) + "), POS: " + convertToString(position) + ", LEN: " + convertToString(1));
                record.push_back(true);
                token *t = new token(convertToString(tokenNumber), convertToString(map.find(input.substr(i,1))->second), input.substr(i, 1), convertToString(position), convertToString(1), "");
                toks.push_back(*t);
                i += 1;
                position += 1;
            }else if(set.count(input.substr(i, 1)) == 1){
                tokens.push_back("TID: " + convertToString(tokenNumber) + ", TYPE: 100(ERR4), POS: " + convertToString(position) + ", LEN: " + convertToString(1));
                record.push_back(false);
                i += 1;
                position += 1;
                cout << "Lex error" << endl;
                return 0;
            }else{
                int start = i;
                int len = 0;
                while(start < input.length() && (input[start] == '_' || ((input[start] - '0' >= 0) && (input[start] - '0' <= 9)) || ((input[start] - 'a' >= 0) && (input[start] - 'a' <= 25)) || ((input[start] - 'A' >= 0) && (input[start] - 'A' <= 25)))){
                    start ++;
                    len ++;
                }
                tokens.push_back("TID: " + convertToString(tokenNumber) + ", TYPE: 1(ID), POS: " + convertToString(position) + ", LEN: " + convertToString(len) + ", VALUE: " + input.substr(i, len));
                record.push_back(true);
                token *t = new token(convertToString(tokenNumber), convertToString(1), "ID", convertToString(position), convertToString(len), input.substr(i, len));
                toks.push_back(*t);
                i += len;
                position += len;
            }
            tokenNumber++;
        }
        if(cin.eof()){
            break;
        }
        position++;
        tokenNumber++;
    }
    n = (int)toks.size();
    if(checkStmt(root) && x == n-1){
        printTree(root, 0);
    }else{
        cout << "Parse error" << endl;
    }
    return 0;
}

int getIntegerLength(string s, int start){
    int len = 0;
    for(int i = start; i < s.length(); i++){
        if((s[i] - '0' >= 0) && (s[i] - '0'<= 9)){
            len ++;
        }else{
            break;
        }
    }
    return len;
}

string convertToString(int num){
    stringstream s;
    s << num;
    string ss;
    s >> ss;
    return ss;
}

bool checkStmt(Node* parent){
    if(x > 0){
        Node* node = new Node("<node><nt>stmt</nt><children>");
        parent->children.push_back(node);
        if(checkWhile(node)){
            x++;
            if(checkStmt(node)){
                return true;
            }else{
                return false;
            }
        }else if(checkFor(node)){
            x++;
            if(checkStmt(node)){
                return true;
            }else{
                return false;
            }
        }else if(checkIf(node)){
            x++;
            if(checkStmt(node)){
                return true;
            }else{
                return false;
            }
        }else if(checkAssign(node)){
            x++;
            if(x < n && toks[x].name == ";"){
                node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
                x++;
                if(checkStmt(node)){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else if(checkOutput(node)){
            x++;
            if(checkStmt(node)){
                return true;
            }else{
                return false;
            }
        }else{
            node->children.push_back(new Node("<node><epsilon></epsilon></node>"));
            x--;
            return true;
        }
    }else{
        if(checkWhile(parent)){
            x++;
            if(checkStmt(parent)){
                return true;
            }else{
                return false;
            }
        }else if(checkFor(parent)){
            x++;
            if(checkStmt(parent)){
                return true;
            }else{
                return false;
            }
        }else if(checkIf(parent)){
            x++;
            if(checkStmt(parent)){
                return true;
            }else{
                return false;
            }
        }else if(checkAssign(parent)){
            x++;
            if(x < n && toks[x].name == ";"){
                parent->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
                x++;
                if(checkStmt(parent)){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else if(checkOutput(parent)){
            x++;
            if(checkStmt(parent)){
                return true;
            }else{
                return false;
            }
        }
    }
    parent->children.push_back(new Node("<node><epsilon></epsilon></node>"));
    x--;
    return true;
}

bool checkWhile(Node* parent){
    int origin = x;
    if(x < n && toks[x].name == "WHILE"){
        Node* node = new Node("<node><nt>while_stmt</nt><children>");
        Node* node_while = new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>");
        parent->children.push_back(node);
        node->children.push_back(node_while);
        x++;
        if(x < n && toks[x].name == "("){
            node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
            x++;
            if(checkCond(node)){
                x++;
                if(x < n && toks[x].name == ")"){
                    node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
                    x++;
                    if(x < n && toks[x].name == "{"){
                        node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
                        x++;
                        if(checkStmt(node)){
                            x++;
                            if(x < n && toks[x].name == "}"){
                                node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
                                return true;
                            }else{
                                x = origin;
                                return false;
                            }
                        }else{
                            x = origin;
                            return false;
                        }
                    }else{
                        x = origin;
                        return false;
                    }
                }else{
                    x = origin;
                    return false;
                }
            }else{
                x = origin;
                return false;
            }
        }else{
            x = origin;
            return false;
        }
    }
    x = origin;
    return false;
}

bool checkFor(Node* parent){
    int origin = x;
    if(x < n && toks[x].name == "FOR"){
        Node* node = new Node("<node><nt>for_stmt</nt><children>");
        Node* node_for = new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>");
        parent->children.push_back(node);
        node->children.push_back(node_for);
        x++;
        if(x < n && toks[x].name == "("){
            node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
            x++;
            if(checkOptAssign(node)){
                x++;
                if(x < n && toks[x].name == ";"){
                    node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
                    x++;
                    if(checkOptCond(node)){
                        x++;
                        if(x < n && toks[x].name == ";"){
                            node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
                            x++;
                            if(checkOptAssign(node)){
                                x++;
                                if(x < n && toks[x].name == ")"){
                                    node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
                                    x++;
                                    if(x < n && toks[x].name == "{"){
                                        node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
                                        x++;
                                        if(checkStmt(node)){
                                            x++;
                                            if(x < n && toks[x].name == "}"){
                                                node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
                                                return true;
                                            }else{
                                                x = origin;
                                                return false;
                                            }
                                        }else{
                                            x = origin;
                                            return false;
                                        }
                                    }else{
                                        x = origin;
                                        return false;
                                    }
                                }else{
                                    x = origin;
                                    return false;
                                }
                            }else{
                                x = origin;
                                return false;
                            }
                        }else{
                            x = origin;
                            return false;
                        }
                    }else{
                        x = origin;
                        return false;
                    }
                }else{
                    x = origin;
                    return false;
                }
            }else{
                x = origin;
                return false;
            }
        }else{
            x = origin;
            return false;
        }
    }
    x = origin;
    return false;
}

bool checkIf(Node* parent){
    int origin = x;
    if(x < n && toks[x].name == "IF"){
        Node* node = new Node("<node><nt>if_stmt</nt><children>");
        Node* node_if = new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>");
        parent->children.push_back(node);
        node->children.push_back(node_if);
        x++;
        if(x < n && toks[x].name == "("){
            node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
            x++;
            if(checkCond(node)){
                x++;
                if(x < n && toks[x].name == ")"){
                    node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
                    x++;
                    if(x < n && toks[x].name == "{"){
                        node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
                        x++;
                        if(checkStmt(node)){
                            x++;
                            if(x < n && toks[x].name == "}"){
                                node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
                                x++;
                                if(checkOptElse(node)){
                                    return true;
                                }else{
                                    x = origin;
                                    return false;
                                }
                            }else{
                                x = origin;
                                return false;
                            }
                        }else{
                            x = origin;
                            return false;
                        }
                    }else{
                        x = origin;
                        return false;
                    }
                }else{
                    x = origin;
                    return false;
                }
            }else{
                x = origin;
                return false;
            }
        }else{
            x = origin;
            return false;
        }
    }
    x = origin;
    return false;
}



bool checkCond(Node* parent){
    int origin = x;
    Node* node = new Node("<node><nt>cond_expr</nt><children>");
    parent->children.push_back(node);
    if(checkAnd(node)){
        x++;
        if(cCond(node)){
            return true;
        }
    }
    x = origin;
    return false;
}

bool cCond(Node* parent){
    int origin = x;
    Node* node = new Node("<node><nt>cond_expr_</nt><children>");
    parent->children.push_back(node);
    if(x < n && toks[x].name == "|"){
        node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
        x++;
        if(checkAnd(node)){
            x++;
            if(cCond(node)){
                return true;
            }else{
                x = origin;
                return false;
            }
        }else{
            x = origin;
            return false;
        }
    }
    node->children.push_back(new Node("<node><epsilon></epsilon></node>"));
    x --;
    return true;
}

bool checkAnd(Node* parent){
    int origin = x;
    Node* node = new Node("<node><nt>and_expr</nt><children>");
    parent->children.push_back(node);
    if(checkEq(node)){
        x++;
        if(cAnd(node)){
            return true;
        }
    }
    x = origin;
    return false;
}

bool cAnd(Node* parent){
    int origin = x;
    Node* node = new Node("<node><nt>and_expr_</nt><children>");
    parent->children.push_back(node);
    if(x < n && toks[x].name == "&"){
        node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
        x++;
        if(checkEq(node)){
            x++;
            if(cAnd(node)){
                return true;
            }else{
                x = origin;
                return false;
            }
        }else{
            x = origin;
            return false;
        }
    }
    node->children.push_back(new Node("<node><epsilon></epsilon></node>"));
    x --;
    return true;
}

bool checkEq(Node* parent){
    int origin = x;
    Node* node = new Node("<node><nt>eq_expr</nt><children>");
    parent->children.push_back(node);
    if(checkCmp(node)){
        x++;
        if(cEq(node)){
            return true;
        }
    }
    x = origin;
    return false;
}

bool cEq(Node* parent){
    int origin = x;
    Node* node = new Node("<node><nt>eq_expr_</nt><children>");
    parent->children.push_back(node);
    if(x < n && toks[x].name == "="){
        node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
        x++;
        if(checkCmp(node)){
            x++;
            if(cEq(node)){
                return true;
            }else{
                x = origin;
                return false;
            }
        }else{
            x = origin;
            return false;
        }
    }else if(x < n && toks[x].name == "!="){
        node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
        x++;
        if(checkCmp(node)){
            x++;
            if(cEq(node)){
                return true;
            }else{
                x = origin;
                return false;
            }
        }else{
            x = origin;
            return false;
        }
    }
    node->children.push_back(new Node("<node><epsilon></epsilon></node>"));
    x --;
    return true;
}

bool checkCmp(Node* parent){
    int origin = x;
    Node* node = new Node("<node><nt>cmp_expr</nt><children>");
    parent->children.push_back(node);
    if(checkExpr(node)){
        x++;
        if(cCmp(node)){
            return true;
        }
    }
    x = origin;
    return false;
}

bool cCmp(Node* parent){
    int origin = x;
    Node* node = new Node("<node><nt>cmp_expr_</nt><children>");
    parent->children.push_back(node);
    if(x < n && toks[x].name == "<"){
        node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
        x++;
        if(checkExpr(node)){
            x++;
            if(cCmp(node)){
                return true;
            }else{
                x = origin;
                return false;
            }
        }else{
            x = origin;
            return false;
        }
    }else if(x < n && toks[x].name == ">"){
        node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
        x++;
        if(checkExpr(node)){
            x++;
            if(cCmp(node)){
                return true;
            }else{
                x = origin;
                return false;
            }
        }else{
            x = origin;
            return false;
        }
    }else if(x < n && toks[x].name == "<="){
        node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
        x++;
        if(checkExpr(node)){
            x++;
            if(cCmp(node)){
                return true;
            }else{
                x = origin;
                return false;
            }
        }else{
            x = origin;
            return false;
        }
    }else if(x < n && toks[x].name == ">="){
        node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
        x++;
        if(checkExpr(node)){
            x++;
            if(cCmp(node)){
                return true;
            }else{
                x = origin;
                return false;
            }
        }else{
            x = origin;
            return false;
        }
    }
    node->children.push_back(new Node("<node><epsilon></epsilon></node>"));
    x --;
    return true;
}

bool checkExpr(Node* parent){
    int origin = x;
    Node* node = new Node("<node><nt>expr</nt><children>");
    parent->children.push_back(node);
    if(checkMult(node)){
        x++;
        if(cExpr(node)){
            return true;
        }
    }
    x = origin;
    return false;
}

bool cExpr(Node* parent){
    int origin = x;
    Node* node = new Node("<node><nt>expr_</nt><children>");
    parent->children.push_back(node);
    if(x < n && toks[x].name == "+"){
        node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
        x++;
        if(checkMult(node)){
            x++;
            if(cExpr(node)){
                return true;
            }else{
                x = origin;
                return false;
            }
        }else{
            x = origin;
            return false;
        }
    }
    node->children.push_back(new Node("<node><epsilon></epsilon></node>"));
    x --;
    return true;
}

bool checkMult(Node* parent){
    int origin = x;
    Node* node = new Node("<node><nt>mult_expr</nt><children>");
    parent->children.push_back(node);
    if(checkUnary(node)){
        x++;
        if(cMult(node)){
            return true;
        }
    }
    x = origin;
    return false;
}

bool cMult(Node* parent){
    int origin = x;
    Node* node = new Node("<node><nt>mult_expr_</nt><children>");
    parent->children.push_back(node);
    if(x < n && toks[x].name == "*"){
        node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
        x++;
        if(checkUnary(node)){
            x++;
            if(cMult(node)){
                return true;
            }else{
                x = origin;
                return false;
            }
        }else{
            x = origin;
            return false;
        }
    }
    node->children.push_back(new Node("<node><epsilon></epsilon></node>"));
    x -- ;
    return true;
}

bool checkUnary(Node* parent){
    int origin = x;
    Node* node = new Node("<node><nt>unary_expr</nt><children>");
    parent->children.push_back(node);
    if(x < n && toks[x].name == "!"){
        node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
        x++;
        if(checkExpr(node)){
            return true;
        }else{
            x = origin;
            return false;
        }
    }else if(x < n && toks[x].name == "+"){
        node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
        x++;
        if(checkExpr(node)){
            return true;
        }else{
            x = origin;
            return false;
        }
    }else if(x < n && toks[x].name == "-"){
        node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
        x++;
        if(checkExpr(node)){
            return true;
        }else{
            x = origin;
            return false;
        }
    }else if(checkParen(node)){
        return true;
    }
    x = origin;
    return false;
}

bool checkParen(Node* parent){
    int origin = x;
    Node* node = new Node("<node><nt>paren_expr</nt><children>");
    parent->children.push_back(node);
    if(x < n && toks[x].name == "("){
        node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
        x++;
        if(checkExpr(node)){
            if(x < n && toks[x].name == ")"){
                node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
                return true;
            }else{
                x = origin;
                return false;
            }
        }else{
            x = origin;
            return false;
        }
    }else if(checkBasic(node)){
        return true;
    }
    x = origin;
    return false;
}

bool checkBasic(Node* parent){
    Node* node = new Node("<node><nt>basic_expr</nt><children>");
    parent->children.push_back(node);
    if((x < n) && (toks[x].name == "ID" || toks[x].name == "STR" || toks[x].name == "INT" || toks[x].name == "FLOAT")){
        Node* node_token = new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>");
        node->children.push_back(node_token);
        return true;
    }
    return false;
}

bool checkOptAssign(Node* parent){
    Node* node = new Node("<node><nt>opt_assign</nt><children>");
    parent->children.push_back(node);
    if(checkAssign(node)){
        return true;
    }
    node->children.push_back(new Node("<node><epsilon></epsilon></node>"));
    x--;
    return true;
}

bool checkOptCond(Node* parent){
    Node* node = new Node("<node><nt>opt_cond_expr</nt><children>");
    parent->children.push_back(node);
    if(checkCond(node)){
        return true;
    }
    node->children.push_back(new Node("<node><epsilon></epsilon></node>"));
    x--;
    return true;
}

bool checkAssign(Node* parent){
    int origin = x;
    if(x < n && toks[x].name == "ID"){
        Node* node = new Node("<node><nt>assignment_stmt</nt><children>");
        parent->children.push_back(node);
        node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
        x++;
        if(x < n && toks[x].name == ":="){
            node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
            x++;
            if(checkExpr(node)){
                return true;
            }else{
                x = origin;
                return false;
            }
        }else{
            x= origin;
            return false;
        }
    }
    x = origin;
    return false;
}

bool checkOptElse(Node* parent){
    int origin = x;
    Node* node = new Node("<node><nt>opt_else</nt><children>");
    parent->children.push_back(node);
    if(x < n && toks[x].name == "ELSE"){
        node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
        x++;
        if(x < n && toks[x].name == "{"){
            node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
            x++;
            if(checkStmt(node)){
                x++;
                if(x < n && toks[x].name == "}"){
                    node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
                    return true;
                }else{
                    x = origin;
                    return false;
                }
            }else{
                x = origin;
                return false;
            }
        }else{
            x = origin;
            return false;
        }
    }
    node->children.push_back(new Node("<node><epsilon></epsilon></node>"));
    x --;
    return true;
}

bool checkOutput(Node* parent){
    int origin = x;
    if(x < n && toks[x].name == "["){
        Node* node = new Node("<node><nt>optput_stmt</nt><children>");
        parent->children.push_back(node);
        node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
        x++ ;
        if(checkExpr(node)){
            x++;
            if(x < n && toks[x].name == "]"){
                node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
                x++;
                if(x < n && toks[x].name == ";"){
                    node->children.push_back(new Node("<node><id>" + toks[x].id + "</id><typenum>" + toks[x].num + "</typenum><typename>" + toks[x].name + "</typename><position>" + toks[x].position + "</position><length>" + toks[x].length + "</length><value>" + toks[x].value + "</value></node>"));
                    return true;
                }else{
                    x = origin;
                    return false;
                }
            }else{
                x = origin;
                return false;
            }
        }else{
            x = origin;
            return false;
        }
    }
    x = origin;
    return false;
}

void printTree(Node* node, int space){
    for(int i = 0; i < space; i++){
        cout << " " ;
    }
    cout << node->value << endl;
    for(vector<string>::size_type i = 0; i != node->children.size(); i++){
        printTree(node->children[i], space + 1);
    }
    if(node->children.size()!=0){
        for(int j = 0; j < space; j++){
            cout<< " ";
        }
        cout << "</node></children>" << endl;
    }
}