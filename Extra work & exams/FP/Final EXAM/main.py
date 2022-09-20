from src.domaim.domain import Flight
from src.domaim.validators import FlightValidator
from src.repository.repo import TextFileRepository, Repository
from src.services.services import FlightServices, AirportService
from src.ui.ui import Console

validator = FlightValidator()
flight_repository = TextFileRepository("input.txt", Flight.line_to_flight, Flight.flight_to_line)
airport_repository = Repository()
flight_services = FlightServices(flight_repository, validator)
airport_services = AirportService(airport_repository, flight_repository)
console = Console(flight_services, airport_services)

console.run()