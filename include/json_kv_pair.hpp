#ifndef JSON_KV_PAIR_HPP
#define JSON_KV_PAIR_HPP

#include <string>

namespace jsonlang
{

// Forward Declarations
class JsonVar;

struct KeyValue
{
    using JsonKey = std::string;

    JsonKey     key_;
    JsonVar*    var_;

    KeyValue(JsonKey key): key_(std::move(key)), var_(nullptr) {}
    KeyValue& operator=(JsonVar& var)
    {
        var_ = &var;
        return *this;
    }
};

} // namespace jsonlang


#endif // !JSON_KV_PAIR_HPP
