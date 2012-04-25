#ifndef __NULLARYPREDICATES_HPP_2012_04_23__
#define __NULLARYPREDICATES_HPP_2012_04_23__

#include "constexpr.hpp"
#include "noexcept.hpp"

namespace assert {
    struct true_predicate {
        typedef bool result_type;

        CONSTEXPR result_type operator ()() throw() {
            return true;
        }
    };

    template <class Pred>
    class negate {
        const Pred pred;

    public:
        typedef bool result_type;

        negate(Pred pred) NOEXCEPT(Pred(pred))
            : pred(pred)
        {
        }

        result_type operator ()() const NOEXCEPT(pred())
        {
            return !pred();
        }
    };

    template <class Pred>
    static negate<Pred> make_negate(Pred pred) NOEXCEPT(negate<Pred>(pred)) {
        return negate<Pred>(pred);
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

    template <class Arg>
    static identity<Arg> make_identity(Arg arg) NOEXCEPT(Arg(arg)) {
        return identity<Arg>(arg);
    }

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

    template <class Pred, class Arg>
    static predicate_binder<Pred, Arg> bind(Pred pred, Arg arg)
        NOEXCEPT((predicate_binder<Pred, Arg>(pred, arg)))
    {
        return predicate_binder<Pred, Arg>(pred, arg);
    }

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

    template <class Class, class Result>
    static member_binder<Class, Result (Class::*)() const> bind_member(
        const Class* pthis, Result (Class::*pred)() const) throw()
    {
        return member_binder<Class, Result (Class::*)() const>(pthis, pred);
    }
}

#endif

