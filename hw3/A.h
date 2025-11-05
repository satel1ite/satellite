#include <vector>
#include <string>
#include <cmath>


class Shape {
public:
    virtual double Area() const = 0;
    virtual double Perimeter() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    double r;
    Circle(double r_) : r(r_) {}
    double Area() const override {
        return std::acos(-1.0) * r * r;
    }
    double Perimeter() const override {
        return 2.0 * std::acos(-1.0) * r;
    }
};

class Rectangle : public Shape {
public:
    double w, h;
    Rectangle(double w_, double h_) : w(w_), h(h_) {}
    double Area() const override {
        return w * h;
    }
    double Perimeter() const override {
        return 2.0 * (w + h);
    }
};

class Square : public Shape {
public:
    double s;
    Square(double s_) : s(s_) {}
    double Area() const override {
        return s * s;
    }
    double Perimeter() const override {
        return 4.0 * s;
    }
};

class Triangle : public Shape {
public:
    double a, b, c;
    Triangle(double a_, double b_, double c_) : a(a_), b(b_), c(c_) {}
    double Area() const override {
        double s = (a + b + c) / 2.0;
        double val = s * (s - a) * (s - b) * (s - c);
        if (val <= 0.0) return 0.0;
        return std::sqrt(val);
    }
    double Perimeter() const override {
        return a + b + c;
    }
};

std::vector<Shape*> CreateShapes(const std::vector<std::pair<std::string, std::vector<double>>>& data) {
    std::vector<Shape*> out;
    out.reserve(data.size());
    for (const auto& item : data) {
        const std::string& name = item.first;
        const std::vector<double>& params = item.second;

        if (name == "Circle") {
            out.push_back(new Circle(params[0]));
        }
        else if (name == "Rectangle") {
            out.push_back(new Rectangle(params[0], params[1]));
        }
        else if (name == "Square") {
            out.push_back(new Square(params[0]));
        }
        else if (name == "Triangle") {
            out.push_back(new Triangle(params[0], params[1], params[2]));
        }
    }
    return out;
}

double CalcArea(const std::vector<Shape*>& shapes) {
    double sum = 0.0;
    for (const Shape* s : shapes) {
        if (!s) continue;
        sum += s->Area();
    }
    return sum;
}

double CalcPerimeter(const std::vector<Shape*>& shapes) {
    double sum = 0.0;
    for (const Shape* s : shapes) {
        if (!s) continue;
        sum += s->Perimeter();
    }
    return sum;
}

void DestructShapes(std::vector<Shape*>&& shapes) {
    for (Shape* s : shapes) {
        delete s;
    }
    shapes.clear();
}
