#pragma once

#ifdef _KERNEL_MODE
namespace std
    {
        // STRUCT TEMPLATE remove_reference
        template <class _Ty>
        struct remove_reference {
            using type = _Ty;
        };

        template <class _Ty>
        struct remove_reference<_Ty&> {
            using type = _Ty;
        };

        template <class _Ty>
        struct remove_reference<_Ty&&> {
            using type = _Ty;
        };

        template <class _Ty>
        using remove_reference_t = typename remove_reference<_Ty>::type;

        // STRUCT TEMPLATE remove_const
        template <class _Ty>
        struct remove_const {
            using type = _Ty;
        };

        template <class _Ty>
        struct remove_const<const _Ty> {
            using type = _Ty;
        };

        template <class _Ty>
        using remove_const_t = typename remove_const<_Ty>::type;
    }
#else
#include <type_traits>
#endif

namespace skc
{
    template<class _Ty>
    using clean_type = typename std::remove_const_t<std::remove_reference_t<_Ty>>;

    template <size_t _size, char _key1, char _key2, typename T>
    class skCrypter
    {
    public:
        constexpr skCrypter(const T* data)
        {
            for (size_t i = 0; i < _size; i++)
            {
                _storage[i] = data[i] ^ (_key1 + i % (1 + _key2));
            }
        }

        constexpr const T* decrypt() const
        {
            static T decrypted[_size]{};
            for (size_t i = 0; i < _size; i++)
            {
                decrypted[i] = _storage[i] ^ (_key1 + i % (1 + _key2));
            }
            return decrypted;
        }

        constexpr operator const T*() const { return decrypt(); }

    private:
        T _storage[_size]{};
    };
}

#define skCrypt(str) skCrypt_key(str, __TIME__[4], __TIME__[7])
#define skCrypt_key(str, key1, key2) \
    []() -> const skc::skCrypter<sizeof(str)/sizeof(str[0]), key1, key2, skc::clean_type<decltype(str[0])>>* { \
        static constexpr auto crypted = skc::skCrypter<sizeof(str)/sizeof(str[0]), key1, key2, skc::clean_type<decltype(str[0])>>(str); \
        return &crypted; \
    }()->decrypt()