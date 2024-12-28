from collections import defaultdict, deque

def solve():
    import sys
    input = sys.stdin.read
    data = input().splitlines()

    # Read N (cows) and P (posts)
    N, P = map(int, data[0].split())
    
    # Read fence posts
    posts = []
    for i in range(1, P + 1):
        x, y = map(int, data[i].split())
        posts.append((x, y))

    # Read cow walks
    cows = []
    for i in range(P + 1, P + N + 1):
        x1, y1, x2, y2 = map(int, data[i].split())
        cows.append(((x1, y1), (x2, y2)))

    # Sort posts in clockwise order to form the polygon
    # Use the bottom-left point as the reference for sorting
    min_point = min(posts)
    posts.sort(key=lambda point: (point[0] - min_point[0], point[1] - min_point[1]))

    # Create a mapping from post coordinates to their indices
    post_index = {posts[i]: i for i in range(P)}

    # Array to store touch counts
    touches = [0] * P

    # Process each cow
    for start, end in cows:
        if start == end:
            # Cow starts and ends at the same point, no movement
            continue

        # Find indices of start and end points
        start_idx = post_index[start]
        end_idx = post_index[end]

        # Calculate the clockwise and counterclockwise distances
        if start_idx <= end_idx:
            clockwise_dist = end_idx - start_idx
            counterclockwise_dist = P - clockwise_dist
        else:
            counterclockwise_dist = start_idx - end_idx
            clockwise_dist = P - counterclockwise_dist

        # Determine the shorter path
        if clockwise_dist < counterclockwise_dist:
            # Walk clockwise
            idx = start_idx
            while idx != end_idx:
                touches[idx] += 1
                idx = (idx + 1) % P
            touches[idx] += 1  # End point
        else:
            # Walk counterclockwise
            idx = start_idx
            while idx != end_idx:
                touches[idx] += 1
                idx = (idx - 1 + P) % P
            touches[idx] += 1  # End point

    # Output the results
    print("\n".join(map(str, touches)))
