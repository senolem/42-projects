/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 09:55:57 by albaur            #+#    #+#             */
/*   Updated: 2023/01/17 21:14:06 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_ITERATOR_HPP
# define RB_ITERATOR_HPP
# include <memory>

namespace ft
{
	enum	color
	{
		RED = 0,
		BLACK
	};


	template <class T>
	struct node
	{
		typedef T	value_type;
		value_type	data;
		bool		color;
		int			leaf;
		node		*parent;
		node		*left;
		node		*right;

		node(void) : data(NULL), parent(NULL), left(NULL), right(NULL), color(0)
		{

		}

		node(T const &data, node *parent, int leaf) : data(data), parent(parent), left(NULL), right(NULL), color(0), leaf(leaf)
		{

		}

		node(node const &other) : data(other.data), parent(other.parent), left(other.left), right(other.right), color(other.color), leaf(other.leaf)
		{

		}

		node &operator=(node const &other)
		{
			if (this != &other)
			{
				this->data = other.data;
				this->color = other.color;
				this->leaf = other.leaf;
				this->parent = other.parent;
				this->left = other.left;
				this->right = other.right;
			}
			return (*this);
		}

		~node(void)
		{

		}
	};
	
	template <class I>
	class RBIterator
	{
		public:
			typedef I								value_type;
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef node<value_type>				tree_node;
			typedef node<const value_type>			const_tree_node;
			typedef ptrdiff_t						difference_type;
			typedef I&								reference;
			typedef const I&						const_reference;
			typedef I*								pointer;
			typedef const I*						const_pointer;
			
			typedef RBIterator<I>					iterator;
			typedef RBIterator<const I>			const_iterator;

		private:
			tree_node	*node;
		
		public:
			RBIterator(void) : node(NULL)
			{

			}

			RBIterator(tree_node *current) : node(current)
			{

			}

			RBIterator(RBIterator const &other) : node(other.base())
			{

			}

			RBIterator	&operator=(RBIterator const &other)
			{
				if (this != &other)
					node = other.base();
				return (*this);
			}

			operator	const_iterator(void) const
			{
				return (const_iterator(reinterpret_cast<const_tree_node *>(node)));
			}

			tree_node	*base(void) const
			{
				return (node);
			}

			reference	operator*(void)
			{
				return (node->data);
			}

			const_reference	operator*(void) const
			{
				return (node->data);
			}

			pointer	operator->(void) const
			{
				return &(node->data);
			}

			RBIterator	&operator++(void)
			{
				if (!node->leaf)
					return (*this);
				if (node && node->right && node->right->leaf)
				{
					node = node->right;
					while (node && node->left && node->left->leaf)
						node = node->left;
				}
				else
				{
					tree_node	*tmp = node;
					node = node->parent;
					while (node && node->leaf && node->right == tmp)
					{
						tmp = node;
						node = node->parent;
					}
				}
				return (*this);
			}

			RBIterator	&operator--(void)
			{
				if (!node->leaf)
				{
					while (node->parent->leaf)
						node = node->parent;
					while (node->right->leaf)
						node = node->right;
					return (*this);
				}
				else if (node->left && node->left->leaf)
				{
					node = node->left;
					while (node->right && node->right->leaf)
						node = node->right;
				}
				else
				{
					tree_node	*tmp = node;
					node = node->parent;
					while (node && node->leaf && node->left == tmp)
					{
						tmp = node;
						node = node->parent;
					}
				}
				return (*this);
			}

			RBIterator	operator++(int)
			{
				RBIterator	tmp(*this);
				operator++();
				return (tmp);
			}

			RBIterator	operator--(int)
			{
				RBIterator	tmp(*this);
				operator--();
				return (tmp);
			}

			bool	operator==(RBIterator const &other)
			{
				return (node == other.node);
			}

			bool	operator!=(RBIterator const &other)
			{
				return (node != other.node);
			}

			bool	operator>(RBIterator const &other)
			{
				return (node > other.node);
			}

			bool	operator>=(RBIterator const &other)
			{
				return (node >= other.node);
			}

			bool	operator<(RBIterator const &other)
			{
				return (node < other.node);
			}

			bool	operator<=(RBIterator const &other)
			{
				return (node <= other.node);
			}
	};
}

#endif