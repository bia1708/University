from src.controller.controller import GameLogistics, Computer
from src.domain.domain import Board
from src.domain.validator import Validator
from src.ui.ui import Console

board = Board()
validator = Validator()
ai = Computer(board)
game_logs = GameLogistics(board, validator, ai)
console = Console(game_logs)

console.run_game()