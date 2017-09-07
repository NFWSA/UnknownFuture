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
            VAR_TYPE_LIST,
            VAR_TYPE_OBJ
    };
}

class ListVariant;
class ObjectVariant;

class Variant
{
public:
    Variant() : m_type(impl::VAR_TYPE_NULL) {}
    ~Variant();
    Variant(const Variant &var);
    Variant(const Variant &&var);
    explicit Variant(const bool b);
    explicit Variant(const int i);
    explicit Variant(const unsigned int ui);
    explicit Variant(const float f);
    explicit Variant(const double d);
    explicit Variant(const char ch);
    explicit Variant(const unsigned char uch);
    explicit Variant(const std::string &str);
    explicit Variant(const std::string &&str);
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

    friend std::ostream& operator<<(std::ostream &out, const Variant &var);

private:
    friend class ListVariant;
    friend class ObjectVariant;
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
        ListVariant *list;
        ObjectVariant *obj;
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
    typedef std::vector<Variant> ListVarContainer;
    typedef std::unordered_map<std::string, Variant> ObjVarContainer;
}

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

std::ostream& operator<<(std::ostream &out, const ListVariant &list);
std::ostream& operator<<(std::ostream &out, const ObjectVariant &obj);

namespace impl
{
    static ListVariant nullList;
    static ObjectVariant nullObj;
}

const Variant toVariant(const std::string &str);

}

#endif //SN_VARIANT_H
