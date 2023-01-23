/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:43:35 by albaur            #+#    #+#             */
/*   Updated: 2023/01/23 22:16:56 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP
# include <functional>
# include <iostream>
# include "rb_tree.hpp"
# include "rb_iterator.hpp"
# include "vector_iterator.hpp"
# include "utils.hpp"

namespace ft
{
	template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class set
	{
		public:
			typedef Key													key_type;
			typedef Key													value_type;
			typedef size_t												size_type;
			typedef ptrdiff_t											difference_type;
			typedef Compare												key_compare;
			typedef Compare												value_compare;
			typedef Allocator											allocator_type;
			typedef &value_type											reference;
			typedef const &value_type									const_reference;
			typedef typename Allocator::pointer							pointer;
			typedef typename Allocator::const_pointer					const_pointer;
			typedef RBTree<value_type, value_compare, allocator_type>	rb_tree;
			
			typedef typename rb_tree::iterator							iterator;
			typedef typename rb_tree::const_iterator					const_iterator;
			typedef reverse_iter<iterator>								reverse_iterator;
			typedef reverse_iter<const_iterator>						const_reverse_iterator;

			class value_compare
			{
				public:
					bool	operator()(const value_type &lhs, const value_type &rhs) const
					{
						return comp(lhs.first, rhs.first);
					}

				protected:
					Compare	comp;
					
					value_compare(key_compare c) : comp(c)
					{
						
					}
			};

			private:
			rb_tree			_tree;
			key_compare		_key_compare;
			allocator_type	_allocator_type;

			public:
				explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(comp, alloc), _key_compare(comp), _allocator_type(alloc)
				{

				}

				set(const set &other) : _tree(other._tree), _key_compare(other._key_compare), _allocator_type(other._allocator_type)
				{

				}

				~set(void)
				{

				}

				set	&operator=(const set &other)
				{
					if (this != &other)
					{
						_tree = other._tree;
						_key_compare = other._key_compare;
						_allocator_type = other._allocator_type;
					}
					return (*this);
				}

				template <class InputIt>
				map(InputIt first, InputIt last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(comp, alloc), _key_compare(comp)
				{
					_tree.insert(first, last);
				}

				// iterators
				iterator	begin(void)
				{
					return (_tree.begin());
				}

				const_iterator	begin(void) const
				{
					return (_tree.begin());
				}

				iterator	end(void)
				{
					return (_tree.end());
				}

				const_iterator	end(void) const
				{
					return (_tree.end());
				}

				reverse_iterator	rbegin(void)
				{
					return (_tree.rbegin());
				}

				const_reverse_iterator	rbegin(void) const
				{
					return (_tree.rbegin());
				}

				reverse_iterator	rend(void)
				{
					return (_tree.rend());
				}

				const_reverse_iterator	rend(void) const
				{
					return (_tree.rend());
				}

				// capacity
				bool	empty(void) const
				{
					return (_tree.empty());
				}

				size_type	size(void) const
				{
					return (_tree.size());
				}

				size_type	max_size(void) const
				{
					return (_tree.max_size());
				}

				// modifiers
				void	clear(void)
				{
					_tree.clear(_tree.get_root());
				}

				pair<iterator, bool>	insert(const value_type &value)
				{
					return (_tree.insert(value));
				}

				iterator	insert(iterator pos, const value_type &value)
				{
					return (_tree.insert(pos, value));
				}

				template <class InputIt>
				void	insert(InputIt first, InputIt last)
				{
					return (_tree.insert(first, last));
				}

				void	erase(iterator pos)
				{
					_tree.erase(pos.base());
				}

				void	erase(iterator first, iterator last)
				{
					_tree.erase(first, last);
				}

				size_type	erase(const Key &key)
				{
					return (_tree.erase(get_value_type(key)));
				}

				void	swap(map &other)
				{
					_tree.swap(other._tree);
				}

				// lookup
				size_type	count(const Key &key) const
				{
					if (_tree.search(_tree.get_root(), get_value_type(key)))
						return (1);
					else
						return (0);
				}

				iterator	find(const Key &key)
				{
					return (_tree.find(get_value_type(key)));
				}

				const_iterator	find(const Key &key) const
				{
					return (_tree.find(get_value_type(key)));
				}

				pair<iterator, iterator>	equal_range(const Key &key)
				{
					return (ft::make_pair(lower_bound(key), upper_bound(key)));
				}

				pair<const_iterator, const_iterator>	equal_range(const Key &key) const
				{
					return (ft::make_pair(lower_bound(key), upper_bound(key)));
				}

				iterator	lower_bound(const Key &key)
				{
					iterator	tmp = begin();
					iterator	tmp2 = end();

					while (tmp != tmp2)
					{
						if (!this->_key_compare(tmp->first, key))
							break ;
						++tmp;
					}
					return (tmp);
				}

				const_iterator	lower_bound(const Key &key) const
				{
					const_iterator	tmp = begin();
					const_iterator	tmp2 = end();

					while (tmp != tmp2)
					{
						if (!this->_key_compare(tmp->first, key))
							break ;
						++tmp;
					}
					return (tmp);
				}

				iterator	upper_bound(const Key &key)
				{
					iterator	tmp = begin();
					iterator	tmp2 = end();

					while (tmp != tmp2)
					{
						if (this->_key_compare(key, tmp->first))
							break ;
						++tmp;
					}
					return (tmp);
				}

				const_iterator	upper_bound(const Key &key) const
				{
					const_iterator	tmp = begin();
					const_iterator	tmp2 = end();

					while (tmp != tmp2)
					{
						if (this->_key_compare(key, tmp->first))
							break ;
						++tmp;
					}
					return (tmp);
				}

				// observers
				key_compare	key_comp(void) const
				{
					return (_key_compare);
				}

				value_compare	value_comp(void) const
				{
					return (value_compare(_key_compare));
				}

				// allocator
				allocator_type	get_allocator(void) const
				{
					return (_tree.get_allocator());
				}

			private:
				// key
				value_type	get_value_type(const Key &key) const
				{
					return (ft::make_pair(key, mapped_type()));
				}
	}
}

#endif