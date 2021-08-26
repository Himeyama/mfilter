#ifndef M_FILTER_HPP
#define M_FILTER_HPP

template <typename T> MArray<T> filter (MArray<T>&, MArray<T>&, MArray<T>&, MArray<T>&, int dim = 0);
template <typename T> MArray<T> filter (MArray<T>&, MArray<T>&, MArray<T>&, int dim = -1);

#endif