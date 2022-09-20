from src.services.book_service import BookService, Validator
from src.ui.console import Console

validator = Validator()
book_service = BookService(validator)
console = Console(book_service)
console.run_console()