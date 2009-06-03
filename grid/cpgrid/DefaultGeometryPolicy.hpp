//===========================================================================
//
// File: DefaultGeometryPolicy.hpp
//
// Created: Tue Jun  2 16:23:01 2009
//
// Author(s): Atgeirr F Rasmussen <atgeirr@sintef.no>
//            B�rd Skaflestad     <bard.skaflestad@sintef.no>
//
// $Date$
//
// $Revision$
//
//===========================================================================

/*
Copyright 2009 SINTEF ICT, Applied Mathematics.
Copyright 2009 Statoil ASA.

This file is part of The Open Reservoir Simulator Project (OpenRS).

OpenRS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OpenRS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OpenRS.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OPENRS_DEFAULTGEOMETRYPOLICY_HEADER
#define OPENRS_DEFAULTGEOMETRYPOLICY_HEADER

#include <boost/mpl/if.hpp>
#include "Geometry.hpp"

namespace Dune
{
    namespace cpgrid
    {

	struct GetCellGeom;
	struct GetFaceGeom;

	class DefaultGeometryPolicy
	{
	public:
	    template <int codim>
	    const std::vector< cpgrid::Geometry<3 - codim, 3> >& geomVector() const
	    {
		typedef typename boost::mpl::if_c<codim == 0, GetCellGeom, GetFaceGeom>::type selector;
		return selector::value(*this);
	    }
	private:
	    friend class GetCellGeom;
	    friend class GetFaceGeom;
	    std::vector< cpgrid::Geometry<3, 3> > cell_geom_;
	    std::vector< cpgrid::Geometry<2, 3> > face_geom_;
	};


	struct GetCellGeom
	{
	    static const std::vector< cpgrid::Geometry<3, 3> >& value(const DefaultGeometryPolicy& geom)
	    {
		return geom.cell_geom_;
	    }
	};


	struct GetFaceGeom
	{
	    static const std::vector< cpgrid::Geometry<2, 3> >& value(const DefaultGeometryPolicy& geom)
	    {
		return geom.face_geom_;
	    }
	};



    } // namespace cpgrid
} // namespace Dune


#endif // OPENRS_DEFAULTGEOMETRYPOLICY_HEADER
