#include <octave-5.2.0/octave/oct.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "filter.hpp"
#include <ruby.h>


VALUE rb_m_filter(VALUE self, VALUE b, VALUE a, VALUE x){
    MArray<double>
        mb(dim_vector(RARRAY_LEN(b), 1)),
        ma(dim_vector(RARRAY_LEN(a), 1)),
        mx(dim_vector(RARRAY_LEN(x), 1));
    for(long i = 0; i < RARRAY_LEN(b); i++)
        mb(i, 0) = NUM2DBL(rb_ary_entry(b, i));
    for(long i = 0; i < RARRAY_LEN(a); i++)
        ma(i, 0) = NUM2DBL(rb_ary_entry(a, i));
    for(long i = 0; i < RARRAY_LEN(x); i++)
        mx(i, 0) = NUM2DBL(rb_ary_entry(x, i));
    MArray<double> my = filter(mb, ma, mx);
    VALUE y = rb_ary_new();
    for(long i = 0; i < RARRAY_LEN(x); i++)
        rb_ary_store(y, i, DBL2NUM(my(i, 0)));
    return y;
}

extern "C"{
    void Init_mfilter(){
        VALUE rb_cMFilter = rb_define_module("MFilter");
        rb_define_module_function(rb_cMFilter, "filter", RUBY_METHOD_FUNC(rb_m_filter), 3);
    }
}