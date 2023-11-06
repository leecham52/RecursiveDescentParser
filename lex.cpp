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

//lexical 함수로 lexical analyze한 값을 token, lexeme 각각 2차원 벡터로 값을 저장
vector<vector<int>> tokens;
vector<vector<string>> lexeme;
//lexical 함수로 token화 한 것을 가지고 Recursive Descent Parser과정을 가지면서 문법에 맞게 되는지 확인하기 위한 전역변수, 2차원으로 [fl][f] 
int fl = 0;
int f = 0;
//warning, error를 표기
vector<string> dup_op;
int duo = 0;
vector<string> error;
//ident의 현재 값을 저장하기 위한 구조체
struct Id {
    string id;
    int val;
};
//(,), *, / +,-는 계산하는데 있어 우선 순위가 있기에 이를 나타내주기 위한 구조체 
struct op {
    string ope;
    int p;
};
//ident 현재 값 저장한 구조체의 vector
vector<Id> ide;
//ident에 대한 계산을 위한 stack
stack<int> num;
stack<op> oper;

//terminal의 token 값, ident의 값이 UNKNOWN일 떄 표기
#define IDENT 10
#define CONST 11
#define ASSIGN_OP 12
#define SEMI_COLON 13
#define ADD_OP 14
#define MUL_OP 16
#define LPAREN 18
#define RPAREN 19
#define UNKNOWN -10000
//lexical 함수에 필요한, check 함수들
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

//Recursive Descent Parser를 Assignment1에 있는 조건에 맞게 함수화
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

//lexical analyzer 함수
void lexical(string str);
//id 계산의 세부 함수, stack의 맨 위에 있는 두 숫자에 대한 계산을 하고, stack oper 맨 위의 operator로 결과를 stack에 저장
void calString();
//Recursive Descent Parser에 알맞은 lexeme들에 대해서 각 id에 대한 계산
void calIdent(vector<vector<int>> tk, vector<vector<string>> lex, vector<Id>& ident);
//일련의 과정을 거친 후 Assignment1의 출력에 맞춰서 출력
void printResult(vector<vector<int>> tk, vector<vector<string>> lex);


int main(int argc, char* argv[]) {
    string in;
    ifstream in_Fp;
    in_Fp.open(argv[1]);
    if (!in_Fp.is_open()) {
        cout << "ERROR - cannot open front.in" << endl;
        return 0;
    }
    while (!in_Fp.eof()) {
        getline(in_Fp, in); //한 줄씩 입력 받음
        lexical(in);
        duo++;
    }
    in_Fp.close();

    program(tokens);
    calIdent(tokens, lexeme, ide);
    printResult(tokens, lexeme);

    return 0;
}

void lexical(string str) {
    int next_token = 0;
    string tok; //identifier, const만 받아와서 저장하는 string
    string notLit; // :=,+,-,*,/,(,) 저장하는 string
    string token_string; //문자열 변수, ascii 32 이하 값들을 무시한 string
    vector<string> lex; //한 줄에 대한 lexeme
    vector<int> n_t; //한 줄에 대한 token
    lex.clear();
    n_t.clear();
    for (int i = 0; i < str.length(); i++) {
        if (!checkWhiteSpace(str[i])) {
            token_string += str[i]; //공백을 뺀 줄을 가져온다. id1 = id2 + 2; => id1=id2+2;
        }
    }
    for (int i = 0; i < token_string.length();) {
        tok.clear();
        notLit.clear();

        //identifier, const 2가지 경우를 걸러서 저장
        while ((checkLetter(token_string[i]) || checkDigit(token_string[i]) || token_string[i] == '_')) {
            tok += token_string[i];
            i++;
        }
        next_token = checkToken(tok.c_str()); // 여기서 identifier, const 걸러서 token화된다.
        //lexeme이랑 token을 어딘가 저장을 해둬야한다.
        if (!tok.empty() && next_token != 0) {
            lex.push_back(tok);
            n_t.push_back(next_token);
        }
        //notLit에 notLiteral한 것들 저장
        if (token_string[i] == ':') {
            notLit += token_string[i];
            i++;
            if (token_string[i] == '=') {
                notLit += token_string[i];
                i++;
            }
        }
        //++,--,**,// 처럼 중복 연산자가 나오면 오류난 곳을 dup_op에 저장하고, lexeme은 1개만 저장
        else if (token_string[i] == '+') {
            notLit += token_string[i];
            i++;
            if (token_string[i] == '+') {
                dup_op.push_back(char(duo) + notLit);
                i++;
            }
        }
        else if (token_string[i] == '-') {
            notLit += token_string[i];
            i++;
            if (token_string[i] == '-') {
                dup_op.push_back(char(duo) + notLit);
                i++;
            }
        }
        else if (token_string[i] == '*') {
            notLit += token_string[i];
            i++;
            if (token_string[i] == '*') {
                dup_op.push_back(char(duo) + notLit);
                i++;
            }
        }
        else if (token_string[i] == '/') {
            notLit += token_string[i];
            i++;
            if (token_string[i] == '/') {
                dup_op.push_back(char(duo) + notLit);
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
    string operate = oper.top().ope;
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
void calIdent(vector<vector<int>> tk, vector<vector<string>> lex, vector<Id>& ident) {
    vector<string> e = error;
    //ident 계산
    for (int k = 0; k < tk.size(); k++) {
        for (int i = 2; i < tk[k].size(); i++) {
            //ident가 assignment 우측에 나올때, ide vector안에 있는게 아니면, Unknown을 넣어준다. 
            if (tk[k][i] == IDENT) {
                //우측에 나왔지만, ide vector에 없는 경우, 첫 줄만 해당된다.
                if (ident.size() == 0) {
                    num.push(UNKNOWN);
                    ident.push_back({ lex[k][i], UNKNOWN });
                    error.push_back(to_string(k) + lex[k][i]);
                }
                for (int j = 0; j < ident.size(); j++) {
                    int l = 0;
                    //ide 안에 저장되어 있으면 num stack에 ident val를 넣는다.
                    if (lex[k][i] == ident[j].id) {
                        num.push(ident[j].val);
                    }
                    else {
                        l++;
                        //ide안에 있는 ident가 안 나왔을 때
                        if (l == ident.size()) {
                            num.push(UNKNOWN);
                            ident.push_back({ lex[k][i], UNKNOWN });
                            for (int c = 0; c < error.size(); c++) {
                                string getE = error[c];
                                for (int b = 1; b < getE.size(); b++) {
                                    error[c].erase(0);
                                    error[c] += getE[b];
                                }
                                cout << error[c].front();
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
                //*,/가 +,-보다 먼저 계산되어야 하기 때문에, 즉 stack의 위쪽에 있게 해서 pr <= oper.top().p가 들어간 것이다.
                while (!oper.empty() && pr <= oper.top().p) {
                    calString();
                }
                oper.push({ lex[k][i], pr });
            }
            else if (tk[k][i] == LPAREN) { // ( )안에 있는 게 계산이 먼저 된다. 
                oper.push({ lex[k][i], 0 });
            }
            else if (tk[k][i] == RPAREN) { // )가 오면 계산 시작, (가 나올때 까지만 한다.
                while (oper.top().ope != "(") {
                    calString();
                }
                oper.pop();
            }
        }
        while (!oper.empty()) {
            calString();
        }
        if (tk[k][0] == IDENT) {
            int ni = 0;
            //이미 있는 ident에 대해서 새로 정의될 때,
            for(int u = 0; u < ident.size(); u++){
                if(ident[u].id == lex[k][0]){
                    ident[u].val = num.top();
                    ni = 1;
                    break;
                }
            }
            if(ni == 0){
                ident.push_back({ lex[k][0], num.top() });
            }
            num.pop();
        }
    }
}
//출력, ID, CONST, OP의 개수를 나타내주는 함수
void printResult(vector<vector<int>> tk, vector<vector<string>> lex) {
    for (int k = 0; k < tk.size(); k++) {
        int id_count = 0;
        int const_count = 0;
        int op_count = 0;
        string m;
        m.clear();
        for (int i = 0; i < tk[k].size(); i++) {
            m += lex[k][i];
            if (i != tk[k].size() - 1) {
                m += " ";
            }
            //id, const, op의 개수 확인
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
        //중복 연산자가 있었다면, dup_op vector 확인후 출력
        int ew = 0;
        for (int s = 0; s < dup_op.size(); s++) {
            if (dup_op[s].front() == (char)k) {
                ew = 1;
                cout << "(WARNING) \"중복 연산자(" << dup_op[s].back() << ") 제거 \" " << endl;
            }
        }
        //Unknown한 ident가 있다면 error
        if (!error.empty()) {
            for (int v = 0; v < error.size(); v++) {
                string errP;
                errP = error[v].front();
                if (errP[0] - '0' == char(k)) {
                    errP.clear();
                    for (int b = 1; b < error[v].size(); b++) {
                        errP += error[v][b];
                    }
                    ew = 1;
                    cout << "(Error) \"정의되지 않은 변수(" << errP << ")가 참조됨\"" << endl;
                    break;
                }
            }
        }
        //둘 다 아니면, ok 출력
        if(ew == 0){
            cout << "(OK)" << endl;
        }
        //OK, WARNING, Error
    }
    //Result 
    cout << "Result ==> ";
    for (int n = 0; n < ide.size(); n++) {
        if (ide[n].val < 0 || ide[n].val > 10000) {
            if (n == ide.size() - 1) {
                cout << ide[n].id << ": Unknown";
            }
            else
                cout << ide[n].id << ": " << "Unknown;";
        }
        else {
            if (n == ide.size() - 1) {
                cout << ide[n].id << ": " << to_string(ide[n].val);
            }
            else
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
//+,-인지 확인
bool checkAddOp(const char c[]) {
    if (c[0] == '+' || c[0] == '-') {
        return true;
    }
    return false;
}
//*,/인지 확인
bool checkMulOp(const char c[]) {
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
    else if (checkRparen(t)) {
        return RPAREN;
    }
    else if (checkSemiColon(t)) {
        return SEMI_COLON;
    }
    else return 0;
}
//Assignment 1 조건에 맞는 Recursive-Descent Parsing
//<program> -> <statements>
void program(vector<vector<int>> tks) {
    cout << "Enter <program>" << endl;
    statements(tks);
    cout << "Exit <program>" << endl;
}
//<statements> -> <statement> {<semi_colon><statements}
void statements(vector<vector<int>> tks) {
    cout << "Enter <statements>" << endl;
    statement(tks);
    if (tks[fl].size() != f) {
        if (tokens[fl][f] == SEMI_COLON) {
            semi_colon(tks);
            statements(tks);
        }
        cout << "Exit <statements>" << endl;
    }
    else {
        if (tks.size() != fl) {
            fl++;
            cout << "조건에 맞지 않는 lexeme:" << lexeme[fl][0] << "입력" << endl;
            exit(100);
        }
    }
}
//<statement> -> <ident> <assignment_op> <expression>
void statement(vector<vector<int>> tks) {
    cout << "Enter <statement>" << endl;
    ident(tks);
    assignment_op(tks);
    expression(tks);
    cout << "Exit <statement>" << endl;
}
//<expression> -> <term> <term_tail>
void expression(vector<vector<int>> tks) {
    cout << "Enter <expression>" << endl;
    term(tks);
    term_tail(tks);
    cout << "Exit <expression>" << endl;
}
//<term> -> <factor> <factor_tail>
void term(vector<vector<int>> tks) {
    cout << "Enter <term>" << endl;
    factor(tks);
    factor_tail(tks);
    cout << "Exit <term>" << endl;
}
//<term_tail> -> {<add_op> <term> <term_tail>}
void term_tail(vector<vector<int>> tks) {
    if (tks[fl].size() != f) {
        if (tks[fl][f] == ADD_OP) {
            cout << "Enter <term_tail>" << endl;
            add_op(tks);
            term(tks);
            term_tail(tks);
            cout << "Exit <term_tail>" << endl;
        }
    }
    else {
        if (tks.size() != fl) {
            cout << "조건에 맞지 않는 lexeme:" << lexeme[fl][0] << "입력" << endl;
            exit(100);
        }
    }
}
//<factor> -> (<left_paren> <expression> <right_paren> | <ident> | <const>)
void factor(vector<vector<int>> tks) {
    if (tks[fl].size() != f) {
        cout << "Enter <factor>" << endl;
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
        else {
            cout << "조건에 맞지 않는 lexeme:" << lexeme[fl][f] << "입력" << endl;
            exit(100);
            return;
        }
        cout << "Exit <factor>" << endl;
    }
    else {
        if (tks.size() != fl) {
            fl++;
            cout << "조건에 맞지 않는 lexeme:" << lexeme[fl][0] << "입력" << endl;
            exit(100);
        }
    }
}
//<factor_tail> -> {<mult_op> <factor> <factor_tail>}
void factor_tail(vector<vector<int>> tks) {
    cout << "Enter <factor_tail>" << endl;
    if (tks[fl].size() != f) {
        if (tks[fl][f] == MUL_OP) {
            mult_op(tks);
            factor(tks);
            factor_tail(tks);
            cout << "Exit <factor_tail>" << endl;
        }
    }
    else {
        if (tks.size() != fl) {
            fl++;
            cout << "조건에 맞지 않는 lexeme:" << lexeme[fl][0] << "입력" << endl;
            exit(100);
        }
    }
}
//<const> -> any decimal numbers
void const_(vector<vector<int>> tks) {
    if (tks[fl].size() != f) {
        cout << "Enter <const>" << endl;
        if (tks[fl][f] == CONST) {
            if (fl != tks.size() - 1 || f != tks[fl].size() - 1) {
                f++;
            }
        }
        cout << "Exit <const>" << endl;
    }
    else {
        if (tks.size() != fl) {
            fl++;
            cout << "조건에 맞지 않는 lexeme:" << lexeme[fl][0] << "입력" << endl;
            exit(100);
        }
    }

}
//<ident> -> any names conforming to C id rules
void ident(vector<vector<int>> tks) {
    if (tks[fl].size() != f) {
        cout << "Enter <ident>" << endl;
        if (tks[fl][f] == IDENT) {
            if (fl != tks.size() - 1 || f != tks[fl].size() - 1) {
                f++;
            }
        }
        cout << "Exit <ident>" << endl;
    }
    else {
        if (tks.size() != fl) {
            fl++;
            cout << "조건에 맞지 않는 lexeme:" << lexeme[fl][0] << "입력" << endl;
            exit(100);
        }
    }
}
//<assignment_op> -> :=
void assignment_op(vector<vector<int>> tks) {
    if (tks[fl].size() != f) {
        cout << "Enter <assignment_op>" << endl;
        if (tks[fl][f] == ASSIGN_OP) {
            f++;
        }
        cout << "Exit <assignmnet_op>" << endl;
    }
    else {
        if (tks.size() != fl) {
            fl++;
            cout << "조건에 맞지 않는 lexeme:" << lexeme[fl][0] << "입력" << endl;
            exit(100);
        }
    }
}
//<semi_colon> -> ;
//여기서 줄이 바뀐다, 2차원 배열이 바뀌는 것,
void semi_colon(vector<vector<int>> tks) {
    if (tks[fl].size() != f) {
        cout << "Enter <semi_colon>" << endl;
        if (tks[fl][f] == SEMI_COLON) {
            if (tks[fl].size() == f + 1) { // 배열 길이, 
                fl++;
                f = 0;
            }
        }
        cout << "Exit <semi_colon>" << endl;
    }
    else {
        if (tks.size() != fl) {
            fl++;
            cout << "조건에 맞지 않는 lexeme:" << lexeme[fl][0] << "입력" << endl;
            exit(100);
        }
    }
}
//<add_op> -> (+|-)
void add_op(vector<vector<int>> tks) {
    if (tks[fl].size() != f) {
        cout << "Enter <add_op>" << endl;
        if (tks[fl][f] == ADD_OP) {
            f++;
        }
        cout << "Exit <add_op>" << endl;
    }
    else {
        if (tks.size() != fl) {
            fl++;
            cout << "조건에 맞지 않는 lexeme:" << lexeme[fl][0] << "입력" << endl;
            exit(100);
        }
    }
}
//<mult_op> -> (*|/)
void mult_op(vector<vector<int>> tks) {
    if (tks[fl].size() != f) {
        cout << "Enter <mult_op>" << endl;
        if (tks[fl][f] == MUL_OP) {
            f++;
        }
        cout << "Exit <mult_op>" << endl;
    }
    else {
        if (tks.size() != fl) {
            fl++;
            cout << "조건에 맞지 않는 lexeme:" << lexeme[fl][0] << "입력" << endl;
            exit(100);
        }
    }
}
//<left_paren> -> (
void left_paren(vector<vector<int>> tks) {
    if (tks[fl].size() != f) {
        cout << "Enter <left_paren>" << endl;
        if (tks[fl][f] == LPAREN) {
            f++;
        }
        cout << "Exit <left_paren>" << endl;
    }
    else {
        if (tks.size() != fl) {
            fl++;
            cout << "조건에 맞지 않는 lexeme:" << lexeme[fl][0] << "입력" << endl;
            exit(100);
        }
    }
}
//<right_paren> -> )
void right_paren(vector<vector<int>> tks) {
    if (tks[fl].size() != f) {
        cout << "Enter <right_paren>" << endl;
        if (tks[fl][f] == RPAREN) {
            f++;
            cout << "Exit <right_paren>" << endl;
        }
    }
    else {
        if (tks.size() != fl) {
            fl++;
            cout << "조건에 맞지 않는 lexeme:" << lexeme[fl][0] << "입력" << endl;
            exit(100);
        }
    }
}