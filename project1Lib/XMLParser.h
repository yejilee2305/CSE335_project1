/**
 * @file XMLParser.h
 * @author Yeji Lee
 *
 *
 */
 
#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <wx/wx.h>
#include <wx/xml/xml.h>
#include <iostream>


class XMLParser {
private:

public:
 bool ParseConfiguration(const wxString& filename);

 bool ParseLevel(const wxString& filename);

 bool ParseObjects(const wxString& filename);

};



#endif //XMLPARSER_H
