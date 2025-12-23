#include <iostream>
#include <cmath>
#include "..\lib_list\list.h"
#include "..\lib_lexem\Lexem.h"
#include "..\lib_stack\stack.h"
enum State {
    Start,
    Number,
    Identifier
};
namespace CalculatorMath {
    static double my_sin(double x) {
        return std::sin(x);
    }
    static double my_cos(double x) {
        return std::cos(x);
    }
    static double my_tg(double x) {
        return std::tan(x);
    }
    static double my_ln(double x) {
        if (x <= 0) {
            throw std::runtime_error("ln(x) for x <= 0");
        }
        return std::log(x);
    }
};
namespace Parser {
    List<Lexem> parse(const std::string& s) {
        List<Lexem> expression;
        State state = Start;
        std::string buffer;
        for (size_t i = 0; i <= s.size(); i++) {
            char c = (i < s.size()) ? s[i] : '\0';

            switch (state) {
            case Start:
                if (isspace(c)) {
                    continue;
                }
                else if (isdigit(c)) {
                    buffer += c;
                    state = Number;
                }
                else if (isalpha(c)) {
                    buffer += c;
                    state = Identifier;
                }
                else if (c == '+' || c == '-') {
                    expression.push_back(Lexem(std::string(1, c), Operator, DBL_MAX, 2));
                }
                else if (c == '*' || c == '/') {
                    expression.push_back(Lexem(std::string(1, c), Operator, DBL_MAX, 3));
                }
                else if (c == '^') {
                    expression.push_back(Lexem(std::string(1, c), Operator, DBL_MAX, 4));
                }
                else if (c == '|') {
                    bool isOpening = true;
                    if (isOpening) {
                        expression.push_back(Lexem("|", OpenedAbs));
                        isOpening = false;
                    }
                    else {
                        expression.push_back(Lexem("|", ClosedAbs));
                        isOpening = true;
                    }
                }
                else if (c == '(') {
                    expression.push_back(Lexem("(", OpenBracket));
                }
                else if (c == ')') {
                    expression.push_back(Lexem(")", CloseBracket));
                }
                break;

            case Number:
                if (isdigit(c) || c == '.') {
                    buffer += c;
                }
                else if (isalpha(c)) {
                    double value = std::stod(buffer);
                    expression.push_back(Lexem(buffer, Constant, value));
                    expression.push_back(Lexem("*", Operator, DBL_MAX, 3));
                    buffer.clear();
                    buffer += c;
                    state = Identifier;
                }
                else {
                    expression.push_back(Lexem(buffer, Constant, std::stod(buffer)));
                    buffer.clear();
                    state = Start;
                    --i;
                }
                break;

            case Identifier: {
                if (isalnum(c)) {
                    buffer += c;
                }
                else {
                    if (buffer == "sin") {
                        double (*funcPtr)(double) = CalculatorMath::my_sin;
                        if (funcPtr != nullptr) {
                            expression.push_back(Lexem(buffer, Function, DBL_MAX, 5, funcPtr));
                        }
                    }
                    else if (buffer == "cos") {
                        double (*funcPtr)(double) = CalculatorMath::my_cos;
                        if (funcPtr != nullptr) {
                            expression.push_back(Lexem(buffer, Function, DBL_MAX, 5, funcPtr));
                        }
                    }
                    else {
                        expression.push_back(Lexem(buffer, Variable));
                    }
                        buffer.clear();
                        state = Start;
                        --i;
                  
                }
                break;
            }
            }
        }
        return expression;
    }
    List<Lexem> buildRPN(const List<Lexem>& infix) {
        List<Lexem> output;
        Stack<Lexem> opStack;
        for (auto it = infix.begin(); it != infix.end(); it++) {
            const Lexem& lex = *it;
            if (lex.type == Constant || lex.type == Variable) output.push_back(lex);
            else if (lex.type == OpenBracket || lex.type == Function) opStack.push(lex);
            else if (lex.type == CloseBracket) {
                while (!opStack.isEmpty() && opStack.top().type != OpenBracket) {
                    output.push_back(opStack.top());
                    opStack.pop();
                }
                if (!opStack.isEmpty()) { // (
                    opStack.pop();
                }

                if (!opStack.isEmpty() && opStack.top().type == Function) {
                    output.push_back(opStack.top());
                    opStack.pop();
                }
            }
            else if (lex.type == Operator || lex.type == UnOperator) {
                while (!opStack.isEmpty() 
                    && (opStack.top().type == Operator ||opStack.top().type == UnOperator || opStack.top().type == Function)
                    && opStack.top().priority >= lex.priority) {
                    output.push_back(opStack.top());
                    opStack.pop();
                }
                opStack.push(lex);
            }

        }
        while (!opStack.isEmpty()) {
            output.push_back(opStack.top());
            opStack.pop();
        }

        return output;
    }
};
