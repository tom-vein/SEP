#include "GameBoard.h"

GameBoard::GameBoard(const GameLib::Game& game, const std::string& file_name) :
  game_(game)
{
  if(!file_name.empty())
  {
    file_manager_.setFileName(file_name);
    should_write_to_file_ = true;
  }
}

void GameBoard::startGame()
{

}

//Depricated!
//bool GameBoard::canTileBePlaced(TilePtr tile_to_add)
//  throw(InvalidPositionException)
//{
//    //TODO Umbau auf game_.getTouchingTiles()!

//  bool hasTouchingTiles = false;
//  bool canBePlaced = false;
//  TilePtr touching_tile = nullptr;
//  const Position position_to_add = tile_to_add->getPosition();

//  if(game_.getTileByPosition(position_to_add) != nullptr)
//    throw NotEmptyException("Invalid coordinates - field not empty\n", position_to_add);

//  // Top
//  touching_tile = game_.getTileByPosition(position_to_add, 0, -1);
//  if(touching_tile != nullptr)
//  {
//    hasTouchingTiles = true;
//    if(touching_tile->getColorAtEdge(TileTypeLib::Edge::TOP) != tile_to_add->getColorAtEdge(TileTypeLib::Edge::BOTTOM))
//      throw ColorMismatchException("Invalid move - connected line colors mismatch\n", position_to_add);

//   canBePlaced = true;
//  }

//  // Bottom
//  touching_tile = game_.getTileByPosition(position_to_add, 0, 1);
//  if(touching_tile != nullptr)
//  {
//    hasTouchingTiles = true;
//    if(touching_tile->getColorAtEdge(TileTypeLib::Edge::BOTTOM) != tile_to_add->getColorAtEdge(TileTypeLib::Edge::TOP))
//      throw ColorMismatchException("Invalid move - connected line colors mismatch\n", position_to_add);

//    canBePlaced = true;
//  }

//  // Left
//  touching_tile = game_.getTileByPosition(position_to_add, -1, 0);
//  if(touching_tile != nullptr)
//  {
//    hasTouchingTiles = true;
//    if(touching_tile->getColorAtEdge(TileTypeLib::Edge::RIGHT) != tile_to_add->getColorAtEdge(TileTypeLib::Edge::LEFT))
//      throw ColorMismatchException("Invalid move - connected line colors mismatch\n", position_to_add);

//    canBePlaced = true;
//  }

//  // Right
//  touching_tile = game_.getTileByPosition(position_to_add, 1, 0);
//  if(touching_tile != nullptr)
//  {
//    hasTouchingTiles = true;
//    if(touching_tile->getColorAtEdge(TileTypeLib::Edge::LEFT) != tile_to_add->getColorAtEdge(TileTypeLib::Edge::RIGHT))
//      throw ColorMismatchException("Invalid move - connected line colors mismatch\n", position_to_add);

//    canBePlaced = true;
//  }


//  return canBePlaced && hasTouchingTiles;
//}

void GameBoard::doTurn(TilePtr tile_to_add)
  throw(InvalidPositionException)
{
  try
  {
    // Hole alle touching tiles
    std::map<TileTypeLib::Edge, TilePtr> touching_tiles = game_.getTouchingTiles(tile_to_add->getPosition());
    // Teste ob hier platziert werden kann
    canTileBePlaced(touching_tiles, tile_to_add);

    // Speichere zwischen (falls später was passiert)
    tried_insertions_.push_back(tile_to_add);

    // Zum Spielfeld hinzufügen
    game_.addTile(tile_to_add);

    // Checken ob weitere tiles platziert werden sollen / müssen
    doForcedPlay(tile_to_add);
  }
  //TODO catch and treat exceptions different
  catch (MessageException &e)
  {
    for(std::vector<TilePtr>::iterator it = tried_insertions_.begin(); it != tried_insertions_.end(); it++)
    {
      game_.removeTile(*it);
    }
    tried_insertions_.clear();
    throw(e);
  }
  tried_insertions_.clear();

}

void GameBoard::doForcedPlay(TilePtr last_placed)
{
  // Get all empty positions around the last placed tile
  std::vector<Position> empty_positions = game_.getEmptyPositionsAround(last_placed->getPosition());

  // for all empty positions
  for(std::vector<Position>::iterator it = empty_positions.begin(); it != empty_positions.end(); it++)
  {
    // Get all touching tiles of this position
    std::map<TileTypeLib::Edge,TilePtr> touching_tiles = game_.getTouchingTiles(*it);

    // If only the last_placed tile touches this position
    if(touching_tiles.size() < 2)
      continue;

    //TODO: not last_placed! try different tiles here
    // Check which tiletype could place and create a tile
    if(canTileBePlaced(touching_tiles, last_placed))
    {
      doTurn(last_placed);
    }


  }
}

bool GameBoard::canTileBePlaced(std::map<TileTypeLib::Edge, TilePtr> touching_tiles, TilePtr tile_to_check)
{
  // Wenn tile_to_check nachbarn hat
    if(touching_tiles.empty())
        //TODO right exception
        throw(InvalidPositionException("No touching tiles", tile_to_check->getPosition()));

    // Für jeden nachbarn
    for(std::map<TileTypeLib::Edge, TilePtr>::iterator it = touching_tiles.begin(); it != touching_tiles.end(); it++)
    {
        // Wenn Edges nicht zusammenpassen
        if(!checkTwoTiles(tile_to_check, it->second, it->first))
            //TODO right exception
            throw(ColorMismatchException("Color mismatch", tile_to_check->getPosition()));
    }
    return true;
}

bool GameBoard::checkTwoTiles(TilePtr tile_to_check, TilePtr other, TileTypeLib::Edge touching_edge_of_first_tile)
{
    switch(touching_edge_of_first_tile)
    {
        case TileTypeLib::Edge::BOTTOM:
        {
            if(tile_to_check->getColorAtEdge(TileTypeLib::Edge::BOTTOM) != other->getColorAtEdge(TileTypeLib::Edge::TOP))
                return false;
        }
        case TileTypeLib::Edge::LEFT:
        {
            if(tile_to_check->getColorAtEdge(TileTypeLib::Edge::LEFT) != other->getColorAtEdge(TileTypeLib::Edge::RIGHT))
                return false;
        }
    case TileTypeLib::Edge::TOP:
    {
        if(tile_to_check->getColorAtEdge(TileTypeLib::Edge::TOP) != other->getColorAtEdge(TileTypeLib::Edge::BOTTOM))
            return false;
    }
    case TileTypeLib::Edge::RIGHT:
    {
        if(tile_to_check->getColorAtEdge(TileTypeLib::Edge::RIGHT) != other->getColorAtEdge(TileTypeLib::Edge::LEFT))
            return false;
    }
    default:
        throw(MessageException("No such edge"));
    }
}
