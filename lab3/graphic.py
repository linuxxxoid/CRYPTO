import matplotlib.pyplot as plt

filename = "statistics"

rounds = []
bits = []

# Read data:
with open(filename, "r") as f:
    for line in f:
        nums = line.split()
        rounds.append(int(nums[0]))
        bits.append(int(nums[1]))

#plotting:

plt.plot(rounds, bits, color = "r")
plt.title("Зависимость среднего количества различных бит от количества раундов алгоритма ГОСТ Р 34.11-94")
plt.xlabel("Количество раундов")
plt.ylabel("Количество различных бит в хэшах")

plt.legend()
plt.show()