#include <iostream>
#include <sstream>

class Rational {
public:
    Rational() : num_(0), den_(1) {}
    Rational(int n, int d = 1) { init(n, d); }

    explicit operator double() const { return static_cast<double>(num_) / den_; }

    Rational& operator+=(const Rational& rhs) {
        long long n = static_cast<long long>(num_) * rhs.den_ + static_cast<long long>(rhs.num_) * den_;
        long long d = static_cast<long long>(den_) * rhs.den_;
        store(n, d);
        return *this;
    }

    Rational& operator-=(const Rational& rhs) {
        long long n = static_cast<long long>(num_) * rhs.den_ - static_cast<long long>(rhs.num_) * den_;
        long long d = static_cast<long long>(den_) * rhs.den_;
        store(n, d);
        return *this;
    }

    Rational& operator*=(const Rational& rhs) {
        long long n = static_cast<long long>(num_) * rhs.num_;
        long long d = static_cast<long long>(den_) * rhs.den_;
        store(n, d);
        return *this;
    }

    Rational& operator/=(const Rational& rhs) {
        if (rhs.num_ == 0) return *this;
        long long n = static_cast<long long>(num_) * rhs.den_;
        long long d = static_cast<long long>(den_) * rhs.num_;
        if (d < 0) { n = -n; d = -d; }
        store(n, d);
        return *this;
    }

    Rational operator++() {
        *this += Rational(1);
        return *this;
    }
    Rational operator++(int) {
        Rational old = *this;
        *this += Rational(1);
        return old;
    }
    Rational operator--() {
        *this -= Rational(1);
        return *this;
    }
    Rational operator--(int) {
        Rational old = *this;
        *this -= Rational(1);
        return old;
    }

    int Numerator() const { return num_; }
    int Denominator() const { return den_; }

private:
    int num_;
    int den_;

    static long long gcd_ll(long long a, long long b) {
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (b) {
            long long t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    void store(long long n, long long d) {
        if (d == 0) { num_ = 0; den_ = 1; return; }
        if (d < 0) { n = -n; d = -d; }
        long long g = gcd_ll(n, d);
        if (g != 0) { n /= g; d /= g; }
        num_ = static_cast<int>(n);
        den_ = static_cast<int>(d);
    }

    void init(int n, int d) {
        if (d == 0) { num_ = 0; den_ = 1; return; }
        store(n, d);
    }
};

Rational operator+(Rational lhs) { return lhs; }
Rational operator+(Rational lhs, const Rational& rhs) { lhs += rhs; return lhs; }
Rational operator-(Rational lhs, const Rational& rhs) { lhs -= rhs; return lhs; }
Rational operator*(Rational lhs, const Rational& rhs) { lhs *= rhs; return lhs; }
Rational operator/(Rational lhs, const Rational& rhs) { lhs /= rhs; return lhs; }
Rational operator-(Rational lhs) { return Rational(-lhs.Numerator(), lhs.Denominator()); }

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator();
}
bool operator!=(const Rational& lhs, const Rational& rhs) { return !(lhs == rhs); }
bool operator<(const Rational& lhs, const Rational& rhs) {
    return static_cast<long long>(lhs.Numerator()) * rhs.Denominator() <
           static_cast<long long>(rhs.Numerator()) * lhs.Denominator();
}
bool operator<=(const Rational& lhs, const Rational& rhs) { return (lhs < rhs) || (lhs == rhs); }
bool operator>=(const Rational& lhs, const Rational& rhs) { return !(lhs < rhs); }
bool operator>(const Rational& lhs, const Rational& rhs) { return !(lhs <= rhs); }

std::ostream& operator<<(std::ostream& out, const Rational& r) {
    out << r.Numerator() << '/' << r.Denominator();
    return out;
}

std::istream& operator>>(std::istream& in, Rational& r) {
    std::ios::fmtflags f = in.flags();
    in.unsetf(std::ios::skipws);
    int n;
    char sep;
    int d;
    if (!(in >> n) || !(in >> sep) || sep != '/' || !(in >> d) || d == 0) {
        in.setstate(std::ios::failbit);
        in.flags(f);
        return in;
    }
    r = Rational(n, d);
    in.flags(f);
    return in;
}
