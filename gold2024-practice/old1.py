import heapq

# Input reading
N, K = map(int, input().split())
T = list(map(int, input().split()))

# Initialize heap and farmer availability tracking
times = [0] * K  # Stores the next available time for each farmer
heap = []  # Min-heap to simulate the process
for i in range(K):
    heapq.heappush(heap, (0, i))  # (available_time, farmer_id)

# Simulate the interview process
edges_into = {}  # Maps end times to potential start times (for BFS)

for t in T:
    start_time, farmer_id = heapq.heappop(heap)  # Get the next available farmer
    end_time = start_time + t  # Calculate the end time for this interview
    edges_into.setdefault(end_time, []).append(start_time)  # Track dependencies
    heapq.heappush(heap, (end_time, farmer_id))  # Update the farmer's next available time

# Find when Bessie's interview starts
bessie_start_time = heapq.heappop(heap)[0]  # The earliest available time after processing all cows

# Perform BFS to determine which farmers could interview Bessie
q = [bessie_start_time]
visited = set()
for x in q:
    if x in visited:
        continue
    visited.add(x)
    if x in edges_into:
        for prev_time in edges_into[x]:
            q.append(prev_time)

# Output results
print(bessie_start_time)  # The start time of Bessie's interview
print("".join(["1" if i in visited else "0" for i in range(K)]))  # Bit string for potential farmers
