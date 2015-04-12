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

bool GameBoard::canTileBePlaced(TilePtr tile_to_add)
  throw(InvalidPositionException)
{
  bool hasTouchingTiles = false;
  bool canBePlaced = false;
  TilePtr touching_tile = nullptr;
  const Position position_to_add = tile_to_add->getPosition();

  if(game_.getTileByPosition(position_to_add) != nullptr)
    throw NotEmptyException("Invalid coordinates - field not empty\n", position_to_add);

  // Top
  touching_tile = game_.getTileByPosition(position_to_add, 0, -1);
  if(touching_tile != nullptr)
  {
    hasTouchingTiles = true;
    if(touching_tile->getColorAtEdge(TileTypeLib::Edge::TOP) != tile_to_add->getColorAtEdge(TileTypeLib::Edge::BOTTOM))
      throw ColorMismatchException("Invalid move - connected line colors mismatch\n", position_to_add);

   canBePlaced = true;
  }

  // Bottom
  touching_tile = game_.getTileByPosition(position_to_add, 0, 1);
  if(touching_tile != nullptr)
  {
    hasTouchingTiles = true;
    if(touching_tile->getColorAtEdge(TileTypeLib::Edge::BOTTOM) != tile_to_add->getColorAtEdge(TileTypeLib::Edge::TOP))
      throw ColorMismatchException("Invalid move - connected line colors mismatch\n", position_to_add);

    canBePlaced = true;
  }

  // Left
  touching_tile = game_.getTileByPosition(position_to_add, -1, 0);
  if(touching_tile != nullptr)
  {
    hasTouchingTiles = true;
    if(touching_tile->getColorAtEdge(TileTypeLib::Edge::RIGHT) != tile_to_add->getColorAtEdge(TileTypeLib::Edge::LEFT))
      throw ColorMismatchException("Invalid move - connected line colors mismatch\n", position_to_add);

    canBePlaced = true;
  }

  // Right
  touching_tile = game_.getTileByPosition(position_to_add, 1, 0);
  if(touching_tile != nullptr)
  {
    hasTouchingTiles = true;
    if(touching_tile->getColorAtEdge(TileTypeLib::Edge::LEFT) != tile_to_add->getColorAtEdge(TileTypeLib::Edge::RIGHT))
      throw ColorMismatchException("Invalid move - connected line colors mismatch\n", position_to_add);

    canBePlaced = true;
  }


  return canBePlaced && hasTouchingTiles;
}

void GameBoard::doTurn(TilePtr tile)
  throw(InvalidPositionException)
{
  try
  {
    canTileBePlaced(tile);
    tried_insertions_.push_back(tile);
    game_.addTile(tile);
    doForcedPlay(tile);
  }
  //TODO catch and treat exceptions different
  catch (std::exception &e)
  {
    for(std::vector<TilePtr>::iterator it = tried_insertions_.begin(); it != tried_insertions_.end(); it++)
    {
      game_.removeTile(*it);
    }
  }

}

void GameBoard::doForcedPlay(TilePtr last_placed)
{

}
