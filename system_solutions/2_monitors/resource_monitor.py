import threading

class ResourceMonitor:

    def __init__(self):
        self.lock = threading.Lock()
        self.resource_a_available = True
        self.resource_b_available = True
        self.condition = threading.Condition(self.lock)
    
    def acquire_both_resources(self, process_id):
        """Acquire both resources atomically to prevent deadlock"""
        with self.condition:
            # Wait until both resources are available
            while not (self.resource_a_available and self.resource_b_available):
                print(f"Process {process_id} waiting for resources...")
                self.condition.wait()
            
            # Acquire both resources atomically
            self.resource_a_available = False
            self.resource_b_available = False
            print(f"[+] Process {process_id} acquired both resources")
    
    def release_both_resources(self, process_id):
        # Release both resources and notify waiting processes
        with self.condition:
            self.resource_a_available = True
            self.resource_b_available = True
            print(f"[+] Process {process_id} released both resources")
            self.condition.notify_all()
