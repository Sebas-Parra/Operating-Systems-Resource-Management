import threading
import time
import random

N = 5
choosing = [False] * N
number = [0] * N

served_order = []
served_lock = threading.Lock()  # only for printing / list append clarity

def bakery_lock(pid: int):
    choosing[pid] = True
    number[pid] = 1 + max(number)
    choosing[pid] = False

    for j in range(N):
        while choosing[j]:
            time.sleep(0)
        while number[j] != 0 and (number[j], j) < (number[pid], pid):
            time.sleep(0)

def bakery_unlock(pid: int):
    number[pid] = 0

def customer(pid: int):
    # Non-critical work: arriving at different times
    time.sleep(random.uniform(0.1, 0.7))

    bakery_lock(pid)

    # Critical section: being served at a single counter
    with served_lock:
        served_order.append(pid)
        print(f"[Customer {pid}] SERVED (ticket={number[pid]})")
    time.sleep(0.2)

    bakery_unlock(pid)

if __name__ == "__main__":
    threads = [threading.Thread(target=customer, args=(i,)) for i in range(N)]
    for t in threads: t.start()
    for t in threads: t.join()

    print("\nService order:", served_order)
