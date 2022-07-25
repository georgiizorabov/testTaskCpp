#include <iostream>
#include <vector>
#include <unordered_map>

template<class Key, class Value>
class dictionary {
public:
    virtual ~dictionary() = default;

    virtual const Value &get(const Key &key) const = 0;

    virtual void set(const Key &key, const Value &value) = 0;

    virtual bool is_set(const Key &key) const = 0;
};

template<class Key>
class not_found_exception : public std::exception {
public:
    virtual const Key &get_key() const noexcept = 0;
};

template<class Key>
class not_found_exception_impl : not_found_exception<Key> {
public:
    const Key &get_key() const noexcept override {
        std::cout << "not found\n";
    }
};

template<class Key, class Value>
class dictionary_impl : dictionary<Key, Value> {
    std::unordered_map<Key, Value> map;

    const Value &get(const Key &key) const override {
        if (map.contains(key)) {
            return map.at(key);
        }
        throw not_found_exception_impl<Key>();
    }

    virtual void set(const Key &key, const Value &value) override {
        map[key] = value;
    }

    virtual bool is_set(const Key &key) const override {
        return map.contains(key);
    };
};
