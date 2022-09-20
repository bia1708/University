import datetime


class FlightException(Exception):
    pass


class FlightValidator:
    @staticmethod
    def validate(flight):
        flight_time = flight.arrival_time - flight.departure_time
        if flight_time < datetime.timedelta(minutes=15) or flight_time > datetime.timedelta(minutes=90):
            raise FlightException("Invalid flight times!")
