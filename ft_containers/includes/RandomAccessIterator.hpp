/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomAccessIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:35:50 by albaur            #+#    #+#             */
/*   Updated: 2023/01/05 15:56:22 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP

namespace ft
{
	template <class T>
	class RandomAccessIterator
	{
		protected:
			T	*val;

		public:
			typedef T&			reference;
			typedef T*			pointer;
			typedef ptrdiff_t	difference_type;

			RandomAccessIterator(void) : val(NULL) {}
			RandomAccessIterator(T *src) : val(src) {}
			RandomAccessIterator(RandomAccessIterator const &src) : val(NULL) {*this = src;}
			virtual ~RandomAccessIterator(void) {}
			RandomAccessIterator			&operator=(RandomAccessIterator const &rhs) {if (this != &rhs) {val = rhs.val;} return (*this);};

			bool							operator==(RandomAccessIterator const &rhs) const {return (val == rhs.val);}
			bool							operator!=(RandomAccessIterator const &rhs) const {return (val != rhs.val);}
			bool							operator>(RandomAccessIterator const &rhs) const {return (val > rhs.val);}
			bool							operator>=(RandomAccessIterator const &rhs) const {return (val >= rhs.val);}
			bool							operator<(RandomAccessIterator const &rhs) const {return (val < rhs.val);}
			bool							operator<=(RandomAccessIterator const &rhs) const {return (val <= rhs.val);}
			RandomAccessIterator<T> 		&operator++(void) {val++; return (*this);}
			RandomAccessIterator<T> 		operator++(int) {RandomAccessIterator<T>	tmp(*this); val++; return (tmp);}
			RandomAccessIterator<T> 		&operator--(void) {val--; return (*this);}
			RandomAccessIterator<T> 		operator--(int) {RandomAccessIterator<T>	tmp(*this); val--; return (tmp);}
			RandomAccessIterator<T>			operator+(difference_type n) const {return RandomAccessIterator(val + n);}
			friend RandomAccessIterator<T>	operator+(difference_type n, RandomAccessIterator const &rhs) {return (rhs.operator+(n));}
			RandomAccessIterator<T>			operator-(difference_type n) const {return (RandomAccessIterator(val +n));}
			difference_type					operator-(RandomAccessIterator const &n) const {return (val - n.val);}
			RandomAccessIterator<T>			&operator+=(difference_type n) {return val += n; return (*this);}
			RandomAccessIterator<T>			&operator-=(difference_type n) {return val -= n; return (*this);}
			reference						operator*(void) const {return (*val);}
			pointer							operator->(void) const {return (val);}
			reference						operator[](difference_type n) const {return (val[n]);}
	};
}

#endif