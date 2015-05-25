//------------------------------------------------------------------------------
// FileManager.cpp
//
// Group: Group 11599, study assistant Philipp Hafner
//
// Authors:
// Thomas Hoedl 1430320
// Mario Theuermann 1430751
// Stephan Valentan 1430529
//------------------------------------------------------------------------------
//


#include "FileManager.h"

//------------------------------------------------------------------------------
FileManager::FileManager(const std::string& file_name) : file_name_(file_name)
{
}

//------------------------------------------------------------------------------
FileManager::FileHeader::FileHeader(Color active_player, signed char min_x,
                                    signed char min_y, signed char max_x,
                                    signed char max_y) :
  active_player_(active_player), min_x_(min_x), min_y_(min_y), max_x_(max_x),
  max_y_(max_y)
{
}

//------------------------------------------------------------------------------
FileManager::Field::Field(TileTypeLib::Shape shape, Color top_color) :
  shape_(shape),
  top_color_(top_color)
{
}

//------------------------------------------------------------------------------
void FileManager::writeToFile(const GameLib::Game& game,
                              const std::string& file_name) const
{
  std::string used_file_name;
  std::vector<Field> fields;
  std::string error_msg;

  if(game.getTileCount() == 0)
    throw NoTilesLeftException("Board is empty!");

  if(!file_name.empty())
    used_file_name = file_name;
  else
    used_file_name = file_name_;

  if(used_file_name.empty())
    throw NoFileNameException("Their has not been specified a file name");

  error_msg = std::string("Cannot write file ") + used_file_name;

  std::ofstream output_file(used_file_name, std::ios::binary);

  if(!output_file)
    throw FileWriteException(error_msg.c_str());

  FileHeader file_header = createFileHeader(game);
  initFields(fields, game);

  file_header.write(output_file);

  if(!output_file)
    throw FileWriteException(error_msg.c_str());

  for(Field field : fields)
  {
    field.write(output_file);

    if(!output_file)
      throw FileWriteException(error_msg.c_str());
  }

  output_file.close();
}

//------------------------------------------------------------------------------
FileManager::FileHeader FileManager::createFileHeader(
    const GameLib::Game& game) const
{
  Color active_player = game.getActivePlayer().getColor();
  signed char min_x = static_cast<signed char>(game.getMinXValue());
  signed char min_y = static_cast<signed char>(game.getMinYValue());
  signed char max_x = static_cast<signed char>(game.getMaxXValue());
  signed char max_y = static_cast<signed char>(game.getMaxYValue());

  return FileHeader(active_player, min_x, min_y, max_x, max_y);
}

void FileManager::initFields(std::vector<Field>& fields,
                             const GameLib::Game& game) const
{
  int min_x = game.getMinXValue();
  int min_y = game.getMinYValue();
  int max_x = game.getMaxXValue();
  int max_y = game.getMaxYValue();

  for(int j = min_y; j <= max_y; j++)
  {
    for(int i = min_x; i <= max_x; i++)
    {
      TilePtr tile = game.getTileByPosition(Position(i, j));
      fields.push_back(createField(tile));
    }
  }
}

//------------------------------------------------------------------------------
FileManager::Field FileManager::createField(TilePtr tile) const
{
  if(tile)
  {
    TileTypeLib::Shape shape = tile->getShape();
    Color top_color = tile->getColorAtEdge(TileTypeLib::Edge::TOP);
    return Field(shape, top_color);
  }

  return Field(TileTypeLib::Shape::NONE, Color::NONE);
}

//------------------------------------------------------------------------------
std::ostream& FileManager::FileHeader::write(std::ostream& os)
{
  os << magic_number_;
  os.write(reinterpret_cast<char*>(&active_player_), sizeof(active_player_));
  os << min_x_;
  os << min_y_;
  os << max_x_;
  os << max_y_;

  return os;
}

//------------------------------------------------------------------------------
std::ostream& FileManager::Field::write(std::ostream& os)
{
  os.write(reinterpret_cast<char*>(&shape_), sizeof(shape_));
  os.write(reinterpret_cast<char*>(&top_color_), sizeof(top_color_));

  return os;
}
