#include <iostream>
#include "..\lib_parser\Parser.h"
#include <map>
#include <cmath>
#include <stdexcept>
class Expression {
private:
	List<Lexem> rpn;
	std::map<std::string, double> variables;
	std::string originalExpression;
public:
	Expression() {}
	Expression(const std::string& expr) {
		originalExpression = expr;
		List<Lexem> infix = Parser::parse(expr);
		rpn = Parser::buildRPN(infix);
	}
	void setVariable(const std::string& name, double value) {
		variables[name] = value;
	}
	double getVariable(const std::string& name) const {
		auto it = variables.find(name);
		if (it == variables.end()) {
			throw std::runtime_error("Variable '" + name + "' is not defined");
		}
		return it->second;
	}
	double evaluate() {
		Stack<double> stack;
		for (auto it = rpn.begin(); it != rpn.end(); ++it) {
			const Lexem& lex = *it;
			switch (lex.type) {
				case Constant: {
					stack.push(lex.value);
					break;
				}
				case Variable: {
					auto variable = variables.find(lex.name);
					if (variable == variables.end()) {
						throw std::runtime_error("Undefined variable: " + lex.name);
					}
					stack.push(variable->second);
					break;
				}
				case Operator: {
					if (stack.sizeReal() < 2) {
						throw std::runtime_error("Not enough operands for operator: " + lex.name);
					}

					double b = stack.top();
					stack.pop();
					double a = stack.top(); 
					stack.pop();
					double result;

					if (lex.name == "+") {
						result = a + b;
					}
					else if (lex.name == "-") {
						result = a - b;
					}
					else if (lex.name == "*") {
						result = a * b;
					}
					else if (lex.name == "/") {
						if (b == 0) {
							throw std::runtime_error("Division by zero");
						}
						result = a / b;
					}
					else if (lex.name == "^") {
						result = pow(a, b);
					}
					else {
						throw std::runtime_error("Unknown operator: " + lex.name);
					}

					stack.push(result);
					break;
				}
				case UnOperator:{
					double a = stack.top();
					stack.pop();

					if (lex.name == "u-") {  // унарный минус
						stack.push(-a);
					}
					else {
						throw std::runtime_error("Unknown unary operator: " + lex.name);
					}
					break;
				}
				case Function: {
					if (stack.isEmpty()) {
						throw std::runtime_error("Not enough operands for function: " + lex.name);
					}

					double a = stack.top(); stack.pop();

					if (lex.function == nullptr) {
						throw std::runtime_error("Function pointer is null for: " + lex.name);
					}

					try {
						double result = lex.function(a);
						stack.push(result);
					}
					catch (const std::exception& e) {
						throw std::runtime_error("Error in function " + lex.name + ": " + e.what());
					}
					break;
				}

				default: {
					throw std::runtime_error("Unexpected lexem type in RPN");
				}
			}
			}
		if (stack.sizeReal() != 1) {
			throw std::runtime_error("Invalid expression format");
		}

		return stack.top();
		}
	std::string getExpression() const {
		return originalExpression;
	}

	// Получение списка переменных
	const std::map<std::string, double>& getVariables() const {
		return variables;
	}

	bool allVariablesDefined() const {
		for (auto it = rpn.begin(); it != rpn.end(); ++it) {
			if (it->type == Variable) {
				if (variables.find(it->name) == variables.end()) {
					return false;
				}
			}
		}
		return true;
	}
};