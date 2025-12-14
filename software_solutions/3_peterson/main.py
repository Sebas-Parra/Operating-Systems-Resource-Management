import threading
import time
import random

flag = [False, False]
turn = 0

balance = 1000

def deposit(pid: int, amount: int, times: int):
    global turn, balance
    other = 1 - pid

    for _ in range(times):
        # Non-critical work
        time.sleep(random.uniform(0.05, 0.2))

        # Peterson's algorithm (2 processes)
        flag[pid] = True
        turn = other
        while flag[other] and turn == other:
            time.sleep(0)  # yield

        # Critical section: update shared balance
        old = balance
        balance = old + amount
        print(f"[P{pid}] deposit {amount} -> {old} -> {balance}")

        flag[pid] = False

if __name__ == "__main__":
    t0 = threading.Thread(target=deposit, args=(0, 50, 10))
    t1 = threading.Thread(target=deposit, args=(1, 30, 10))
    t0.start(); t1.start()
    t0.join(); t1.join()

    print("\nFinal balance:", balance)
