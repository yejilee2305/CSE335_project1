/**
 * @file XMLParser.cpp
 * @author Yeji Lee
 */
 
#include "XMLParser.h"

// Parse a configuration file
bool XMLParser::ParseConfiguration(const wxString& filename)
{
    wxXmlDocument xmlDoc;
    if (!xmlDoc.Load(filename)) {
        std::cerr << "Failed to load XML file: " << filename.ToStdString() << std::endl;
        return false;
    }

    wxXmlNode* root = xmlDoc.GetRoot();
    if (!root) {
        std::cerr << "No root node in XML file: " << filename.ToStdString() << std::endl;
        return false;
    }

    wxXmlNode* child = root->GetChildren();
    while (child) {
        wxString name = child->GetName();
        if (name == "Setting") {
            wxString key = child->GetAttribute("name", "");
            wxString value = child->GetNodeContent();
            std::cout << "Configuration Setting: " << key.ToStdString() << " = " << value.ToStdString() << std::endl;
        }
        child = child->GetNext();
    }

    return true;
}

// Parse level data from XML
bool XMLParser::ParseLevel(const wxString& filename)
{
    wxXmlDocument xmlDoc;
    if (!xmlDoc.Load(filename)) {
        std::cerr << "Failed to load level XML file: " << filename.ToStdString() << std::endl;
        return false;
    }

    wxXmlNode* root = xmlDoc.GetRoot();
    if (!root) {
        std::cerr << "No root node in XML file: " << filename.ToStdString() << std::endl;
        return false;
    }

    wxXmlNode* child = root->GetChildren();
    while (child) {
        wxString name = child->GetName();
        if (name == "Object") {
            wxString objectType = child->GetAttribute("type", "");
            wxString x = child->GetAttribute("x", "0");
            wxString y = child->GetAttribute("y", "0");

            std::cout << "Object Type: " << objectType.ToStdString()
                      << ", X: " << x.ToStdString()
                      << ", Y: " << y.ToStdString() << std::endl;
        }
        child = child->GetNext();
    }

    return true;
}

// Parse objects and spawn them from XML
bool XMLParser::ParseObjects(const wxString& filename)
{
    wxXmlDocument xmlDoc;
    if (!xmlDoc.Load(filename)) {
        std::cerr << "Failed to load objects XML file: " << filename.ToStdString() << std::endl;
        return false;
    }

    wxXmlNode* root = xmlDoc.GetRoot();
    if (!root) {
        std::cerr << "No root node in XML file: " << filename.ToStdString() << std::endl;
        return false;
    }

    wxXmlNode* child = root->GetChildren();
    while (child) {
        wxString name = child->GetName();
        if (name == "Object") {
            wxString objectName = child->GetAttribute("name", "");
            std::cout << "Loading object: " << objectName.ToStdString() << std::endl;
        }
        child = child->GetNext();
    }

    return true;
}