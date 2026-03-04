#include "..\lib_polynom\polynom.h"
#include "..\lib_doubly_linked_list\DoublyLinkedList.h"
Polynom parse(const std::string& s) {

    enum class State {
        Start,
        Coefficient,
        Variable,
        PowerStart,
        Power
    };

    Polynom result;

    State state = State::Start;

    double coef = 1.0;
    int x = 0, y = 0, z = 0;
    int sign = 1;

    std::string buffer;
    char currentVar = 0;

    auto flushTerm = [&]() {
        result.insertSorted(Monom(sign * coef, x, y, z));

        coef = 1.0;
        x = y = z = 0;
        sign = 1;
        };

    for (size_t i = 0; i <= s.size(); ++i) {

        char c = (i < s.size()) ? s[i] : '\0';

        if (c == ' ') continue;

        switch (state) {

        case State::Start:
            if (c == '+') {
                sign = 1;
            }
            else if (c == '-') {
                sign = -1;
            }
            else if (isdigit(c) || c == '.') {
                buffer += c;
                state = State::Coefficient;
            }
            else if (c == 'x' || c == 'y' || c == 'z') {
                currentVar = c;
                state = State::Variable;
            }
            else if (c == '\0') {
                flushTerm();
            }
            else {
                throw std::invalid_argument("Unexpected character");
            }
            break;

        case State::Coefficient:
            if (isdigit(c) || c == '.') {
                buffer += c;
            }
            else {
                coef = std::stod(buffer);
                buffer.clear();
                state = State::Start;
                --i; // вернуть символ на переразбор
            }
            break;

        case State::Variable:
            if (c == '^') {
                state = State::PowerStart;
            }
            else {
                // степень по умолчанию = 1
                if (currentVar == 'x') x = 1;
                if (currentVar == 'y') y = 1;
                if (currentVar == 'z') z = 1;

                state = State::Start;
                --i;
            }
            break;

        case State::PowerStart:
            if (!isdigit(c))
                throw std::invalid_argument("Expected digit after ^");

            buffer += c;
            state = State::Power;
            break;

        case State::Power:
            if (isdigit(c)) {
                buffer += c;
            }
            else {
                int power = std::stoi(buffer);
                buffer.clear();

                if (currentVar == 'x') x = power;
                if (currentVar == 'y') y = power;
                if (currentVar == 'z') z = power;

                state = State::Start;
                --i;
            }
            break;
        }
    }

    return result;
}
            /*char c = (i < s.size()) ? s[i] : '\0';

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
        return expression;*/
    }
//    List<Lexem> buildRPN(const List<Lexem>& infix) {
//        List<Lexem> output;
//        Stack<Lexem> opStack;
//        for (auto it = infix.begin(); it != infix.end(); it++) {
//            const Lexem& lex = *it;
//            if (lex.type == Constant || lex.type == Variable) output.push_back(lex);
//            else if (lex.type == OpenBracket || lex.type == Function) opStack.push(lex);
//            else if (lex.type == CloseBracket) {
//                while (!opStack.isEmpty() && opStack.top().type != OpenBracket) {
//                    output.push_back(opStack.top());
//                    opStack.pop();
//                }
//                if (!opStack.isEmpty()) { // (
//                    opStack.pop();
//                }
//
//                if (!opStack.isEmpty() && opStack.top().type == Function) {
//                    output.push_back(opStack.top());
//                    opStack.pop();
//                }
//            }
//            else if (lex.type == Operator || lex.type == UnOperator) {
//                while (!opStack.isEmpty() 
//                    && (opStack.top().type == Operator ||opStack.top().type == UnOperator || opStack.top().type == Function)
//                    && opStack.top().priority >= lex.priority) {
//                    output.push_back(opStack.top());
//                    opStack.pop();
//                }
//                opStack.push(lex);
//            }
//
//        }
//        while (!opStack.isEmpty()) {
//            output.push_back(opStack.top());
//            opStack.pop();
//        }
//
//        return output;
//    }
//};
