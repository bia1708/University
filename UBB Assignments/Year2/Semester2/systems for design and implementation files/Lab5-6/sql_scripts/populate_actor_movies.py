import random
import sys
from faker import Faker


def populate_actors_movies():
    fake = Faker()
    step = 1_000_000
    header = "INSERT INTO ActorMovie(aid, mid, actor_salary, actor_awarded, code) VALUES "
    file_prefix = "actorsmovies4"
    file_suffix = ".sql"

    original_stdout = sys.stdout

    with open(f"{file_prefix}{file_suffix}", "w") as file:
        sys.stdout = file
        print(header)
        for j in range(step):
            if random.randint(0, 1) % 2 == 0:
                print(
                    f"({random.randint(1, 1000000)},{random.randint(1, 1000000)},{random.randint(0, 1000000)},False,{random.randint(1, 10000000)})",
                    end='')

            else:
                print(
                    f"({random.randint(1, 1000000)},{random.randint(1, 1000000)},{random.randint(0, 1000000)},True,{random.randint(1, 10000000)})",
                    end='')
            if j != step - 1:
                print(',')
    sys.stdout = original_stdout


if __name__ == '__main__':
    populate_actors_movies()
