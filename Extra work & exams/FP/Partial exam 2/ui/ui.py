

class Console:
    def __init__(self, taxi_service, ride_service):
        self.__ride_service = ride_service
        self.__taxi_service = taxi_service

    def display_taxis(self):
        for taxi in self.__taxi_service.get_all_taxis():
            print(taxi)

    @staticmethod
    def print_menu():
        print("Menu:\n"
              "1. Add a ride\n"
              "2. Simulate rides")

    def ui_add_ride(self):
        x1 = int(input("Start point x: "))
        y1 = int(input("Start point y: "))
        x2 = int(input("End point x: "))
        y2 = int(input("End point y: "))

        self.__ride_service.add_ride([x1, y1], [x2, y2])

    def startup(self):
        print("Welcome!")

        try:
            number_of_taxis = int(input("How many taxis?\n"))
            self.__taxi_service.add_taxis(number_of_taxis)
        except ValueError:
            print("Please enter a number between 1 and 10")

        self.display_taxis()

        commands = {
            "1" : self.ui_add_ride
        }

        while True:
            Console.print_menu()
            cmd = input("Option: ")
            if cmd == "x":
                break
            else:
                try:
                    commands[cmd]()
                    self.display_taxis()
                except KeyError as ke:
                    print(str(ke) + "is not a valid command! Please try again!")
