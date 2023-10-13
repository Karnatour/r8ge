#include "Object.h"

namespace r8ge {
    namespace utility {
        void Object::add(const StringKey &key, const Json &value) {
            if(m_map.find(key.get()) != m_map.end())
                return;

            m_map.emplace(key.get(), value);
        }

        Object::Object(const StringKey &key, const Json &value) {
            add(key, value);
        }

        Object::Object(const std::initializer_list<std::pair<StringKey, Json>> &list) {
            for(auto& pair : list)
                add(pair.first, pair.second);
        }


        std::string Object::to_string(bool format, size_t _count_of_indent) const {
            std::string str = "{";
            str += format ? "\n" : "";

            size_t i = 0;
            for(auto&[key, value]: m_map) {
                for(size_t c = 0; c < _count_of_indent*4; c++)
                    str += format ? " " : "";

                str += "\"" + key + "\":" + (format?" ":"") + value.to_string(format, _count_of_indent, false);
                if(i++ < m_map.size()-1)
                    str += ",";
                str+=format?"\n":"";
            }
            for(size_t c = 0; c < (_count_of_indent-1)*4; c++)
                str += format ? " " : "";
            return str + "}";
        }

        Object::Object() {
            m_map = {};
        }

        Json &Object::operator[](const StringKey &key) {
            return m_map[key.get()];
        }
    }
}