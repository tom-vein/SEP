#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <fstream>
#include "Color.h"
#include "Game.h"

class FileManager
{
private:
  class FileHeader
  {
  private:
    std::string magic_number_ = "TRAX";
    Color active_player_;
    signed char min_x_;
    signed char min_y_;
    signed char max_x_;
    signed char max_y_;
  public:
    FileHeader(Color active_player, signed char min_x,
               signed char min_y, signed char max_x,
               signed char max_y);
    std::ostream& write(std::ostream& os);
  };

  class Field
  {
  private:
    TileTypeLib::Shape shape_;
    Color top_color_;
  public:
    Field(TileTypeLib::Shape shape, Color top_color);
    std::ostream& write(std::ostream& os);
  };

  std::string file_name_;

  FileHeader createFileHeader(const GameLib::Game& game) const;
  Field createField(TilePtr tile) const;
  void initFields(std::vector<Field>& fields, const GameLib::Game& game) const;
public:
  void setFileName(const std::string& file_name);
  void writeToFile(const GameLib::Game& game) const;
};

#endif // FILEMANAGER_H
