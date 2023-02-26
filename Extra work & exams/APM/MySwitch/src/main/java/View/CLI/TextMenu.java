package View.CLI;

import java.util.HashMap;
import java.util.Scanner;

public class TextMenu {
    private HashMap<String, Command> commands;

    // CONSTRUCTOR
    public TextMenu() {
        this.commands = new HashMap<>();
    }

    // ADD A COMMAND
    public void addCommand(Command command) {
        this.commands.put(command.getKey(), command);
    }

    // PRINT THE MENU
    private void printMenu() {
        for (Command command: commands.values()) {
            String line = String.format("%4s: %s", command.getKey(), command.getDescription());
            System.out.println(line);
        }
    }

    // LET USER CHOOSE A COMMAND
    public void show() {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            printMenu();
            System.out.printf("Input the option: ");
            String key = scanner.nextLine();
            Command command = commands.get(key);
            if (command == null) {
                System.out.println("Invalid option!");
            }
            else {
                command.execute();
            }
        }
    }


}
