/*
 * stdexcept.hpp            -- <stdexcept> assert class
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

#ifndef __STDEXCEPTASSERT_HPP_2012_04_23__
#define __STDEXCEPTASSERT_HPP_2012_04_23__

#include <stdexcept>

namespace assert {
    struct stdexcept {
        template <class Pred, class Message>
        static void assert(Pred pred, Message message) {
            if (!pred()) {
                throw std::logic_error(message);
            }
        }

        template <class Pred, class Message>
        static void out_of_range_assert(Pred pred, Message message) {
            if (!pred()) {
                throw std::out_of_range(message);
            }
        }
    };
}

#endif

