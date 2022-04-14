from datetime import datetime

now = datetime.now()

current_time = now.strftime("%H:%M:%S:%s")

print(current_time)
