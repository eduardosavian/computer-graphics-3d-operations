// See end of file for license information
#ifndef _linalg_hpp_include_
#define _linalg_hpp_include_

#include <cstddef>
#include <cmath>

/// Vector /////////////////////////////////////////////////////////////////////
namespace linalg {
using usize = size_t;

using std::sqrt, std::sin, std::cos, std::tan;

// Absolute value
template<typename T>
constexpr
T abs(T const& x){
    if(x < 0){
        return -x;
    }
    return x;
}

// Maximum
template<typename T>
constexpr
T max(T const& a, T const& b){
    if(b > a){ return b; }
    return a;
}

// Minimum
template<typename T>
constexpr
T min(T const& a, T const& b){
    if(b < a){ return b; }
    return a;
}

// Maximum
template<typename T, typename ...Rest>
constexpr
T max(T const& a, T const& b, Rest&& ...rest){
    if(b > a){
        return max(b, rest...);
    }
    return max(a, rest...);
}

// Minimum
template<typename T, typename ...Rest>
constexpr
T min(T const& a, T const& b, Rest&& ...rest){
    if(b < a){
        return min(b, rest...);
    }
    return min(a, rest...);
}

// Make x fit the rage mini..maxi (inclusive)
template<typename T>
constexpr
T clamp(T const& mini, T const& x, T const& maxi){
    return min(max(x, mini), maxi);
}

template<typename T, usize N>
struct vector {
    T data[N]{};

    constexpr
    usize size() const { return N; }

    constexpr
    T* raw_data() { return &data[0]; }

    constexpr
    T const* raw_data() const { return &data[0]; }

    constexpr
    T& operator[](usize idx){ return data[idx]; }

    constexpr
    T const& operator[](usize idx) const { return data[idx]; }

	constexpr
	vector clip(T const& lo, T const& hi){
		vector<T, N> res;
		for(usize i = 0; i < N; i += 1){
			res[i] = clamp(lo, data[i], hi);
		}
		return res;
	}

	static constexpr
	vector splat(T const& scalar){
		vector<T, N> v;
		for(auto& e : v){
			e = scalar;
		}
		return v;
	}

    // C++ Iterator insanity.
    using value_type = T;

    struct VecIterator {
        constexpr VecIterator(T* data) : ptr_val(data) {}
        constexpr T& operator*() const { return *ptr_val; }
        constexpr T* operator->() const { return ptr_val; }
        constexpr auto& operator++(){ ptr_val += 1; return *this; }
        constexpr bool operator==(VecIterator const& it){ return ptr_val == it.ptr_val; }
        constexpr bool operator!=(VecIterator const& it){ return ptr_val != it.ptr_val; }
    private:
        T* ptr_val;
    };

    struct ConstVecIterator {
        constexpr ConstVecIterator(T const* data) : ptr_val(data) {}
        constexpr T const& operator*() const { return *ptr_val; }
        constexpr T* operator->() const { return ptr_val; }
        constexpr auto& operator++(){ ptr_val += 1; return *this; }
        constexpr bool operator==(ConstVecIterator const& it){ return ptr_val == it.ptr_val; }
        constexpr bool operator!=(ConstVecIterator const& it){ return ptr_val != it.ptr_val; }

    private:
        T const* ptr_val;
    };


    constexpr auto begin(){ return VecIterator(&data[0]); }

    constexpr auto end(){ return VecIterator(&data[N]); }

    constexpr auto begin() const { return ConstVecIterator(&data[0]); }

    constexpr auto end() const { return ConstVecIterator(&data[N]); }

};

template<typename T, usize N>
auto magnitude(vector<T, N> const& v){
    T acc{0};
    for(usize i = 0; i < N; i += 1){
        acc += v[i] * v[i];
    }
    return sqrt(acc);
}

template<typename T, usize N>
constexpr
vector<T, N> abs(vector<T, N> const& a){
    vector<T, N> res;
    for(usize i = 0; i < N; i += 1){
        res[i] = abs(a[i]);
    }
    return res;
}

template<typename T, usize N>
constexpr
bool vector_equal(vector<T, N> const& a, vector<T, N> const& b){
    for(usize i = 0; i < N; i += 1){
        if(a[i] != b[i]){ return false; }
    }
    return true;
}

namespace detail {
template<typename T, usize N, usize I, typename U>
constexpr
void fill_arr_with_param_pack(vector<T, N>& v, U&& elem){
    static_assert(I < N, "Out of bounds");
    v[I] = static_cast<T>(elem);
}

template<typename T, usize N, usize I = 0, typename U,typename... Args>
constexpr
void fill_arr_with_param_pack(vector<T, N>& v, U&& elem, Args&& ...indices){
    static_assert(I < N, "Out of bounds");
    v[I] = static_cast<T>(elem);
    fill_arr_with_param_pack<T, N, I+1>(v, indices...);
}
}

template<typename T, usize N, typename U>
constexpr
auto swizzle(const vector<T, N>& v, U&& idx){
    vector<T, 1> res;
    res[0] = v[idx];
    return res;
}

template<typename T, usize N, typename... Index>
constexpr
auto swizzle(const vector<T, N>& v, Index&& ...indices){
    constexpr usize L  = sizeof...(indices);
    vector<usize, L> idxv;
    vector<T, L> res;

    detail::fill_arr_with_param_pack(idxv, indices...);
    for(usize i = 0; i < L; i += 1){
        res[i] = v[idxv[i]];
    }

    return res;
}

// Element wise operations
template<typename T, usize N>
constexpr vector<bool, N> operator!(vector<T, N> const& a){
    vector<bool, N> res;
    for(usize i = 0; i < N; i += 1){
        res[i] = !a[i];
    }
    return res;
}

// Arithmetic unary operation
#define ARITH_OP1(name_, token_) \
template<typename T, usize N>                        \
constexpr vector<T, N> name_(vector<T, N> const& a){ \
    vector<T, N> res;                                \
    for(usize i = 0; i < N; i += 1){                 \
        res[i] = token_ a[i];                        \
    }                                                \
    return res;                                      \
}

// Arithmetic binary operation
#define ARITH_OP2(name_, token_) \
template<typename T, usize N>                                       \
constexpr auto name_(vector<T, N> const& a, vector<T, N> const& b){ \
    vector<T, N> res;                                               \
    for(usize i = 0; i < N; i += 1){                                \
        res[i] = a[i] token_ b[i];                                  \
    }                                                               \
    return res;                                                     \
}

// Logic binary operation
#define LOGIC_OP2(name_, token_) \
template<typename T, usize N>                                       \
constexpr auto name_(vector<T, N> const& a, vector<T, N> const& b){ \
    vector<bool, N> res;                                            \
    for(usize i = 0; i < N; i += 1){                                \
        res[i] = a[i] token_ b[i];                                  \
    }                                                               \
    return res;                                                     \
}

// Scalar arithmetic operation
#define SCALAR_LOGIC_OP2(name_, token_) \
template<typename T, usize N>                                                     \
constexpr auto name_(vector<T, N> const& a, T const& val){                        \
    vector<bool, N> res;                                                          \
    for(usize i = 0; i < N; i += 1){                                              \
        res[i] = a[i] token_ val;                                                 \
    }                                                                             \
    return res;                                                                   \
}                                                                                 \
template<typename T, usize N>                                                     \
constexpr auto name_(T const& val, vector<T, N> const& a){ return a token_ val; }

// Scalar logic operation
#define SCALAR_ARITH_OP2(name_, token_) \
template<typename T, usize N>                                                     \
constexpr auto name_(vector<T, N> const& a, T const& val){                        \
    vector<T, N> res;                                                             \
    for(usize i = 0; i < N; i += 1){                                              \
        res[i] = a[i] token_ val;                                                 \
    }                                                                             \
    return res;                                                                   \
}                                                                                 \
template<typename T, usize N>                                                     \
constexpr auto name_(T const& val, vector<T, N> const& a){ return a token_ val; }

ARITH_OP1(operator+, +);
ARITH_OP1(operator-, -);

ARITH_OP2(operator+, +);
ARITH_OP2(operator-, -);
ARITH_OP2(operator*, *);
ARITH_OP2(operator/, /);
ARITH_OP2(operator%, %);

SCALAR_ARITH_OP2(operator+, +);
SCALAR_ARITH_OP2(operator-, -);
SCALAR_ARITH_OP2(operator*, *);
SCALAR_ARITH_OP2(operator/, /);
SCALAR_ARITH_OP2(operator%, %);

ARITH_OP1(operator~, ~);
ARITH_OP2(operator&, &);
ARITH_OP2(operator|, |);
ARITH_OP2(operator^, ^);
ARITH_OP2(operator<<, <<);
ARITH_OP2(operator>>, >>);

SCALAR_ARITH_OP2(operator&, &);
SCALAR_ARITH_OP2(operator|, |);
SCALAR_ARITH_OP2(operator^, ^);
SCALAR_ARITH_OP2(operator<<, <<);
SCALAR_ARITH_OP2(operator>>, >>);

LOGIC_OP2(operator&&, &&);
LOGIC_OP2(operator||, ||);
LOGIC_OP2(operator==, ==);
LOGIC_OP2(operator!=, !=);
LOGIC_OP2(operator>=, >=);
LOGIC_OP2(operator<=, <=);
LOGIC_OP2(operator<,  <);
LOGIC_OP2(operator>,  >);

SCALAR_LOGIC_OP2(operator&&, &&);
SCALAR_LOGIC_OP2(operator||, ||);
SCALAR_LOGIC_OP2(operator==, ==);
SCALAR_LOGIC_OP2(operator!=, !=);
SCALAR_LOGIC_OP2(operator>=, >=);
SCALAR_LOGIC_OP2(operator<=, <=);
SCALAR_LOGIC_OP2(operator<,  <);
SCALAR_LOGIC_OP2(operator>,  >);

#undef SCALAR_ARITH_OP2
#undef SCALAR_LOGIC_OP2
#undef ARITH_OP1
#undef ARITH_OP2
#undef LOGIC_OP2
}


/// Matrix /////////////////////////////////////////////////////////////////////
namespace linalg {
template<typename T, usize NRows, usize NColumns = NRows>
struct matrix {
	using Column = vector<T, NRows>;
	using Row = vector<T, NColumns>;
	using RowRepr = vector<T, NRows * NColumns>;

	matrix(){}

	constexpr
	matrix(RowRepr const& rows){
		Column buf;
		for(usize i = 0; i < NColumns; i += 1){
			for(usize j = 0; j < NRows; j += 1){
				buf[j] = rows[i + j * NColumns];
			}
			columns[i] = buf;
		}
	}

	constexpr
	Column col(usize idx) const {
		return columns[idx];
	}

	constexpr
	usize row_count() const {
		return NRows;
	}

	constexpr
	usize column_count() const {
		return NColumns;
	}

	constexpr
	Row row(usize idx) const {
		Row res;
		for(usize i = 0; i < NColumns; i += 1){
			res[i] = columns[i][idx];
		}
		return res;
	}

	constexpr
	T& at(usize row, usize col){
		return columns[col][row];
	}

	constexpr
	T const& at(usize row, usize col) const {
		return columns[col][row];
	}

	vector<Column, NColumns> columns{};
};

template<typename T,usize RowsA, usize ColsA, usize RowsB, usize ColsB>
constexpr
auto operator*(matrix<T, RowsA, ColsA> const& a, matrix<T, RowsB, ColsB> const& b){
	static_assert(RowsA == ColsB, "Mismatched matrix sizes.");
	matrix<T, RowsA, ColsB> res;
	constexpr auto sum = [](auto v){
		typename decltype(v)::value_type acc{0};
		for(usize i = 0; i < v.size(); i += 1){
			acc += v[i];
		}
		return acc;
	};

	for(usize i = 0; i < RowsA; i += 1){
		for(usize j = 0; j < ColsB; j += 1){
			res.at(i, j) = sum(a.row(i) * b.col(j));
		}
	}
	return res;
}


template<typename T, usize NR, usize NC>
constexpr
bool matrix_equal(matrix<T, NR, NC> const& a, matrix<T, NR, NC> const& b){
	for(usize i = 0; i < NC; i += 1){
		if(!vector_equal(a.col(i), b.col(i))){ return false; }
	}
	return true;
}

template<typename T, usize NR, usize NC>
constexpr
auto operator!(matrix<T, NR, NC> const& a){
	matrix<bool, NR, NC> res;
	for(usize i = 0; i < NC; i += 1){
		res.columns[i] = !a.columns[i];
	}
	return res;
}

#define ARITH_OP2(name_, token_) \
template<typename T, usize NR, usize NC>                            \
constexpr                                                           \
auto name_(matrix<T, NR, NC> const& a, matrix<T, NR, NC> const& b){ \
	matrix<T, NR, NC> res;                                          \
	for(usize i = 0; i < NC; i += 1){                               \
		res.columns[i] = a.columns[i] token_ b.columns[i];          \
	}                                                               \
	return res;                                                     \
}

#define LOGIC_OP2(name_, token_) \
template<typename T, usize NR, usize NC>                            \
constexpr                                                           \
auto name_(matrix<T, NR, NC> const& a, matrix<T, NR, NC> const& b){ \
	matrix<bool, NR, NC> res;                                       \
	for(usize i = 0; i < NC; i += 1){                               \
		res.columns[i] = a.columns[i] token_ b.columns[i];          \
	}                                                               \
	return res;                                                     \
}

#define ARITH_OP1(name_, token_) \
template<typename T, usize NR, usize NC>                            \
constexpr                                                           \
auto name_(matrix<T, NR, NC> const& a){                             \
	matrix<T, NR, NC> res;                                          \
	for(usize i = 0; i < NC; i += 1){                               \
		res.columns[i] = token_ a.columns[i];                       \
	}                                                               \
	return res;                                                     \
}

#define SCALAR_ARITH_OP2(name_, token_)                  \
template<typename T, usize NR, usize NC>                 \
constexpr                                                \
auto name_ (matrix<T, NR, NC> const& m, T const& value){ \
	matrix<T, NR, NC> res;                               \
	for(usize i = 0; i < NC; i += 1){                    \
		res.columns[i] = m.columns[i] token_ value;      \
	}                                                    \
	return res;                                          \
}                                                        \
template<typename T, usize NR, usize NC>                 \
constexpr                                                \
auto name_ (T const& value, matrix<T, NR, NC> const& m){ return m token_ value; }

#define SCALAR_LOGIC_OP2(name_, token_) \
template<typename T, usize NR, usize NC>                \
constexpr                                               \
auto name_ (matrix<T, NR, NC> const& m, T const& value){ \
	matrix<bool, NR, NC> res;                              \
	for(usize i = 0; i < NC; i += 1){                   \
		res.columns[i] = m.columns[i] token_ value;     \
	}                                                   \
	return res;                                         \
}                                                       \
template<typename T, usize NR, usize NC>                \
constexpr                                               \
auto name_ (T const& value, matrix<T, NR, NC> const& m){ return m token_ value; }


ARITH_OP1(operator+, +);
ARITH_OP1(operator-, -);
ARITH_OP2(operator+, +);
ARITH_OP2(operator-, -);
ARITH_OP2(hadamard_product, *);
ARITH_OP2(operator/, /);
ARITH_OP2(operator%, %);

SCALAR_ARITH_OP2(operator+, +);
SCALAR_ARITH_OP2(operator-, -);
SCALAR_ARITH_OP2(operator*, *);
SCALAR_ARITH_OP2(operator/, /);
SCALAR_ARITH_OP2(operator%, %);

ARITH_OP1(operator~, ~);
ARITH_OP2(operator&, &);
ARITH_OP2(operator|, |);
ARITH_OP2(operator^, ^);
ARITH_OP2(operator<<, <<);
ARITH_OP2(operator>>, >>);

SCALAR_ARITH_OP2(operator&, &);
SCALAR_ARITH_OP2(operator|, |);
SCALAR_ARITH_OP2(operator^, ^);
SCALAR_ARITH_OP2(operator<<, <<);
SCALAR_ARITH_OP2(operator>>, >>);

LOGIC_OP2(operator&&, &&);
LOGIC_OP2(operator||, ||);
LOGIC_OP2(operator==, ==);
LOGIC_OP2(operator!=, !=);
LOGIC_OP2(operator>=, >=);
LOGIC_OP2(operator<=, <=);
LOGIC_OP2(operator<,  <);
LOGIC_OP2(operator>,  >);

SCALAR_LOGIC_OP2(operator&&, &&);
SCALAR_LOGIC_OP2(operator||, ||);
SCALAR_LOGIC_OP2(operator==, ==);
SCALAR_LOGIC_OP2(operator!=, !=);
SCALAR_LOGIC_OP2(operator>=, >=);
SCALAR_LOGIC_OP2(operator<=, <=);
SCALAR_LOGIC_OP2(operator<,  <);
SCALAR_LOGIC_OP2(operator>,  >);

#undef SCALAR_ARITH_OP2
#undef SCALAR_LOGIC_OP2
#undef ARITH_OP1
#undef ARITH_OP2
#undef LOGIC_OP2
}

/*
	Copyright 2024 marcs-feh

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the “Software”), to deal in the Software without
	restriction, including without limitation the rights to use, copy,
	modify, merge, publish, distribute, sublicense, and/or sell copies
	of the Software, and to permit persons to whom the Software is
	furnished to do so.

	THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
	DEALINGS IN THE SOFTWARE.
*/

#endif /* Include guard */
