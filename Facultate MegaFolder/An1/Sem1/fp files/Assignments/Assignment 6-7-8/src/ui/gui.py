import PySimpleGUI as sg

from src.domain.validators import ClientValidator
from src.repository.repo import Repository
from src.services.services import ClientService
# from src.ui.gui_support import Services, ClientServicesUI

client_validator = ClientValidator()
client_repo = Repository(client_validator)
client_service = ClientService(client_repo)



sg.theme("Dark Purple 4")
services = ["CLIENT SERVICES", "MOVIE SERVICES", "RENTAL SERVICES", "STATISTICS"]
client_services = ["List all clients", "Add new client", "Remove a client", "Update client", "Find client"]

# Define the window's contents
home_screen_layout = [[sg.Text("Welcome to our Movie Rental Service! What would you like to do today?", font="TimesNewRoman 12")],
                      [sg.Combo(services, size=(20, 4), enable_events=True, key='choice')],
                      [sg.Text(size=(40,1), key='-OUTPUT-')]]
          #[sg.Button('Ok'), sg.Button('Quit')]]

layout1 = [
    [sg.Text("Please select an option:")],
    [sg.Combo(client_services, size=(40, 12), enable_events=True, key='client_choice')]
]

layout1_list_clients = [
    [sg.Text("Clients:")],
    #[sg.Print(ClientServicesUI(client_service).ui_list_clients())]
]

layout2 = [
    [sg.Text('Please enter your Name, Address, Phone')],
    [sg.Text('Name', size=(15, 1)), sg.InputText()],
    [sg.Text('Address', size=(15, 1)), sg.InputText()],
    [sg.Text('Phone', size=(15, 1)), sg.InputText()],
    [sg.Submit(), sg.Cancel()]
]

main_layout = [[sg.Column(home_screen_layout, key='home'),
                sg.Column(layout1, visible=False, key='client_service'),
                sg.Column(layout1_list_clients, visible=False, key='list_clients'),
                sg.Column(layout2, visible=False, key='-COL2-')]
               ]
# window = sg.Window('Simple data entry window', layout)
# event, values = window.read()
# window.close()
# print(event, values[0], values[1], values[2])

# Create the window
window = sg.Window('Movie Rental', main_layout)

# Display and interact with the Window using an Event Loop
while True:
    event, values = window.read()
    # See if user wants to quit or window was closed
    if event == sg.WINDOW_CLOSED:
        break
    else:
        # window = sg.Window('Simple data entry window', layout2)
        # window['-OUTPUT-'].update('Hello ' + values['choice'] + "! Thanks for trying PySimpleGUI")
        if event == 'choice':

            if values['choice'] == services[0]:
                # I change the window to the Client service menu layout
                window['home'].update(visible=False)
                window['client_service'].update(visible=True)

                while True:
                    event, values = window.read()
                    if event == sg.WINDOW_CLOSED:
                        break
                    elif event == 'client_choice':
                        if values['client_choice'] == client_services[0]:
                            print("Sdc")
                            window['client_service'].update(visible=False)
                            window['list_clients'].update(visible=True)
            elif values['choice'] == services[1]:
                pass

    # Output a message to the window

# Finish up by removing from the screen
window.close()








"""
import tkinter as tk


class GUI:
    def __init__(self, movie_service=None, client_service=None, rental_service=None):
        self.__movie_service = movie_service
        self.__client_service = client_service
        self.__rental_service = rental_service

    def startup(self):
        window = tk.Tk()
        window.title("Movie Rental Service")

        frame1 = tk.Frame(master=window, height=100)
        greeting = tk.Label(master=frame1, text="Welcome to the Movie Rental Service App!")
        greeting.pack()
        frame1.pack(fill=tk.X, expand=True)

        frame2 = tk.Frame(master=window)
        frame2.pack()
        btn1 = tk.Button(master=frame2, text="Admin", width=15)
        # btn1.bind("<Button-1>", self.admin_window())
        btn1.pack(side='left')
        btn2 = tk.Button(master=frame2, text="User", width=15)
        btn2.pack(side='right')
        window.mainloop()

    def admin_window(self):
        window = tk.Tk()
        frame1 = tk.Frame(master=window, height=100)
        greeting = tk.Label(master=frame1, text="Hello, Admin!")
        greeting.pack()
        frame1.pack(fill=tk.X, expand=True)
        window.mainloop()


if __name__ == '__main__':
    gui = GUI()
    gui.startup()
"""