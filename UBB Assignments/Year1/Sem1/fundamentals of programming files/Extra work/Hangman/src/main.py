from src.controller.controller import Controller
from src.domain.validator import SentenceValidator
from src.repository.repo import TextFileRepository
from src.ui.UI import Console

validator = SentenceValidator()
repository = TextFileRepository(r"files/sentences.txt")
controller = Controller(repository, validator)
console = Console(controller)

console.run_game()