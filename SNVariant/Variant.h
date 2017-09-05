#ifndef SN_VARIANT_H
#define SN_VARIANT_H

#include <string>
#include <unordered_map>
#include <vector>
#include <initializer_list>

namespace SurgeNight{

namespace impl
{
    enum VariantType {
            VAR_TYPE_NULL,
            VAR_TYPE_BOOL,
            VAR_TYPE_INT,
            VAR_TYPE_UINT,
            VAR_TYPE_FLOAT,
            VAR_TYPE_DOUBLE,
            VAR_TYPE_CHAR,
            VAR_TYPE_UCHAR,
            VAR_TYPE_STR,
            VAR_TYPE_OBJ,
            VAR_TYPE_LIST
    };
}

class ObjectVariant;
class ListVariant;

class Variant
{
public:
    Variant() : m_type(impl::VAR_TYPE_NULL) {}
    ~Variant();
    Variant(const Variant &var);
    Variant(const Variant &&var);
    Variant(const bool b);
    Variant(const int i);
    Variant(const unsigned int ui);
    Variant(const float f);
    Variant(const double d);
    Variant(const char ch);
    Variant(const unsigned char uch);
    Variant(const std::string &str);
    Variant(const std::string &&str);
    Variant(const ListVariant &list);
    Variant(const ListVariant &&list);
    Variant(const ObjectVariant &obj);
    Variant(const ObjectVariant &&obj);

    Variant& operator=(const Variant &var);
    Variant& operator=(const Variant &&var);
    Variant& operator=(const bool b);
    Variant& operator=(const int i);
    Variant& operator=(const unsigned int ui);
    Variant& operator=(const float f);
    Variant& operator=(const double d);
    Variant& operator=(const char ch);
    Variant& operator=(const unsigned char uch);
    Variant& operator=(const std::string &str);
    Variant& operator=(const std::string &&str);
    Variant& operator=(const ListVariant &list);
    Variant& operator=(const ListVariant &&list);
    Variant& operator=(const ObjectVariant &obj);
    Variant& operator=(const ObjectVariant &&obj);

    const bool asBool(const bool defaultValue = false) const;
    const int asInt(const int defaultValue = 0) const;
    const unsigned int asUInt(const unsigned int defaultValue = 0) const;
    const float asFloat(const float defaultValue = 0.0f) const;
    const double asDouble(const double defaultValue = 0.0) const;
    const char asChar(const char defaultValue = '\0') const;
    const unsigned char asUChar(const unsigned char defaultValue = '\0') const;
    const std::string asString(const std::string &defaultValue = "") const;
    ListVariant& asList();
    const ListVariant asList() const;
    ObjectVariant& asObject();
    const ObjectVariant asObject() const;

    const bool isNull() const { return impl::VAR_TYPE_NULL == m_type; }
    const bool isBool() const { return impl::VAR_TYPE_BOOL == m_type; }
    const bool isInt() const { return impl::VAR_TYPE_INT == m_type; }
    const bool isUInt() const { return impl::VAR_TYPE_UINT == m_type; }
    const bool isFloat() const { return impl::VAR_TYPE_FLOAT == m_type; }
    const bool isDouble() const { return impl::VAR_TYPE_DOUBLE == m_type; }
    const bool isChar() const { return impl::VAR_TYPE_CHAR == m_type; }
    const bool isUChar() const { return impl::VAR_TYPE_UCHAR == m_type; }
    const bool isString() const { return impl::VAR_TYPE_STR == m_type; }
    const bool isList() const { return impl::VAR_TYPE_LIST == m_type; }
    const bool isObject() const { return impl::VAR_TYPE_OBJ== m_type; }

private:
    friend class ObjectVariant;
    friend class ListVariant;
    void clear();

    union VariantData {
        bool b;
        int i;
        unsigned int ui;
        float f;
        double d;
        char ch;
        unsigned char uch;
        std::string str;
        ObjectVariant *obj;
        ListVariant *list;
        VariantData()
        {
        };
        ~VariantData()
        {
        }
    };

    VariantData m_data;
    impl::VariantType m_type;
};

namespace impl
{
    typedef std::unordered_map<std::string, Variant> ObjVarContainer;
    typedef std::vector<Variant> ListVarContainer;
}

class ObjectVariant : public impl::ObjVarContainer
{
public:
    using size_type = impl::ObjVarContainer::size_type;
    using iterator = impl::ObjVarContainer::iterator;
    using const_iterator = impl::ObjVarContainer::const_iterator;

    ObjectVariant() = default;
    ~ObjectVariant() = default;
    ObjectVariant(const ObjectVariant &obj);
    ObjectVariant(const ObjectVariant &&obj);
    ObjectVariant& operator=(const ObjectVariant &obj);
    ObjectVariant& operator=(const ObjectVariant &&obj);
    ObjectVariant(std::initializer_list<std::pair<const std::string, Variant>> list);

    const bool has(const std::string &key) const { return find(key) != end(); }

    void add(const std::string &key, const Variant &value);
    const iterator erase(const std::string &key);
};

class ListVariant : public impl::ListVarContainer
{
public:
    using size_type = impl::ListVarContainer::size_type;
    using iterator = impl::ListVarContainer::iterator;
    using const_iterator = impl::ListVarContainer::const_iterator;
    using reverse_iterator = impl::ListVarContainer::reverse_iterator;
    using const_reverse_iterator = impl::ListVarContainer::const_reverse_iterator;

    ListVariant() = default;
    ~ListVariant() = default;
    ListVariant(const ListVariant &list);
    ListVariant(const ListVariant &&list);
    ListVariant& operator=(const ListVariant &list);
    ListVariant& operator=(const ListVariant &&list);
    ListVariant(std::initializer_list<Variant> list);

    void add(const Variant &value);
    const iterator erase(const size_type index);
};

namespace impl
{
    static ObjectVariant nullObj;
    static ListVariant nullList;
}

}

#endif //SN_VARIANT_H
