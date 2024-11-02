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
 * @class XMLParser
 * @brief A parser that loads game levels and items from an XML file.
 *
 * @details The XMLParser class reads XML files to initialize and load game configurations and level data. This includes
 * reading attributes for items like sensors, conveyors, products, and various in-game elements, then adding them
 * to the associated Game instance.
 */
class XMLParser {
private:
    /// The game the level will be loaded into
    Game* mGame;

    int mProductCounter = 0;

public:
    /**
 * @brief Constructs an XMLParser instance for a given game.
 *
 * @param game A pointer to the Game object that the XMLParser will load data into.
 */
    XMLParser(Game *game);

    /// Default constructor (disabled)
    XMLParser() = delete;

    /// Copy constructor (disabled)
    XMLParser(const XMLParser&) = delete;

    /// Assignment operator
    void operator=(const XMLParser&) = delete;

    /**
 * @brief Loads the game configuration from an XML file.
 *
 * @param filename The path to the XML file to be loaded.
 *
 * @details This method parses the XML file specified by `filename` and loads all game elements and configurations
 * into the Game instance associated with the parser.
 */
    void Load(const wxString &filename);

    /**
 * @brief Parses XML nodes to create game items and add them to the game.
 *
 * @param node Pointer to the root XML node that contains game item elements.
 *
 * @details The method processes each child node to create and configure game items such as sensors, conveyors,
 * products, and scoreboards, then adds each to the Game instance.
 */
    void XmlItems(wxXmlNode *node);
};



#endif //XMLPARSER_H
