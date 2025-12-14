import time
import threading

my_semaphore = threading.Semaphore(2)

def work(name):
    print(f"{name} is trying to acquire the semaphore.")
    my_semaphore.acquire()
    print(f"{name} has acquired the semaphore.")
    time.sleep(4)
    print(f"{name} is releasing the semaphore.")
    my_semaphore.release()


if __name__ == "__main__":
    my_threades = []

    for i in range(4):
        thread = threading.Thread(target=work, args=(f"Thread-{i+1}",))
        my_threades.append(thread)
        thread.start()

    for thread in my_threades:
        thread.join()