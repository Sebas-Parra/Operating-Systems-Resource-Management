import threading
import time
from resource_monitor import ResourceMonitor
from process import process

if __name__ == "__main__":
    monitor = ResourceMonitor()
    
    threads = []
    for i in range(5):
        t = threading.Thread(target=process, args=(monitor, i))
        threads.append(t)
        t.start()
        time.sleep(0.1)  
    

    for t in threads:
        t.join()
    
    print("\n [+] All processes have completed successfully.")
