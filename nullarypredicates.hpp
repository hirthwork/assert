#ifndef __NULLARYPREDICATES_HPP_2012_04_23__
#define __NULLARYPREDICATES_HPP_2012_04_23__

namespace assert {
    template <class Pred>
    class negate {
        const Pred pred;

    public:
        negate(Pred pred) throw()
            : pred(pred)
        {
        }

        bool operator ()() const throw()
        {
            return !pred();
        }
    };

    template <class Pred>
    static negate<Pred> make_negate(Pred pred) throw() {
        return negate<Pred>(pred);
    }

    template <class Pred, class Arg>
    class bind {
        const Pred pred;
        const Arg arg;

    public:
        bind(Pred pred, Arg arg) throw()
            : pred(pred)
            , arg(arg)
        {
        }

        bool operator ()() const throw()
        {
            return pred(arg);
        }
    };

    template <class Pred, class Arg>
    static bind<Pred, Arg> make_bind(Pred pred, Arg arg) throw() {
        return bind<Pred, Arg>(pred, arg);
    }

    template <class Pred, class Arg>
    class bind_predicate {
        const Pred pred;
        const Arg arg;

    public:
        bind_predicate(Pred pred, Arg arg) throw()
            : pred(pred)
            , arg(arg)
        {
        }

        bool operator ()() const throw()
        {
            return pred(arg());
        }
    };

    template <class Pred, class Arg>
    static bind_predicate<Pred, Arg> make_bind_predicate(Pred pred,
        Arg arg) throw()
    {
        return bind_predicate<Pred, Arg>(pred, arg);
    }

    template <class Class, class Pred>
    class bind_member {
        const Class* const pthis;
        const Pred pred;

    public:
        bind_member(const Class* pthis, Pred pred) throw()
            : pthis(pthis)
            , pred(pred)
        {
        }

        bool operator ()() const throw()
        {
            return (pthis->*pred)();
        }
    };

    template <class Class, class Pred>
    static bind_member<Class, Pred> make_bind_member(const Class* pthis,
        Pred pred) throw()
    {
        return bind_member<Class, Pred>(pthis, pred);
    }
}

#endif

