#include <algorithm>
#include <cassert>
#include <cmath>
#include <complex>
#include <iostream>
#include <memory>
#include <numeric>
#include <vector>

struct A {
    A(std::string s) { str_ = std::move(s); }

    void print() { std::cout << str_ << std::endl; }

    std::string str_;
};

template <typename T, typename Allocator = std::allocator<T>>
class ObjectPool {
   public:
    ObjectPool() = default;
    ~ObjectPool() {
        assert(freeObjects_.size() == kInitChunkSize * (std::pow(2, pool_.size()) - 1));

        size_t chunkSize{kInitChunkSize};
        for (auto* chunk : pool_) {
            allocator_.deallocate(chunk, chunkSize);
            chunkSize *= 2;
        }
        pool_.clear();
    }

    template <typename... Args>
    std::shared_ptr<T> acquireObject(Args... args) {
        if (freeObjects_.empty()) {
            addChunk();
        }

        T* object{freeObjects_.back()};

        new (object) T{std::forward<Args>(args)...};

        freeObjects_.pop_back();

        return std::shared_ptr<T>(object, [this](T* object) {
            std::_Destroy(object);
            freeObjects_.push_back(object);
        });
    }

   private:
    std::vector<T*> pool_;

    std::vector<T*> freeObjects_;

    static const size_t kInitChunkSize{5};

    size_t newChunkSize{kInitChunkSize};

    void addChunk() {
        std::cout << "add Chunk \n";

        auto* firstNewObject{allocator_.allocate(newChunkSize)};
        pool_.push_back(firstNewObject);

        auto oldFreeObjectSize{freeObjects_.size()};
        freeObjects_.resize(oldFreeObjectSize + newChunkSize);
        std::iota(std::begin(freeObjects_) + oldFreeObjectSize, std::end(freeObjects_), firstNewObject);

        newChunkSize *= 2;
    }

    Allocator allocator_;
};

using APool = ObjectPool<A>;

int main() {
    APool pool;
    for (int i = 0; i < 20; i++) {
        auto x = pool.acquireObject(std::string("hello"));
        x->print();
    }
    return 0;
}