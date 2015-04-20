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
  std::vector<TileTypeLib::TileType> tile_types = TileTypeLib::TileType::getAllTileTypes();

  // for all empty positions
  for(std::vector<Position>::iterator it = empty_positions.begin(); it != empty_positions.end(); it++)
  {
    // Get all touching tiles of this position
    std::map<TileTypeLib::Edge,TilePtr> touching_tiles = game_.getTouchingTiles(*it);

    // If only the last_placed tile touches this position
    if(touching_tiles.size() < 2)
      continue;


    int counter = 0;
    TilePtr tile;
    TilePtr tile_to_try;

    for(std::vector<TileTypeLib::TileType>::iterator types_it = tile_types.begin(); types_it != tile_types.end(); types_it++)
    {
      tile_to_try.reset(new Tile(*types_it, *it));
      if(canTileBePlaced(touching_tiles, tile_to_try))
      {
        counter++;
        tile = tile_to_try;
      }
    }

    if(counter == 1)
      doTurn(tile);
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

const Player& GameBoard::WinnerChecker::determineWinner(
    const GameLib::Game& game) const
{
  const Player& active_player = game.getActivePlayer();
  const Player& paused_player = game.getPausedPlayer();

  if(hasPlayerWon(active_player, game))
    return active_player;

  if(hasPlayerWon(paused_player, game))
    return paused_player;

  throw NoPlayerWinsException("no player has won");
}

bool GameBoard::WinnerChecker::hasPlayerWon(const Player& player,
                                            const GameLib::Game& game) const
{
  std::vector<TilePtr> last_placed_tiles = game.getLastPlacedTiles();

  for(TilePtr tile : last_placed_tiles)
  {
    if(isLoop(player.getColor(), tile, nullptr, tile, game) ||
       doesLineWin(player.getColor(), tile, game))
      return true;
  }

  return false;
}

bool GameBoard::WinnerChecker::isLoop(Color player_color,
                                      TilePtr start_tile,
                                      TilePtr previous_tile,
                                      TilePtr current_tile,
                                      const GameLib::Game& game,
                                      bool start_of_recursion) const
{
  std::vector<TilePtr> next_tiles;

  next_tiles = determineNextTiles(player_color, previous_tile, current_tile,
                                  game);

  if(next_tiles.size() == 0)
    return false;

  if((next_tiles.size() == 2 && !start_of_recursion) ||
     next_tiles.size() > 2)
  {
    throw InappropriateNumberOfNextTilesException
        ("the number of next tiles is inappropriate here");
  }

  TilePtr next_tile = next_tiles.at(0);

  if(next_tile == start_tile)
    return true;

  return isLoop(player_color, start_tile, current_tile, next_tile, game, false);
}

bool GameBoard::WinnerChecker::doesLineWin(Color player_color,
                                           TilePtr start_tile,
                                           const GameLib::Game& game) const
{
  LineWinningCriteria line_winning_criteria;

  checkIfLineWins(player_color, nullptr, start_tile, game,
                  line_winning_criteria);

  return line_winning_criteria.allWinningCriteriaFulfilled(game);
}

void GameBoard::WinnerChecker::checkIfLineWins(Color player_color,
                                               TilePtr previous_tile,
                                               TilePtr current_tile,
                                               const GameLib::Game& game,
                                               LineWinningCriteria&
                                               line_winning_criteria,
                                               bool start_of_recursion)
const
{
  std::vector<TilePtr> next_tiles;
  line_winning_criteria.addXValue(current_tile->getPosition().getX());
  line_winning_criteria.addYValue(current_tile->getPosition().getY());

  next_tiles = determineNextTiles(player_color, previous_tile, current_tile,
                                  game);

  if((next_tiles.size() == 2 && !start_of_recursion) ||
     next_tiles.size() > 2)
  {
    throw InappropriateNumberOfNextTilesException
        ("the number of next tiles is inappropriate here");
  }

  if(next_tiles.size() == 0 || (next_tiles.size() == 1 && start_of_recursion))
    line_winning_criteria.analyseLineEnd(player_color, current_tile, game);

  for(TilePtr next_tile : next_tiles)
  {
    checkIfLineWins(player_color, current_tile, next_tile, game,
                    line_winning_criteria, false);
  }
}

std::vector<TilePtr> GameBoard::WinnerChecker::determineNextTiles(
    Color player_color,
    TilePtr previous_tile,
    TilePtr current_tile,
    const GameLib::Game& game)
const
{
  std::vector<TilePtr> next_tiles;
  std::map<TileTypeLib::Edge, TilePtr> touching_tiles =
      game.getTouchingTiles(current_tile->getPosition(), player_color);

  for(auto& touching_tile : touching_tiles)
  {
    TilePtr tile = touching_tile.second;

    if(tile != previous_tile)
      next_tiles.push_back(tile);
  }

  return next_tiles;
}

void GameBoard::WinnerChecker::LineWinningCriteria::analyseLineEnd(
    Color color, TilePtr tile, const GameLib::Game& game)
{
  LineDirection line_direction = LineDirection::NONE;

  try
  {
    line_direction = determineDirectionOfFreeEdge(color, tile, game);
  }
  catch(TooLessFreeEdgesException)
  {
    line_direction = LineDirection::NONE;
  }
  catch(TooManyFreeEdgesException)
  {
    line_direction = LineDirection::NONE;
  }
  catch(NoSuitableLineDirectionException)
  {
    line_direction = LineDirection::NONE;
  }

  if(direction_of_first_end_ != LineDirection::NONE &&
     direction_of_second_end_ != LineDirection::NONE)
  {
    throw BothLineDirectionAlreadySetException
        ("Both line directions has already been set");
  }

  if(direction_of_first_end_ == LineDirection::NONE &&
     line_direction != LineDirection::NONE)
  {
    direction_of_first_end_ = line_direction;
    position_of_first_end_ = tile->getPosition();
  }
  else if(direction_of_second_end_ == LineDirection::NONE &&
          line_direction != LineDirection::NONE)
  {
    direction_of_second_end_ = line_direction;
    position_of_second_end_ = tile->getPosition();
  }
}

GameBoard::WinnerChecker::LineWinningCriteria::LineDirection
GameBoard::WinnerChecker::LineWinningCriteria::
determineDirectionOfFreeEdge(Color color, TilePtr tile, const
                             GameLib::Game& game)
const
{
  std::map<TileTypeLib::Edge, Color> touching_colors =
      game.getTouchingColors(tile->getPosition());

  //Erasing all touching_colors that are not NONE
  //and are at an edge that has not the color color
  for(std::map<TileTypeLib::Edge, Color>::iterator it = touching_colors.end();
      it != touching_colors.begin(); it--)
  {
    TileTypeLib::Edge e = it->first;
    Color c = it->second;

    if(c != Color::NONE || tile->getColorAtEdge(e) != color)
      touching_colors.erase(it);
  }

  if(touching_colors.size() < 1)
    throw TooLessFreeEdgesException("here are too less free edges");

  if(touching_colors.size() > 1)
    throw TooManyFreeEdgesException("here are too many free edges");

  TileTypeLib::Edge edge = touching_colors.begin()->first;

  switch(edge)
  {
    case TileTypeLib::Edge::BOTTOM: return LineDirection::DOWN;
    case TileTypeLib::Edge::TOP: return LineDirection::UP;
    case TileTypeLib::Edge::LEFT: return LineDirection::LEFT;
    case TileTypeLib::Edge::RIGHT: return LineDirection::RIGHT;
    case TileTypeLib::Edge::NONE: break;
  }

  throw NoSuitableLineDirectionException("no suitable line direction found");
}

void GameBoard::WinnerChecker::LineWinningCriteria::addXValue(int x)
{
  x_values_of_line_.insert(x);
}

void GameBoard::WinnerChecker::LineWinningCriteria::addYValue(int y)
{
  y_values_of_line_.insert(y);
}

bool GameBoard::WinnerChecker::LineWinningCriteria::
allWinningCriteriaFulfilled(const GameLib::Game& game) const
{
  if(x_values_of_line_.size() >= MIN_LENGTH_OF_WINNING_LINE &&
     ((direction_of_first_end_ == LineDirection::RIGHT &&
       position_of_first_end_.getX() == game.getMaxXValue()) ||
      (direction_of_first_end_ == LineDirection::LEFT &&
       position_of_first_end_.getX() == game.getMinXValue())) &&
     ((direction_of_second_end_ == LineDirection::RIGHT &&
       position_of_second_end_.getX() == game.getMaxXValue()) ||
      (direction_of_second_end_ == LineDirection::LEFT &&
       position_of_second_end_.getX() == game.getMinXValue())) &&
     direction_of_first_end_ != direction_of_second_end_)
    return true;

  if(y_values_of_line_.size() >= MIN_LENGTH_OF_WINNING_LINE &&
     ((direction_of_first_end_ == LineDirection::DOWN &&
       position_of_first_end_.getY() == game.getMaxYValue()) ||
      (direction_of_first_end_ == LineDirection::UP &&
       position_of_first_end_.getY() == game.getMinYValue())) &&
     ((direction_of_second_end_ == LineDirection::DOWN &&
       position_of_second_end_.getY() == game.getMaxYValue()) ||
      (direction_of_second_end_ == LineDirection::UP &&
       position_of_second_end_.getY() == game.getMinYValue())) &&
     direction_of_first_end_ != direction_of_second_end_)
    return true;

  return false;
}
