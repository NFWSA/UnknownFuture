#ifndef __SN_VARIANT_H__
#define __SN_VARIANT_H__

#include <string>
#include <unordered_map>
#include <vector>
#include <initializer_list>

namespace SurgeNight{

enum VariantType {
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

class ObjectVariant;
class ListVariant;

class Variant
{
public:
    Variant();
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

    const bool asBool() const;
    const int asInt() const;
    const unsigned int asUInt() const;
    const float asFloat() const;
    const double asDouble() const;
    const char asChar() const;
    const unsigned char asUChar() const;
    const std::string asString() const;
    const ListVariant asList() const;
    const ObjectVariant asObject() const;

    const bool isBool() const;
    const bool isInt() const;
    const bool isUInt() const;
    const bool isFloat() const;
    const bool isDouble() const;
    const bool isChar() const;
    const bool isUChar() const;
    const bool isString() const;
    const bool isList() const;
    const bool isObject() const;

private:
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
    VariantType m_type;
};

class ObjectVariant
{
public:
    ObjectVariant() = default;
    ~ObjectVariant() = default;
    ObjectVariant(const ObjectVariant &obj);
    ObjectVariant(const ObjectVariant &&obj);
    ObjectVariant& operator=(const ObjectVariant &obj);
    ObjectVariant& operator=(const ObjectVariant &&obj);

private:
    std::unordered_map<std::string, Variant> m_data;
};

class ListVariant
{
public:
    ListVariant() = default;
    ~ListVariant() = default;
    ListVariant(const ListVariant &list);
    ListVariant(const ListVariant &&list);
    ListVariant& operator=(const ListVariant &list);
    ListVariant& operator=(const ListVariant &&list);
    ListVariant(std::initializer_list<Variant> list);

private:
    std::vector<Variant> m_data;
};

}

#endif //__SN_VARIANT_H__
