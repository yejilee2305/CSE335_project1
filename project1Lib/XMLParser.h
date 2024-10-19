/**
 * @file XMLParser.h
 * @author Yeji Lee
 * @author Nicolas Roberts
 *
 * File for XMLParser class.
 */
 
#ifndef XMLPARSER_H
#define XMLPARSER_H

class Game;

/**
 * Base class for XMLParser.
 */
class XMLParser {
private:
    /// The game the level will be loaded into
    Game* mGame;

public:
    XMLParser(Game *game);

    /// Default constructor (disabled)
    XMLParser() = delete;

    /// Copy constructor (disabled)
    XMLParser(const XMLParser&) = delete;

    /// Assignment operator
    void operator=(const XMLParser&) = delete;

    void Load(const wxString &filename);

    void XmlItems(wxXmlNode *node);
};



#endif //XMLPARSER_H
