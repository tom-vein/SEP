//------------------------------------------------------------------------------
// GameBoard.cpp
//
// Group: Group 11599, study assistant Philipp Hafner
//
// Authors:
// Thomas Hoedl 1430320
// Mario Theuermann 1430751
// Stephan Valentan 1430529
//------------------------------------------------------------------------------
//

#include "GameBoard.h"

//------------------------------------------------------------------------------
GameBoard::GameBoard(const GameLib::Game& game, const std::string& file_name) :
  game_(game), file_manager_(FileManager(file_name)), ai(*this)
{
  if(!file_name.empty())
    should_write_to_file_ = true;
  else
    should_write_to_file_ = false;
}

//------------------------------------------------------------------------------
void GameBoard::placeTile(TilePtr tile_to_add)
{

  game_.addTile(tile_to_add);

  // Save all insertions of this turn
  tried_insertions_.push_back(tile_to_add);
  doForcedPlay(tile_to_add);

  winner_ = result_checker_.determineWinner(game_);

  game_.tooglePlayer();

  if(should_write_to_file_)
    write();


  tried_insertions_.clear();
  game_.resetNumOfPlacedTilesInCurrentTurn();
}

//------------------------------------------------------------------------------
void GameBoard::doTurn(const Position& position, TileTypeLib::Shape shape)
{
  try
  {
    std::map<TileTypeLib::Edge, TilePtr> touching_tiles =
        game_.getTouchingTiles(position);

    TileTypeLib::TileType type_red =
        TileTypeLib::TileType::getTileType(shape, Color::RED);
    TileTypeLib::TileType type_white =
        TileTypeLib::TileType::getTileType(shape, Color::WHITE);

    TilePtr tile_to_add = nullptr;
    TilePtr tile_top_red = std::shared_ptr<Tile>(new Tile(type_red, position));
    TilePtr tile_top_white =
        std::shared_ptr<Tile>(new Tile(type_white, position));

    try
    {
      canTileBePlaced(touching_tiles, tile_top_red);
      tile_to_add = tile_top_red;
    }
    catch(ColorMismatchException& e)
    {
      //Nothing to to
    }

    if(!tile_to_add)
    {
      canTileBePlaced(touching_tiles, tile_top_white);
      tile_to_add = tile_top_white;
    }
    placeTile(tile_to_add);
  }

  catch (MessageException& e)
  {
    for(TilePtr tile : tried_insertions_)
    {
      game_.removeTile(tile);
    }
    tried_insertions_.clear();
    std::cout << e.what() << std::endl;
    game_.resetNumOfPlacedTilesInCurrentTurn();
  }
  catch (std::exception& e)
  {
    game_.resetNumOfPlacedTilesInCurrentTurn();
    throw;
  }
}

//------------------------------------------------------------------------------
void GameBoard::doForcedPlay(TilePtr last_placed)
{
  // Get all empty positions around the last placed tile
  std::vector<Position> empty_positions =
      game_.getEmptyPositionsAround(last_placed->getPosition());
  std::vector<TileTypeLib::TileType> all_tile_types =
      TileTypeLib::TileType::getAllTileTypes();

  // for all empty positions
  for(std::vector<Position>::iterator position_iterator =
      empty_positions.begin(); position_iterator != empty_positions.end();
      position_iterator++)
  {
    // Get all touching tiles of this position
    std::map<TileTypeLib::Edge,TilePtr> touching_tiles =
        game_.getTouchingTiles(*position_iterator);

    // If only the last_placed tile touches this position
    if(touching_tiles.size() < 2)
      continue;


    int number_of_placeable_tiles = 0;
    TilePtr placeable_tile;
    TilePtr tile_to_try;

    for(std::vector<TileTypeLib::TileType>::iterator types_iterator =
        all_tile_types.begin(); types_iterator != all_tile_types.end();
        types_iterator++)
    {
      tile_to_try.reset(new Tile(*types_iterator, *position_iterator));
      try
      {
        if(canTileBePlaced(touching_tiles, tile_to_try))
        {
          number_of_placeable_tiles++;
          placeable_tile = tile_to_try;
        }
      }
      catch(ColorMismatchException& ex)
      {
        //nothing to do
      }
      catch(InvalidPositionException& ex)
      {
        //nothing to do
      }
    }

    if(number_of_placeable_tiles == 1)
    {
      game_.addTile(placeable_tile);
      tried_insertions_.push_back(placeable_tile);
      doForcedPlay(placeable_tile);
    }
  }

}

//------------------------------------------------------------------------------
bool GameBoard::canTileBePlaced(
    std::map<TileTypeLib::Edge, TilePtr> touching_tiles, TilePtr tile_to_check)
const
{
  // If first tile not on (0,0)
  if(game_.getTileCount() == 0 && tile_to_check->getPosition() != Position(0,0))
    throw(InvalidPositionException("Invalid coordinates - "
                                   "first tile must be set on (0,0)",
                                   tile_to_check->getPosition()));

  if(game_.getTileByPosition(tile_to_check->getPosition()))
    throw(InvalidPositionException("Invalid coordinates - field not empty",
                                   tile_to_check->getPosition()));

  // If tile has touching tiles
  if(touching_tiles.empty() && game_.getTileCount() != 0)
    throw(InvalidPositionException("Invalid coordinates - "
                                   "field not connected to tile",
                                   tile_to_check->getPosition()));

  // For each touching tile
  for(std::map<TileTypeLib::Edge, TilePtr>::iterator touching_tile_iterator =
      touching_tiles.begin(); touching_tile_iterator != touching_tiles.end();
      touching_tile_iterator++)
  {
    if(!checkTwoTiles(tile_to_check, touching_tile_iterator->second,
                      touching_tile_iterator->first))
      throw(ColorMismatchException("Invalid move - "
                                   "connected line colors mismatch",
                                   tile_to_check->getPosition()));
  }

  std::vector<Position> empty_positions =
      game_.getEmptyPositionsAround(tile_to_check->getPosition());
  for(std::vector<Position>::iterator position_iterator =
      empty_positions.begin();
      position_iterator != empty_positions.end(); position_iterator++)
  {
    int counter_red_edges = 0;
    int counter_white_edges = 0;
    std::map<TileTypeLib::Edge, Color> touching_colors =
        game_.getTouchingColors(*position_iterator);

    TileTypeLib::Edge touching_edge =
        game_.getTouchingEdge(*position_iterator, tile_to_check->getPosition());

    touching_colors[touching_edge] = tile_to_check->getColorAtEdge(
                                       TileTypeLib::getOppositeEdge(
                                         touching_edge));

    for(std::map<TileTypeLib::Edge, Color>::iterator it_color =
        touching_colors.begin(); it_color != touching_colors.end(); it_color++)
    {
      if(it_color->second == Color::RED)
        counter_red_edges++;
      else if(it_color->second == Color::WHITE)
        counter_white_edges++;
    }
    if(counter_red_edges > 2 || counter_white_edges > 2)
      throw(InvalidPositionException("Invalid move - "
                                     "connected line colors mismatch",
                                     tile_to_check->getPosition()));
  }
  return true;
}



//------------------------------------------------------------------------------
bool GameBoard::checkTwoTiles(TilePtr tile_to_check, TilePtr other,
                              TileTypeLib::Edge touching_edge_of_tile_to_check)
const
{
  switch(touching_edge_of_tile_to_check)
  {

    case TileTypeLib::Edge::BOTTOM:
    {
      if(tile_to_check->getColorAtEdge(TileTypeLib::Edge::BOTTOM) !=
         other->getColorAtEdge(TileTypeLib::Edge::TOP))
        return false;
      return true;
    }
    case TileTypeLib::Edge::LEFT:
    {
      if(tile_to_check->getColorAtEdge(TileTypeLib::Edge::LEFT) !=
         other->getColorAtEdge(TileTypeLib::Edge::RIGHT))
        return false;
      return true;
    }
    case TileTypeLib::Edge::TOP:
    {
      if(tile_to_check->getColorAtEdge(TileTypeLib::Edge::TOP) !=
         other->getColorAtEdge(TileTypeLib::Edge::BOTTOM))
        return false;
      return true;
    }
    case TileTypeLib::Edge::RIGHT:
    {
      if(tile_to_check->getColorAtEdge(TileTypeLib::Edge::RIGHT) !=
         other->getColorAtEdge(TileTypeLib::Edge::LEFT))
        return false;
      return true;
    }
    default:
      throw(MessageException("No such edge"));
  }
}

//------------------------------------------------------------------------------
Color GameBoard::ResultChecker::determineWinner(const GameLib::Game& game) const
{
  const Player& active_player = game.getActivePlayer();
  const Player& paused_player = game.getPausedPlayer();

  if(hasPlayerWon(active_player, game))
    return active_player.getColor();

  if(hasPlayerWon(paused_player, game))
    return paused_player.getColor();

  return Color::NONE;
}

//------------------------------------------------------------------------------
bool GameBoard::ResultChecker::isDraw(const GameLib::Game& game) const
{
  return game.getTileCount() >= GameLib::Game::getMaxOfTiles();
}

//------------------------------------------------------------------------------
bool GameBoard::ResultChecker::hasPlayerWon(const Player& player,
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

//------------------------------------------------------------------------------
bool GameBoard::ResultChecker::isLoop(Color player_color,
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

//------------------------------------------------------------------------------
bool GameBoard::ResultChecker::doesLineWin(Color player_color,
                                           TilePtr start_tile,
                                           const GameLib::Game& game) const
{
  LineWinningCriteria line_winning_criteria;

  checkIfLineWins(player_color, nullptr, start_tile, game,
                  line_winning_criteria);

  return line_winning_criteria.allWinningCriteriaFulfilled(game);
}

//------------------------------------------------------------------------------
void GameBoard::ResultChecker::checkIfLineWins(Color player_color,
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

//------------------------------------------------------------------------------
std::vector<TilePtr> GameBoard::ResultChecker::determineNextTiles(
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

//------------------------------------------------------------------------------
void GameBoard::ResultChecker::LineWinningCriteria::analyseLineEnd(
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
//------------------------------------------------------------------------------
GameBoard::ResultChecker::LineWinningCriteria::LineDirection
GameBoard::ResultChecker::LineWinningCriteria::
determineDirectionOfFreeEdge(Color color, TilePtr tile, const
                             GameLib::Game& game)
const
{
  std::map<TileTypeLib::Edge, Color> touching_colors =
      game.getTouchingColors(tile->getPosition());

  //Erasing all touching_colors that are not NONE
  //and are at an edge that has not the color color
  std::map<TileTypeLib::Edge, Color>::iterator it = touching_colors.begin();
  while(it != touching_colors.end())
  {
    TileTypeLib::Edge e = it->first;
    Color c = it->second;

    if(c != Color::NONE || tile->getColorAtEdge(e) != color)
      it = touching_colors.erase(it);
    else
      it++;
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

//------------------------------------------------------------------------------
void GameBoard::ResultChecker::LineWinningCriteria::addXValue(int x)
{
  x_values_of_line_.insert(x);
}

//------------------------------------------------------------------------------
void GameBoard::ResultChecker::LineWinningCriteria::addYValue(int y)
{
  y_values_of_line_.insert(y);
}

//------------------------------------------------------------------------------
bool GameBoard::ResultChecker::LineWinningCriteria::
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

//------------------------------------------------------------------------------
bool GameBoard::isDraw() const
{
  return result_checker_.isDraw(game_);
}

//------------------------------------------------------------------------------
bool GameBoard::hasWinner() const
{
  return winner_ != Color::NONE;
}

//------------------------------------------------------------------------------
std::string GameBoard::getWinner() const
{
  if(winner_ == Color::RED)
    return "red";

  if(winner_ == Color::WHITE)
    return "white";

  return "no winner";
}

//------------------------------------------------------------------------------
void GameBoard::write(const std::string& file_name)
{
  try
  {
    file_manager_.writeToFile(game_, file_name);
  }
  catch(MessageException ex)
  {
    std::cout << ex.what() << std::endl;
  }
}

//------------------------------------------------------------------------------
TilePtr GameBoard::ArtificialIntelligence::determineNextTile(Color player)
{
  std::vector<TilePtr> edges = game_board_.game_.getAllEdges();
  std::vector<TilePtr> all_placeable_tiles;
  std::vector<TilePtr> other_player_winning_tiles;

  for(std::vector<TilePtr>::iterator it_edges = edges.begin();
      it_edges != edges.end(); ++it_edges)
  {
    std::vector<TilePtr> placeable_tiles;
    determinePlaceableTiles(*it_edges, placeable_tiles);

    std::pair<Color, TilePtr> winning_tile =
        determineWinningTile(placeable_tiles);

    if(winning_tile.first == player)
      return winning_tile.second;

    std::copy(placeable_tiles.begin(), placeable_tiles.end(),
              back_inserter(all_placeable_tiles));

    if(winning_tile.first != player && winning_tile.first != Color::NONE)
      other_player_winning_tiles.push_back(winning_tile.second);
  }

  if(all_placeable_tiles.empty())
  {
    TileTypeLib::TileType tile_type =
        TileTypeLib::TileType::getTileType(TileTypeLib::Shape::CROSS,
                                           Color::RED);
    return std::shared_ptr<Tile>(new Tile(tile_type, Position(0, 0)));
  }

  if(!other_player_winning_tiles.empty())
  {
    for(TilePtr tile : all_placeable_tiles)
    {
      bool prevents_other_players_winning = false;

      for(TilePtr other_player_winning_tile : other_player_winning_tiles)
      {
        if (tile->getPosition() == other_player_winning_tile->getPosition() &&
            tile->getShape() == other_player_winning_tile->getShape())
        {
          prevents_other_players_winning = false;
          break;
        }
        else if (tile->getPosition() == other_player_winning_tile->getPosition()
                 && tile->getShape() != other_player_winning_tile->getShape())
        {
          prevents_other_players_winning = true;
        }
      }

      if(prevents_other_players_winning)
        return tile;
    }

    //TODO if nothing can prevent - remove the other_player_winning_tiles
    //from all_placeable_tiles
  }

  std::random_device rn;
  std::mt19937 engine(rn());
  std::uniform_int_distribution<unsigned int> dice(
        0, all_placeable_tiles.size() - 1);
  unsigned int rand_index = dice(engine);

  return all_placeable_tiles.at(rand_index);
}

//------------------------------------------------------------------------------
std::pair<Color, TilePtr> GameBoard::ArtificialIntelligence::
determineWinningTile(const std::vector<TilePtr>& placeable_tiles)
{
  Color winner = Color::NONE;

  for(TilePtr tile : placeable_tiles)
  {
    game_board_.game_.addTile(tile);

    try
    {
      game_board_.doForcedPlay(tile);
      winner = game_board_.result_checker_.
               determineWinner(game_board_.game_);
    }
    catch(InvalidPositionException& e)
    {
      //Nothing to do
    }

    //Placed tiles must be removed otherwise the play would not be valid
    std::vector<TilePtr> tiles_to_remove =
        game_board_.game_.getLastPlacedTiles();

    for(TilePtr& tile_to_remove : tiles_to_remove)
    {
      game_board_.game_.removeTile(tile_to_remove);
    }

    if(winner != Color::NONE)
      return make_pair(winner, tile);
  }

  return make_pair(Color::NONE, TilePtr());
}

//------------------------------------------------------------------------------
void GameBoard::ArtificialIntelligence::determinePlaceableTiles(
    TilePtr edge, std::vector<TilePtr>& placeable_tiles) const
{
  determineAllTiles(edge, placeable_tiles);

  placeable_tiles.erase(
        std::remove_if(placeable_tiles.begin(), placeable_tiles.end(),
                       [this](TilePtr tile)
  {
    bool shouldRemove = true;

    try
    {
      //Check if tile can be placed
      std::map<TileTypeLib::Edge, TilePtr> touching_tiles =
      game_board_.game_.getTouchingTiles(tile->getPosition());
      game_board_.canTileBePlaced(touching_tiles, tile);
      //Checks if you go out of tiles by forced play
      game_board_.game_.addTile(tile);
      game_board_.doForcedPlay(tile);
      shouldRemove = false;
    }
    catch(InvalidPositionException e)
    {
      //Nothing to do
    }
    catch(ColorMismatchException e)
    {
      //Nothing to do
    }
    catch(NoTilesLeftException e)
    {
      //Nothing to do
    }

    //Placed tiles must be removed otherwise the play would not be valid
    std::vector<TilePtr> tiles_to_remove =
        game_board_.game_.getLastPlacedTiles();

    for(TilePtr& tile_to_remove : tiles_to_remove)
    {
      game_board_.game_.removeTile(tile_to_remove);
    }

    return shouldRemove; }), placeable_tiles.end());
}

//------------------------------------------------------------------------------
void GameBoard::ArtificialIntelligence::determineAllTiles(
    TilePtr edge, std::vector<TilePtr>& all_tiles) const
{
  const Position& position = edge->getPosition(); //TODO look if works

  const Position right_pos(position.getX() + 1, position.getY());
  const Position left_pos(position.getX() - 1, position.getY());
  const Position bottom_pos(position.getX(), position.getY() + 1);
  const Position top_pos(position.getX(), position.getY() - 1);

  determineAllTilesAtPosition(right_pos, all_tiles);
  determineAllTilesAtPosition(left_pos, all_tiles);
  determineAllTilesAtPosition(bottom_pos, all_tiles);
  determineAllTilesAtPosition(top_pos, all_tiles);
}

//------------------------------------------------------------------------------
void GameBoard::ArtificialIntelligence::determineAllTilesAtPosition(
    const Position& position, std::vector<TilePtr>& all_tiles) const
{
  const std::vector<TileTypeLib::TileType>& all_tile_types =
      TileTypeLib::TileType::getAllTileTypes();

  for(const TileTypeLib::TileType& tile_type : all_tile_types)
  {
    all_tiles.push_back(std::shared_ptr<Tile>(new Tile(tile_type, position)));
  }
}

//------------------------------------------------------------------------------
void GameBoard::play()
{
  try
  {
    TilePtr next_tile = ai.determineNextTile(game_.getActivePlayer().getColor());

    placeTile(next_tile);
    char shape;
    switch(next_tile->getShape())
    {
      case TileTypeLib::Shape::CROSS:
      {
        shape = '+';
        break;
      }
      case TileTypeLib::Shape::CURVE_TOP_LEFT_CORNER:
      {
        shape = '/';
        break;
      }
      case TileTypeLib::Shape::CURVE_TOP_RIGHT_CORNER:
      {
        shape = '\\';
        break;
      }
      default:
        throw(MessageException("No such Shape!"));
    }

    std::cout << next_tile->getPosition().toString() << " " <<
                 shape << std::endl;

  }
  catch (MessageException& e)
  {
    for(TilePtr tile : tried_insertions_)
    {
      game_.removeTile(tile);
    }
    tried_insertions_.clear();
    std::cout << e.what() << std::endl;
    game_.resetNumOfPlacedTilesInCurrentTurn();
  }

}
