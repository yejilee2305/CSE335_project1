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

    void Load(const wxString &filename);
};



#endif //XMLPARSER_H
