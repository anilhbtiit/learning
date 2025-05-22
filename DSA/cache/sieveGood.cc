

//https://github.com/kassane/sieve-cache-cpp/blob/main/include/sieve.hpp


/**
 * This is an implementation of the
 * [SIEVE](https://cachemon.github.io/SIEVE-website) cache eviction algorithm.
 * Authors: Matheus Catarino França
 * Copyright: Copyright © 2024 Matheus C. França
 * License: MIT
 */

#ifndef SIEVE_HPP
#define SIEVE_HPP
#include <atomic>
#include <cassert>
#include <memory>
#include <memory_resource>
#include <unordered_map>

#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <iomanip>


template <typename K, typename V> class SieveCache {
public:
  explicit SieveCache(size_t capacity, std::pmr::memory_resource *resource =
                                           std::pmr::get_default_resource())
      : capacity_(capacity), head_(nullptr), tail_(nullptr), hand_(nullptr),
        length_(0) {
    assert(capacity > 0 && "capacity must be greater than zero.");
    std::pmr::set_default_resource(resource);
  }

  size_t capacity() const { return capacity_; }

  size_t length() const { return length_.load(); }

  bool empty() const { return length_.load() == 0; }

  bool contains(const K &key) const { return cache_.find(key) != cache_.end(); }

  std::shared_ptr<V> get(const K &key) {
    auto it = cache_.find(key);
    if (it == cache_.end()) {
      return nullptr;
    }
    it->second->visited = true;
    return std::make_shared<V>(it->second->value);
  }

  bool insert(const K &key, const V &value) {
    auto it = cache_.find(key);
    if (it != cache_.end()) {
      it->second->value = value;
      it->second->visited = true;
      return false;
    }
    if (length_.load() >= capacity_) {
      evict();
    }
    auto node = std::make_shared<Node>(key, value);
    addNode(node);
    cache_[key] = node;
    length_++;
    return true;
  }

  bool remove(const K &key) {
    auto it = cache_.find(key);
    if (it == cache_.end()) {
      return false;
    }
    auto node = it->second;
    if (node == hand_) {
      hand_ = node->prev.lock();
    }
    removeNode(node);
    cache_.erase(it);
    length_--;
    return true;
  }

  void clear() {
    cache_.clear();
    head_.reset();
    tail_.reset();
    hand_.reset();
    length_ = 0;
  }

  V &operator[](const K &key) {
    auto it = cache_.find(key);
    if (it != cache_.end()) {
      it->second->visited = true;
      return it->second->value;
    }
    if (length_.load() >= capacity_) {
      evict();
    }
    auto node = std::make_shared<Node>(key, V());
    addNode(node);
    cache_[key] = node;
    length_++;
    return node->value;
  }

private:
  struct Node {
    K key;
    V value;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;
    bool visited;

    Node(const K &k, const V &v) : key(k), value(v), visited(false) {}
  };

  void addNode(std::shared_ptr<Node> node) {
    node->next = head_;
    node->prev.reset();
    if (head_) {
      head_->prev = node;
    }
    head_ = node;
    if (!tail_) {
      tail_ = head_;
    }
  }

  void removeNode(std::shared_ptr<Node> node) {
    auto prev = node->prev.lock();
    auto next = node->next;

    if (prev) {
      prev->next = next;
    } else {
      head_ = next;
    }

    if (next) {
      next->prev = prev;
    } else {
      tail_ = prev;
    }

    node->prev.reset();
    node->next.reset();
  }

  void evict() {
    auto node = hand_ ? hand_ : tail_;
    while (node) {
      if (!node->visited) {
        break;
      }
      node->visited = false;
      node = node->prev.lock() ? node->prev.lock() : tail_;
    }

    if (node) {
      hand_ = node->prev.lock();
      cache_.erase(node->key);
      removeNode(node);
      length_--;
    }
  }

  size_t capacity_;
  std::shared_ptr<Node> head_;
  std::shared_ptr<Node> tail_;
  std::shared_ptr<Node> hand_;
  std::atomic<size_t> length_;
  std::pmr::unordered_map<K, std::shared_ptr<Node>> cache_;
};


/*
void TEST_CASE("Testing SieveCache functionality") {
  SieveCache<std::string, std::string> cache(3);

  SUBCASE("Initial state checks") {
    CHECK(cache.capacity() == 3);
    CHECK(cache.empty());
  }

  SUBCASE("Insert and remove operations") {
    CHECK(cache.insert("foo", "foocontent"));
    CHECK(cache.insert("bar", "barcontent"));
    CHECK(cache.remove("bar"));
    CHECK(cache.insert("bar2", "bar2content"));
    CHECK(cache.insert("bar3", "bar3content"));
  }

  SUBCASE("Content verification after operations") {
    cache.insert("foo", "foocontent");
    cache.insert("bar", "barcontent");
    cache.remove("bar");
    cache.insert("bar2", "bar2content");
    cache.insert("bar3", "bar3content");
    CHECK(*cache.get("foo") == "foocontent");
    CHECK(cache.contains("foo"));
    CHECK(cache.get("bar") == nullptr);
    CHECK(*cache.get("bar2") == "bar2content");
    CHECK(*cache.get("bar3") == "bar3content");
    CHECK(cache.length() == 3);
  }

  SUBCASE("Clear cache and check state") {
    cache.insert("foo", "foocontent");
    cache.insert("bar", "barcontent");
    cache.remove("bar");
    cache.insert("bar2", "bar2content");
    cache.insert("bar3", "bar3content");
    cache.clear();
    CHECK(cache.length() == 0);
    CHECK(!cache.contains("foo"));
  }

  SUBCASE("Updating visited flag") {
    cache.insert("key1", "value1");
    cache.insert("key2", "value2");
    cache.insert("key1", "updated");
    cache.insert("key3", "value3");
    CHECK(cache.contains("key1"));
  }
  SUBCASE("Operator[] test") {
    cache["key1"] = "value1";
    CHECK(cache.contains("key1"));
    CHECK(*cache.get("key1") == "value1");

    cache["key1"] = "updated";
    CHECK(*cache.get("key1") == "updated");

    cache["key2"] = "value2";
    cache["key3"] = "value3";
    CHECK(cache.length() == 3);

    // Insert a new key and check for evictions
    cache["key4"] = "value4";
    CHECK(cache.length() == 3);

    // Verify that one of the initial keys was evicted
    bool key1_evicted = !cache.contains("key1");
    bool key2_evicted = !cache.contains("key2");
    bool key3_evicted = !cache.contains("key3");

    // Ensure that exactly one of the keys is evicted (only key2 is evicted)
    int evicted_count = key1_evicted + key2_evicted + key3_evicted;
    CHECK(evicted_count == 1);

    // Individually check each condition to understand which key was evicted
    if (!key1_evicted) {
      CHECK(*cache.get("key1") == "updated");
    }
    if (!key3_evicted) {
      CHECK(*cache.get("key3") == "value3");
    }
    CHECK(*cache.get("key4") == "value4");
  }
}
*/

struct S {
    S() = default;
    explicit S(const std::pmr::vector<unsigned char>& vec, unsigned long value) : a(vec), b(value) {}

    std::pmr::vector<unsigned char> a;
    unsigned long b;
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    // Sequence.
    {
        SieveCache<unsigned long, unsigned long> cache(68);

        for (int i = 1; i < 1000; ++i) {
            const auto n = i % 100;
            cache[n] = n;
        }

        for (int i = 1; i < 1000; ++i) {
            const auto n = i % 100;
            cache.get(n);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> elapsed_seconds = end - start;
    std::cout << "Sequence: " << std::fixed << std::setprecision(3) << elapsed_seconds.count() << "us\n";

    // Composite.
    {
        SieveCache<unsigned long, S> cache(68);
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<unsigned long> dist(0, 99);

        for (int i = 1; i < 1000; ++i) {
            const auto n = dist(rng);
            cache[n] = S(std::pmr::vector<unsigned char>(12), n);
        }

        for (int i = 1; i < 1000; ++i) {
            const auto n = dist(rng);
            cache.get(n);
        }
    }

    end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Composite: " << std::fixed << std::setprecision(3) << elapsed_seconds.count() << "us\n";

    // CompositeNormal.
    {
        constexpr double SIGMA = 50.0 / 3.0;
        SieveCache<unsigned long, S> cache(static_cast<size_t>(SIGMA));
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<unsigned long> dist(0, 99);

        for (int i = 1; i < 1000; ++i) {
            const auto n = dist(rng);
            cache[n] = S(std::pmr::vector<unsigned char>(12), n);
        }

        for (int i = 1; i < 1000; ++i) {
            const auto n = dist(rng);
            cache.get(n);
        }
    }

    end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Composite Normal: " << std::fixed << std::setprecision(3) << elapsed_seconds.count() << "us\n";

    return 0;
}
#endif // SIEVE_HPP
