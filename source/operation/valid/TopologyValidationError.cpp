/**********************************************************************
 * $Id$
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.refractions.net
 *
 * Copyright (C) 2001-2002 Vivid Solutions Inc.
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation. 
 * See the COPYING file for more information.
 *
 **********************************************************************
 * $Log$
 * Revision 1.7  2004/09/13 10:14:47  strk
 * Added INVALID_COORDINATE code num and error message.
 *
 * Revision 1.6  2004/07/02 13:28:29  strk
 * Fixed all #include lines to reflect headers layout change.
 * Added client application build tips in README.
 *
 * Revision 1.5  2003/11/07 01:23:43  pramsey
 * Add standard CVS headers licence notices and copyrights to all cpp and h
 * files.
 *
 *
 **********************************************************************/


#include <geos/opValid.h>
#include <stdio.h>

namespace geos {

string TopologyValidationError::errMsg[]={
    "Topology Validation Error",
    "Repeated Point",
    "Hole lies outside shell",
    "Holes are nested",
    "Interior is disconnected",
    "Self-intersection",
    "Ring Self-intersection",
    "Nested shells",
    "Duplicate Rings",
    "Too few points in geometry component",
    "Invalid Coordinate"
};

TopologyValidationError::TopologyValidationError(int newErrorType,Coordinate newPt) {
	errorType=newErrorType;
	pt=newPt;
}

TopologyValidationError::TopologyValidationError(int newErrorType) {
	TopologyValidationError(errorType,Coordinate::getNull());
}

int TopologyValidationError::getErrorType() {
	return errorType;
}

Coordinate& TopologyValidationError::getCoordinate(){
	return pt;
}

string TopologyValidationError::getMessage(){
	return errMsg[errorType];
}

string TopologyValidationError::toString() {
	return (getMessage().append(" at or near point")).append(pt.toString());
}
}

