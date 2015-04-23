//------------------------------------------------------------------------------
// FileManager.h
//
// Group: Group 11599, study assistant Philipp Hafner
//
// Authors:
// Thomas Hoedl 1430320
// Mario Theuermann 1430751
// Stephan Valentan 1430529
//------------------------------------------------------------------------------
//


#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <fstream>
#include "Color.h"
#include "Game.h"

//----------------------------------------------------------------------------
// Filemanager Class
// Is responsible of filehandling and writing the gameboard to a file
//
class FileManager
{
private:
  //TODO; header OK?
  //----------------------------------------------------------------------------
  // Fileheader Class
  // encapsulates the header of the file which should be written
  //
  class FileHeader
  {
  private:
    //--------------------------------------------------------------------------
    // magic number for the trax-gameboard-file
    //
    std::string magic_number_ = "TRAX";

    //--------------------------------------------------------------------------
    // Color of player which is next to play
    //
    Color active_player_;

    //--------------------------------------------------------------------------
    // smallest index in x direction
    //
    signed char min_x_;

    //--------------------------------------------------------------------------
    // smallest index in y direction
    //
    signed char min_y_;

    //--------------------------------------------------------------------------
    // biggest index in x direction
    //
    signed char max_x_;

    //--------------------------------------------------------------------------
    // biggest index in y direction
    //
    signed char max_y_;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    FileHeader(Color active_player, signed char min_x,
               signed char min_y, signed char max_x,
               signed char max_y);

    //--------------------------------------------------------------------------
    // Method to retrieve outputstream for fileheader
    // @param os outputstream in which the header should be written
    // @return reference of the used outputstream
    //
    std::ostream& write(std::ostream& os);
  };

  //--------------------------------------------------------------------------
  // Class for encapsulating one field of the gameboard
  //
  class Field
  {
  private:
    //--------------------------------------------------------------------------
    // the shape of the tile laying on this field
    //
    TileTypeLib::Shape shape_;

    //--------------------------------------------------------------------------
    // the color which is on the upper edge of the tile
    //
    Color top_color_;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    Field(TileTypeLib::Shape shape, Color top_color);

    //--------------------------------------------------------------------------
    // Method to retrieve outputstream for this tile
    // @param os outputstream in which the filed should be written
    // @return reference of the used outputstream
    //
    std::ostream& write(std::ostream& os);
  };

  //--------------------------------------------------------------------------
  // Name of the file which should be written
  //
  std::string file_name_;

  //--------------------------------------------------------------------------
  // Method for creating the Fileheader
  // @param game const Reference to instance of game
  // @return instance of a fileheader-class
  //
  FileHeader createFileHeader(const GameLib::Game& game) const;

  //--------------------------------------------------------------------------
  // Method for creating a field
  // @param tile std::shared_ptr<Tile> of the tile of which a Field should be
  // created
  // @return instance of a field-class
  //
  Field createField(TilePtr tile) const;

  //--------------------------------------------------------------------------
  // Method which creates a vector containing all fields which should be
  // written and initializes them
  // @param fields Reference to empty vector of Field, which gets filled in this
  //  method
  // @param game const Reference to instance of game
  //
  void initFields(std::vector<Field>& fields, const GameLib::Game& game) const;

public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  FileManager(const std::string& file_name);

  //--------------------------------------------------------------------------
  // Method used for writing the gameboard to a file
  // @param game Reference to the game-instance
  // @param file_name const Reference to the file-name
  //
  void writeToFile(const GameLib::Game& game,
                   const std::string& file_name = "") const;
};

#endif // FILEMANAGER_H
