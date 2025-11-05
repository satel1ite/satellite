#include <vector>
#include <cstddef>
#include <ranges>

struct State {
    std::size_t ref_count;
    std::vector<double> data;
    State(): ref_count(1), data() {}
    State(const std::vector<double>& d): ref_count(1), data(d) {}
};

class COWVector {
public:
    COWVector(): state_(new State()) {}
    ~COWVector() {
        if (--state_->ref_count == 0) delete state_;
    }

    COWVector(const COWVector& other): state_(other.state_) {
        ++state_->ref_count;
    }

    COWVector& operator=(const COWVector& other) {
        if (other.state_ == state_) return *this;
        ++other.state_->ref_count;
        if (--state_->ref_count == 0) delete state_;
        state_ = other.state_;
        return *this;
    }

    std::size_t Size() const {
        return state_->data.size();
    }

    void Resize(std::size_t size) {
        if (size == state_->data.size()) return;
        ensure_unique();
        state_->data.resize(size);
    }

    void PushBack(double value) {
        ensure_unique();
        state_->data.push_back(value);
    }

    const double& Get(std::size_t at) const {
        return state_->data[at];
    }

    const double& Back() const {
        return state_->data.back();
    }

    void Set(std::size_t at, double value) {
        ensure_unique();
        state_->data[at] = value;
    }

private:
    State* state_;

    void ensure_unique() {
        if (state_->ref_count == 1) return;
        State* n = new State(state_->data);
        --state_->ref_count;
        state_ = n;
    }
};
