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
    double* p[3] = {(double*)mb.data(), (double*)ma.data(), (double*)mx.data()};
    const VALUE* pr[3] = {
        RARRAY_CONST_PTR_TRANSIENT(b),
        RARRAY_CONST_PTR_TRANSIENT(a),
        RARRAY_CONST_PTR_TRANSIENT(x)
    };
    long len[3] = {RARRAY_LEN(b), RARRAY_LEN(a), RARRAY_LEN(x)};
    for(int n = 0; n < 3; n++)
        for(long i = 0; i < len[n]; i++)
            p[n][i] = NUM2DBL(pr[n][i]);
    
    if(si == Qnil){
        my = filter(mb, ma, mx);
    }else if(rb_obj_class(si) == rb_cArray){
        MArray<double> msi(dim_vector(RARRAY_LEN(si), 1));
        for(long i = 0; i < RARRAY_LEN(si); i++)
            msi(i, 0) = NUM2DBL(rb_ary_entry(si, i));
        my = filter(mb, ma, mx, msi);
    }else{
        rb_raise(rb_eTypeError, "si should belong to Array class");
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