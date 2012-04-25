#ifndef __NULLARYPREDICATES_HPP_2012_04_23__
#define __NULLARYPREDICATES_HPP_2012_04_23__

#include <reinvented-wheels/enableif.hpp>

#include "constexpr.hpp"
#include "noexcept.hpp"

namespace assert {
    struct truth {
        typedef bool result_type;

        CONSTEXPR result_type operator ()() throw() {
            return true;
        }
    };

    template <class Pred>
    class negator {
        const Pred pred;

    public:
        typedef bool result_type;

        negator(Pred pred) NOEXCEPT(Pred(pred))
            : pred(pred)
        {
        }

        result_type operator ()() const NOEXCEPT(pred())
        {
            return !pred();
        }
    };

    template <class Pred>
    static negator<Pred> negate(Pred pred) NOEXCEPT(negator<Pred>(pred)) {
        return negator<Pred>(pred);
    }

    template <class Arg>
    class identity {
        const Arg arg;

    public:
        typedef Arg result_type;

        identity(Arg arg) NOEXCEPT(Arg(arg))
            : arg(arg)
        {
        }

        result_type operator ()() const NOEXCEPT(Arg(arg)) {
            return arg;
        }
    };

    template <class Pred, class Arg>
    class predicate_binder {
        const Pred pred;
        const Arg arg;

    public:
        typedef typename Pred::result_type result_type;

        predicate_binder(Pred pred, Arg arg) NOEXCEPT2(Pred(pred), Arg(arg))
            : pred(pred)
            , arg(arg)
        {
        }

        result_type operator ()() const NOEXCEPT(pred(arg()))
        {
            return pred(arg());
        }
    };

    template <class Class, class Pred>
    class member_binder;

    template <class Class, class Result>
    class member_binder<Class, Result (Class::*)() const> {
        const Class* const pthis;
        typedef Result (Class::*Pred)() const;
        const Pred pred;

    public:
        typedef Result result_type;

        member_binder(const Class* pthis, Pred pred) throw()
            : pthis(pthis)
            , pred(pred)
        {
        }

        result_type operator ()() const NOEXCEPT((pthis->*pred)())
        {
            return (pthis->*pred)();
        }
    };

    template <class>
    struct is_predicate {
        static const bool value = false;
    };

    template <class Class, class Result>
    struct is_predicate<Result (Class::*)() const> {
        static const bool value = true;
    };

    template <class Arg>
    static identity<Arg> bind(Arg arg) NOEXCEPT(Arg(arg)) {
        return identity<Arg>(arg);
    }

    template <class Pred, class Arg>
    static typename NReinventedWheels::TEnableIf<!is_predicate<Arg>::value,
        predicate_binder<Pred, Arg> >::TType_ bind(Pred pred, Arg arg)
        NOEXCEPT((predicate_binder<Pred, Arg>(pred, arg)))
    {
        return predicate_binder<Pred, Arg>(pred, arg);
    }

    template <class Class, class Pred>
    static typename NReinventedWheels::TEnableIf<is_predicate<Pred>::value,
        member_binder<Class, Pred> >::TType_ bind(const Class* pthis,
            Pred pred) throw()
    {
        return member_binder<Class, Pred>(pthis, pred);
    }
}

#endif

