#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cmath>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

struct Variable {   
    // с помощью этой структуры задаётся переменная
    string name;
    string value;
};

int Rang(char Ch) {
    if (Ch == '^') return 3;
    if (Ch == '*' || Ch == '/') return 2;
    if (Ch == '+' || Ch == '-') return 1;
    else return 0;
}

bool Math(Stack* Stack_n, Stack* Stack_o)
{
    double num1, num2, result;
    num1 = head(Stack_n); 
    pop(Stack_n);
    // cout << num1<<endl;
    double operation = head(Stack_o);
    pop(Stack_o);
    switch ((char)operation) {
    case '+':
        num2 = head(Stack_n);
        pop(Stack_n);
        //  cout << num2<< endl;
        result = num1 + num2;
        push(Stack_n, result);
        // result = pop(Stack_o);
        return 1;
    case ('-'):
        num2 = head(Stack_n);
        pop(Stack_n);
        result = num2 - num1;
        push(Stack_n, result);
        // result = pop(Stack_o);
        return 1;
    case ('*'):
        num2 = head(Stack_n);
        pop(Stack_n);
        //  cout << num2;
        result = num1 * num2;
        push(Stack_n, result);
        //  result = pop(Stack_o);
          //cout << head(Stack_o);
        return 1;
    case ('/'):
        if (num1 == 0)
        {
            cout << "You can't divide by zero";
            return 0;
        }
        num2 = head(Stack_n);
        pop(Stack_n);
        result = num2 / num1;
        push(Stack_n, result);
        //result = pop(Stack_o);
        break;
    case ('^'):
        num2 = head(Stack_n); 
        pop(Stack_n);
        result = pow(num2, num1);
        push(Stack_n, result);
        //result = pop(Stack_o);
        break;
    default:
        cout << "INCORRECT RECORD";
        return 0;
    }


}

void Parsing(string& line, Stack* Stack_n, Stack* Stack_o)
{
    int i = 0;
    string part = "";
    int flag1 = 0; // добавляем числа или нет
    int sign = 0; // знак числа
    int flag2 = 0; // вычисление подвыражения (ограниченного операцией или скобками)
    double num;
    while (i < line.size())
    {
        flag1 = 0;
        flag2 = 0;
        if (line[i] >= '0' && line[i] <= '9' || line[i] == '.')
        {
            part += line[i];
            //  cout << part;
        }
        if (line[i] == '-' && (i == 0 || line[i - 1] == '('))
        {
            sign = 1;
        }
        else if (line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/' || line[i] == '^')
        {

            if (Stack_o->top == 0 || (Stack_o->top != 0 && (Rang(line[i]) > Rang(head(Stack_o)) || head(Stack_o) == '('))) {
                push(Stack_o, line[i]);
                //cout << 3;
            }
            else if (Stack_o->top != 0 && Rang(line[i]) <= Rang(head(Stack_o))) {
                //cout << Rang(line[i]);
                //cout << "   " << Rang(head(Stack_o));
                flag2 = 1;
            }
            flag1 = 1;

        }
        else if (line[i] == '(')
        {
            push(Stack_o, line[i]);
        }
        else if (line[i] == ')')
        {
            flag1 = 1;
            flag2 = 1;
        }
        if (line[i] == ' ' || i == (line.size() - 1))
        {
            flag1 = 1;
        }
        if (flag1 && part != "")
        {
            num = stod(part);
            if (sign)
            {
                num = -num;
                sign = 0;
            }
            //cout << num << endl;
            push(Stack_n, num);
            part = "";
        }
        if (flag2)
        {
            while (Stack_o->top != 0 && head(Stack_o) != '(')
            {
                if (Math(Stack_n, Stack_o) == false)
                    return;
            }
            if (line[i] != ')')
            {
                push(Stack_o, line[i]);
            }
            else
                if (head(Stack_o) == '(')
                {
                    pop(Stack_o);
                }
            //cout << 1;
        }
        i++;
    }

}

double Calculate(string line) {
    Stack* Stack_n = createStack();
    Stack* Stack_o = createStack();
    Parsing(line, Stack_n, Stack_o);
    while (Stack_o->top != 0) {
        if (Math(Stack_n, Stack_o) == false)
            return 1;
    }
    cut(Stack_n); cut(Stack_o);
    double result = head(Stack_n);
    deleteStack(&Stack_n); deleteStack(&Stack_o);
    return result;
}

void VarParsing(string& line) {
    Variable* Variables = new Variable[100];    // массив переменных
    int i = 0; // индекс строки 
    int j = 0; // индекс массива
    string part = "";

    // Запоминаем имена
    while (i < line.size()) {
        bool letter = line[i] >= 'a' && line[i] <= 'z' || line[i] >= 'A' && line[i] <= 'Z';
        if (letter) {
            part += line[i];
        }
        if (((!letter) || (i == line.size() - 1)) && part != "") {
            //cout << part << " ";
            Variables[j].name = part;
            part = "";
            j++;
        }
        i++;
    }
    //cout << endl;
    int n = j; // кол-во переменных 
    for (int t = 0; t < n; t++) {
        cout << Variables[t].name << " = ";
        string expression;
        cin >> expression;
        Variables[t].value =  to_string(Calculate(expression));
    }

    //cout << endl;
    // Вставляем в строку значения переменных
    i = 0; 
    j = 0;
    while (i < line.size()) {
        bool letter = line[i] >= 'a' && line[i] <= 'z' || line[i] >= 'A' && line[i] <= 'Z';
        if (letter) {
            line.erase(i, Variables[j].name.size());    // удаляет с позиции i "Variables[j].name.size()" элементов
            if (Variables[j].value[0] == '-')
                Variables[j].value = '(' + Variables[j].value + ')';
            //cout << Variables[j].value << endl;
            line.insert(i, Variables[j].value);     // вставляет на позицию i строку "Variables[j].value" 
            j++;
        }
        i++;
    }
    //cout << line << endl;
    delete[] Variables;
}

int main() {
    string line;
    getline(cin, line);
    VarParsing(line);
    cout << Calculate(line) << endl;
    return 0;
}
