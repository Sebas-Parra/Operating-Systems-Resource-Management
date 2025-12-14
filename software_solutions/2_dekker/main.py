import threading
import time
import random

flag = [False, False]
turn = 0

log_data = []
log_lock_for_print = threading.Lock()  # only to avoid mixed console prints

def write_log(pid: int, entries: int):
    global turn
    other = 1 - pid

    for k in range(entries):
        # Non-critical work
        time.sleep(random.uniform(0.1, 0.4))

        # Dekker's algorithm (2 processes)
        flag[pid] = True
        while flag[other]:
            if turn == other:
                flag[pid] = False
                while turn == other:
                    time.sleep(0)  # yield
                flag[pid] = True

        # Critical section: append to shared log
        msg = f"Process {pid} wrote entry {k}"
        log_data.append(msg)
        with log_lock_for_print:
            print(f"[P{pid}] LOG WRITE -> {msg}")

        # Exit protocol
        turn = other
        flag[pid] = False

if __name__ == "__main__":
    t0 = threading.Thread(target=write_log, args=(0, 6))
    t1 = threading.Thread(target=write_log, args=(1, 6))
    t0.start(); t1.start()
    t0.join(); t1.join()

    print("\nFinal log size:", len(log_data))
