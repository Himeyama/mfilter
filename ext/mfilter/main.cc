#include <octave/oct.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "filter.hpp"
#include <ruby.h>
#include <numo/narray.h>



extern VALUE numo_cDFloat;


VALUE rb_na_filter(VALUE self, VALUE b, VALUE a, VALUE x, VALUE si){
    long len[3] = {NUM2LONG(rb_funcall(b, rb_intern("size"), 0)), NUM2LONG(rb_funcall(a, rb_intern("size"), 0)), NUM2LONG(rb_funcall(x, rb_intern("size"), 0))};
    MArray<double>
        mb(dim_vector(len[0], 1)),
        ma(dim_vector(len[1], 1)),
        mx(dim_vector(len[2], 1)),
        my;
    double* p[3] = {(double*)mb.data(), (double*)ma.data(), (double*)mx.data()};
    // double* pr[3] = {
    //     (double*)na_get_pointer(b),
    //     (double*)na_get_pointer(a),
    //     (double*)na_get_pointer(x)
    // };
    VALUE pr[3] = {
        b, a, x
    };
    VALUE y = rb_funcall(numo_cDFloat, rb_intern("zeros"), 1, LONG2NUM(len[2]));
    for(int n = 0; n < 3; n++)
        for(long i = 0; i < len[n]; i++)
            // p[n][i] = pr[n][i];
            p[n][i] = NUM2DBL(rb_funcall(pr[n], rb_intern("[]"), 1, INT2NUM(i)));

            
    if(si == Qnil)
        my = filter(mb, ma, mx);
    else if(rb_obj_class(si) == numo_cDFloat){
        long lsi = NUM2LONG(rb_funcall(si, rb_intern("size"), 0));
        MArray<double> msi(dim_vector(lsi, 1));
        double* namsi = (double*)na_get_pointer(si);
        for(long i = 0; i < lsi; i++)
            msi(i, 0) = namsi[i];
        my = filter(mb, ma, mx, msi);
    }
    else
        rb_raise(rb_eTypeError, "si should belong to DFloat class");

    double* py = (double*)na_get_pointer(y);
    double* pmy = (double*)my.data();
    for(long i = 0; i < len[2]; i++)
        py[i] = pmy[i];

    return y;
}


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
    VALUE y;
    for(int n = 0; n < 3; n++)
        for(long i = 0; i < len[n]; i++)
            p[n][i] = NUM2DBL(pr[n][i]);
    
    if(si == Qnil)
        my = filter(mb, ma, mx);
    else if(rb_obj_class(si) == rb_cArray){
        MArray<double> msi(dim_vector(RARRAY_LEN(si), 1));
        for(long i = 0; i < RARRAY_LEN(si); i++)
            msi(i, 0) = NUM2DBL(rb_ary_entry(si, i));
        my = filter(mb, ma, mx, msi);
    }
    else
        rb_raise(rb_eTypeError, "si should belong to Array class");
    
    y = rb_ary_new();
    for(long i = 0; i < RARRAY_LEN(x); i++)
        rb_ary_store(y, i, DBL2NUM(my(i, 0)));
    
    return y;
}

extern "C"{
    void Init_mfilter(){
        VALUE rb_cMFilter = rb_define_module("MFilter");
        rb_define_module_function(rb_cMFilter, "_filter", rb_m_filter, 4);
        rb_define_module_function(rb_cMFilter, "na_filter", rb_na_filter, 4);
    }
}