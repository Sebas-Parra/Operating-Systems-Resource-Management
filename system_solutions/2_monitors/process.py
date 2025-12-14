import time

def process(monitor, process_id):
    """Simulates a process that needs two resources"""
    print(f"Process {process_id} started")
    
    # Acquire both resources atomically (prevents deadlock)
    monitor.acquire_both_resources(process_id)
    
    
    print(f"Process {process_id} working...")
    time.sleep(1)
    
    # Release both resources
    monitor.release_both_resources(process_id)
    print(f"Process {process_id} finished")
