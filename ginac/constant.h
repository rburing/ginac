/** @file constant.h
 *
 *  Interface to GiNaC's constant types and some special constants. */

/*
 *  GiNaC Copyright (C) 1999-2003 Johannes Gutenberg University Mainz, Germany
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __GINAC_CONSTANT_H__
#define __GINAC_CONSTANT_H__

#include <string>
#include "basic.h"
#include "ex.h"

namespace GiNaC {

typedef ex (*evalffunctype)();
	
/** This class holds constants, symbols with specific numerical value. Each
 *  object of this class must either provide their own function to evaluate it
 *  to class numeric or provide the constant as a numeric (if it's an exact
 *  number). */
class constant : public basic
{
	GINAC_DECLARE_REGISTERED_CLASS(constant, basic)
	
// member functions
	
	// other constructors
public:
	constant(const std::string & initname, evalffunctype efun = 0, const std::string & texname = std::string());
	constant(const std::string & initname, const numeric & initnumber, const std::string & texname = std::string());
	
	// functions overriding virtual functions from base classes
public:
	ex evalf(int level = 0) const;
protected:
	ex derivative(const symbol & s) const;
	bool is_equal_same_type(const basic & other) const;
	unsigned calchash() const;
	
	// non-virtual functions in this class
protected:
	void do_print(const print_context & c, unsigned level) const;
	void do_print_tree(const print_tree & c, unsigned level) const;
	void do_print_latex(const print_latex & c, unsigned level) const;
	void do_print_python_repr(const print_python_repr & c, unsigned level) const;

// member variables
private:
	std::string name;     ///< printname of this constant
	std::string TeX_name; ///< LaTeX name
	evalffunctype ef;
	ex number;            ///< numerical value this constant evalf()s to
	unsigned serial;      ///< unique serial number for comparison
	static unsigned next_serial;
};

extern const constant Pi;
extern const constant Catalan;
extern const constant Euler;

// utility functions

/** Specialization of is_exactly_a<constant>(obj) for constant objects. */
template<> inline bool is_exactly_a<constant>(const basic & obj)
{
	return obj.tinfo()==TINFO_constant;
}

} // namespace GiNaC

#endif // ndef __GINAC_CONSTANT_H__
