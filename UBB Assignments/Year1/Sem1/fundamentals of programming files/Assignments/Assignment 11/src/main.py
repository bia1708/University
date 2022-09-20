from src.game_logistics.game_logistics import Game
from src.ui.ui import UI
from src.game_logistics.ai import Computer


game = Game(Computer("smart"))
ui = UI(game)

ui.startup()
