import random

def partition(nums, left, right):
    fill = left
    pi = random.randint(left, right)
    pivot = nums[pi]
    # swap to the right to avoid complication:
    nums[pi], nums[right] = nums[right], nums[pi]
    for i in range(left, right):
        if nums[i] <= pivot:# pay attention must be <= otherwise take example 256444-> 246445 wrong
            nums[fill], nums[i] = nums[i], nums[fill]
            fill += 1
    nums[fill], nums[right] = nums[right], nums[fill]
    return fill


def quickSort(nums, left, right):
    if left >= right: return
    pi = partition(nums, left, right)
    quickSort(nums, left, pi - 1)
    quickSort(nums, pi + 1, right)

    
nums = [3,2,3,1,2,4,5,5,6]
quickSort(nums, 0, len(nums) - 1)
print(nums)

