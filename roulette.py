import os
from random import randint


def roulette(chambers: int) -> int:
    return randint(1, chambers)


def shutdown():
    if os.name == 'nt':
        os.system('shutdown /s /t 0')
    elif os.name == 'posix':
        os.system('sudo shutdown -h now')
    else:
        print('You\'re running this on an alien device')


def validator(input_value, upper_bound) -> bool:
    if not isinstance(input_value, int):
        print('Please enter a numeric value.')
        return False
    if input_value > upper_bound:
        print('Input must be less than or equal to the upper bound.')
        return False
    if input_value <= 0:
        print('Input must be at least 1.')
        return False
    return True


modes = {
    "classic": 6,
    "roulette": 38,
    "one-percenter": 100,
    "coin": 2
}


def game_mode(chambers):
    result = roulette(chambers)
    while True:
        guess = input(f"Take a guess between 1 and {chambers}: ")
        if not guess.isdigit():
            print("Please enter a numeric value.")
            continue
        guess = int(guess)
        if guess == result:
            print("BANG! You're dead.")
            shutdown()
        else:
            print("Nothing happens. This time. Try again.")
            choice = input("Enter 'r' to redo this mode or 'm' to return to the main menu: ").lower()
            if choice == 'r':
                result = roulette(chambers)
            elif choice == 'm':
                return
            else:
                print("Invalid choice! Returning to the main menu.")
                return


def main():
    while True:
        print("\nWelcome to roulette!")
        print("The rules are simple: pick a number in the given range. If nothing happens, you get to try again.")
        print("Trust me, you'll know when you lose.\n")
        print("Choose a mode:")
        print("a) Russian roulette (6 slots | 16.67% chance of death)")
        print("b) Casino roulette (38 slots | 2.63% chance of death)")
        print("c) Percenter (100 slots | 1% chance of death)")
        print("d) Coin (2 slots | 50% chance of death)")
        print("e) Custom\n")
        print("q) Quit")

        mode = input("Enter your choice: ").lower()
        if mode not in ["a", "b", "c", "d", "e", "q"]:
            print("That's not a valid choice!")
            continue

        if mode == "q":
            print("You'll be back. I know it.")
            break

        if mode == "e":
            chambers = int(input("Enter number of chambers: "))
            if validator(chambers, float('inf')):
                game_mode(chambers)
            else:
                print("That's not a valid choice!")
        else:
            chamber_count = {"a": modes["classic"], "b": modes["roulette"], "c": modes["one-percenter"],
                             "d": modes["coin"]}
            game_mode(chamber_count[mode])


if __name__ == '__main__':
    main()
