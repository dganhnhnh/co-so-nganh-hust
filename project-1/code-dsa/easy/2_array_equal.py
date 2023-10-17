'''
https://programming.daotao.ai/programming-contest/student-view-contest-problem-detail/GENERAL_CONTEST/ARRAY_EQUALITY
'''

def check_equal(arr1, arr2):
    if len(arr1) != len(arr2):
        return False
    for i in range(len(arr1)):
        if arr1[i] != arr2[i]:
            return False
    return True

def main():
    t = int(input())
    arr_res = []
    for _ in range(t):
        arr1    = []
        arr2    = []
        n, m    = map(int, input().split())
        line = input()
        arr1 = list(map(int, line.split()))
        arr1 = arr1[:n]
        # print("arr1: ", arr1)
        line = input()
        arr2 = list(map(int, line.split()))
        arr2 = arr2[:m]
        # print("arr2: ", arr2)
        if check_equal(arr1, arr2):
            arr_res.append(1)
        else:
            arr_res.append(0)
    for i in range(len(arr_res)):
        print(arr_res[i])
if __name__ == "__main__":
    main()