#ifndef __BASEASSERT_HPP_2012_04_23__
#define __BASEASSERT_HPP_2012_04_23__

namespace assert {
    template <class Derived>
    struct base_assert {
        template <class Pred, class Message>
        static void out_of_range_assert(Pred pred, Message message)
            NOEXCEPT(Derived::assert(pred, message))
        {
            Derived::assert(pred, message);
        }
    };
}

#endif

