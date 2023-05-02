import random
import sys
from faker import Faker


def populate_directors():
    fake = Faker()
    step = 1_000_000
    header = "INSERT INTO Directors(director_name, birth_date, star_sign, contact, votes) VALUES "
    file_prefix = "directors"
    file_suffix = ".sql"

    stars = ['taurus', 'pisces', 'leo', 'gemini', 'aquarius', 'libra', 'scorpio', 'sagittarius', 'aries', 'cancer', 'capricorn', 'virgo']

    original_stdout = sys.stdout

    with open(f"{file_prefix}{file_suffix}", "w") as file:
        sys.stdout = file
        print(header)
        for j in range(step):
            print(f"('{fake.name()}','{fake.date_of_birth()}','{random.choice(stars)}','{fake.email()}',{random.randint(0, 1000)})", end='')
            if j != step - 1:
                print(',')
    sys.stdout = original_stdout


if __name__ == '__main__':
    populate_directors()
