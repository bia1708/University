from src.controller.game_logistics import GameLogistics
from src.domain.domain import Board
from src.ui.ui import Console

game_board = Board()
player_board = Board()
game_logs = GameLogistics(game_board, player_board)
console = Console(game_logs)

console.run_game()