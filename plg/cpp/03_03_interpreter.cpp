#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <cctype>

using namespace std;

// Abstract base class for Expressions
class Expression {
public:
    virtual ~Expression() = default;
    virtual double interpret() const = 0;
};

// Terminal Expression for Numbers
class Number : public Expression {
    double value;

public:
    explicit Number(double value) : value(value) {}

    double interpret() const override {
        return value;
    }
};

// Nonterminal Expression for Addition
class Add : public Expression {
    shared_ptr<Expression> left, right;

public:
    Add(shared_ptr<Expression> left, shared_ptr<Expression> right)
        : left(move(left)), right(move(right)) {}

    double interpret() const override {
        return left->interpret() + right->interpret();
    }
};

// Nonterminal Expression for Subtraction
class Subtract : public Expression {
    shared_ptr<Expression> left, right;

public:
    Subtract(shared_ptr<Expression> left, shared_ptr<Expression> right)
        : left(move(left)), right(move(right)) {}

    double interpret() const override {
        return left->interpret() - right->interpret();
    }
};

// Nonterminal Expression for Multiplication
class Multiply : public Expression {
    shared_ptr<Expression> left, right;

public:
    Multiply(shared_ptr<Expression> left, shared_ptr<Expression> right)
        : left(move(left)), right(move(right)) {}

    double interpret() const override {
        return left->interpret() * right->interpret();
    }
};

// Nonterminal Expression for Division
class Divide : public Expression {
    shared_ptr<Expression> left, right;

public:
    Divide(shared_ptr<Expression> left, shared_ptr<Expression> right)
        : left(move(left)), right(move(right)) {}

    double interpret() const override {
        return left->interpret() / right->interpret();
    }
};

// Parser class to build the expression tree from a string
class Parser {
    vector<string> tokens;
    size_t current_token_index = 0;

    // Helper functions for tokenizing and parsing
    void tokenize(const string& expression) {
        string number;
        for (char ch : expression) {
            if (isdigit(ch) || ch == '.') {
                number += ch;
            } else {
                if (!number.empty()) {
                    tokens.push_back(number);
                    number.clear();
                }
                if (!isspace(ch)) {
                    tokens.push_back(string(1, ch));
                }
            }
        }
        if (!number.empty()) {
            tokens.push_back(number);
        }
    }

    string current_token() const {
        return current_token_index < tokens.size() ? tokens[current_token_index] : "";
    }

    void consume_token() {
        current_token_index++;
    }

    shared_ptr<Expression> parse_expression();
    shared_ptr<Expression> parse_term();
    shared_ptr<Expression> parse_factor();

public:
    explicit Parser(const string& expression) {
        tokenize(expression);
    }

    shared_ptr<Expression> parse() {
        return parse_expression();
    }
};

shared_ptr<Expression> Parser::parse_expression() {
    auto left = parse_term();
    while (current_token() == "+" || current_token() == "-") {
        string op = current_token();
        consume_token();
        auto right = parse_term();
        if (op == "+") {
            left = make_shared<Add>(left, right);
        } else if (op == "-") {
            left = make_shared<Subtract>(left, right);
        }
    }
    return left;
}

shared_ptr<Expression> Parser::parse_term() {
    auto left = parse_factor();
    while (current_token() == "*" || current_token() == "/") {
        string op = current_token();
        consume_token();
        auto right = parse_factor();
        if (op == "*") {
            left = make_shared<Multiply>(left, right);
        } else if (op == "/") {
            left = make_shared<Divide>(left, right);
        }
    }
    return left;
}

shared_ptr<Expression> Parser::parse_factor() {
    string token = current_token();
    if (isdigit(token[0])) {
        consume_token();
        return make_shared<Number>(stod(token));
    } else if (token == "(") {
        consume_token();
        auto expression = parse_expression();
        consume_token();  // Consume ")"
        return expression;
    }
    throw runtime_error("Unexpected token: " + token);
}

int main() {
    string expression = "3 + 5 * ( 10 - 4 ) / 2";
    Parser parser(expression);
    shared_ptr<Expression> syntax_tree = parser.parse();
    double result = syntax_tree->interpret();
    cout << "The result of '" << expression << "' is " << result << endl;
    return 0;
}
