/*
 * nullarypredicates.hpp    -- lazy functional predicates implementation
 *
 * Copyright (C) 2012 Dmitry Potapov <potapov.d@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __NULLARYPREDICATES_HPP_2012_04_23__
#define __NULLARYPREDICATES_HPP_2012_04_23__

#include <limits>

#include <reinvented-wheels/enableif.hpp>

#include "constexpr.hpp"
#include "noexcept.hpp"

namespace assert {
    template <class T, T Value = T()>
    struct const_value {
        typedef T result_type;

        CONSTEXPR result_type operator ()() throw() {
            return Value;
        }
    };

    template <class Result, class Pred, class Arg1, class Arg2>
    class selector {
        const Pred pred;
        const Arg1 arg1;
        const Arg2 arg2;

    public:
        typedef Result result_type;

        selector(Pred pred, Arg1 arg1, Arg2 arg2)
            NOEXCEPT((Pred(pred), Arg1(arg1), Arg2(arg2)))
            : pred(pred)
            , arg1(arg1)
            , arg2(arg2)
        {
        }

        result_type operator ()() const
            NOEXCEPT((bool(pred()),result_type(arg1()), result_type(arg2())))
        {
            if (pred()) {
                return arg1();
            } else {
                return arg2();
            }
        }
    };

    template <class Result, class Pred, class Arg1, class Arg2>
    selector<Result, Pred, Arg1, Arg2> select(Pred pred, Arg1 arg1, Arg2 arg2)
        NOEXCEPT((selector<Result, Pred, Arg1, Arg2>(pred, arg1, arg2)))
    {
        return selector<Result, Pred, Arg1, Arg2>(pred, arg1, arg2);
    }

    template <class Pred, class Arg1, class Arg2>
    selector<typename Arg1::result_type, Pred, Arg1, Arg2>
        select(Pred pred, Arg1 arg1, Arg2 arg2)
        NOEXCEPT((selector<typename Arg1::result_type, Pred, Arg1, Arg2>(pred,
            arg1, arg2)))
    {
        return selector<typename Arg1::result_type, Pred, Arg1, Arg2>(pred,
            arg1, arg2);
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

        predicate_binder(Pred pred, Arg arg) NOEXCEPT((Pred(pred), Arg(arg)))
            : pred(pred)
            , arg(arg)
        {
        }

        result_type operator ()() const NOEXCEPT(pred(arg()))
        {
            return pred(arg());
        }
    };

    template <class Pred, class Arg1, class Arg2>
    class binary_predicate_binder {
        const Pred pred;
        const Arg1 arg1;
        const Arg2 arg2;

    public:
        typedef typename Pred::result_type result_type;

        binary_predicate_binder(Pred pred, Arg1 arg1, Arg2 arg2)
            NOEXCEPT((Pred(pred), Arg1(arg1), Arg2(arg2)))
            : pred(pred)
            , arg1(arg1)
            , arg2(arg2)
        {
        }

        result_type operator ()() const NOEXCEPT(pred(arg1(), arg2()))
        {
            return pred(arg1(), arg2());
        }
    };

    template <class Pred>
    class member_binder;

    template <class Class, class Result>
    class member_binder<Result (Class::*)() const> {
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
    static typename reinvented_wheels::enable_if<!is_predicate<Arg>::value,
        predicate_binder<Pred, Arg> >::type bind(Pred pred, Arg arg)
        NOEXCEPT((predicate_binder<Pred, Arg>(pred, arg)))
    {
        return predicate_binder<Pred, Arg>(pred, arg);
    }

    template <class Pred, class Arg1, class Arg2>
    static binary_predicate_binder<Pred, Arg1, Arg2>
        bind(Pred pred, Arg1 arg1, Arg2 arg2)
        NOEXCEPT((binary_predicate_binder<Pred, Arg1, Arg2>(pred, arg1, arg2)))
    {
        return binary_predicate_binder<Pred, Arg1, Arg2>(pred, arg1, arg2);
    }

    template <class Class, class Pred>
    static typename reinvented_wheels::enable_if<is_predicate<Pred>::value,
        member_binder<Pred> >::type bind(const Class* pthis, Pred pred)
        NOEXCEPT((member_binder<Pred>(pthis, pred)))
    {
        return member_binder<Pred>(pthis, pred);
    }
}

#endif

