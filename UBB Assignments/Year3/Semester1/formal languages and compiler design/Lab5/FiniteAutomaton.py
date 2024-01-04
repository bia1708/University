class FiniteAutomaton:
    def __init__(self):
        self.states = set()
        self.alphabet = set()
        self.transitions = {}
        self.initial_state = None
        self.final_states = set()

    def read_from_file(self, filename):
        with open(filename, 'r') as file:
            for line in file:
                line = line.strip().split()
                if line[0] == 'states':
                    self.states = set(line[1:])
                elif line[0] == 'alphabet':
                    # Split alphabet by spaces, accounting for string constants -- not used for now
                    self.alphabet = set("".join(line[1:]).split(','))
                elif line[0] == 'transitions':
                    for transition in line[1:]:
                        parts = transition.split(',')
                        start, symbol, end = parts[0], ",".join(parts[1:-1]), parts[-1]
                        self.transitions[(start, symbol)] = end
                elif line[0] == 'initial':
                    self.initial_state = line[1]
                elif line[0] == 'final':
                    self.final_states = set(line[1:])

    def is_accepted_sequence(self, sequence):
        # FIXME: constants_fa.in and this function do not allow for the constant 0 to exist, both should be changed
        # FIXME: as a workaround to this, i added the transition p,0,q to constants_fa.in, ik it is wrong,
        #  but we will fix it later
        current_state = self.initial_state

        for symbol in sequence:
            if (current_state, symbol) in self.transitions:
                current_state = self.transitions[(current_state, symbol)]
            else:
                return False

        return current_state in self.final_states

    def display_elements(self):
        print("Set of States:", self.states)
        print("Alphabet:", self.alphabet)
        print("Transitions:")
        for transition, end_state in self.transitions.items():
            print(f"  {transition[0]} --({transition[1]})--> {end_state}")
        print("Initial State:", self.initial_state)
        print("Set of Final States:", self.final_states)
