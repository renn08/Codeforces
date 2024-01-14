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

def partition_laoshi(nums, left, right):
    fill = left
    pivot = nums[right]
    for i in range(left, right):
        if nums[i] <= pivot:# pay attention must be <= otherwise take example 256444-> 246445 wrong
            nums[fill], nums[i] = nums[i], nums[fill]
            fill += 1
    nums[fill], nums[right] = nums[right], nums[fill]
    return fill

def partition_more_efficient(nums, left, right):
    fill = left
    pi = random.randint(left, right)
    pivot = nums[pi]
    for i in range(left, right + 1):
        if nums[i] <= pivot:
            if nums[i] == pivot: pi = fill # just add we should change pi since pi might be swapped to another position for example 131 and pi = 2
            nums[fill], nums[i] = nums[i], nums[fill]
            fill += 1
    fill -= 1
    nums[fill], nums[pi] = nums[pi], nums[fill]
    return fill



def quickSort(nums, left, right):
    if left >= right: return
    pi = partition_more_efficient(nums, left, right)
    quickSort(nums, left, pi - 1)
    quickSort(nums, pi + 1, right)

    
nums = [3,2,3,1,2,4,5,5,6]
nums = [3,2,3,1,3]
quickSort(nums, 0, len(nums) - 1)
print(nums)

