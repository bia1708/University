from src.repository.repository import Repository
from src.services.services import TaxiService, RideService
from src.ui.ui import Console

taxi_repo = Repository()
ride_repo = Repository()
ride_service = RideService(ride_repo, taxi_repo)
taxi_service = TaxiService(taxi_repo)
console = Console(taxi_service, ride_service)

console.startup()