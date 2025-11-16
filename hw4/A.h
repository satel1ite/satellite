#include <string>
#include <stack>
#include <memory>
#include <sstream>
#include <cmath>
#include <algorithm>


using namespace std;

class Node {
public:
    virtual double Eval() const = 0;
    virtual ~Node() = default;
};

class NumberNode : public Node {
public:
    double val;
    NumberNode(double v) : val(v) {}
    double Eval() const override { return val; }
};

class UnaryNode : public Node {
public:
    char op;
    shared_ptr<Node> child;
    UnaryNode(char o, shared_ptr<Node> c) : op(o), child(c) {}
    double Eval() const override {
        double x = child->Eval();
        if (op == 's') return sin(x);
        if (op == 'c') return cos(x);
        if (op == 't') return tan(x);
        if (op == 'g') return 1.0 / tan(x);
        if (op == 'e') return exp(x);
        if (op == 'l') return log10(x);
        if (op == 'q') return sqrt(x);
        return -1;
    }
};

class BinaryNode : public Node {
public:
    char op;
    shared_ptr<Node> left, right;
    BinaryNode(char o, shared_ptr<Node> l, shared_ptr<Node> r) : op(o), left(l), right(r) {}
    double Eval() const override {
        double a = left->Eval();
        double b = right->Eval();
        if (op == '+') return a + b;
        if (op == '-') return a - b;
        if (op == '*') return a * b;
        if (op == '/') return a / b;
        return -1;
    }
};

class PowNode : public Node {
public:
    shared_ptr<Node> left, right;
    PowNode(shared_ptr<Node> l, shared_ptr<Node> r) : left(l), right(r) {}
    double Eval() const override {
        return pow(left->Eval(), right->Eval());
    }
};

class Atan2Node : public Node {
public:
    shared_ptr<Node> y, x;
    Atan2Node(shared_ptr<Node> l, shared_ptr<Node> r) : y(l), x(r) {}
    double Eval() const override {
        return atan2(y->Eval(), x->Eval());
    }
};

class MedianNode : public Node {
public:
    shared_ptr<Node> a, b, c;
    MedianNode(shared_ptr<Node> x, shared_ptr<Node> y, shared_ptr<Node> z) : a(x), b(y), c(z) {}
    double Eval() const override {
        double arr[3] = {a->Eval(), b->Eval(), c->Eval()};
        sort(arr, arr + 3);
        return arr[1];
    }
};

double EvaluateExpression(const string& expr) {
    istringstream iss(expr);
    string token;
    stack<shared_ptr<Node>> st;

    while (iss >> token) {
        try {
            double val = stod(token);
            st.push(make_shared<NumberNode>(val));
            continue;
        } catch (...) {}

        if (token == "sin") { auto x = st.top(); st.pop(); st.push(make_shared<UnaryNode>('s', x)); continue; }
        if (token == "cos") { auto x = st.top(); st.pop(); st.push(make_shared<UnaryNode>('c', x)); continue; }
        if (token == "tg")  { auto x = st.top(); st.pop(); st.push(make_shared<UnaryNode>('t', x)); continue; }
        if (token == "ctg") { auto x = st.top(); st.pop(); st.push(make_shared<UnaryNode>('g', x)); continue; }
        if (token == "exp") { auto x = st.top(); st.pop(); st.push(make_shared<UnaryNode>('e', x)); continue; }
        if (token == "log10"){ auto x = st.top(); st.pop(); st.push(make_shared<UnaryNode>('l', x)); continue; }
        if (token == "sqrt"){ auto x = st.top(); st.pop(); st.push(make_shared<UnaryNode>('q', x)); continue; }

        if (token == "median") {
            auto c = st.top(); st.pop();
            auto b = st.top(); st.pop();
            auto a = st.top(); st.pop();
            st.push(make_shared<MedianNode>(a, b, c));
            continue;
        }

        if (token == "+") { auto r = st.top(); st.pop(); auto l = st.top(); st.pop(); st.push(make_shared<BinaryNode>('+', l, r)); continue; }
        if (token == "-") { auto r = st.top(); st.pop(); auto l = st.top(); st.pop(); st.push(make_shared<BinaryNode>('-', l, r)); continue; }
        if (token == "*") { auto r = st.top(); st.pop(); auto l = st.top(); st.pop(); st.push(make_shared<BinaryNode>('*', l, r)); continue; }
        if (token == "/") { auto r = st.top(); st.pop(); auto l = st.top(); st.pop(); st.push(make_shared<BinaryNode>('/', l, r)); continue; }
        if (token == "pow") { auto r = st.top(); st.pop(); auto l = st.top(); st.pop(); st.push(make_shared<PowNode>(l, r)); continue; }
        if (token == "atan2"){ auto r = st.top(); st.pop(); auto l = st.top(); st.pop(); st.push(make_shared<Atan2Node>(l, r)); continue; }

    }

    return st.top()->Eval();
}
