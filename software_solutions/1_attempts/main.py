import threading
import time
import random

want = [False, False]

def print_job(pid: int, pages: int):
    other = 1 - pid

    # Non-critical work (CPU / preparation)
    time.sleep(random.uniform(0.3, 0.8))

    # Attempts algorithm (software mutual exclusion, 2 processes)
    want[pid] = True
    while want[other]:
        want[pid] = False
        time.sleep(0)  # yield
        want[pid] = True

    # Critical section: printer access
    print(f"[P{pid}] Printer START -> printing {pages} pages")
    time.sleep(0.2 * pages)
    print(f"[P{pid}] Printer END")

    want[pid] = False

if __name__ == "__main__":
    t0 = threading.Thread(target=print_job, args=(0, 6))
    t1 = threading.Thread(target=print_job, args=(1, 4))
    t0.start(); t1.start()
    t0.join(); t1.join()
