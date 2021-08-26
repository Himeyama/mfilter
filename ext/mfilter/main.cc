#include <octave/oct.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "filter.hpp"
#include <ruby.h>


VALUE rb_m_filter(VALUE self, VALUE b, VALUE a, VALUE x, VALUE si){
    MArray<double>
        mb(dim_vector(RARRAY_LEN(b), 1)),
        ma(dim_vector(RARRAY_LEN(a), 1)),
        mx(dim_vector(RARRAY_LEN(x), 1)),
        my;
    for(long i = 0; i < RARRAY_LEN(b); i++)
        mb(i, 0) = NUM2DBL(rb_ary_entry(b, i));
    for(long i = 0; i < RARRAY_LEN(a); i++)
        ma(i, 0) = NUM2DBL(rb_ary_entry(a, i));
    for(long i = 0; i < RARRAY_LEN(x); i++)
        mx(i, 0) = NUM2DBL(rb_ary_entry(x, i));

    if(si == Qnil){
        my = filter(mb, ma, mx);
    }else if(rb_funcall(si, rb_intern("is_a?"), 1, rb_cArray) == Qtrue){
        MArray<double> msi(dim_vector(RARRAY_LEN(si), 1));
        for(long i = 0; i < RARRAY_LEN(si); i++)
            msi(i, 0) = NUM2DBL(rb_ary_entry(si, i));
        my = filter(mb, ma, mx, msi);
    }else{
        return Qfalse;
    }
    
    VALUE y = rb_ary_new();
    for(long i = 0; i < RARRAY_LEN(x); i++)
        rb_ary_store(y, i, DBL2NUM(my(i, 0)));
    return y;
}

extern "C"{
    void Init_mfilter(){
        VALUE rb_cMFilter = rb_define_module("MFilter");
        rb_define_module_function(rb_cMFilter, "_filter", RUBY_METHOD_FUNC(rb_m_filter), 4);
    }
}