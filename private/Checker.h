#pragma once
#include <string>
#include <type_traits>
#include <utility>

template <class T>
class StudentChecker {
    using yes = std::true_type;
    using no = std::false_type;
    template <class U>
    struct Derived : U { friend class StudentChecker; };
    template <typename U, typename FnPtr, FnPtr> struct SFINAE {
        using type = void;
    };
    template <class C> static typename SFINAE<C, const std::string&(C::*)() const, &C::FirstName>::type HasFirstName(std::nullptr_t) {}
    template <class C> static no HasFirstName(void*) {}
    template <class C> static typename SFINAE<C, const std::string&(C::*)() const, &C::LastName>::type HasLastName(std::nullptr_t) {}
    template <class C> static no HasLastName(void*) {}
    template <class C> static typename SFINAE<C, const std::string&(C::*)() const &, &C::FirstName>::type HasFirstNameLV(std::nullptr_t) {}
    template <class C> static no HasFirstNameLV(void*) {}
    template <class C> static typename SFINAE<C, const std::string&(C::*)() const &, &C::LastName>::type HasLastNameLV(std::nullptr_t) {}
    template <class C> static no HasLastNameLV(void*) {}
    template <class C> static std::enable_if_t<std::is_same_v<std::string, decltype(std::declval<Derived<C>>().firstName)>> HasProtFn(std::nullptr_t) {}
    template <class C> static no HasProtFn(...) {}
    template <class C> static std::enable_if_t<std::is_same_v<std::string, decltype(std::declval<Derived<C>>().lastName)>> HasProtLn(std::nullptr_t) {}
    template <class C> static no HasProtLn(...) {}
    template <class C> static std::enable_if_t<std::is_same_v<C, decltype(C{})>> HasDefaultConstructor(std::nullptr_t) {}
    template <class C> static no HasDefaultConstructor(...) {}
    template <class C> static std::enable_if_t<std::is_same_v<C, decltype(C{std::string{}, std::string{}})>> HasStrConstructor(std::nullptr_t) {}
    template <class C> static no HasStrConstructor(...) {}
    template <class C> static typename SFINAE<C, C&(C::*)(std::string), &C::FirstName>::type HasFNSetter(std::nullptr_t) {}
    template <class C> static no HasFNSetter(...) {}
    template <class C> static typename SFINAE<C, C&(C::*)(std::string), &C::LastName>::type HasLNSetter(std::nullptr_t) {}
    template <class C> static no HasLNSetter(...) {}
    template <class C> static typename SFINAE<C, bool(C::*)(const C&) const, &C::operator==>::type HasCmpOperator(std::nullptr_t) {}
    template <class C> static no HasCmpOperator(...) {}

public:
    static constexpr bool has_firstname = std::is_same_v<void, decltype(HasFirstName<T>(nullptr))> ||
            std::is_same_v<void, decltype(HasFirstNameLV<T>(nullptr))>;
    static constexpr bool has_lastname = std::is_same_v<void, decltype(HasLastName<T>(nullptr))> ||
            std::is_same_v<void, decltype(HasLastNameLV<T>(nullptr))>;
    static constexpr bool has_prot_firstName = std::is_same_v<void, decltype(HasProtFn<T>(nullptr))>;
    static constexpr bool has_prot_lastName = std::is_same_v<void, decltype(HasProtLn<T>(nullptr))>;
    static constexpr bool has_default_constructor = std::is_same_v<void, decltype(HasDefaultConstructor<T>(nullptr))>;
    static constexpr bool has_str_constructor = std::is_same_v<void, decltype(HasStrConstructor<T>(nullptr))>;
    static constexpr bool has_fn_setter = std::is_same_v<void, decltype(HasFNSetter<T>(nullptr))>;
    static constexpr bool has_ln_setter = std::is_same_v<void, decltype(HasLNSetter<T>(nullptr))>;
    static constexpr bool has_cmp_operator = std::is_same_v<void, decltype(HasCmpOperator<T>(nullptr))>;
};