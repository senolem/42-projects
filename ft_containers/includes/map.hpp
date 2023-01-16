/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:43:25 by albaur            #+#    #+#             */
/*   Updated: 2023/01/16 10:42:38 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_CLASS_HPP
# define MAP_CLASS_HPP
# include <functional>
# include <iostream>
# include "rb_tree.hpp"
# include "rb_iterator.hpp"
# include "vector_iterator.hpp"
# include "utils.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			class																value_compare;
			typedef Key															key_type;
			typedef T															mapped_type;
			typedef ft::pair<const Key, T>										value_type;
			typedef size_t														size_type;
			typedef ptrdiff_t													difference_type;
			typedef Compare														key_compare;
			typedef Allocator													allocator_type;
			typedef value_type													&reference;
			typedef const value_type											&const_reference;
			typedef typename Allocator::pointer									pointer;
			typedef typename Allocator::const_pointer							const_pointer;
			typedef node<value_type>											node_tree;
			typedef RBTree<value_type, value_compare, allocator_type>			rb_tree;
			
			typedef typename rb_tree::iterator									iterator;
			typedef typename rb_tree::const_iterator							const_iterator;
			typedef VectorReverseIterator<iterator>								reverse_iterator;
			typedef VectorReverseIterator<const_iterator>						const_reverse_iterator;
			
			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map;

				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					
					bool	operator()(const value_type &lhs, const value_type &rhs) const
					{
						return comp(lhs.first, rhs.first);
					}

				protected:
					Compare	comp;
					
					value_compare(Compare c) : comp(c)
					{
						
					}
			};

		private:
			rb_tree			_tree;
			key_compare		_key_compare;
			allocator_type	_allocator_type;

		public:
			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(comp, alloc), _key_compare(comp), _allocator_type(alloc)
			{

			}

			map(const map &other) : _tree(other._tree), _key_compare(other._key_compare), _allocator_type(_allocator_type)
			{

			}

			~map(void)
			{

			}
			
			map	&operator=(const map &other)
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
			iterator								begin(void)
			{
				return (_tree.begin());
			}

			const_iterator							begin(void) const
			{
				return (_tree.begin());
			}

			iterator								end(void)
			{
				return (_tree.end());
			}

			const_iterator							end(void) const
			{
				return (_tree.end());
			}

			reverse_iterator						rbegin(void)
			{
				return (_tree.rbegin());
			}

			const_reverse_iterator					rbegin(void) const
			{
				return (_tree.rbegin());
			}

			reverse_iterator						rend(void)
			{
				return (_tree.rend());
			}

			const_reverse_iterator					rend(void) const
			{
				return (_tree.rend());
			}

			// capacity
			bool									empty(void) const
			{
				return (_tree.empty());
			}

			size_type								size(void) const
			{
				return (_tree.size());
			}

			size_type								max_size(void) const
			{
				return (_tree.max_size());
			}

			// element access
			T										&at(const Key &key)
			{
				node_tree	*tmp = _tree.search(_tree._root, key);
				if (tmp)
					return (tmp->data().second);
			}

			const T									&at(const Key &key) const
			{
				return (const_cast<mapped_type>(at(key)));
			}

			T										&operator[](const Key &key)
			{
				return (*(insert(ft::make_pair(key, mapped_type())).first)).second;
			}

			// modifiers
			void									clear(void)
			{
				_tree.clear(_tree._root);
			}

			pair<iterator, bool>					insert(const value_type &value)
			{
				return (_tree.insert(value));
			}

			iterator								insert(iterator pos, const value_type &value)
			{
				return (_tree.insert(pos, value));
			}

			template <class InputIt>
			void									insert(InputIt first, InputIt last);
			void									erase(iterator pos);
			void									erase(iterator first, iterator last);
			size_type								erase(const Key &key);
			void									swap(map &other);


			// lookup
			size_type								count(const Key &key) const;
			iterator								find(const Key &key);
			const_iterator							find(const Key &key) const;
			pair<iterator, iterator>				equal_range(const Key &key);
			pair<const_iterator, const_iterator>	equal_range(const Key &key) const;
			iterator								lower_bound(const Key &key);
			const_iterator							lower_bound(const Key &key) const;
			iterator								upper_bound(const Key &key);
			const_iterator							upper_bound(const Key &key) const;

			// observers
			key_compare								key_comp(void) const;
			value_compare							value_comp(void) const;

			// allocator
			allocator_type							get_allocator(void) const;
	};

	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		else
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		if (lhs == rhs)
			return (false);
		else
			return (true);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void	swap(map<Key, T, Compare, Alloc> &lhs, map<Key, T, Compare, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}
}

#endif