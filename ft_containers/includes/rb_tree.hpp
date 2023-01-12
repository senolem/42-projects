/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:59:56 by albaur            #+#    #+#             */
/*   Updated: 2023/01/12 21:44:11 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
# define RB_TREE_HPP
# include "utils.hpp"
# include "rb_iterator.hpp"
# include "vector_iterator.hpp"

namespace ft
{
	template <class T, class Compare = ft::less<T>, class Allocator = std::allocator<T> >
	class RBTree
	{
		public:
			typedef T														value_type;
			typedef Compare													key_compare;
			typedef Allocator												allocator_type;
			typedef size_t													size_type;
			typedef ptrdiff_t												difference_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef RBIterator<value_type>									iterator;
			typedef RBIterator<const value_type>							const_iterator;
			typedef VectorReverseIterator<iterator>							reverse_iterator;
			typedef VectorReverseIterator<const_iterator>					const_reverse_iterator;
			typedef node<value_type>										node_tree;
			typedef typename Allocator::template rebind<node_tree>::other	node_allocator;
		
		private:
			Compare			_comp;
			node_tree		*_node_ptr;
			node_tree		*_root;
			node_allocator	_node_allocator;
			allocator_type	_allocator_type;
			size_type		_size;

		public:
			explicit RBTree(const key_compare &comp, const allocator_type &alloc) : _comp(comp), _node_ptr(newNullNode()), _allocator_type(alloc), _size(0)
			{

			}

			RBTree(RBTree const &other) : _comp(other.comp), _node_ptr(newNullNode()), _root(_node_ptr), _allocator_type(other._allocator_type)
			{

			}

			RBTree &operator=(const RBTree &other)
			{
				if (this != &other)
				{
					clear(_root);
					insert(other.begin(), other.end());
					_comp = other._comp;
					_allocator_type = other._allocator_type;
				}
				return (*this);
			}

			~RBTree(void)
			{

			}

			node_tree	*newNullNode(void)
			{
				node_tree	*tmp = _node_allocator(1);
				tmp->color = BLACK;
				tmp->leaf = 0;
				tmp->parent = NULL;
				tmp->left = _node_ptr;
				tmp->right = _node_ptr;
				return (tmp);
			}

			allocator_type	get_allocator(void) const
			{
				return (_allocator_type);
			}

			node_tree	*search(node_tree *search, const value_type &value) const
			{
				while (search != _node_ptr)
				{
					if (_comp(value, search->value))
						search = search->left;
					else if (_comp(search->value, value))
						search = search->right;
					else
						return (search);
				}
				return (NULL);
			}

			ft::pair<iterator, bool>	insert(value_type const &value)
			{
				node_tree	*node;
				node_tree	*parent;

				if (_root == _node_ptr)
				{
					_root = newTreeNode(value, _node_ptr, 2);
					_root->color = BLACK;
					return (ft::make_pair(iterator(_root), true));
				}
				while (node != _node_ptr)
				{
					parent = node;
					if (_comp(value, node->value))
						node = node->left;
					else if (_comp(node->value, value))
						node = node->right;
					else
						return (ft::make_pair(iterator(node), false));
				}
				node = newTreeNode(value, parent, 1);
				if (_comp(value, parent->value))
					parent->left = node;
				else
					parent->right = node;
				node->left->parent = node;
				node->right->parent = node;
				rebalanceTree(node, 0);
				return (ft::make_pair(iterator(node), true));
			}

			iterator	insert(iterator iter, const value_type &value)
			{
				(void)iter;
				return (insert(value).first);
			}

			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last)
			{
				while (first != last)
					insert(*first++);
			}

			size_type	erase(value_type const &value)
			{
				node_tree *tmp = search(_root, value);
				if (tmp)
				{
					erase(tmp);
					return (1);
				}
				return (0);
			}

			void	erase(node_tree *node)
			{
				node_tree	*to_search = node;
				node_tree	*tmp;
				int			color = node->color;

				if (node->left == _node_ptr)
				{
					tmp = node->right;
					insertNode(node, node->right);
				}
				else if (node->right == _node_ptr)
				{
					tmp = node->left;
					insertNode(node, node->left);
				}
				else
				{
					to_search = getMin(node->right);
					color = to_search->color;
					if (to_search->right)
						tmp = to_search->right;
					if (to_search->parent == node)
						tmp->parent = to_search;
					else
					{
						insertNode(to_search, to_search->right);
						to_search->right = node->right;
						to_search->right->parent = to_search;
					}
					insertNode(node, to_search);
					to_search->left = tmp->left;
					to_search->left->parent = to_search;
					to_search->color = node->color;
				}
				if (color == BLACK)
					rebalanceTree(tmp, 1);
				deleteNode(node);
			}

			void	erase(iterator first, iterator last)
			{
				while (first != last)
					erase(*first++);
			}

			iterator	find(const value_type &value) const
			{
				node_tree	*result = search(_root, value);
				if (result)
					return (iterator(result));
				return (iterator(getMax(_root)));
			}

			void	clear(node_tree *node)
			{
				if (node && node->leaf)
				{
					clear(node->left);
					clear(node->right);
					deleteNode(node);
				}
				_root = _node_ptr;
			}

			bool	empty(void) const
			{
				return (_size == 0);
			}

			size_type	size(void) const
			{
				return (_size);
			}

			size_type	max_size(void) const
			{
				return (_node_allocator.max_size());
			}

			iterator	begin(void)
			{
				node_tree	*node;

				if (_root == _node_ptr)
					return (iterator(_node_ptr));
				node = _root;
				while (node && node->left != _node_ptr)
					node = node->left;
				return (iterator(node));			
			}

			const_iterator	begin(void) const
			{
				node_tree	*node;

				if (_root == _node_ptr)
					return (const_iterator(_node_ptr));
				node = _root;
				while (node && node->left != _node_ptr)
					node = node->left;
				return (const_iterator(node));			
			}

			iterator	end(void)
			{
				return (iterator(getMax(_root)));
			}

			const_iterator	end(void) const
			{
				return (const_iterator(getMax(_root)));
			}

			reverse_iterator	rbegin(void)
			{
				return (reverse_iterator(end()));
			}

			const_reverse_iterator	rbegin(void) const
			{
				return (const_iterator(end()));
			}

			reverse_iterator	rend(void)
			{
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator	rend(void) const
			{
				return (const_iterator(begin()));
			}

			void	swap(RBTree &x)
			{
				_comp = x._comp;
				_node_ptr = x._node_ptr;
				_root = x._root;
				_node_allocator = x._node_allocator;
				_allocator_type = x._allocator_type;
				_size = x._size;
			}
	};
}


#endif