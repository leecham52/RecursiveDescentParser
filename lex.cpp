#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
using namespace std;

<<<<<<< HEAD
vector<vector<int>> tokens;
vector<vector<string>> lexeme;
int fl = 0;
int f = 0;
vector<string> dup_op;
vector<string> error;
struct id {
    string id;
    int val;
};
struct op {
    string op;
    int p;
};
vector<id> ide;
stack<int> num;
stack<op> oper;
=======
//아쉽지만, 전역변수로 받기
//2차원 배열로 값 받기

int* tokens[100];
string* lexeme[100];
int k = 0;
int te = 0;
int fl = 0;
int f = 0;
string* dup_op;
int s = 0;
int cur_ident[100];
>>>>>>> 6a9cd65a158fa2226a362cddb96e30fb9cc9cee8

#define IDENT 10
#define CONST 11
#define ASSIGN_OP 12
#define SEMI_COLON 13
#define ADD_OP 14
#define MUL_OP 16
#define LPAREN 18
#define RPAREN 19
#define UNKNOWN -10000

bool checkWhiteSpace(char c);
bool checkLetter(char c);
bool checkDigit(char c);
bool checkIdent(const char c[]);
bool checkConst(const char c[]);
bool checkAddOp(const char c[]);
bool checkMulOp(const char c[]);
bool checkAssignOp(const char c[]);
bool checkLparen(const char c[]);
bool checkRparen(const char c[]);
bool checkSemiColon(const char c[]);
int checkToken(const char t[]);

void program(vector<vector<int>> tks);
void statements(vector<vector<int>> tks);
void statement(vector<vector<int>> tks);
void expression(vector<vector<int>> tks);
void term(vector<vector<int>> tks);
void term_tail(vector<vector<int>> tks);
void factor(vector<vector<int>> tks);
void factor_tail(vector<vector<int>> tks);
void const_(vector<vector<int>> tks);
void ident(vector<vector<int>> tks);
void assignment_op(vector<vector<int>> tks);
void semi_colon(vector<vector<int>> tks);
void add_op(vector<vector<int>> tks);
void mult_op(vector<vector<int>> tks);
void left_paren(vector<vector<int>> tks);
void right_paren(vector<vector<int>> tks);

void lexical(string str);
<<<<<<< HEAD
void calString();
void calIdent(vector<vector<int>> tk, vector<vector<string>> lex, vector<id>& ident);
void printResult(vector<vector<int>> tk, vector<vector<string>> lex);


int main(int argc, char* argv[]) {
    
    string in;

    //c++에 맞춰서 변환, string으로 낑겨 받으면 좋을수도 아닐수도
    ifstream in_Fp("input1.txt");
    if (!in_Fp.is_open()) {
        cout << "ERROR - cannot open front.in" << endl;
        return 0;
    }
    while (!in_Fp.eof()) {
        getline(in_Fp, in); //한 줄씩 입력 받음
        lexical(in);
=======
void printResult(int** tk, string** lex);
void program(int** tks);
void statements(int** tks);
void statement(int** tks);
void expression(int** tks);
void term(int** tks);
void term_tail(int** tks);
void factor(int** tks);
void factor_tail(int** tks);
void const_(int** tks);
void ident(int** tks);
void assignment_op(int** tks);
void semi_colon(int** tks);
void add_op(int** tks);
void mult_op(int** tks);
void left_paren(int** tks);
void right_paren(int** tks);


int main(int argc, char* argv[]) {
    if (argc < 2)
    {
        cout << "파일 입력 오류" << endl;
        return 0;
    }
    string in[100];

    //c++에 맞춰서 변환, string으로 낑겨 받으면 좋을수도 아닐수도
    ifstream in_Fp;
    in_Fp.open(argv[1]);
    if (!in_Fp.is_open())
        cout << "ERROR - cannot open front.in" << endl;
    while (!in_Fp.eof()) {
        getline(in_Fp, in[k]); //한 줄씩 입력 받음
        lexical(in[k]);
        k++;
>>>>>>> 6a9cd65a158fa2226a362cddb96e30fb9cc9cee8
    }
    in_Fp.close();
    program(tokens); //RecursiveDescentParser 하기
    calIdent(tokens, lexeme, ide);
    printResult(tokens, lexeme);

    return 0;
}

void lexical(string str) {
<<<<<<< HEAD
    int next_token = 0;
    string tok;
    string notLit;
    string token_string;
    vector<string> lex;
    vector<int> n_t;
    lex.clear();
    n_t.clear();
    for (int i = 0; i < str.length(); i++) {
        if (!checkWhiteSpace(str[i])) {
            token_string += str[i]; //공백을 뺀 줄을 가져온다. id1 = id2 + 2; => id1=id2+2;
        }
    }
    for (int i = 0; i < token_string.length();) {
=======
    int next_token;
    string token_string;
    string tok;
    string notLit;
    string tempstr = "";
    for (int i = 0; i < str.length(); i++) {
        if (checkWhiteSpace(str[i])) {
            tempstr += str[i]; //공백을 뺀 줄을 가져온다. id1 = id2 + 2; => id1=id2+2;
        }
    }
    for (int i = 0; i < tempstr.length();) {
>>>>>>> 6a9cd65a158fa2226a362cddb96e30fb9cc9cee8
        tok.clear();
        notLit.clear();

        //identifier, const 2가지 경우를 걸러서 저장
<<<<<<< HEAD
        while ((checkLetter(token_string[i]) || checkDigit(token_string[i]) || token_string[i] == '_')) {
            tok += token_string[i];
=======
        while ((checkLetter(tempstr[i]) || checkDigit(tempstr[i] || tempstr[i] == '_'))) {
            tok += tempstr[i];
>>>>>>> 6a9cd65a158fa2226a362cddb96e30fb9cc9cee8
            i++;
        }
        next_token = checkToken(tok.c_str()); // 여기서 identifier, const 걸러서 token화된다.
        //lexeme이랑 token을 어딘가 저장을 해둬야한다.
<<<<<<< HEAD
        if (!tok.empty() && next_token != 0) {
            lex.push_back(tok);
            n_t.push_back(next_token);
        }
        if (token_string[i] == ':') {
            notLit += token_string[i];
            i++;
            if (token_string[i] == '=') {
                notLit += token_string[i];
                i++;
            }
        }
        else if (token_string[i] == '+') {
            notLit += token_string[i];
            i++;
            if (token_string[i] == '+') {
                notLit += token_string[i];
                i++;
            }
        }
        else if (token_string[i] == '-') {
            notLit += token_string[i];
            i++;
            if (token_string[i] == '-') {
                notLit += token_string[i];
                i++;
            }
        }
        else if (token_string[i] == '*') {
            notLit += token_string[i];
            i++;
            if (token_string[i] == '*') {
                notLit += token_string[i];
                i++;
            }
        }
        else if (token_string[i] == '/') {
            notLit += token_string[i];
            i++;
            if (token_string[i] == '/') {
                notLit += token_string[i];
                i++;
            }
        }
        else if (token_string[i] == '(' || token_string[i] == ')' || token_string[i] == ';') {
            notLit += token_string[i];
            i++;
        }
        next_token = checkToken(notLit.c_str());
        if (!notLit.empty() && next_token != 0) {
            lex.push_back(notLit);
            n_t.push_back(next_token);
        }
    }
    //2차원 vector에 저장
    tokens.push_back(n_t);
    lexeme.push_back(lex);
}
void calString() {
    int a, b, result;
    b = num.top();
    num.pop();
    a = num.top();
    num.pop();
    string operate = oper.top().op;
    oper.pop();
    if (operate == "*")
        result = a * b;
    else if (operate == "/")
        result = a / b;
    else if (operate == "+")
        result = a + b;
    else if (operate == "-")
        result = a - b;
    num.push(result);
}
void calIdent(vector<vector<int>> tk, vector<vector<string>> lex, vector<id>& ident) {
    vector<string> e = error;
    //ident 계산
    for (int k = 0; k < tk.size(); k++) {
        for (int i = 2; i < tk[k].size(); i++) {
            if (tk[k][i] == IDENT) {
                if (ident.size() == 0) {
                    num.push(UNKNOWN);
                    ident.push_back({ lex[k][i], UNKNOWN });
                    error.push_back(to_string(k) + lex[k][i]);
                }
                for (int j = 1; j < ident.size(); j++) {
                    int l = 1;
                    if (lex[k][i] == ident[j].id) {
                        num.push(ident[j].val);
                    }
                    else {
                        l++;
                        if (l == ident.size()) {
                            num.push(UNKNOWN);
                            ident.push_back({lex[k][i], UNKNOWN});
                            for (int c = 0; c < error.size(); c++) {
                                string getE = error[c];
                                for (int b = 1; b < getE.size(); b++) {
                                    error[c].erase(0);
                                    error[c] += getE[b];
                                }
                                cout<< error[c].front();
                                if (lex[k][i] != error[c]) {
                                    error.push_back(to_string(k) + lex[k][i]);
                                    error[c] = getE;
                                    break;
                                }
                                error[c] = getE;
                            }
                        }
                    }
                }
            }
            else if (tk[k][i] == CONST) {
                num.push(stoi(lex[k][i]));
            }
            else if (tk[k][i] == ADD_OP || tk[k][i] == MUL_OP) {
                int pr = 3;
                if (lex[k][i] == "*" || lex[k][i] == "/") {
                    pr = 2;
                }
                else if (lex[k][i] == "+" || lex[k][i] == "-") {
                    pr = 1;
                }
                while (!oper.empty() && pr <= oper.top().p) {
                    calString();
                }
                oper.push({ lex[k][i], pr });
            }
            else if (tk[k][i] == LPAREN) {
                oper.push({lex[k][i], 0});
            }
            else if (tk[k][i] == RPAREN) {
                while (oper.top().op != "(") {
                    calString();
                }
                oper.pop();
            }
        }
        while (!oper.empty()) {
            calString();
        }
        if (tk[k][0] == IDENT) {
            ident.push_back({ lex[k][0], num.top() });
            num.pop();
=======
        if (!tok.empty() && next_token != NULL) {
            lexeme[k][te] = tok;
            tokens[k][te] = next_token;
            te++;
        }
        if (tempstr[i] == ':') {
            notLit += tempstr[i];
            i++;
            if (tempstr[i] == '=') {
                notLit += tempstr[i];
                i++;
            }
        }
        else if (tempstr[i] == '+') {
            notLit += tempstr[i];
            i++;
            if (tempstr[i] == '+') {
                notLit += tempstr[i];
                i++;
            }
        }
        else if (tempstr[i] == '-') {
            notLit += tempstr[i];
            i++;
            if (tempstr[i] == '-') {
                notLit += tempstr[i];
                i++;
            }
        }
        else if (tempstr[i] == '*') {
            notLit += tempstr[i];
            i++;
            if (tempstr[i] == '*') {
                notLit += tempstr[i];
                i++;
            }
        }
        else if (tempstr[i] == '/') {
            notLit += tempstr[i];
            i++;
            if (tempstr[i] == '/') {
                notLit += tempstr[i];
                i++;
            }
        }
        else if (tempstr[i] == '(' || tempstr[i] == ')' || tempstr[i] == ';') {
            notLit += tempstr[i];
            i++;
        }
        next_token = checkToken(notLit.c_str());
        if (!notLit.empty() && next_token != NULL) {
            lexeme[k][te] = notLit;
            tokens[k][te] = next_token;
            te++;
        }
        /*
        if(checkToken(tok.c_str()) != EOF){

>>>>>>> 6a9cd65a158fa2226a362cddb96e30fb9cc9cee8
        }
    }
}
//출력, ID, CONST, OP의 개수를 나타내주는 함수
<<<<<<< HEAD
void printResult(vector<vector<int>> tk, vector<vector<string>> lex) {
    for (int k = 0; k < tk.size(); k++) {
=======
void printResult(int** tk, string** lex) {
    for (int k = 0; k < sizeof(tk) / sizeof(tk[0]); k++) {
>>>>>>> 6a9cd65a158fa2226a362cddb96e30fb9cc9cee8
        int id_count = 0;
        int const_count = 0;
        int op_count = 0;
        string m;
        m.clear();
<<<<<<< HEAD
        for (int i = 0; i < tk[k].size(); i++) {
            m += lex[k][i];
            if (i != tk[k].size() - 2) {
                m += " ";
            }
=======
        for (int i = 0; i < sizeof(tk[k]) / sizeof(int); i++) {

            m += lex[k][i];
            m += " ";
>>>>>>> 6a9cd65a158fa2226a362cddb96e30fb9cc9cee8
            if (tk[k][i] == IDENT) {
                id_count++;
            }
            else if (tk[k][i] == CONST) {
                const_count++;
            }
            else if (tk[k][i] == ADD_OP || tk[k][i] == MUL_OP) {
                op_count++;
            }
        }
        cout << m << endl;
        cout << "ID: " << id_count << "; CONST: " << const_count << "; OP: " << op_count << ";" << endl;
<<<<<<< HEAD
        for (int s = 0; s < dup_op.size(); s++) {
            if (dup_op[s].front() == (char)k) {
                cout << "(WARNING) \"중복 연산자(" << dup_op[s].back() << ") 제거 \" " << endl;
            }
        }
        if (!error.empty()) {
            for (int v = 0; v < error.size(); v++) {
                string errP;
                errP = error[v].front();
                if (errP[0] - '0' == char(k)) {
                    errP.clear();
                    for (int b = 1; b < error[v].size(); b++) {
                        errP += error[v][b];
                    }
                    cout << "(Error) \"정의되지 않은 변수(" << errP << ")가 참조됨\"" << endl;
                    break;
                }
            }
        }
        else {
            cout << "(OK)" << endl;
        }
=======
>>>>>>> 6a9cd65a158fa2226a362cddb96e30fb9cc9cee8
        //OK, WARNING, Error
    }
    //Result 
    cout << "Result ==> ";
    for (int n = 0; n < ide.size(); n++) {
        if (ide[n].val < 0 || ide[n].val > 10000) {
            if (n == ide.size() - 1) {
                cout << ide[n].id << ": Unknown";
            }
            cout << ide[n].id << ": " << "Unknown;";
        }
        else {
            if (n == ide.size() - 1) {
                cout << ide[n].id << ": " << to_string(ide[n].val);
            }
            cout << ide[n].id << ": " << to_string(ide[n].val) << ";";
        }
    }
    
}
//ascii code 32이하인지 확인
bool checkWhiteSpace(char c) {
    if (c <= 32) {
        return true;
    }
    return false;
}
bool checkLetter(char c) {
    if (c >= 65 && c <= 90) {
        return true;
    }
    else if (c >= 97 && c <= 122) {
        return true;
    }
    else return false;
}
bool checkDigit(char c) {
    if (c >= 48 && c <= 57) {
        return true;
    }
    else return false;
}
//identifier인지 확인
bool checkIdent(const char c[]) {
    if (c[0] == '_' || checkLetter(c[0])) {
        if ((int)strlen(c) == 1) { //한 자릿 수의 identifier일 때
            return true;
        }
        for (int i = 1; i < (int)strlen(c); i++) {
            if (c[i] != '_' && !checkLetter(c[i]) && !checkDigit(c[i])) {
                return false;
            }
        }
        return true;
    }
    else return false;
}
//const인지 확인
bool checkConst(const char c[]) {
    if (c[0] == '0' && (int)strlen(c) == 1) { //0일때
        return true;
    }
    if (checkDigit(c[0]) && c[0] != '0') {
        for (int i = 1; i <= (int)strlen(c); i++) {
            if (checkDigit(c[i])) {
                continue;
            }
            else if (c[i] == '\0') return true;
            else return false;
        }
    }
    return false;
}
//+,-인지 확인 + ++, --에 대해서는? 따로 처리 레츠고
//++, -- 한번씩만 더 쓴 걸로 생각 하고 +-, -+ 같은 경우는 false로 처리
//
bool checkAddOp(const char c[]) {
    if ((int)strlen(c) == 2) {
        if ((c[0] == '+' && c[1] == '+') || (c[0] == '-' && c[1] == '-')) {
            return true;
        }
    }
    if ((int)strlen(c) != 1) {
        return false;
    }
    if (c[0] == '+' || c[0] == '-') {
        return true;
    }
    return false;
}
//*,/인지 확인
bool checkMulOp(const char c[]) {
    if ((int)strlen(c) == 2) {
        if ((c[0] == '*' && c[1] == '*') || (c[0] == '/' && c[1] == '/')) {
<<<<<<< HEAD
            return true;
=======

>>>>>>> 6a9cd65a158fa2226a362cddb96e30fb9cc9cee8
        }
    }
    if ((int)strlen(c) != 1) {
        return false;
    }
    if (c[0] == '*' || c[0] == '/') {
        return true;
    }
    return false;
}
// := 인지 확인
bool checkAssignOp(const char c[]) {
    if ((int)strlen(c) == 2 && c[0] == ':' && c[1] == '=') {
        return true;
    }
    return false;
}
//(인지 확인
bool checkLparen(const char c[]) {
    if ((int)strlen(c) == 1 && c[0] == '(') {
        return true;
    }
    return false;
}
//)인지 확인
bool checkRparen(const char c[]) {
    if ((int)strlen(c) == 1 && c[0] == ')') {
        return true;
    }
    return false;
}
//;인지 확인
bool checkSemiColon(const char c[]) {
    if ((int)strlen(c) == 1 && c[0] == ';') {
        return true;
    }
    return false;
}
int checkToken(const char t[]) {
    if (checkIdent(t)) {
        return IDENT;
    }
    else if (checkConst(t)) {
        return CONST;
    }
    else if (checkAddOp(t)) {
        return ADD_OP;
    }
    else if (checkMulOp(t)) {
        return MUL_OP;
    }
    else if (checkAssignOp(t)) {
        return ASSIGN_OP;
    }
    else if (checkLparen(t)) {
        return LPAREN;
    }
<<<<<<< HEAD
    else if (checkRparen(t)) {  
=======
    else if (checkRparen(t)) {
>>>>>>> 6a9cd65a158fa2226a362cddb96e30fb9cc9cee8
        return RPAREN;
    }
    else if (checkSemiColon(t)) {
        return SEMI_COLON;
    }
<<<<<<< HEAD
    else return 0;
}
//Assignment 1 조건에 맞는 Recursive-Descent Parsing
//<program> -> <statements>
void program(vector<vector<int>> tks) {
    //cout << "Enter <program>" << endl;
    statements(tks);
    //cout << "Exit <program>" << endl;
}
//<statements> -> <statement> {<semi_colon><statements}
void statements(vector<vector<int>> tks) {
    //cout << "Enter <statements>" << endl;
=======
    else return EOF;
}
//Assignment 1 조건에 맞는 Recursive-Descent Parsing
//<program> -> <statements>
void program(int** tks) {
    cout << "Enter <program>" << endl;
    statements(tks);
    cout << "Exit <program>" << endl;
}
//<statements> -> <statement> {<semi_colon><statements}
void statements(int** tks) {
    cout << "Enter <statements>" << endl;
>>>>>>> 6a9cd65a158fa2226a362cddb96e30fb9cc9cee8
    statement(tks);
    if (tokens[fl][f] == SEMI_COLON) {
        semi_colon(tks);
        statements(tks);
    }
<<<<<<< HEAD
    //cout << "Exit <statements>" << endl;
}
//<statement> -> <ident> <assignment_op> <expression>
void statement(vector<vector<int>> tks) {
    //cout << "Enter <statement>" << endl;
    ident(tks);
    assignment_op(tks);
    expression(tks);
    //cout << "Exit <statement>" << endl;
}
//<expression> -> <term> <term_tail>
void expression(vector<vector<int>> tks) {
    //cout << "Enter <expression>" << endl;
    term(tks);
    term_tail(tks);
    //cout << "Exit <expression>" << endl;
}
//<term> -> <factor> <factor_tail>
void term(vector<vector<int>> tks) {
    //cout << "Enter <term>" << endl;
    factor(tks);
    factor_tail(tks);
    //cout << "Exit <term>" << endl;
}
//<term_tail> -> {<add_op> <term> <term_tail>}
void term_tail(vector<vector<int>> tks) {
    if (tks[fl][f] == ADD_OP) {
        //cout << "Enter <term_tail>" << endl;
        add_op(tks);
        term(tks);
        term_tail(tks);
        //cout << "Exit <term_tail>" << endl;
    }
}
//<factor> -> (<left_paren> <expression> <right_paren> | <ident> | <const>)
void factor(vector<vector<int>> tks) {
    //cout << "Enter <factor>" << endl;
=======
    cout << "Exit <statements>" << endl;
}
//<statement> -> <ident> <assignment_op> <expression>
void statement(int** tks) {
    cout << "Enter <statement>" << endl;
    ident(tks);
    assignment_op(tks);
    expression(tks);
    cout << "Exit <statement>" << endl;
}
//<expression> -> <term> <term_tail>
void expression(int** tks) {
    cout << "Enter <expression>" << endl;
    term(tks);
    term_tail(tks);
    cout << "Exit <expression>" << endl;
}
//<term> -> <factor> <factor_tail>
void term(int** tks) {
    cout << "Enter <term>" << endl;
    factor(tks);
    factor_tail(tks);
    cout << "Exit <term>" << endl;
}
//<term_tail> -> {<add_op> <term> <term_tail>}
void term_tail(int** tks) {
    if (tks[fl][f] == ADD_OP) {
        cout << "Enter <term_tail>" << endl;
        add_op(tks);
        term(tks);
        term_tail(tks);
        cout << "Exit <term_tail>" << endl;
    }
}
//<factor> -> (<left_paren> <expression> <right_paren> | <ident> | <const>)
void factor(int** tks) {
    cout << "Enter <factor>" << endl;
>>>>>>> 6a9cd65a158fa2226a362cddb96e30fb9cc9cee8
    if (tks[fl][f] == LPAREN) {
        left_paren(tks);
        expression(tks);
        right_paren(tks);
    }
    else if (tks[fl][f] == IDENT) {
        ident(tks);
    }
    else if (tks[fl][f] == CONST) {
        const_(tks);
    }
<<<<<<< HEAD
    //cout << "Exit <factor>" << endl;
}
//<factor_tail> -> {<mult_op> <factor> <factor_tail>}
void factor_tail(vector<vector<int>> tks) {
    if (tks[fl][f] == MUL_OP) {
        //cout << "Enter <factor_tail>" << endl;
        mult_op(tks);
        factor(tks);
        factor_tail(tks);
        //cout << "Exit <factor_tail>" << endl;
    }
}
//<const> -> any decimal numbers
void const_(vector<vector<int>> tks) {
    //cout << "Enter <const>" << endl;
    if (tks[fl][f] == CONST) {
        if (fl != tks.size()-1 || f != tks[fl].size() - 1) {
            f++;
        }
    }
    //cout << "Exit <const>" << endl;
}
//<ident> -> any names conforming to C id rules
void ident(vector<vector<int>> tks) {
    //cout << "Enter <ident>" << endl;
    if (tks[fl][f] == IDENT) {
        if (fl != tks.size() - 1 || f != tks[fl].size()-1) {
            f++;
        }
    }
    //cout << "Exit <ident>" << endl;
}
//<assignment_op> -> :=
void assignment_op(vector<vector<int>> tks) {
    //cout << "Enter <assignment_op>" << endl;
    if (tks[fl][f] == ASSIGN_OP) {
        f++;
    }
    //cout << "Exit <assignmnet_op>" << endl;
}
//<semi_colon> -> ;
//여기서 줄이 바뀐다, 2차원 배열이 바뀌는 것,
void semi_colon(vector<vector<int>> tks) {
    //cout << "Enter <semi_colon>" << endl;
    if (tks[fl][f] == SEMI_COLON) {
        if (tks[fl].size() == f + 1) { // 배열 길이, 
=======
    cout << "Exit <factor>" << endl;
}
//<factor_tail> -> {<mult_op> <factor> <factor_tail>}
void factor_tail(int** tks) {
    if (tks[fl][f] == MUL_OP) {
        cout << "Enter <factor_tail>" << endl;
        mult_op(tks);
        factor(tks);
        factor_tail(tks);
        cout << "Exit <factor_tail>" << endl;
    }
}
//<const> -> any decimal numbers
void const_(int** tks) {
    cout << "Enter <const>" << endl;
    if (tks[fl][f] == CONST) {
        if (!(tks[fl][f] == NULL)) { // 맨 끝은 identifier 아니면 const로 끝난다.
            f++;
        }
    }
    cout << "Exit <const>" << endl;
}
//<ident> -> any names conforming to C id rules
void ident(int** tks) {
    cout << "Enter <ident>" << endl;
    if (tks[fl][f] == IDENT) {
        if (!(tks[fl][f] == NULL)) {
            f++;
        }
    }
    cout << "Exit <ident>" << endl;
}
//<assignment_op> -> :=
void assignment_op(int** tks) {
    cout << "Enter <assignment_op>" << endl;
    if (tks[fl][f] == ASSIGN_OP) {
        f++;
    }
    cout << "Exit <assignmnet_op>" << endl;
}
//<semi_colon> -> ;
//여기서 줄이 바뀐다, 2차원 배열이 바뀌는 것,
void semi_colon(int** tks) {
    cout << "Enter <semi_colon>" << endl;
    if (tks[fl][f] == SEMI_COLON) {
        if (sizeof(tks[fl]) / sizeof(int) == f + 1) { // 배열 길이, 
>>>>>>> 6a9cd65a158fa2226a362cddb96e30fb9cc9cee8
            fl++;
            f = 0;
        }
    }
<<<<<<< HEAD
    //cout << "Exit <semi_colon>" << endl;
}
//<add_op> -> (+|-)
void add_op(vector<vector<int>> tks) {
    //cout << "Enter <add_op>" << endl;
    if (lexeme[fl][f] == "++") {
        lexeme[fl][f] = "+";
        dup_op.push_back(char(fl) + lexeme[fl][f]);
    }
    else if (lexeme[fl][f] == "--") {
        lexeme[fl][f] = "-";
        dup_op.push_back(char(fl) + lexeme[fl][f]);
    }
    if (tks[fl][f] == ADD_OP) {
        f++;
    }


    //cout << "Exit <add_op>" << endl;
}
//<mult_op> -> (*|/)
void mult_op(vector<vector<int>> tks) {
    //cout << "Enter <mult_op>" << endl;
    if (lexeme[fl][f] == "**") {
        lexeme[fl][f] = "*";
        dup_op.push_back(char(fl) + lexeme[fl][f]);
    }
    else if (lexeme[fl][f] == "//") {
        lexeme[fl][f] = "/";
        dup_op.push_back(char(fl) + lexeme[fl][f]);
=======
    cout << "Exit <semi_colon>" << endl;
}
//<add_op> -> (+|-)
void add_op(int** tks) {
    cout << "Enter <add_op>" << endl;
    if (lexeme[fl][f] == "++") {
        lexeme[fl][f] = "+";
        dup_op[s] = to_string(fl) + "+";
        s++;
    }
    else if (lexeme[fl][f] == "--") {
        lexeme[fl][f] = "-";
        dup_op[s] = to_string(fl) + "-";
        s++;
    }
    if (tks[fl][f] == ADD_OP) {
        f++;
    }
    cout << "Exit <add_op>" << endl;
}
//<mult_op> -> (*|/)
void mult_op(int** tks) {
    cout << "Enter <mult_op>" << endl;
    if (lexeme[fl][f] == "**") {
        lexeme[fl][f] = "*";
        dup_op[s] = to_string(fl) + "*";
        s++;
    }
    else if (lexeme[fl][f] == "//") {
        lexeme[fl][f] = "/";
        dup_op[s] = to_string(fl) + "/"; //몇 번줄에서 일어났는지,
        s++;
>>>>>>> 6a9cd65a158fa2226a362cddb96e30fb9cc9cee8
    }
    if (tks[fl][f] == MUL_OP) {
        f++;
    }
<<<<<<< HEAD
    //cout << "Exit <mult_op>" << endl;
}
//<left_paren> -> (
void left_paren(vector<vector<int>> tks) {
    //cout << "Enter <left_paren>" << endl;
    if (tks[fl][f] == LPAREN) {
        f++;
    }
    //cout << "Exit <left_paren>" << endl;
}
//<right_paren> -> )
void right_paren(vector<vector<int>> tks) {
    //cout << "Enter <right_paren>" << endl;
    if (tks[fl][f] == RPAREN) {
        f++;
    }
    //cout << "Exit <right_paren>" << endl;
}
=======
    cout << "Exit <mult_op>" << endl;
}
//<left_paren> -> (
void left_paren(int** tks) {
    cout << "Enter <left_paren>" << endl;
    if (tks[fl][f] == LPAREN) {
        f++;
    }
    cout << "Exit <left_paren>" << endl;
}
//<right_paren> -> )
void right_paren(int** tks) {
    cout << "Enter <right_paren>" << endl;
    if (tks[fl][f] == RPAREN) {
        f++;
    }
    cout << "Exit <right_paren>" << endl;
}
>>>>>>> 6a9cd65a158fa2226a362cddb96e30fb9cc9cee8
