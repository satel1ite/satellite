#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <cstdint>
#include <initializer_list>

class IPV4Address {
public:
    IPV4Address() : bytes_{0,0,0,0} {}
    IPV4Address(std::initializer_list<unsigned char> l) : bytes_{0,0,0,0} {
        size_t i = 0;
        for (auto v : l) {
            if (i >= 4) break;
            bytes_[i++] = v;
        }
    }
    explicit IPV4Address(uint32_t value) {
        bytes_[0] = static_cast<unsigned char>((value >> 24) & 0xFF);
        bytes_[1] = static_cast<unsigned char>((value >> 16) & 0xFF);
        bytes_[2] = static_cast<unsigned char>((value >> 8) & 0xFF);
        bytes_[3] = static_cast<unsigned char>(value & 0xFF);
    }
    uint32_t ToUint() const {
        return (static_cast<uint32_t>(bytes_[0]) << 24) |
               (static_cast<uint32_t>(bytes_[1]) << 16) |
               (static_cast<uint32_t>(bytes_[2]) << 8) |
               static_cast<uint32_t>(bytes_[3]);
    }
    const std::array<unsigned char,4>& Bytes() const { return bytes_; }
private:
    std::array<unsigned char,4> bytes_;
};

std::ostream& operator<<(std::ostream& out, const IPV4Address& a) {
    auto b = a.Bytes();
    out << static_cast<int>(b[0]) << '.' << static_cast<int>(b[1]) << '.'
        << static_cast<int>(b[2]) << '.' << static_cast<int>(b[3]);
    return out;
}

std::istream& operator>>(std::istream& in, IPV4Address& a) {
    std::string token;
    if (!(in >> token)) return in;
    for (char c : token) {
        if (!(std::isdigit(static_cast<unsigned char>(c)) || c == '.')) {
            in.setstate(std::ios::failbit);
            return in;
        }
    }
    std::vector<std::string> parts;
    size_t start = 0;
    while (true) {
        size_t pos = token.find('.', start);
        if (pos == std::string::npos) {
            parts.push_back(token.substr(start));
            break;
        } else {
            parts.push_back(token.substr(start, pos - start));
            start = pos + 1;
        }
    }
    if (parts.size() != 4) {
        in.setstate(std::ios::failbit);
        return in;
    }
    std::array<unsigned char,4> tmp = {0,0,0,0};
    for (size_t i = 0; i < 4; ++i) {
        const std::string& s = parts[i];
        if (s.empty()) {
            tmp[i] = 0;
            continue;
        }
        int v = 0;
        for (char c : s) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                in.setstate(std::ios::failbit);
                return in;
            }
            v = v * 10 + (c - '0');
            if (v > 255) {
                in.setstate(std::ios::failbit);
                return in;
            }
        }
        tmp[i] = static_cast<unsigned char>(v);
    }
    a = IPV4Address{tmp[0], tmp[1], tmp[2], tmp[3]};
    return in;
}

std::vector<IPV4Address> Range(const IPV4Address& a, const IPV4Address& b) {
    uint32_t va = a.ToUint();
    uint32_t vb = b.ToUint();
    std::vector<IPV4Address> res;
    if (va > vb) return res;
    uint64_t start = va;
    uint64_t end = vb;
    res.reserve(static_cast<size_t>(end - start + 1));
    for (uint64_t v = start; v <= end; ++v) {
        res.emplace_back(static_cast<uint32_t>(v));
    }
    return res;
}
