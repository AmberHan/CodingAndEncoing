import math
import random
# 递归做法
# def sort_tree(foot, value, code_dict):
#     if code_dict[foot][0] > value:
#         code_dict[foot][-1] += 1
#         if code_dict[foot][1] == -1:
#             code_dict[foot][1] = value
#             return
#         else:
#             sort_tree(code_dict[foot][1], value, code_dict)
#     if code_dict[foot][0] < value:
#         code_dict[value][-1] = code_dict[foot][-1] + 1
#         if code_dict[foot][2] == -1:
#             code_dict[foot][2] = value
#             return
#         else:
#             sort_tree(code_dict[foot][2], value, code_dict)

# code_dict1 = {}
code_dict = []
code_left_child = []
mul_list1 = [1]


def multi1_save(num):
    n, result = 1, 1
    while n <= num:
        result, n = result * n, n+1
        mul_list1.append(result)


def sort_tree(code_list):
    code_dict1 = {j: [j, -1, -1, 0] for j in code_list}
    last_one = code_list[-1]
    code_dict1[last_one][-1] = 1
    sum_list = [0]
    for i in range(len(code_list) - 2, -1, -1):
        sum1 = 0
        foot = last_one
        value = code_list[i]
        while 1:
            if code_dict1[foot][0] > value:
                code_dict1[foot][-1] += 1
                if code_dict1[foot][1] == -1:
                    code_dict1[foot][1] = value
                    code_dict1[value][-1] = 1
                    sum_list.append(sum1)
                    break
                else:
                    foot = code_dict1[foot][1]
            elif code_dict1[foot][0] < value:
                sum1 += code_dict1[foot][-1]
                if code_dict1[foot][2] == -1:
                    code_dict1[foot][2] = value
                    code_dict1[value][-1] = 1
                    sum_list.append(sum1)
                    break
                else:
                    foot = code_dict1[foot][2]
    # print(sum_list)
    return sum_list


def rank_list(list_1, mid):
    code_len = len(list_1)
    code_dict_copy = [0] * code_len
    sum_list = []
    for i in range(code_len - 1, -1, -1):
        list_num = list_1[i]
        foot = mid
        sum1 = 0
        while 1:
            if foot == -1:
                break
            if list_num == foot:
                sum1 += code_dict_copy[foot]
                code_dict_copy[foot] += 1
                if i == 0:
                    global code_left_child
                    code_left_child = code_dict_copy[:]
                    # print(code_left_child)
                sum_list.append(sum1)
                break
            if list_num > foot:
                sum1 += code_dict_copy[foot]
                foot = code_dict[foot][1]
            else:
                code_dict_copy[foot] += 1
                foot = code_dict[foot][0]
    # print(sum_list)
    return sum_list

# def multi_reverse(num):
#     time = num
#     while num > 0:
#         n, result = 1, 1
#         while n <= time - num:
#             result, n = result*n, n+1
#         # print(result)
#         yield result
#         num -= 1
#
#
# def multi(num):
#     while num > 0:
#         n, result = num, 1
#         while n > 0:
#             result, n = result*n, n-1
#         yield result
#         num -= 1


def div_num(rem, bit, multi_list):
    # multi_list = multi_list[-2:0:-1]
    list_mul = []
    bit -= 1
    for mul_i in multi_list[-2:0:-1]:
        rem, quo = rem % mul_i, rem // mul_i
        list_mul.append(quo)
    list_mul.append(0)
    return list_mul


def sort_tree1(mid, left, right):
    left1 = math.ceil((mid + left)/2)
    right1 = math.ceil((mid + right)/2)
    if left1 == mid:
        left1 = -1
    if right1 == right:
        right1 = -1
    if mid == 1:
        left1 = 0
    code_dict[mid] = [left1, right1]
    if left1 == -1 or right1 == -1:
        return
    sort_tree1(left1, left, mid)
    sort_tree1(right1, mid, right)


def function_code1(code_list, mul_list):
    code_result = 0
    for (i, j) in zip(sort_tree(code_list), mul_list):
        code_result += i * j
        # print('{},{}'.format(i, j))
    print('法一生成的数值值：{}'.format(code_result))
    return code_result


def function_code2_init(total_num):
    # left = 0
    right = total_num
    mid = total_num // 2
    global code_dict
    code_dict = [[-1, -1]] * right
    sort_tree1(mid, 0, right)


def function_code2(list_1, mul_list):
    code_result = 0
    mid = len(list_1) // 2
    for (i, j) in zip(rank_list(list_1, mid), mul_list):
        code_result += i * j
    print('法二生成的数值值：{}'.format(code_result))
    return code_result


def code_to_list1(res_num, n, multi_list):
    list_code = div_num(res_num, 2 ** n, multi_list)
    print('解码的商：{}'.format(list_code))
    list_1 = [i for i in range(len(list_code) + 1)]
    list_res = []
    for list_code_i in list_code:
        list_res.append(list_1.pop(list_code_i))
    print('法一解码得到列表：{}'.format(list_res))


def code_to_list2(res_num, n, multi_list):
    list_code = div_num(res_num, 2 ** n, multi_list)
    list_len = len(code_left_child)
    code_left = code_left_child[:]
    is_exist = [1] * list_len
    return_list = []
    for list_i in list_code:
        list_i += 1
        foot = list_len // 2
        sum_left = code_left[foot]
        while 1:
            if list_i > sum_left:
                foot = code_dict[foot][1]
                sum_left += code_left[foot]
            elif list_i < sum_left or (list_i == sum_left and is_exist[foot] == 0):
                sum_left -= code_left[foot]
                code_left[foot] -= 1
                foot = code_dict[foot][0]
                sum_left += code_left[foot]
            else:
                return_list.append(foot)
                is_exist[foot] = 0
                code_left[foot] -= 1
                break
    print('法二解码得到列表：{}'.format(return_list))
    return return_list


def main():
    n = input('输入比特数：')
    n = int(n)
    total_num = 2 ** n
    multi1_save(total_num)
    list_1 = [i for i in range(total_num)]
    random.shuffle(list_1)
    list_1 = [13, 7, 3, 2, 4, 14, 10, 9, 12, 6, 0, 11, 1, 15, 8, 5]
    print('生成的编码：{}'.format(list_1))
    print('*' * 100)
    function_code2_init(total_num)
    # 法一：
    res_num1 = function_code1(list_1, mul_list1)
    print('*' * 100)
    # 法二：
    res_num2 = function_code2(list_1, mul_list1)
    print('*' * 100)
    # 解码法一：
    code_to_list1(res_num1, n, mul_list1)
    code_to_list1(res_num2, n, mul_list1)
    print('*' * 100)
    # 解码法二：
    code_to_list2(res_num1, n, mul_list1)
    code_to_list2(res_num2, n, mul_list1)


if __name__ == '__main__':
    main()
