def max_unrelated_people(data):
    # Create a dictionary to store parent-child relationships
    parent_child_dict = {}
    for line in data:
        code, _, father_code, mother_code, _, _ = line.split()
        if father_code != '0000000':
            parent_child_dict[father_code] = parent_child_dict.get(father_code, []) + [code]
        if mother_code != '0000000':
            parent_child_dict[mother_code] = parent_child_dict.get(mother_code, []) + [code]

    # Initialize a set to store unrelated people
    unrelated_set = set()

    # Iterate through the data to find unrelated people
    for line in data:
        code, _, _, _, _, _ = line.split()
        if code not in parent_child_dict:
            unrelated_set.add(code)

    # Find the largest subset of unrelated people
    max_unrelated_size = 0
    current_subset = set()

    for code in unrelated_set:
        if code not in current_subset:
            current_subset.add(code)
            current_size = 1
            stack = [code]

            while stack:
                current_person = stack.pop()
                children = parent_child_dict.get(current_person, [])
                current_subset.update(children)
                stack.extend(children)
                current_size += len(children)

            max_unrelated_size = max(max_unrelated_size, current_size)

    return max_unrelated_size

# Read input
data = []
while True:
    line = input().strip()
    if line == '*':
        break
    data.append(line)

queries = []
while True:
    line = input().strip()
    if line == '***':
        break
    queries.append(line)


print(data)
print(queries)

# Execute queries
for query in queries:
    if query == 'MAX_UNRELATED_PEOPLE':
        result = max_unrelated_people(data)
        print(result)
