import threading
import time
import queue

my_queue = queue.Queue()

def sender():
    for i in range(10):
        print(f"Sender: Sending message {i}")
        my_queue.put(f"Message {i}")
        time.sleep(0.5)

def receiver():
    for _ in range(10):
        print(f"Receiver: Received {my_queue.get()}")
        my_queue.task_done()

thead1 = threading.Thread(target=sender)
thread2 = threading.Thread(target=receiver)

thead1.start()
thread2.start()

thead1.join()
thread2.join()