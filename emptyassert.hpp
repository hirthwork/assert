#ifndef __EMPTYASSERT_HPP_2012_04_23__
#define __EMPTYASSERT_HPP_2012_04_23__

namespace assert {
    struct empty_assert {
        template <class Pred, class Message>
        static void assert(Pred, Message) throw() {
        }

        template <class Pred, class Message>
        static void out_of_range_assert(Pred, Message) throw() {
        }
    };
}

#endif

