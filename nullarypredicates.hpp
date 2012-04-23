#ifndef __NULLARYPREDICATES_HPP_2012_04_23__
#define __NULLARYPREDICATES_HPP_2012_04_23__

#include "constexpr.hpp"
#include "noexcept.hpp"

namespace assert {
    struct true_predicate {
        CONSTEXPR bool operator ()() throw() {
            return true;
        }
    };

    template <class Pred>
    class negate {
        const Pred pred;

    public:
        negate(Pred pred) NOEXCEPT(Pred(pred))
            : pred(pred)
        {
        }

        bool operator ()() const NOEXCEPT(pred())
        {
            return !pred();
        }
    };

    template <class Pred>
    static negate<Pred> make_negate(Pred pred) NOEXCEPT(negate<Pred>(pred)) {
        return negate<Pred>(pred);
    }

    template <class Pred, class Arg>
    class bind {
        const Pred pred;
        const Arg arg;

    public:
        bind(Pred pred, Arg arg) NOEXCEPT2(Pred(pred), Arg(arg))
            : pred(pred)
            , arg(arg)
        {
        }

        bool operator ()() const NOEXCEPT(pred(arg))
        {
            return pred(arg);
        }
    };

    template <class Pred, class Arg>
    static bind<Pred, Arg> make_bind(Pred pred, Arg arg)
        NOEXCEPT((bind<Pred, Arg>(pred, arg)))
    {
        return bind<Pred, Arg>(pred, arg);
    }

    template <class Pred, class Arg>
    class bind_predicate {
        const Pred pred;
        const Arg arg;

    public:
        bind_predicate(Pred pred, Arg arg) NOEXCEPT2(Pred(pred), Arg(arg))
            : pred(pred)
            , arg(arg)
        {
        }

        bool operator ()() const NOEXCEPT(pred(arg()))
        {
            return pred(arg());
        }
    };

    template <class Pred, class Arg>
    static bind_predicate<Pred, Arg> make_bind_predicate(Pred pred,
        Arg arg) NOEXCEPT((bind_predicate<Pred, Arg>(pred, arg)))
    {
        return bind_predicate<Pred, Arg>(pred, arg);
    }

    template <class Class, class Pred>
    class bind_member {
        const Class* const pthis;
        const Pred pred;

    public:
        bind_member(const Class* pthis, Pred pred) NOEXCEPT(Pred(pred))
            : pthis(pthis)
            , pred(pred)
        {
        }

        bool operator ()() const NOEXCEPT((pthis->*pred)())
        {
            return (pthis->*pred)();
        }
    };

    template <class Class, class Pred>
    static bind_member<Class, Pred> make_bind_member(const Class* pthis,
        Pred pred) NOEXCEPT((bind_member<Class, Pred>(pthis, pred)))
    {
        return bind_member<Class, Pred>(pthis, pred);
    }
}

#endif

