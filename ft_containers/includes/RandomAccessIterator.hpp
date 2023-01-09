/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomAccessIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:35:50 by albaur            #+#    #+#             */
/*   Updated: 2023/01/09 15:41:34 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP
# include "utils.hpp"

namespace ft
{
	template <class T, bool use_const = false>
	class IteratorWrapper
	{
		protected:
			T	*val;

		public:
			typedef typename enable_const<use_const, T&, const T&>::type	reference;
			typedef typename enable_const<use_const, T*, const T*>::type	pointer;
			typedef ptrdiff_t												difference_type;
			typedef T														value_type;
			typedef size_t													size_type;

			IteratorWrapper(void) : val(NULL)
			{

			}

			IteratorWrapper(T *src) : val(src)
			{

			}

			IteratorWrapper(const IteratorWrapper<T, false> &src) : val(NULL)
			{
				*this = src;
			}

			virtual ~IteratorWrapper(void)
			{

			}

			IteratorWrapper			&operator=(IteratorWrapper const &rhs)
			{
				if (this != &rhs)
					val = rhs.val;
				return (*this);
			}

			bool							operator==(IteratorWrapper const &rhs) const
			{
				return (val == rhs.val);
			}

			bool							operator!=(IteratorWrapper const &rhs) const
			{
				return (val != rhs.val);
			}

			bool							operator>(IteratorWrapper const &rhs) const
			{
				return (val > rhs.val);
			}

			bool							operator>=(IteratorWrapper const &rhs) const
			{
				return (val >= rhs.val);
			}

			bool							operator<(IteratorWrapper const &rhs) const
			{
				return (val < rhs.val);
			}

			bool							operator<=(IteratorWrapper const &rhs) const
			{
				return (val <= rhs.val);
			}

			IteratorWrapper<T> 		&operator++(void)
			{
				val++;
				return (*this);
			}

			IteratorWrapper<T> 		operator++(int)
			{
				IteratorWrapper<T>	tmp(*this);
				val++;
				return (tmp);
			}

			IteratorWrapper<T> 		&operator--(void)
			{
				val--;
				return (*this);
			}

			IteratorWrapper<T> 		operator--(int)
			{
				IteratorWrapper<T>	tmp(*this);
				val--;
				return (tmp);
			}

			IteratorWrapper<T>			operator+(difference_type n) const
			{
				return IteratorWrapper(val + n);
			}

			friend IteratorWrapper<T>	operator+(difference_type n, IteratorWrapper const &rhs)
			{
				return (rhs.operator+(n));
			}

			IteratorWrapper<T>			operator-(difference_type n) const
			{
				return (IteratorWrapper(val + n));
			}

			difference_type					operator-(IteratorWrapper const &n) const
			{
				return (val - n.val);
			}

			IteratorWrapper<T>			&operator+=(difference_type n)
			{
				val += n;
				return (*this);
			}

			IteratorWrapper<T>			&operator-=(difference_type n)
			{
				val -= n;
				return (*this);
			}

			reference						operator*(void) const
			{
				return (*val);
			}

			pointer							operator->(void) const
			{
				return (val);
			}

			reference						operator[](size_type n) const
			{
				return (val[n]);
			}
	};

	template <class T>
	class iter : public IteratorWrapper<T>
			{
				public:
					typedef T										iterator_type;
					typedef iterator_traits<T>						iter_traits;
					typedef typename iter_traits::reference			reference;
					typedef typename iter_traits::pointer			pointer;
					typedef typename iter_traits::difference_type	difference_type;
					typedef typename iter_traits::value_type		value_type;
					typedef size_t									size_type;
				
					iter(void) : IteratorWrapper<T>(NULL)
					{

					}

					iter(T *src) : IteratorWrapper<T>(src)
					{

					}

					iter(iter const &src) : IteratorWrapper<T>(src)
					{

					}

					virtual ~iter(void)
					{

					}

					reference		operator*(void) const
					{
						return (*this->val);
					}

					pointer			operator->(void) const
					{
						return (this->val);
					}

					reference		operator[](size_type n) const
					{
						return (this->val[n]);
					}

					iter			&operator+=(difference_type n)
					{
						this->val += n;
						return (*this);
					}

					iter			&operator-=(difference_type n)
					{
						this->val -= n;
						return (*this);
					}

					difference_type	operator-(const IteratorWrapper<value_type> &n) const
					{
						return (IteratorWrapper<T>::operator-(n));
					}

					iter			operator-(difference_type n) const
					{
						return (IteratorWrapper<T>::operator-(n));
					}

					iter			operator+(difference_type n) const
					{
						return (IteratorWrapper<T>::operator+(n));
					}

					friend iter		operator+(difference_type n, const iter &rhs)
					{
						return (rhs.operator+(n));
					};

					iter		&operator++(void)
					{
						IteratorWrapper<T>::operator++();
						return (*this);
					}

					iter		operator++(int)
					{
						return (IteratorWrapper<T>::operator++(0));
					}

					iter		&operator--(void)
					{
						IteratorWrapper<T>::operator--();
						return (*this);
					}

					iter		operator--(int)
					{
						return (IteratorWrapper<T>::operator--(0));
					}

				private:
					typedef IteratorWrapper<T>	type;
					iter(const IteratorWrapper<T> &src);
			};

			template <class T>
			class const_iter : public IteratorWrapper<T>
			{
				public:
					typedef T										iterator_type;
					typedef iterator_traits<T>						iter_traits;
					typedef typename iter_traits::reference			reference;
					typedef typename iter_traits::pointer			pointer;
					typedef typename iter_traits::difference_type	difference_type;
					typedef typename iter_traits::value_type		value_type;
					typedef size_t									size_type;
				
					const_iter(void) : IteratorWrapper<T>()
					{

					}

					const_iter(T *src) : IteratorWrapper<T>(src)
					{

					}

					const_iter(const IteratorWrapper<value_type> &src) : IteratorWrapper<T>(src)
					{

					}

					virtual ~const_iter(void)
					{

					}

					reference			operator*(void) const
					{
						return *(this->val);
					}

					pointer				operator->(void) const
					{
						return (this->val);
					}

					reference			operator[](size_type n) const
					{
						return (this->val[n]);
					}

					const_iter			&operator+=(difference_type n)\
					{
						this->val += n;
						return (*this);
					}

					const_iter			&operator-=(difference_type n)
					{
						this->val -= n;
						return (*this);
					}

					difference_type		operator-(const IteratorWrapper<value_type> &n) const
					{
						return (IteratorWrapper<T>::operator-(n));
					}
					
					const_iter			operator-(difference_type n) const
					{
						return (IteratorWrapper<T>::operator-(n));
					}

					const_iter			operator+(difference_type n) const
					{
						return (IteratorWrapper<T>::operator+(n));
					}
					
					friend const_iter	operator+(difference_type n, const const_iter &rhs)
					{
						return (rhs.operator+(n));
					}

					const_iter		&operator++(void)
					{
						IteratorWrapper<T>::operator++();
						return (*this);
					}

					const_iter		operator++(int)
					{
						return (IteratorWrapper<T>::operator++(0));
					}

					const_iter		&operator--(void)
					{
						IteratorWrapper<T>::operator--();
						return (*this);
					}
					
					const_iter		operator--(int)
					{
						return (IteratorWrapper<T>::operator--(0));
					}
			};
}

#endif