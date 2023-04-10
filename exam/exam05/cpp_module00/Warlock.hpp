#ifndef WARLOCK_HPP
# define WARLOCK_HPP
# include <string>
# include <iostream>

class Warlock
{
	public:
		Warlock(const std::string &name, const std::string &title);
		~Warlock(void);

		const std::string	&getName(void) const;
		const std::string	&getTitle(void) const;
		void				setTitle(const std::string &src);
		void				introduce(void) const;

	private:
		Warlock(void);
		Warlock(const Warlock &src);
		Warlock &operator=(const Warlock &src);

		std::string	name;
		std::string	title;
};

#endif
