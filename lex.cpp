#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
using namespace std;

//아쉽지만, 전역변수로 받기
//2차원 배열로 값 받기

int* tokens[];
string* lexeme[];
int k = 0;
int te = 0;
int fl = 0;
int f = 0;

#define IDENT 10
#define CONST 11
#define ASSIGN_OP 12
#define SEMI_COLON 13
#define ADD_OP 14
#define MUL_OP 16
#define LPAREN 18
#define RPAREN 19
#define EOF 99

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

void lexical(string str);
void printLexCount(int* tk);
void RecursiveDescentParsing();

class Node {
    public:
        string parse;
        bool nonTorT; //true면 nonTerminal, false면 Terminal
        int terminalVal;
        Node* left;
        Node* center;
        Node* right;
        Node(string val){
            parse = val;
            nonTorT = true;
            left = NULL;
            center = NULL;
            right = NULL;
        }
        Node(string val, int terminal){
            parse = val;
            nonTorT = false;
            terminalVal = terminal;
            left = NULL;
            center = NULL;
            right = NULL;
        }
        //뭔가 있어야함. 함수로 next_token을 이용한 것으로.
};

int main(int argc, char* argv[]) {
    if (argc < 2)
	{
		cout << "파일 입력 오류" << endl;
		return 0;
	}
    string* in;
    
    //c++에 맞춰서 변환, string으로 낑겨 받으면 좋을수도 아닐수도
    ifstream in_Fp(argv[1]);
    if (!in_Fp.is_open())
        cout<< "ERROR - cannot open front.in" << endl;
    while(!in_Fp.eof()){
        getline(in_Fp, in[k]); //한 줄씩 입력 받음
        cout << in[k] << endl;
        lexical(in[k]);
        printLexCount(tokens[k]);
        k++;
    }
    in_Fp.close();
    program(*tokens);
    return 0;
}

void lexical(string str){
    int next_token;
    string token_string;
    string tok;
    string notLit;
    string tempstr;
    for(int i = 0; i<str.length(); i++){
        if(isspace(str[i]) == 0){
            tempstr += str[i]; //공백을 뺀 줄을 가져온다. id1 = id2 + 2; => id1=id2+2;
        }
    }
    for(int i = 0; i<tempstr.length();){
        tok.clear();
        notLit.clear();
        
        //identifier, const 2가지 경우를 걸러서 저장
        while((checkLetter(tempstr[i]) || checkDigit(tempstr[i] || tempstr[i] == '_'))){
            tok += tempstr[i];
            i++;
        }
        next_token = checkToken(tok.c_str()); // 여기서 identifier, const 걸러서 token화된다.
        //lexeme이랑 token을 어딘가 저장을 해둬야한다.
        if(!tok.empty() && next_token != NULL){
            lexeme[k][te] = tok;
            tokens[k][te] = next_token;
            te++;    
        }
        if(tempstr[i] == ':'){
            notLit += tempstr[i];
            i++;
            if(tempstr[i] == '='){
                notLit += tempstr[i];
                i++;
            }
        }
        else if(tempstr[i] == '+'){
            notLit += tempstr[i];
            i++;
            if(tempstr[i] == '+'){
                notLit += tempstr[i];
                i++;
            }
        }
        else if(tempstr[i] == '-'){
            notLit += tempstr[i];
            i++;
            if(tempstr[i] == '-'){
                notLit += tempstr[i];
                i++;
            }
        }
        else if(tempstr[i] == '*'){
            notLit += tempstr[i];
            i++;
            if(tempstr[i] == '*'){
                notLit += tempstr[i];
                i++;
            }
        }
        else if(tempstr[i] == '/'){
            notLit += tempstr[i];
            i++;
            if(tempstr[i] == '/'){
                notLit += tempstr[i];
                i++;
            }
        }
        else if(tempstr[i] == '(' || tempstr[i] == ')' || tempstr[i] == ';'){
            notLit += tempstr[i];
            i++;
        }
        next_token = checkToken(notLit.c_str());
        if(!notLit.empty() && next_token != NULL){
            lexeme[k][te] = notLit;
            tokens[k][te] = next_token;
            te++;
        }
        /*
        if(checkToken(tok.c_str()) != EOF){
               
        }
        else {
            tok = cpytok;
        }*/
    }
}
//ID, CONST, OP의 개수를 나타내주는 함수
void printLexCount(int** tk){
    int id_count = 0;
    int const_count = 0;
    int op_count = 0;
    for(int i =0; i< sizeof(tk[k])/sizeof(int); i++){
        if(tk[k][i] == IDENT){
            id_count++;
        }
        else if(tk[k][i] == CONST){
            const_count++;
        }
        else if(tk[k][i] == ADD_OP || tk[k][i] == MUL_OP){
            op_count++;
        }
    }
    cout<<"ID: "<<id_count<<"; CONST: "<<const_count<<"; OP: "<<op_count<<";"<<endl;
}
bool checkLetter(char c) {
    if (c >= 65 && c <= 90) {  // refer to ascii code
		return true;
	}
	else if (c >= 97 && c <= 122) { // refer to ascii code
		return true;
	}
	else return false;
}
bool checkDigit(char c){
    if (c >= 48 && c <= 57) { // refer to ascii code
		return true;
	}
	else return false;
}
//identifier인지 확인
bool checkIdent(const char c[]){
    if(c[0] == '_' || checkLetter(c[0])){
        if((int)strlen(c) == 1){ //한 자릿 수의 identifier일 때
            return true;
        }
        for (int i = 1; i<(int)strlen(c); i++){
            if(c[i] != '_' && !checkLetter(c[i]) && !checkDigit(c[i])){
                return false;
            }
        }
        return true;
    }
    else return false;
}
//const인지 확인
bool checkConst(const char c[]){
    if(c[0] == '0' && (int)strlen(c) == 1){ //0일때
        return true;
    }
    if(checkDigit(c[0]) && c[0] != '0'){
        for(int i = 1; i<=(int)strlen(c); i++){
            if(checkDigit(c[i])){
                continue;
            }
            else if(c[i] == '\0') return true;
            else return false;
        }
    }
    return false;
}
//+,-인지 확인 + ++, --에 대해서는? 따로 처리 레츠고
//++, -- 한번씩만 더 쓴 걸로 생각 하고 +-, -+ 같은 경우는 false로 처리
//
bool checkAddOp(const char c[]){
    if((int)strlen(c) == 2){
        if((c[0] == '+' && c[1] == '+') || (c[0] == '-' && c[1] == '-')){
            return true; //Warning 받아갈만한것을 넣어주면 될듯,
        }
    }
    if((int)strlen(c) != 1){
        return false;
    }
    if(c[0] == '+' || c[0] == '-'){
        return true;
    }
    return false;
}
//*,/인지 확인
bool checkMulOp(const char c[]){
    if((int)strlen(c) == 2){
        if((c[0] == '*' && c[1] == '*') || (c[0] == '/' && c[1] == '/')){
            
        }
    }
    if((int)strlen(c) != 1){
        return false;
    }
    if(c[0] == '*' || c[0] == '/'){
        return true;
    }
    return false;
}
// := 인지 확인
bool checkAssignOp(const char c[]){
    if((int)strlen(c) == 2 && c[0] == ':' && c[1] == '='){
        return true;
    } 
    return false;
}
//(인지 확인
bool checkLparen(const char c[]){
    if((int)strlen(c) == 1 && c[0] == '('){
        return true;
    }
    return false;
}
//)인지 확인
bool checkRparen(const char c[]){
    if((int)strlen(c) == 1 && c[0] == ')'){
        return true;
    }
    return false;
}
//;인지 확인
bool checkSemiColon(const char c[]){
    if((int)strlen(c) == 1 && c[0] == ';'){
        return true;
    }   
    return false;
}
int checkToken(const char t[]){
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
    else return EOF;
}
void RecursiveDescentParsing(){    
    Node* program = new Node("program");
    Node* statements = new Node("statements");
    program->left = statements;
    Node* statement = new Node("statement");
    Node* semi_colon = new Node("semi_colon", SEMI_COLON);
    statements-> left = statement;
    statements-> center = semi_colon;
    statements-> right = statements;
    Node* ident = new Node("ident", IDENT);
    Node* assign_op = new Node("assign_op", ASSIGN_OP);
    Node* expression = new Node("expression");
    statement->left = ident;
    statement->center = assign_op;
    statement->right = expression;
    Node* term = new Node("term");
    Node* term_tail = new Node("term_tail");
    expression->left = term;
    expression->center = term_tail;
    Node* factor = new Node("factor");
    Node* factor_tail = new Node("factor_tail");
    term->left = factor;
    term->center = factor_tail;
    Node* add_op = new Node("add_op", ADD_OP);
    Node* mul_op = new Node("mul_op", MUL_OP);
    term_tail->left = add_op;
    term_tail->center = term;
    term_tail->right = term_tail;
    Node* lparen = new Node("lparen", LPAREN);
    Node* rparen = new Node("rparen", RPAREN);
    Node* const_ = new Node("const", CONST);
    factor->left = lparen;
    factor->center = expression;
    factor->right = rparen;
    factor_tail->left = mul_op;
    factor_tail->center = factor;
    factor_tail->right = factor_tail;
}

//Assignment 1 조건에 맞는 Recursive-Descent Parsing
//<program> -> <statements>
void program(int** tks) {
    cout<< "Enter <program>" << endl;
    statements(tks);
    cout<<"Exit <program>"<<endl;
}
//<statements> -> <statement> {<semi_colon><statements}
void statements(int** tks){
    cout<<"Enter <statements>"<<endl;
    statement(tks);
    if(tokens[fl][f] == SEMI_COLON){
        semi_colon(tks);
        statements(tks);
    }
    cout<<"Exit <statements>"<<endl;
}
//<statement> -> <ident> <assignment_op> <expression>
void statement(int** tks){
    cout<<"Enter <statement>"<<endl;
    ident(tks);
    assignment_op(tks);
    expression(tks);
    cout<<"Exit <statement>"<<endl;
}
//<expression> -> <term> <term_tail>
void expression(int** tks){
    cout<<"Enter <expression>"<<endl;
    term(tks);
    term_tail(tks);
    cout<<"Exit <expression>"<<endl;
}
//<term> -> <factor> <factor_tail>
void term(int** tks){
    cout<<"Enter <term>"<<endl;
    factor(tks);
    factor_tail(tks);
    cout<<"Exit <term>"<<endl;
}
//<term_tail> -> {<add_op> <term> <term_tail>}
void term_tail(int** tks){
    if(tks[fl][f] == ADD_OP){
        cout<<"Enter <term_tail>"<<endl;
        add_op(tks);
        term(tks);
        term_tail(tks);
        cout<<"Exit <term_tail>"<<endl;
    }
}
//<factor> -> (<left_paren> <expression> <right_paren> | <ident> | <const>)
void factor(int** tks){  
    cout<<"Enter <factor>"<<endl;
    if(tks[fl][f] == LPAREN){
        left_paren(tks);
        expression(tks);
        right_paren(tks);
    }
    else if(tks[fl][f] == IDENT){
        ident(tks);
    }
    else if(tks[fl][f] == CONST){
        const_(tks);
    }
    cout<<"Exit <factor>"<<endl;
}
//<factor_tail> -> {<mult_op> <factor> <factor_tail>}
void factor_tail(int** tks) {
    if(tks[fl][f] == MUL_OP){
        cout<<"Enter <factor_tail>"<<endl;
        mult_op(tks);
        factor(tks);
        factor_tail(tks);
        cout<<"Exit <factor_tail>"<<endl;
    }
}
//<const> -> any decimal numbers
void const_(int** tks){
    cout<<"Enter <const>"<<endl;
    if(tks[fl][f] == CONST){
        f++;
        if(sizeof(tks[fl]))
    }
    cout<<"Exit <const>"<<endl;
}
//<ident> -> any names conforming to C id rules
void ident(int** tks){
    cout<<"Enter <ident>"<<endl;
    if(tks[fl][f] == IDENT){
        f++;
    }
    cout<<"Exit <ident>"<<endl;
}
//<assignment_op> -> :=
void assignment_op(int** tks){
    cout<<"Enter <assignment_op>"<<endl;
    if(tks[fl][f] == ASSIGN_OP){
        f++;
    }
    cout<<"Exit <assignmnet_op>"<<endl;
}
//<semi_colon> -> ;
void semi_colon(int** tks){
    cout<<"Enter <semi_colon>"<<endl;
    if(tks[fl][f] == SEMI_COLON){
        if(sizeof(tks[fl])/sizeof(int) == f+1){
            fl++;
        }
        else f++;
    }
    cout<<"Exit <semi_colon>"<<endl;
}
//<add_op> -> (+|-)
void add_op(int** tks){
    cout<<"Enter <add_op>"<<endl;
    lex();
    cout<<"Exit <add_op>"<<endl;
}
//<mult_op> -> (*|/)
void mult_op(int** tks){
    cout<<"Enter <mult_op>"<<endl;
    lex();
    cout<<"Exit <mult_op>"<<endl;
}
//<left_paren> -> (
void left_paren(int** tks){
    cout<<"Enter <left_paren>"<<endl;
    lex();
    cout<<"Exit <left_paren>"<<endl;
}
//<right_paren> -> )
void right_paren(int** tks){
    cout<<"Enter <right_paren>"<<endl;
    lex();
    cout<<"Exit <right_paren>"<<endl;
}   