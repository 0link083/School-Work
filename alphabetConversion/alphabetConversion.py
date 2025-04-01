k = 0
N = 0


def setN(n):
    global N
    N = n


def setk(K):
    global k
    k = K


def encrypt(m):
    c = (m + k) % N
    return c


def decrypt(c):
    m = (c - k) % N
    return m


def main():
    alphabet = {
        "a": "01",
        "b": "02",
        "c": "03",
        "d": "04",
        "e": "05",
        "f": "06",
        "g": "07",
        "h": "08",
        "i": "09",
        "j": "10",
        "k": "11",
        "l": "12",
        "m": "13",
        "n": "14",
        "o": "15",
        "p": "16",
        "q": "17",
        "r": "18",
        "s": "19",
        "t": "20",
        "u": "21",
        "v": "22",
        "w": "23",
        "x": "24",
        "y": "25",
        "z": "26",

        "01": "a",
        "02": "b",
        "03": "c",
        "04": "d",
        "05": "e",
        "06": "f",
        "07": "g",
        "08": "h",
        "09": "i",
        "10": "j",
        "11": "k",
        "12": "l",
        "13": "m",
        "14": "n",
        "15": "o",
        "16": "p",
        "17": "q",
        "18": "r",
        "19": "s",
        "20": "t",
        "21": "u",
        "22": "v",
        "23": "w",
        "24": "x",
        "25": "y",
        "26": "z",
    }
    string_name = "video"
    for i in string_name:
        print(alphabet[i])
    string_name = "14 15 20 05 19"
    hlp = string_name.split()
    for i in hlp:
        print(alphabet[i])
    setN(95)
    setk(6)
    print((decrypt(5)))


if __name__ == main():
    main()
