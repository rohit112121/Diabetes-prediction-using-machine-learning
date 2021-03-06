#include <bits/stdc++.h>
#define col 5
#define _s 30

using namespace std;

int init[20],fin[20],a=0,b=0;
string init_dfa[_s],fin_dfa[_s];
int _a = 0, _b = 0;

void initialise(int nfa_table[][col]){
    for(int i=0;i<1000;i++){
        for(int j=0;j<col;j++){
            nfa_table[i][j]=-1;
        }
    }
}

void print_initial_final(){
    cout<<"initial state/s is/are :- ";
    for(int i=0;i<a;i++)
        cout<<init[i]<<" ";
        cout<<endl;
        cout<<"final state/s is/are :- ";
    for(int i=0;i<b;i++)
        cout<<fin[i]<<" ";
        cout<<endl;
}

void print_initial_final_dfa(){
    cout<<"initial state/s is/are :- ";
    for(int i=0;i<_a;i++)
        cout<<init_dfa[i]<<" ";
        cout<<endl;
        cout<<"final state/s is/are :- ";
    for(int i=0;i<_b;i++)
        cout<<fin_dfa[i]<<" ";
        cout<<endl<<endl;
    for(int i=0;i<60;i++)
            cout<<"-";
    cout<<endl<<endl;
}

void reduce_fin(int x){
    for(int i=x; i<b-1; i++)
        fin[i] = fin[i+1];
        b -= 1;
}

/*
 preprocessor function simplifies the expression, as we have no symbol for concatenation
 operation. preprocessor function provide one.
*/

string preprocessor(string s){
    char x[5000];
    int l=s.length();
    int j=0;
    x[j]='(';
    j += 1;
    for(int i=0;i<l;i++){
            x[j]=s[i];
            j += 1;
        if(s[i]>=97&&s[i]<=122&&s[i+1]>=97&&s[i+1]<=122){
            x[j]='.';
            j += 1;
        }else if(s[i]==')'&&s[i+1]=='('){
            x[j]='.';
            j += 1;
        }else if(s[i]>=97&&s[i]<=122&&s[i+1]=='('){
            x[j]='.';
            j += 1;
        }else if(s[i]==')'&&s[i+1]>=97&&s[i+1]<=122){
            x[j]='.';
            j += 1;
        }else if(s[i]=='*'&&(s[i+1]=='(' || (s[i+1]>=97&&s[i+1]<122))){
            x[j]='.';
            j += 1;
        }
    }
    x[j] = ')';
    j += 1;
    string p;
    for(int i=0;i<j;i++)
       p += x[i];
    return p;
}

/*
    converts given regular expression into it's corresponding
    postfix notation
*/

string postfix(string s){
    int l=s.length();
    char a[5000];
    stack <char> ch;
    int j=0;
    for(int i=0;i<l;i++){
         char x = s[i];
         switch(x){
            case 'a':   a[j]='a';
                        j += 1;
                        break;
            case 'b':   a[j]='b';
                        j+=1;
                        break;
            case '(':   ch.push('(');
                        break;
            case ')':   while(!ch.empty()){
                            if(ch.top()=='('){
                                ch.pop();
                                break;
                            }else{
                                a[j]=ch.top();
                                    ch.pop();
                                    j += 1;
                            }
                        }
                        break;
            case '.':   if(ch.empty()){
                            ch.push('.');
                        }else {
                            char temp = ch.top();
                            if(temp=='(')
                                ch.push('.');
                            else if(temp=='*'){
                                a[j]=ch.top();
                                ch.pop();
                                j += 1;
                                if(ch.top()== '.'){
                                    a[j] = '.';
                                    j += 1;
                                }else{
                                    ch.push('.');
                                }
                            }else if(temp=='.'){
                                a[j]=ch.top();
                                ch.pop();
                                j += 1;
                                ch.push('.');
                        }else if(temp == '|'){
                               ch.push('.');
                        }
                    }
                        break;
            case '|':   if(ch.empty()){
                            ch.push('|');
                        }else{
                            char temp = ch.top();
                            if(temp == '(')
                                ch.push('|');
                            else if(temp == '*'){
                                a[j] = ch.top();
                                ch.pop();
                                j += 1;
                                ch.push('|');
                            }else if(temp == '.'){
                                a[j] = ch.top();
                                j += 1;
                                ch.pop();
                                ch.push('|');
                            }
                        }
                            break;
            case '*':   if(ch.empty()){
                            ch.push('*');
                        }else{
                            char temp = ch.top();
                            if(temp == '(' || temp == '.' || temp == '|' )
                                ch.push('*');
                            else{
                                a[j] = ch.top();
                                ch.pop();
                                j += 1;
                                ch.push('*');
                            }
                        }
                        break;
         }
    }
    string p;
    for(int i=0;i<j;i++){
        p += a[i];
    }
    return p;
}

/*
    this function convert's given postfix of reg expression
    into it's corresponding nfa
*/

int reg_nfa(string s,int nfa_table[][col]){
    int l = s.length();
    int states = 1;
    int m,n,j,counter;
    for(int i=0;i<l;i++){
        char x = s[i];
        switch(x){
            case 'a': nfa_table[states][0] = states;
                        init[a] = states;
                         a += 1;
                            states += 1;
                      nfa_table[states-1][1] = states;
                        fin[b] = states;
                        b += 1;
                      nfa_table[states][0] = states;
                            states +=1;
                      break;
            case 'b': nfa_table[states][0] = states;
                        init[a] = states;
                         a += 1;
                            states += 1;
                      nfa_table[states-1][2] = states;
                          fin[b] = states;
                          b += 1;
                      nfa_table[states][0] = states;
                            states +=1;
                      break;
            case '.': m = fin[b-2];
                      n = init[a-1];
                      nfa_table[m][3]=n;
                      reduce_fin(b-2);  //reduces final state
                      a -= 1;           //reduces initial states
                      break;
            case '|': for(j=a-1,counter=0;counter<2;counter++){
                        m = init[j-counter];
                        nfa_table[states][3+counter]=m;
                      }
                      a=a-2;
                      init[a]=states;
                      a += 1;
                      nfa_table[states][0] = states;
                      states += 1;
                      for(j=b-1,counter=0;counter<2;counter++){
                        m = fin[j-counter];
                        nfa_table[m][3]=states;
                      }
                      b=b-2;
                      fin[b]=states;
                      b += 1;
                      nfa_table[states][0] = states;
                      states += 1;
                      break;
            case '*': m = init[a-1];
                      nfa_table[states][3] = m;
                      nfa_table[states][0] = states;
                      init[a-1] = states;

                      states += 1;
                      n = fin[b-1];
                      nfa_table[n][3]=m;
                      nfa_table[n][4]=states;
                      nfa_table[states-1][4]=states;
                      fin[b-1]=states;
                      nfa_table[states][0]=states;
                      states += 1;
                        break;
        }
    }
  return states;
}

void print_nfa_table(int nfa_table[][col],int states){
    cout<<endl;
    for(int i=0;i<60;i++)
        cout<<"*";
        cout<<endl<<endl;
    cout<<setw(43)<<"TRANSITION TABLE FOR NFA"<<endl<<endl;
    cout<<setw(10)<<"States"<<setw(10)<<"a"<<setw(10)<<"b"<<setw(10)<<"e"<<setw(10)<<"e"<<endl;
    for(int i=0;i<60;i++)
        cout<<"-";
        cout<<endl;
    for(int i=1;i<states;i++){
        for(int j=0;j<col;j++){
            if(nfa_table[i][j]==-1)
                cout<<setw(10)<<"--";
            else
                cout<<setw(10)<<nfa_table[i][j];
        }
        cout<<endl;
    }

    cout<<endl;
    for(int i=0;i<60;i++)
        cout<<"*";
    cout<<endl;
    print_initial_final();
}

int main(){

    int nfa_table[1000][col];
    initialise(nfa_table);
    int states=0;
    cout<<"Enter a regular expression :-  "<<endl;
    string s;
    cin>>s;

    s=preprocessor(s);


    s=postfix(s);


    states = reg_nfa(s,nfa_table);
    print_nfa_table(nfa_table,states);

 return 0;
}
