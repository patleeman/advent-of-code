

def part1(data):
    """
    A = X = Rock (1pt)
    B = Y = Paper (2pt)
    C = Z = Scissors (3pt)
    
    You win when: CX, AY, BZ

    """
    you_win = ['C X', 'A Y', 'B Z']
    draw = ['A X', 'B Y', 'C Z']
    games = data.split("\n")
    score = 0
    for game in games:
        round_score = 0
        if not game:
            continue

        if game in draw:
            round_score += 3
        
        if game in you_win: 
            round_score += 6

        if game[2] == "X":
            round_score += 1
        elif game[2] == "Y":
            round_score += 2
        elif game[2] == "Z":
            round_score += 3

        score += round_score

    return score
    
def part2(data):
    """
    Part 2:
    X = Lose
    Y = Draw
    Z = Win
    """    
    
    score_lookup = {
        "A": 1,
        "B": 2,
        "C": 3,
    }


    games = data.split("\n")
    score = 0
    for game in games:
        if not game:
            continue
        
        round_score = 0
        strategy = game[2]
        oppo = game[0]
        if strategy == "Y":
            round_score += 3 + score_lookup[oppo]
        elif strategy == "Z":
            round_score += 6
            if oppo == "A":
                round_score += 2
            elif oppo == "B":
                round_score += 3
            else:
                round_score += 1
        else:
            if oppo == "A":
                round_score += 3
            elif oppo == "B":
                round_score += 1
            else:
                round_score += 2
        print(game, round_score)
        score += round_score
    return score  



if __name__ == "__main__":
    with open('data.txt', 'r') as f:
        data = f.read()

    result = part2(data)
    print(result)
