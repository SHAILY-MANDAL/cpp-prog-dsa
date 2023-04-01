#include <iostream>
#include <stack>
#include <string>

using namespace std;

int precedence(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    } else {
        return 0;
    }
}

string infixToPostfix(string infix) {
    stack<char> s;
    string postfix = "";
    int n = infix.length();

    for (int i = 0; i < n; i++) {
        char c = infix[i];

        if (c >= 'A' && c <= 'Z') {
            postfix += c;
        } else if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        } else {
            while (!s.empty() && precedence(s.top()) >= precedence(c)) {
                postfix += s.top();
                s.pop();
            }
            s.push(c);
        }
    }

    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}

int evaluatePostfix(string postfix) {
    stack<int> s;
    int n = postfix.length();

    for (int i = 0; i < n; i++) {
        char c = postfix[i];

        if (c >= '0' && c <= '9') {
            s.push(c - '0');
        } else {
            int operand2 = s.top();
            s.pop();
            int operand1 = s.top();
            s.pop();

            switch (c) {
                case '+':
                    s.push(operand1 + operand2);
                    break;
                case '-':
                    s.push(operand1 - operand2);
                    break;
                case '*':
                    s.push(operand1 * operand2);
                    break;
                case '/':
                    s.push(operand1 / operand2);
                    break;
            }
        }
    }

    return s.top();
}

int main() {
    string infix = "(A*B-(C-D))/(E+F)";
    string postfix = infixToPostfix(infix);
    cout << "Infix expression: " << infix << endl;
    cout << "Postfix expression: " << postfix << endl;
    cout << "Result: " << evaluatePostfix(postfix) << endl;

    return 0;
}
