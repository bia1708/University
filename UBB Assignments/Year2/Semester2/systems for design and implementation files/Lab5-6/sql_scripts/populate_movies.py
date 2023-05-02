import random
import sys
from faker import Faker


def populate_movies():
    fake = Faker()
    step = 1_000_000
    header = "INSERT INTO Movies(movies_text, release_date, director_id, imdb_score, votes) VALUES "
    file_prefix = "movies"
    file_suffix = ".sql"

    original_stdout = sys.stdout

    with open(f"{file_prefix}{file_suffix}", "w") as file:
        sys.stdout = file
        print(header)
        for j in range(step):
            print(f"('{fake.catch_phrase()}',{random.randint(1950, 2023)},{random.randint(1,1000000)},{random.randint(0, 9)}.{random.randint(0, 9)},{random.randint(0, 1000)})", end='')
            if j != step - 1:
                print(',')
    sys.stdout = original_stdout


if __name__ == '__main__':
    populate_movies()
    # fake = Faker()

    # print(fake.__dir__())
    # print()
    # print(fake.catch_phrase())
    # print(fake.date_of_birth())
    # print(fake.email())
    # print(fake.name())
    # print(random.randint(1950, 2023))

