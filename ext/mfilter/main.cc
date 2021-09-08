#include <oct.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "filter.hpp"
#include <ruby.h>
#include <numo/narray.h>

extern VALUE numo_cDFloat;

double* NA_GET_DBL_PT(VALUE na){
    double* p = (double*)na_get_pointer(na);
    long offset = na_get_offset(na) / sizeof(double);
    return p + offset;
}

VALUE rb_na_filter(VALUE self, VALUE b, VALUE a, VALUE x, VALUE si){
    size_t len[3] = {RNARRAY_SIZE(b), RNARRAY_SIZE(a), RNARRAY_SIZE(x)};
    MArray<double>
        mb(dim_vector(len[0], 1)),
        ma(dim_vector(len[1], 1)),
        mx(dim_vector(len[2], 1)),
        my;
    memcpy((double*)mb.data(), NA_GET_DBL_PT(b), sizeof(double) * len[0]);
    memcpy((double*)ma.data(), NA_GET_DBL_PT(a), sizeof(double) * len[1]);
    memcpy((double*)mx.data(), NA_GET_DBL_PT(x), sizeof(double) * len[2]);
    VALUE y = rb_funcall(numo_cDFloat, rb_intern("zeros"), 1, LONG2NUM(len[2]));   
            
    if(si == Qnil)
        my = filter(mb, ma, mx);
    else if(rb_obj_class(si) == numo_cDFloat){
        long lsi = NUM2LONG(rb_funcall(si, rb_intern("size"), 0));
        MArray<double> msi(dim_vector(lsi, 1));
        double* namsi = NA_GET_DBL_PT(si);
        memcpy((double*)msi.data(), namsi, sizeof(double) * lsi);
        my = filter(mb, ma, mx, msi);
    }
    else
        rb_raise(rb_eTypeError, "si should belong to Numo::DFloat class");
    memcpy(NA_GET_DBL_PT(y),  (double*)my.data(), sizeof(double) * len[2]);

    return y;
}


VALUE rb_m_filter(VALUE self, VALUE b, VALUE a, VALUE x, VALUE si){
    long len[3] = {RARRAY_LEN(b), RARRAY_LEN(a), RARRAY_LEN(x)};
    MArray<double>
        mb(dim_vector(len[0], 1)),
        ma(dim_vector(len[1], 1)),
        mx(dim_vector(len[2], 1)),
        my;
    double* p[3] = {(double*)mb.data(), (double*)ma.data(), (double*)mx.data()};
    const VALUE* pr[3] = {
        RARRAY_CONST_PTR_TRANSIENT(b),
        RARRAY_CONST_PTR_TRANSIENT(a),
        RARRAY_CONST_PTR_TRANSIENT(x)
    };
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