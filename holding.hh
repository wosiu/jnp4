#ifndef HOLDING_HH
#define HOLDING_HH

#include <iostream>

/* ========================== BEZPIECZNA ARYTMETYKA ========================= */

constexpr unsigned int safe_substract( unsigned int a, unsigned int b )
{
    return ( a > b ) ? ( a - b ) : 0;
}

constexpr unsigned int safe_divide( unsigned int a, unsigned int b )
{
    return ( b != 0 ) ? ( a / b ) : 0;
}

/* ========================== COMPANY ======================================= */

template <unsigned int _acc, unsigned int _hun, unsigned int _exc>
struct Company
{
	static constexpr unsigned int acc = _acc;
	static constexpr unsigned int hsh = _hun;
	static constexpr unsigned int exo = _exc;
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
	typedef Company<safe_substract( C1::acc, C2::acc ),
					safe_substract( C1::hsh, C2::hsh ),
					safe_substract( C1::exo, C2::exo )> type;
};

template<class C1, int n> struct multiply_comp
{
	static_assert( n >= 0, "Negative multiplication value." );
	typedef Company<C1::acc * n,
					C1::hsh * n,
					C1::exo * n> type;
};


template<class C1, unsigned int n> struct split_comp
{
	static_assert( n >= 0, "Negative split value." );
	typedef Company<safe_divide( C1::acc, n ),
					safe_divide( C1::hsh, n ),
					safe_divide( C1::exo, n )> type;
};

template<class C> struct additive_expand_comp
{
	typedef Company<C::acc + 1,
					C::hsh + 1,
					C::exo + 1> type;
};

template<class C> struct additive_rollup_comp
{
	typedef Company<safe_substract( C::acc, 1 ),
					safe_substract( C::hsh, 1 ),
					safe_substract( C::exo, 1 )> type;
};



/* ========================== GROUPA ======================================== */

template<class C> class Group
{
	unsigned int acc_val;
	unsigned int hsh_val;
	unsigned int exo_val;
	unsigned int companies_no;

	// pomocnicze:
	// zwracaja sumaryczna wartosc danych przedsiebiorstw wewnatrz grupy
	unsigned int get_total_acc_val() const;
	unsigned int get_total_hs_val() const;
	unsigned int get_total_exo_val() const;
	// zwracaja sumaryczna ilosc danych przedsiebiorstw wewnatrz grupy
	unsigned int get_acc_no() const;
	unsigned int get_hs_no() const;
	unsigned int get_exo_no() const;

public:
	Group();
	Group( unsigned int k );
	Group( Group<C> const& );

	unsigned int get_size() const;
	void set_acc_val( unsigned int );
	void set_hs_val( unsigned int );
	void set_exo_val( unsigned int );
	unsigned int get_acc_val() const;
	unsigned int get_hs_val() const;
	unsigned int get_exo_val() const;

	unsigned int get_value() const;

	typedef C company_type;
	static const company_type company;

	Group<C>& operator+=( const Group<C>& );
	Group<C> operator+( const Group<C>& ) const;
	Group<C>& operator-=( const Group<C>& );
	Group<C> operator-( const Group<C>& ) const;

	Group operator*( unsigned int ) const;
	Group operator/( unsigned int ) const;
	Group<C>& operator*=( unsigned int );
	Group& operator/=( unsigned int );


	template<class C1, class C2>
	friend bool operator==( Group<C1> a, Group<C2> b );

	template<class C1, class C2>
	friend bool operator!=( Group<C1> a, Group<C2> b );

	template<class C1, class C2>
	friend bool operator<=( Group<C1> a, Group<C2> b );

	template<class C1, class C2>
	friend bool operator>=( Group<C1> a, Group<C2> b );

	template<class C1, class C2>
	friend bool operator<( Group<C1> a, Group<C2> b );

	template<class C1, class C2>
	friend bool operator>( Group<C1> a, Group<C2> b );


	template<class C1>
	friend std::ostream& operator<<( std::ostream& os, Group<C1> const& a );
};

template<class C>
unsigned int Group<C>::get_total_acc_val() const
{
	return companies_no * acc_val * C::acc;
}

template<class C>
unsigned int Group<C>::get_total_hs_val() const
{
	return companies_no * hsh_val * C::hsh;
}

template<class C>
unsigned int Group<C>::get_total_exo_val() const
{
	return companies_no * exo_val * C::exo;
}

template<class C>
Group<C>::Group( unsigned int k ) :
	acc_val( 15 ),
	hsh_val( 150 ),
	exo_val( 50 ),
	companies_no( k )
{}

template<class C>
Group<C>::Group() :
	Group( 1 )
{}

template<class C>
Group<C>::Group( Group<C> const &g ) :
	acc_val( g.get_acc_val() ),
	hsh_val( g.get_hs_val() ),
	exo_val( g.get_exo_val() ),
	companies_no( g.get_size() )
{}

// TODO ? Przekminic czy settery i gettery nie zrobic inline w klasie
// ( zeby siedzialy wewnatrz klasy i wtedy nawet w jednej linii je robic
// sporo linii by odeszlo..
// tak, to jest dobry pomysl - Accek

template<class C>
unsigned int Group<C>::get_size() const
{
    return companies_no;
}

template<class C>
void Group<C>::set_acc_val( unsigned int n )
{
    acc_val = n;
}

template<class C>
void Group<C>::set_hs_val( unsigned int n )
{
    hsh_val = n;
}

template<class C>
void Group<C>::set_exo_val( unsigned int n )
{
    exo_val = n;
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
unsigned int Group<C>::get_acc_no() const
{
	return companies_no * company.acc;
}

template<class C>
unsigned int Group<C>::get_hs_no() const
{
	return companies_no * company.hsh;
}

template<class C>
unsigned int Group<C>::get_exo_no() const
{
	return companies_no * company.exo;
}

template<class C>
unsigned int Group<C>::get_value() const
{
	return ( acc_val * company.acc + hsh_val * company.hsh
			+ exo_val * company.exo ) * companies_no;
}

template<class C>
Group<C>& Group<C>::operator+=( const Group<C>& g2 )
{
	// nowa ilosc firm
	unsigned int n_companies_no = companies_no + g2.companies_no;
	// nowe sumaryczne ilosci kantorów, sklepów myśliwskich, biur rachunkowych
	// w calym przedsiebiorstwie
	unsigned int n_acc_total_no = C::acc * n_companies_no;
	unsigned int n_hsh_total_no = C::hsh * n_companies_no;
	unsigned int n_exo_total_no = C::exo * n_companies_no;

	acc_val = safe_divide( get_total_acc_val() + g2.get_total_acc_val(),
								n_acc_total_no );

	hsh_val = safe_divide( get_total_hs_val() + g2.get_total_hs_val(),
								n_hsh_total_no );

	exo_val = safe_divide( get_total_exo_val() + g2.get_total_exo_val(),
								n_exo_total_no );

	companies_no = n_companies_no;

	return *this;
}

template<class C>
Group<C> Group<C>::operator+( const Group<C>& g2 ) const
{
	Group<C> result( *this );
	result += g2;
	return result;
}

template<class C>
Group<C>& Group<C>::operator-=( const Group<C>& g2 )
{
	unsigned int a, b;
	unsigned int n_companies_no = safe_substract( companies_no, g2.companies_no );
	unsigned int n_acc_total_no = C::acc * n_companies_no;
	unsigned int n_hsh_total_no = C::hsh * n_companies_no;
	unsigned int n_exo_total_no = C::exo * n_companies_no;

	a = get_total_acc_val();
	b = g2.get_total_acc_val();
	acc_val = safe_divide( safe_substract( a, b ), n_acc_total_no );

	a = get_total_hs_val();
	b = g2.get_total_hs_val();
	hsh_val = safe_divide( safe_substract( a, b ), n_hsh_total_no );

	a = get_total_exo_val();
	b = g2.get_total_exo_val();
	exo_val = safe_divide( safe_substract( a, b ), n_exo_total_no );

	companies_no = n_companies_no;

	return *this;
}



template<class C>
Group<C> Group<C>::operator-( const Group<C>& g2 ) const
{
	Group<C> result( *this );
	result -= g2;
	return result;
}

template<class C>
Group<C>& Group<C>::operator*=( unsigned int n )
{
	//tresc: licznosc grupy rosnie n razy
	companies_no *= n;
	if ( n != 0 ) {
		//ale wartosc pojedynczego przedsiebiorstwa maleje n razy
		acc_val /= n;
		hsh_val /= n;
		exo_val /= n;
	} else {
		acc_val = hsh_val = exo_val = 0;
	}
	return *this;
}

template<class C>
Group<C> Group<C>::operator*( unsigned int n ) const
{
	Group<C> result( *this );
	result *= n;
	return result;
}

template<class C>
Group<C>& Group<C>::operator/=( unsigned int n )
{
	companies_no = safe_divide( companies_no, n );
	acc_val *= n;
	hsh_val *= n;
	exo_val *= n;
	return *this;
}

template<class C>
Group<C> Group<C>::operator/( unsigned int n ) const
{
	Group<C> result( *this );
	result /= n;
	return result;
}


/* ========================== PRZYJACIELE GRUPY ============================= */

template<class C1, class C2>
bool operator==( Group<C1> a, Group<C2> b )
{
	if ( typeid(C1) == typeid(C2) ) {
		return a.get_size() == b.get_size();
	}
	return a.get_hs_no() == b.get_hs_no() && a.get_exo_no() == b.get_exo_no();
}

template<class C1, class C2>
bool operator!=( Group<C1> a, Group<C2> b )
{
	return !( a == b );
}


template<class C1, class C2>
bool operator<=( Group<C1> a, Group<C2> b )
{
	if ( typeid(C1) == typeid(C2) ) {
		return a.get_size() <= b.get_size();
	}
	return a.get_hs_no() <= b.get_hs_no() && a.get_exo_no() <= b.get_exo_no();
}

template<class C1, class C2>
bool operator>=( Group<C1> a, Group<C2> b )
{
	if ( typeid(C1) == typeid(C2) ) {
		return a.get_size() >= b.get_size();
	}
	return a.get_hs_no() >= b.get_hs_no() && a.get_exo_no() >= b.get_exo_no();
}

template<class C1, class C2>
bool operator<( Group<C1> a, Group<C2> b )
{
	// nowe ustalenie! (patrz komentarze forum)
	return a <= b && a != b;
}

template<class C1, class C2>
bool operator>( Group<C1> a, Group<C2> b )
{
	// j.w.
	return a >= b && a != b;
}


template<typename C>
std::ostream& operator<<( std::ostream &out, const Group<C> &rhs )
{
	out << "Number of companies: " << rhs.get_size()
		<< "; Value: " << rhs.get_value() << std::endl
		<< "Accountancies value: " << rhs.get_acc_val()
		<< ", Hunting shops value: " << rhs.get_hs_val()
		<< ", Exchange offices value: " << rhs.get_exo_val() << std::endl
		<< "Accountancies: " << C::acc
		<< ", Hunting shops: " << C::hsh
		<< ", Exchange offices: " << C::exo << std::endl;
	return out;
}


/* ========================== FUNKCJE GLOBALNE ============================== */

template<class C>
Group<typename additive_expand_comp<C>::type> const
additive_expand_group( Group<C> const &s1 )
{
	return Group< typename additive_expand_comp<C>::type >(s1.get_size());
}

template<class C>
Group<typename multiply_comp<C, 10>::type> const
multiplicative_expand_group( Group<C> const &s1 )
{
	return Group< typename multiply_comp<C, 10>::type >( s1.get_size() );
}

template<class C>
Group<typename additive_rollup_comp<C>::type> const
additive_rollup_group( Group<C> const &s1 )
{
	return Group< typename additive_rollup_comp<C>::type >( s1.get_size() );
}

template<class C>
Group<typename split_comp<C, 10>::type> const
multiplicative_rollup_group( Group<C> const &s1 )
{
	return Group< typename split_comp<C, 10>::type >( s1.get_size() );
}

template<class C1, class C2, class C3>
bool solve_auction( Group<C1> const &g1, Group<C2> const &g2,
				Group<C3> const &g3 )
{
	return ( g1 > g2 && g1 > g3 ) || ( g2 > g1 && g2 > g3 )
			|| ( g3 > g2 && g3 > g1 );
}
#endif
