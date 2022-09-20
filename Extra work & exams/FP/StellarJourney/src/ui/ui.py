from src.controller.game_logistics import GameException, EndingException


class Console:
    def __init__(self, controller):
        self.__controller = controller

    @staticmethod
    def print_menu():
        print("Welcome to STELLAR JOURNEY!")

    def warp_player(self, position):
        x, y = position[0], int(position[1]) - 1
        x = ord(x) - 65
        self.__controller.move_player(x, y)

    def fire_player(self, position):
        x, y = position[0], int(position[1]) - 1
        x = ord(x) - 65
        self.__controller.fire_player(x, y)

    def run_game(self):
        self.print_menu()
        self.__controller.place_stars()
        self.__controller.place_player_ship()
        self.__controller.place_enemy_ships(3)
        self.__controller.update_player_board()
        game_round = 1
        game_status = "ongoing"

        while game_status != "over":
            print(f"Round {game_round}!\n")
            game_round += 1
            print(self.__controller.get_player_board())
            print("\n")

            commands = {
                "warp": self.warp_player,
                "fire": self.fire_player,
            }
            move = True
            while move is True:
                cmd = input("Your command: ")
                if cmd == "cheat":
                    print(self.__controller.get_game_board())
                else:
                    cmd = cmd.split()
                    try:
                        commands[cmd[0]](cmd[1])
                        self.__controller.update_player_board()
                        move = False
                    except KeyError:
                        print("Please enter a valid command!")
                    except GameException as ge:
                        print(ge)
                    except EndingException as ee:
                        print(ee)
                        game_status = "over"
                        break
                    except ValueError:
                        print("Please enter a correct position!")
            if self.__controller.game_status() == 1:
                print("YOU WON")
                game_status = "over"
