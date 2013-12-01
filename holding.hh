#ifndef HOLDING_HH
#define HOLDING_HH

#include <iostream>

// CODE RLZ!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Jak sie nie podoba to wypierdalać
// ..albo mi powiedzieć, zebym wiedzial ze robimy inaczej.
// 1.: taby nie spacje
// 2.:
// if/for/while_(_warunek_){
//     blabla; (nawet jesli jedna instrukcja)
// }
// void funckja(_argumenty_)
// {
//     blabla;
// }
// TODO :* zniszczyc powyzsze

/* ========================== COMPANY ======================================= */

template <unsigned int _acc, unsigned int _hun, unsigned int _exc>
struct Company
{
	//TODO przekminic constexpr zamaist const
	static const unsigned int acc = _acc;
	static const unsigned int hsh = _hun;
	static const unsigned int exo = _exc;
};

typedef Company<1, 0, 0> Accountancy;
typedef Company<0, 1, 0> Hunting_shop;
typedef Company<0, 0, 1> Exchange_office;

template<class C1, class C2> struct add_comp
{
	typedef Company<C1::acc + C2::acc,
					C1::hsh + C2::hsh,
					C1::exo + C2::exo> type;
};

template<class C1, class C2> struct remove_comp
{
	typedef Company<( C1::acc > C2::acc ) ? ( C1::acc - C2::acc ) : 0,
					( C1::hsh > C2::hsh ) ? ( C1::hsh - C2::hsh ) : 0,
					( C1::exo > C2::exo ) ? ( C1::exo - C2::exo ) : 0> type;
};

template<class C1, int n> struct multiply_comp
{
	static_assert( n >= 0, "Negative multiplication value." );
	typedef Company<C1::acc * n,
					C1::hsh * n,
					C1::exo * n> type;
};


template<class C1, int n> struct split_comp
{
	static_assert( n >= 0, "Negative split value." );
	typedef Company<( n == 0 ) ? 0 : ( C1::acc / n ),
					( n == 0 ) ? 0 : ( C1::hsh / n ),
					( n == 0 ) ? 0 : ( C1::exo / n )> type;
};

template<class C> struct additive_expand_comp
{
	typedef Company<C::acc + 1,
					C::hsh + 1,
					C::exo + 1> type;
};

template<class C> struct additive_rollup_comp
{
	typedef Company<( C::acc > 1 ) ? ( C::acc - 1 ) : 0,
					( C::hsh > 1 ) ? ( C::hsh - 1 ) : 0,
					( C::exo > 1 ) ? ( C::exo - 1 ) : 0> type;
};



/* ========================== GROUP ======================================= */

template<class C> class Group
{
	unsigned int acc_val;
	unsigned int hsh_val;
	unsigned int exo_val;
	unsigned int companies_no;

public:
	Group();
	Group( unsigned int k );
	Group( Group<C> const& );

	unsigned int get_size() const;
	void set_acc_val( unsigned int i );
	void set_hs_val( unsigned int i );
	void set_exo_val( unsigned int i );
	unsigned int get_acc_val() const;
	unsigned int get_hs_val() const;
	unsigned int get_exo_val() const;

	unsigned int get_value() const;

	typedef C company_type;
	static const company_type company;
/*
	// TODO doimplementowac
	template<class C1, class C2>
	friend Group<add_comp<C1,C2> > operator+( Group<C1> &a, Group<C2> &b );

	template<class C1, class C2>
	friend Group<remove_comp<C1,C2> > operator-( Group<C1> &a, Group<C2> &b );

	template<class C1, class C2>
	friend Group<add_comp<C1,C2> >& operator+=( Group<C1> &a, Group<C2> &b );

	template<class C1, class C2>
	friend Group<remove_comp<C1,C2> >& operator-=( Group<C1> &a, Group<C2> &b );

	//TODO a moze by tak void..
	Group operator*( int i );
	Group operator/( int i );
	Group& operator*=( int i );
	Group& operator/=( int i );

	template<class C1, class C2>
	friend bool operator==( Group<C1> a, Group<C2> b );

	template<class C1, class C2>
	friend bool operator!=( Group<C1> a, Group<C2> b );

	template<class C1, class C2>
	friend bool operator<( Group<C1> a, Group<C2> b );

	template<class C1, class C2>
	friend bool operator>( Group<C1> a, Group<C2> b );

	template<class C1, class C2>
	friend bool operator<=( Group<C1> a, Group<C2> b );

	template<class C1, class C2>
	friend bool operator>=( Group<C1> a, Group<C2> b );

	template<class C1>
	friend std::ostream& operator<<( std::ostream& os, Group<C1> const& a );
*/
};

template<class C>
Group<C>::Group( unsigned int k ) :
	acc_val( 50 ),
	hsh_val( 150 ),
	exo_val( 15 ),
	companies_no( k )
{}

template<class C>
Group<C>::Group() :
	Group( 1 )
{}

template<class C>
Group<C>::Group(Group<C> const &g) :
	acc_val( g.get_acc_val() ),
	hsh_val( g.get_hs_val() ),
	exo_val( g.get_exo_val() ),
	companies_no( g.get_size() )
{}

template<class C>
unsigned int Group<C>::get_size() const
{
    return companies_no;
}

template<class C>
void Group<C>::set_acc_val( unsigned int i )
{
    acc_val = i;
}

template<class C>
void Group<C>::set_hs_val( unsigned int i )
{
    hsh_val = i;
}

template<class C>
void Group<C>::set_exo_val( unsigned int i )
{
    exo_val = i;
}

template<class C>
unsigned int Group<C>::get_acc_val() const
{
	return acc_val;
}

template<class C>
unsigned int Group<C>::get_hs_val() const
{
	return hsh_val;
}

template<class C>
unsigned int Group<C>::get_exo_val() const
{
	return exo_val;
}

template<class C>
unsigned int Group<C>::get_value() const
{
	return ( acc_val * company.acc + hsh_val * company.hsh
			+ exo_val * company.exo ) * companies_no;
}



/* ========================== FUNKCJE GLOBALNE ============================== */
/*
//TODO :*
template<class C>
Group<typename additive_expand_comp<C>::type> const
additive_expand_group(Group<C> const &s1);

template<class C>
Group<typename multiply_comp<C, 10>::type> const
multiplicative_expand_group(Group<C> const &s1);

template<class C>
Group<typename additive_rollup_comp<C>::type> const
additive_rollup_group(Group<C> const &s1);

template<class C>
Group<typename split_comp<C, 10>::type> const
multiplicative_rollup_group(Group<C> const &s1);

template<class C1, class C2, class C3>
bool
solve_auction(Group<C1> const &g1, Group<C2> const &g2, Group<C3> const &g3);
*/


#endif
