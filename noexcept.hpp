/*
 * noexcept.hpp             -- noexcept compatibility wrapper
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

#ifndef __NOEXCEPT_HPP_2012_04_23__
#define __NOEXCEPT_HPP_2012_04_23__

#if __cplusplus >= 201103L
#define NOEXCEPT(expr) noexcept(noexcept(expr))
#else
#define NOEXCEPT(expr)
#endif

#endif

